#!/usr/bin/env python
from warnings import warn
from scipy import sparse
import _superscs_indirect

__version__ = _superscs_indirect.version()

def solve(probdata, cone, **kwargs):
    """
    solves convex cone problems
     
    @return dictionary with solution with keys:
         'x' - primal solution
         's' - primal slack solution
         'y' - dual solution
         'info' - information dictionary
    """
    if not probdata or not cone:
        raise TypeError("Missing data or cone information")

    if not 'A' in probdata or not 'b' in probdata or not 'c' in probdata:
        raise TypeError("Missing one or more of A, b, c from data dictionary")
    A = probdata['A']
    b = probdata['b']
    c = probdata['c']

    warm = {}
    if 'x' in probdata:
        warm['x'] = probdata['x']
    if 'y' in probdata:
        warm['y'] = probdata['y']
    if 's' in probdata:
        warm['s'] = probdata['s']

    if A is None or b is None or c is None:
        raise TypeError("Incomplete data specification")
    if not sparse.issparse(A):
        raise TypeError("A is required to be a sparse matrix")
    if not sparse.isspmatrix_csc(A):
        warn("Converting A to a CSC (compressed sparse column) matrix; may take a while.")
        A = A.tocsc()

    if sparse.issparse(b):
        b = b.todense()

    if sparse.issparse(c):
        c = c.todense()

    m, n = A.shape
    
    Adata, Aindices, Acolptr = A.data, A.indices, A.indptr
    if kwargs.pop('gpu', False): # False by default
        import _superscs_gpu
        return _superscs_gpu.csolve((m, n), Adata, Aindices, Acolptr, b, c, cone, warm, **kwargs)

    if not kwargs.pop('use_indirect', True): # True by default
        import _superscs_direct
        return _superscs_direct.csolve((m, n), Adata, Aindices, Acolptr, b, c, cone, warm, **kwargs)

    return _superscs_indirect.csolve((m, n), Adata, Aindices, Acolptr, b, c, cone, warm, **kwargs)
