#include <pybind11/pybind11.h>
#include "simulation.hpp"

PYBIND11_MODULE(phik_simulation_core, m) {
    bind_sim_2d_data(m);
    bind_sim_2d_data_patefield(m);
}
