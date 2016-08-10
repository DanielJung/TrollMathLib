#include <Matrix.h>

#include <string.h>
#include <assert.h>

template <typename index, typename real>
Matrix<index, real>::Matrix(index numRows, index numCols, real fill = (real)0.0, index incRow = (index)1, index incCol = numRows) : 
    mNumRows(numRows),
    mNumCols(numCols),
    mIncRow(incRow),
    mIncCol(incCol),
    mData(NULL) {
        mData = new real[mNumRows*mNumCols];
        memset(mData, (real)0.0, sizeof(real)*mNumRows*mNumCols);
}

template <typename index, typename real>
Matrix<index, real>::~Matrix() {
    if(mData)   delete[] mData;
    mNumRows    = 0;
    mNumCols    = 0;
    mIncRow     = 0;
    mIncCol     = 0;
    mData       = NULL;
}

template <typename index, typename real>
real* Matrix<index, real>at(index i, index j) {

    assert(i>=0 && i<mNumRows);
    assert(j>=0 && j<mNumCols);
    
    return mData+i*incRow+j*incCol;
}

template <typename index, typename real>
real* Matrix<index, real>getData() {
    return mData;
}