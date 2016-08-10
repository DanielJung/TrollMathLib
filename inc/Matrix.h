#pragma once

template <typename index, typename real>
class Matrix {
    public:
        Matrix(index numRows, index numCols, real fill = (real)0.0, index incRow = (index)1, index incCol = numRows);
        virtual ~Matrix();

        real* at(index i, index j);
        real* getData();
    private:
        index mNumRows;
        index mNumCols;

        index mIncRow;
        index mIncCol;

        real* mData;
};