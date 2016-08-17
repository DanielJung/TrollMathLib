#pragma once

#include <assert.h>
#include <cstdlib>

namespace storage {
    template <typename index, typename real>
    class Matrix {
        public:
            Matrix(index numRows, index numCols, real fill = (real)0.0, index incRow = (index)1, index incCol = (index)0) :
                            mNumRows(numRows),
                            mNumCols(numCols),
                            mIncRow(incRow),
                            mIncCol(incCol ? incCol : numRows),
                            mData(NULL) {
                            mData = new real[mNumRows*mNumCols];
                            if (fill != (real)0.0) {
                                    for (index i = 0; i < mNumRows*mNumCols; ++i) {
                                            mData[i] = fill;
                                    }
                            }
                    }

            virtual ~Matrix() {
                            if (mData)   delete[] mData;
                            mNumRows = 0;
                            mNumCols = 0;
                            mIncRow = 0;
                            mIncCol = 0;
                            mData = NULL;
                    }

            real* at(index i, index j) {

                            assert(i >= 0 && i<mNumRows);
                            assert(j >= 0 && j<mNumCols);

                            return mData + i*incRow + j*incCol;
                    }
            real* getData() {
                            return mData;
                    }
        private:
            index mNumRows;
            index mNumCols;

            index mIncRow;
            index mIncCol;

            real* mData;
    };
}