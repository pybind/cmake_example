/*
 * Taken from:
 * https://people.sc.fsu.edu/~jburkardt/cpp_src/asa159/asa159.html
 *
 * Michael Patefield,
 * Algorithm AS 159: An Efficient Method of Generating RXC Tables with Given Row and Column Totals,
 * Applied Statistics,
 * Volume 30, Number 1, 1981, pages 91-97.
 */

# include <cmath>
# include <cstdlib>
# include <ctime>
# include <iostream>
# include <iomanip>
#include <string>

using namespace std;

# include "asa159.hpp"

//****************************************************************************80

int i4_max ( int i1, int i2 )

//****************************************************************************80
//
//  Purpose:
//
//    I4_MAX returns the maximum of two I4's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    13 October 1998
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I1, I2, are two integers to be compared.
//
//    Output, int I4_MAX, the larger of I1 and I2.
//
{
  int value;

  if ( i2 < i1 )
  {
    value = i1;
  }
  else
  {
    value = i2;
  }
  return value;
}
//****************************************************************************80

int i4_min ( int i1, int i2 )

//****************************************************************************80
//
//  Purpose:
//
//    I4_MIN returns the minimum of two I4's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    13 October 1998
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I1, I2, two integers to be compared.
//
//    Output, int I4_MIN, the smaller of I1 and I2.
//
{
  int value;

  if ( i1 < i2 )
  {
    value = i1;
  }
  else
  {
    value = i2;
  }
  return value;
}
//****************************************************************************80

void i4mat_print ( int m, int n, int a[], string title )

//****************************************************************************80
//
//  Purpose:
//
//    I4MAT_PRINT prints an I4MAT.
//
//  Discussion:
//
//    An I4MAT is an MxN array of I4's, stored by (I,J) -> [I+J*M].
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    10 September 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int M, the number of rows in A.
//
//    Input, int N, the number of columns in A.
//
//    Input, int A[M*N], the M by N matrix.
//
//    Input, string TITLE, a title.
//
{
  i4mat_print_some ( m, n, a, 1, 1, m, n, title );

  return;
}
//****************************************************************************80

void i4mat_print_some ( int m, int n, int a[], int ilo, int jlo, int ihi,
  int jhi, string title )

//****************************************************************************80
//
//  Purpose:
//
//    I4MAT_PRINT_SOME prints some of an I4MAT.
//
//  Discussion:
//
//    An I4MAT is an MxN array of I4's, stored by (I,J) -> [I+J*M].
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    20 August 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int M, the number of rows of the matrix.
//    M must be positive.
//
//    Input, int N, the number of columns of the matrix.
//    N must be positive.
//
//    Input, int A[M*N], the matrix.
//
//    Input, int ILO, JLO, IHI, JHI, designate the first row and
//    column, and the last row and column to be printed.
//
//    Input, string TITLE, a title.
//
{
# define INCX 10

  int i;
  int i2hi;
  int i2lo;
  int j;
  int j2hi;
  int j2lo;

  cout << "\n";
  cout << title << "\n";

  if ( m <= 0 || n <= 0 )
  {
    cout << "\n";
    cout << "  (None)\n";
    return;
  }
//
//  Print the columns of the matrix, in strips of INCX.
//
  for ( j2lo = jlo; j2lo <= jhi; j2lo = j2lo + INCX )
  {
    j2hi = j2lo + INCX - 1;
    if ( n < j2hi )
    {
      j2hi = n;
    }
    if ( jhi < j2hi )
    {
      j2hi = jhi;
    }

    cout << "\n";
//
//  For each column J in the current range...
//
//  Write the header.
//
    cout << "  Col:";
    for ( j = j2lo; j <= j2hi; j++ )
    {
      cout << "  " << setw(6) << j - 1;
    }
    cout << "\n";
    cout << "  Row\n";
    cout << "\n";
//
//  Determine the range of the rows in this strip.
//
    if ( 1 < ilo )
    {
      i2lo = ilo;
    }
    else
    {
      i2lo = 1;
    }
    if ( ihi < m )
    {
      i2hi = ihi;
    }
    else
    {
      i2hi = m;
    }

    for ( i = i2lo; i <= i2hi; i++ )
    {
//
//  Print out (up to INCX) entries in row I, that lie in the current strip.
//
      cout << setw(5) << i - 1 << ":";
      for ( j = j2lo; j <= j2hi; j++ )
      {
        cout << "  " << setw(6) << a[i-1+(j-1)*m];
      }
      cout << "\n";
    }
  }

  return;
# undef INCX
}
//****************************************************************************80

void i4vec_print ( int n, int a[], string title )

//****************************************************************************80
//
//  Purpose:
//
//    I4VEC_PRINT prints an I4VEC.
//
//  Discussion:
//
//    An I4VEC is a vector of I4's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    14 November 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of components of the vector.
//
//    Input, int A[N], the vector to be printed.
//
//    Input, string TITLE, a title.
//
{
  int i;

  cout << "\n";
  cout << title << "\n";
  cout << "\n";
  for ( i = 0; i < n; i++ )
  {
    cout << "  " << setw(8) << i
         << ": " << setw(8) << a[i]  << "\n";
  }
  return;
}
//****************************************************************************80

int i4vec_sum ( int n, int a[] )

//****************************************************************************80
//
//  Purpose:
//
//    I4VEC_SUM sums the entries of an I4VEC.
//
//  Discussion:
//
//    An I4VEC is a vector of I4's.
//
//  Example:
//
//    Input:
//
//      A = ( 1, 2, 3, 4 )
//
//    Output:
//
//      I4VEC_SUM = 10
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    26 May 1999
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of entries in the vector.
//
//    Input, int A[N], the vector to be summed.
//
//    Output, int I4VEC_SUM, the sum of the entries of A.
//
{
  int i;
  int sum;

  sum = 0;
  for ( i = 0; i < n; i++ )
  {
    sum = sum + a[i];
  }

  return sum;
}
//****************************************************************************80

double r8_uniform_01 ( int *seed )

//****************************************************************************80
//
//  Purpose:
//
//    R8_UNIFORM_01 is a unit pseudorandom R8.
//
//  Discussion:
//
//    This routine implements the recursion
//
//      seed = 16807 * seed mod ( 2**31 - 1 )
//      unif = seed / ( 2**31 - 1 )
//
//    The integer arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    11 August 2004
//
//  Reference:
//
//    Paul Bratley, Bennett Fox, Linus Schrage,
//    A Guide to Simulation,
//    Springer Verlag, pages 201-202, 1983.
//
//    Bennett Fox,
//    Algorithm 647:
//    Implementation and Relative Efficiency of Quasirandom
//    Sequence Generators,
//    ACM Transactions on Mathematical Software,
//    Volume 12, Number 4, pages 362-376, 1986.
//
//  Parameters:
//
//    Input/output, int *SEED, a seed for the random number generator.
//
//    Output, double R8_UNIFORM_01, a new pseudorandom variate, strictly between
//    0 and 1.
//
{
  int k;
  double r;

  k = *seed / 127773;

  *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

  if ( *seed < 0 )
  {
    *seed = *seed + 2147483647;
  }

  r = ( double ) ( *seed ) * 4.656612875E-10;

  return r;
}
//****************************************************************************80

void rcont2 ( int nrow, int ncol, int nrowt[], int ncolt[], bool *key,
  int *seed, int matrix[],  int *ierror )

//****************************************************************************80
//
//  Purpose:
//
//    RCONT2 constructs a random two-way contingency table with given sums.
//
//  Discussion:
//
//    It is possible to specify row and column sum vectors which
//    correspond to no table at all.  As far as I can see, this routine does
//    not detect such a case.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    10 March 2009
//
//  Author:
//
//    Original FORTRAN77 version by WM Patefield.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    WM Patefield,
//    Algorithm AS 159:
//    An Efficient Method of Generating RXC Tables with
//    Given Row and Column Totals,
//    Applied Statistics,
//    Volume 30, Number 1, 1981, pages 91-97.
//
//  Parameters:
//
//    Input, int NROW, NCOL, the number of rows and columns
//    in the table.  NROW and NCOL must each be at least 2.
//
//    Input, int NROWT[NROW], NCOLT[NCOL], the row and column
//    sums.  Each entry must be positive.
//
//    Input/output, bool *KEY, a flag that indicates whether data has
//    been initialized for this problem.  Set KEY = .FALSE. before the first
//    call.
//
//    Input/output, int *SEED, a seed for the random number generator.
//
//    Output, int MATRIX[NROW*NCOL], the matrix.
//
//    Output, int *IERROR, an error flag, which is returned
//    as 0 if no error occurred.
//
{
  bool done1;
  bool done2;
  static double *fact = NULL;
  int i;
  int ia;
  int iap;
  int ib;
  int ic;
  int id;
  int idp;
  int ie;
  int igp;
  int ihp;
  int ii;
  int iip;
  int j;
  int jc;
  int *jwork;
  int l;
  bool lsm;
  bool lsp;
  int m;
  int nll;
  int nlm;
  int nlmp;
  int nrowtl;
  static int ntotal = 0;
  double r;
  double sumprb;
  double x;
  double y;

  *ierror = 0;
//
//  On user's signal, set up the factorial table.
//
  if ( !(*key) )
  {

    *key = true;

    if ( nrow <= 1 )
    {
      cout << "\n";
      cout << "RCONT - Fatal error!\n";
      cout << "  Input number of rows is less than 2.\n";
      *ierror = 1;
      return;
    }

    if ( ncol <= 1 )
    {
      cout << "\n";
      cout << "RCONT - Fatal error!\n";
      cout << "  The number of columns is less than 2.\n";
      *ierror = 2;
      return;
    }

    for ( i = 0; i < nrow; i++ )
    {
      if ( nrowt[i] <= 0 )
      {
        cout << "\n";
        cout << "RCONT - Fatal error!\n";
        cout << "  An entry in the row sum vector is not positive.\n";
        *ierror = 3;
        return;
      }
    }

    for ( j = 0; j < ncol; j++ )
    {
      if ( ncolt[j] <= 0 )
      {
        cout << "\n";
        cout << "RCONT - Fatal error!\n";
        cout << "  An entry in the column sum vector is not positive.\n";
        *ierror = 4;
        return;
      }
    }

    if ( i4vec_sum ( ncol, ncolt ) != i4vec_sum ( nrow, nrowt ) )
    {
      cout << "\n";
      cout << "RCONT - Fatal error!\n";
      cout << "  The row and column sum vectors do not have the same sum.\n";
      *ierror = 6;
      return;
    }

    ntotal = i4vec_sum ( ncol, ncolt );

    if ( fact )
    {
      delete [] fact;
    }

    fact = new double[ntotal+1];
//
//  Calculate log-factorials.
//
    x = 0.0;
    fact[0] = 0.0;
    for ( i = 1; i <= ntotal; i++ )
    {
      x = x + log ( ( double ) ( i ) );
      fact[i] = x;
    }

  }
//
//  Construct a random matrix.
//
  jwork = new int[ncol];

  for ( i = 0; i < ncol - 1; i++ )
  {
    jwork[i] = ncolt[i];
  }

  jc = ntotal;

  for ( l = 0; l < nrow - 1; l++ )
  {
    nrowtl = nrowt[l];
    ia = nrowtl;
    ic = jc;
    jc = jc - nrowtl;

    for ( m = 0; m < ncol - 1; m++ )
    {
      id = jwork[m];
      ie = ic;
      ic = ic - id;
      ib = ie - ia;
      ii = ib - id;
//
//  Test for zero entries in matrix.
//
      if ( ie == 0 )
      {
        ia = 0;
        for ( j = m; j < ncol; j++ )
        {
          matrix[l+j*nrow] = 0;
        }
        break;
      }
//
//  Generate a pseudo-random number.
//
      r = r8_uniform_01 ( seed );
//
//  Compute the conditional expected value of MATRIX(L,M).
//
      done1 = false;

      for ( ; ; )
      {
        nlm = ( int ) ( ( double ) ( ia * id ) / ( double ) ( ie ) + 0.5 );
        iap = ia + 1;
        idp = id + 1;
        igp = idp - nlm;
        ihp = iap - nlm;
        nlmp = nlm + 1;
        iip = ii + nlmp;
        x = exp ( fact[iap-1] + fact[ib] + fact[ic] + fact[idp-1] -
          fact[ie] - fact[nlmp-1] - fact[igp-1] - fact[ihp-1] - fact[iip-1] );

        if ( r <= x )
        {
          break;
        }

        sumprb = x;
        y = x;
        nll = nlm;
        lsp = false;
        lsm = false;
//
//  Increment entry in row L, column M.
//
        while ( !lsp )
        {
          j = ( id - nlm ) * ( ia - nlm );

          if ( j == 0 )
          {
            lsp = true;
          }
          else
          {
            nlm = nlm + 1;
            x = x * ( double ) ( j ) / ( double ) ( nlm * ( ii + nlm ) );
            sumprb = sumprb + x;

            if ( r <= sumprb )
            {
              done1 = true;
              break;
            }
          }

          done2 = false;

          while ( !lsm )
          {
//
//  Decrement the entry in row L, column M.
//
            j = nll * ( ii + nll );

            if ( j == 0 )
            {
              lsm = true;
              break;
            }

            nll = nll - 1;
            y = y * ( double ) ( j ) / ( double ) ( ( id - nll ) * ( ia - nll ) );
            sumprb = sumprb + y;

            if ( r <= sumprb )
            {
              nlm = nll;
              done2 = true;
              break;
            }

            if ( !lsp )
            {
              break;
            }

          }

          if ( done2 )
          {
            break;
          }

        }

        if ( done1 )
        {
          break;
        }

        if ( done2 )
        {
          break;
        }

        r = r8_uniform_01 ( seed );
        r = sumprb * r;

      }

      matrix[l+m*nrow] = nlm;
      ia = ia - nlm;
      jwork[m] = jwork[m] - nlm;

    }
    matrix[l+(ncol-1)*nrow] = ia;
  }
//
//  Compute the last row.
//
  for ( j = 0; j < ncol - 1; j++ )
  {
    matrix[nrow-1+j*nrow] = jwork[j];
  }
  matrix[nrow-1+(ncol-1)*nrow] = ib - matrix[nrow-1+(ncol-2)*nrow];

  delete [] jwork;

  return;
}
//****************************************************************************80

void timestamp ( )

//****************************************************************************80
//
//  Purpose:
//
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
//
//  Example:
//
//    May 31 2001 09:45:54 AM
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    03 October 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    None
//
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}
