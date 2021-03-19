/* python/phik/simulation/simulation.hpp wrapper and bindings for
 * Michael Patefield,
 * Algorithm AS 159: An Efficient Method of Generating RXC Tables with Given Row and Column Totals,
 * Applied Statistics,
 * Volume 30, Number 1, 1981, pages 91-97.
 *
 * https://people.sc.fsu.edu/~jburkardt/cpp_src/asa159/asa159.html
 */

#ifndef PYTHON_PHIK_SIMCORE_SIMULATION_HPP_
#define PYTHON_PHIK_SIMCORE_SIMULATION_HPP_
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <random>
#include "asa159.hpp"

namespace py = pybind11;

struct simulation_error: std::exception {
    const char* p_message;
    explicit simulation_error(const char* message) : p_message(message) {}
    const char* what() const throw() { return p_message; }
};

void _sim_2d_data_patefield(
    int nrow,
    int ncol,
    const py::array_t<int>& nrowt,
    const py::array_t<int>& ncolt,
    int seed,
    py::array_t<int>& result
) {
    bool key = false;
    int ierror = 0;
    int* nrowt_ptr = reinterpret_cast<int*>(nrowt.request().ptr);
    int* ncolt_ptr = reinterpret_cast<int*>(ncolt.request().ptr);
    int* result_ptr = reinterpret_cast<int*>(result.request().ptr);

    // constructs a random two-way contingency table with given sums,
    // the underlying memory of result is directly modified
    rcont2(nrow, ncol, nrowt_ptr, ncolt_ptr, &key, &seed, result_ptr, &ierror);
    if (ierror != 0) {
        throw simulation_error("Could not construct two-way contingency table");
    }
    return;
}

auto docstring = R"pbdoc(Construct a random two-way contingency table with given sums

Parameters
----------
nrow : int
    number of rows in the table, should be >= 2
ncol : int
    number of columns in the table, should be >= 2
nrowt : np.array[int]
    the row sums, note all values should be positive
ncolt : np.array[int]
    the col sums, note all values should be positive
seed : int
    random seed for the generation
result : np.array[int]
    initialized array where the results will be stored

Reference
---------
WM Patefield,
Algorithm AS 159:
An Efficient Method of Generating RXC Tables with
Given Row and Column Totals,
Applied Statistics,
Volume 30, Number 1, 1981, pages 91-97.
)pbdoc";

void bind_sim_2d_data_patefield(py::module &m) {
    m.def(
        "_sim_2d_data_patefield",
        &_sim_2d_data_patefield,
        docstring,
        py::arg("nrow"),
        py::arg("ncol"),
        py::arg("nrowt"),
        py::arg("ncolt"),
        py::arg("seed"),
        py::arg("result")
    );
}

/*     Simulate a 2 dimensional dataset given a 2 dimensional pdf
 */
void _sim_2d_data(
    const py::array_t<int64_t>& hist,
    const int64_t hist_sum,
    const int64_t ndata,
    const size_t seed,
    py::array_t<int64_t>& hout
) {

    size_t N = hist.size();
    double scaler = (static_cast<double>(ndata) / static_cast<double>(hist_sum));
    double* hcr = new double[N];

    auto h_ptr = hist.unchecked<1>();
    auto hout_ptr = hout.mutable_unchecked<1>();

    std::mt19937_64 engine(seed);

    // scale and ravel
    for (size_t i = 0; i < N; i++) {
        hcr[i] = static_cast<double>(h_ptr[i]) * scaler;
    }

    // **first estimate, unconstrained**
    // below could be made parallel but the engine needs to
    // instantiated with independent seeds
    // for each thread as you would get duplicate runs otherwise
    // The overhead and complexity is probably not worth it
    // unless the array is quite large
    for (size_t i = 0; i < N; i++) {
        std::poisson_distribution<int64_t> rpoisson(hcr[i]);
        hout_ptr[i] = rpoisson(engine);
    }

    double hmax = *std::max_element(hcr, hcr + N);

    double acc1 = 0;
    for (size_t i = 0; i < N; i++) {
        acc1 += hout_ptr[i];
    }
    int64_t houtsum = lround(acc1);

    // iterate until houtsum == ndata
    bool wgt = houtsum > ndata ? false : true;
    int64_t nextra = std::abs(static_cast<int64_t>(ndata) - houtsum);

    double h, hran = 0.;
    int64_t ibin, hout_val = 0;
    // randint
    std::uniform_int_distribution<int64_t> randint(0, N);
    // random uniform
    std::uniform_real_distribution<double> uni(0.0, hmax);

    while (nextra > 0) {
        ibin = randint(engine);
        h = hcr[ibin];
        hran = uni(engine);

        if (hran < h) {
            if (wgt) {
                hout_ptr[ibin] += 1;
            } else {
                if (hout_ptr[ibin] > 0) {
                    hout_ptr[ibin] -= 1;
                } else {
                    continue;
                }
            }
            nextra -= 1;
        }
    }

    delete[] hcr;
    return;
}

auto docstring_sim_2d_data = R"pbdoc(Simulate a 2 dimensional dataset given a 2 dimensional pdf

Parameters
----------
hist : np.array[int32 or int64]
    contingency table, which contains the observed number of occurrences in each category. \
    This table is used as probability density function.
hist_sum : int
    sum of hist
ndata : int
    number of simulations
seed : int
    random seed for the generation
hout : np.array[int64]
    initialized array where the results will be stored, note array is modified inplace
)pbdoc";

void bind_sim_2d_data(py::module &m) {
    m.def(
        "_sim_2d_data",
        &_sim_2d_data,
        docstring_sim_2d_data,
        py::arg("hist"),
        py::arg("hist_sum"),
        py::arg("ndata"),
        py::arg("seed"),
        py::arg("hout")
    );
}

#endif  // PYTHON_PHIK_SIMCORE_SIMULATION_HPP_
