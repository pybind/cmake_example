# -*- coding: utf-8 -*-
from phik import _sim_2d_data_patefield
import numpy as np

NUMPY_INT_MAX = np.iinfo(np.int32).max - 1

def test_sim_2d_data_patefield():
    """Quick tester."""
    hist, _ = np.histogram(np.random.uniform(0, 1, 100), bins=10)
    hist2, _ = np.histogram(np.random.uniform(0, 1, 100), bins=10)
    data = np.hstack((hist[:, None], hist2[:, None]))

    # number of rows and columns
    nrows, ncols = data.shape

    # totals per row and column
    nrowt = np.rint(data.sum(axis=1)).astype(np.int32)
    ncolt = np.rint(data.sum(axis=0)).astype(np.int32)

    matrix = np.empty(nrows * ncols, dtype=np.int32)
    seed = np.random.randint(0, NUMPY_INT_MAX)
    # simulate the data, returned through matrix inplace modification
    _sim_2d_data_patefield(nrows, ncols, nrowt, ncolt, seed, matrix)
    result = matrix.reshape(ncols, nrows)
    return result

if __name__ == '__main__':
    print(test_sim_2d_data_patefield())
