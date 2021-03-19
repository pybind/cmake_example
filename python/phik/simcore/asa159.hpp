/*
 * Taken from:
 * https://people.sc.fsu.edu/~jburkardt/cpp_src/asa159/asa159.html
 *
 * Michael Patefield,
 * Algorithm AS 159: An Efficient Method of Generating RXC Tables with Given Row and Column Totals,
 * Applied Statistics,
 * Volume 30, Number 1, 1981, pages 91-97.
 */

#ifndef PYTHON_PHIK_SIMCORE_ASA159_HPP_
#define PYTHON_PHIK_SIMCORE_ASA159_HPP_

#include <string>

int i4_max ( int i1, int i2 );
int i4_min ( int i1, int i2 );
void i4mat_print ( int m, int n, int a[], std::string title );
void i4mat_print_some ( int m, int n, int a[], int ilo, int jlo, int ihi,
  int jhi, std::string title );
void i4vec_print ( int n, int a[], std::string title );
int i4vec_sum ( int n, int a[] );
double r8_uniform_01 ( int *seed );
void rcont2 ( int nrow, int ncol, int nrowt[], int ncolt[], bool *key,
  int *seed, int matrix[],  int *ierror );
void timestamp ( );

#endif  // PYTHON_PHIK_SIMCORE_ASA159_HPP_
