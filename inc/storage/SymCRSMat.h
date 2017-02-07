#pragma once

#include <assert.h>

#include "IMat.h"

namespace troll {
	namespace storage {
		template <typename index, typename real>
		class SymCRSMat : public IMat<index, real> {
		public:
			SymCRSMat(index NumRows, index NumCols, const IVec<index, real>& Diagonal, const IVec<index, real>& Data, const IVec<index, index>& RowPtr, const IVec<index, index>& Cols) :
				mNumRows(NumRows),
				mNumCols(NumCols),
				mDiagonal(Diagonal),
				mData(Data),
				mRowPtr(RowPtr),
				mCols(Cols) {
				assert(false); // not tested
				assert(mNumRows > 0 && mNumCols > 0);
				assert(mData.getSize() == mCols.getSize());
				assert(mRowPtr.getSize() == mNumCols + 1);
			}

			virtual ~SymCRSMat() {}

			real get(index row, index col) const {
				assert(row < mNumRows);
				assert(col < mNumCols);

				real val = 0.0;

				if (row == col) { // diagonal
					return mDiagonal.at(row);
				}

				auto* Data = mData.getData();
				auto* RowPtr = mRowPtr.getData();
				auto* Cols = mCols.getData();

				for (index i = 0; i < mRowPtr.getSize() - 1; ++i) {
					for (index k = RowPtr[i]; k < RowPtr[i + 1]; ++k) {
						index j = Cols[k];
						if ((i == row && j == col) || (j == row && i == col))	val += Data[k];
					}
				}

				return val;
			}

			void set(index i, index j, real val) {
				assert(false);
			}

			index getNumRows() const {
				return mNumRows;
			}

			index getNumCols() const {
				return mNumCols;
			}

			void Resize(index m, index n) {
				assert(false);
			}

			void Scal(real alpha) {
				if (alpha == (real)1.0)	return;
				if (alpha == (real)0.0) {
					mData.clear();
					mRowPtr.clear();
					mCols.clear();
				}
				else {
					real* Data = mData.getData();
					for (index i = 0; i < mData.getSize(); ++i) {
						Data[i] *= alpha;
					}
				}
			}

			void Gemv(real alpha, const IVec<index, real>& x, real beta, IVec<index, real>& y) const {
				assert(x.getData());
				assert(y.getData());
				assert(x.getSize() == mNumCols);
				assert(y.getSize() == mNumRows);

				y.Scal(beta);

				auto* DataX		= x.getData();
				auto* DataY		= y.getData();

				auto* Diagonal	= mDiagonal.getData();
				auto* Data		= mData.getData();
				auto* RowPtr	= mRowPtr.getData();
				auto* Cols		= mCols.getData();

				for (index i = 0; i < mNumRows; ++i) {
					DataY[i] += alpha*Diagonal[i] * DataX[i];
				}

				for (index i = 0; i < mRowPtr.getSize() - 1; ++i) {
					for (index k = RowPtr[i]; k < RowPtr[i + 1]; ++k) {
						index j = Cols[k];
						DataY[i] += alpha*Data[k] * DataX[j];
						DataY[j] += alpha*Data[k] * DataX[i];
					}
				}
			}

		private:
			index mNumRows;
			index mNumCols;
			Vec<index, real> mDiagonal;
			Vec<index, real> mData;
			Vec<index, index> mRowPtr;
			Vec<index, index> mCols;
		};
	}
}