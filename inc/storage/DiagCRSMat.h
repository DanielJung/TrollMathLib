#pragma once

#include <assert.h>

#include "IMat.h"
#include "Vec.h"
#include "CRSMat.h"

namespace troll {
	namespace storage {
		template <typename index, typename real>
		class DiagCRSMat : public IMat<index, real> {
		public:
			DiagCRSMat(index NumRows, index NumCols, const IVec<index, real>& Diagonal, const IVec<index, real>& Data, const IVec<index, index>& RowPtr, const IVec<index, index>& Cols) :
				mNumRows(NumRows),
				mNumCols(NumCols),
				mDiagonal(Diagonal),
				mData(Data),
				mRowPtr(RowPtr),
				mCols(Cols) {
				assert(mNumRows > 0 && mNumCols > 0);
				assert(mData.getSize() == mCols.getSize());
				assert(mRowPtr.getSize() == mNumCols + 1);
				assert(mNumCols == mNumRows);
				assert(mDiagonal.getSize() == mNumRows);
			}

			DiagCRSMat(const CRSMat<index, real>& A) :
				mNumRows(A.getNumRows()),
				mNumCols(A.getNumCols()),
				mDiagonal(A.getNumRows(), 0.0),
				mData(A.getData().getSize()),
				mRowPtr(A.getNumRows()+1),
				mCols(A.getCols().getSize()) {

				index nnz = 0;
				mRowPtr.at(0) = 0;
				for (index i = 0; i < A.getRowPtr().getSize() - 1; ++i) {
					for (index k =A.getRowPtr().at(i); k <A.getRowPtr().at(i+1); ++k) {
						index j = A.getCols().at(k);
						if (i == j) {
							mDiagonal.at(i) += A.getData().at(k);
						}
						else {
							mData.at(nnz) = A.getData().at(k);
							mCols.at(nnz) = A.getCols().at(k);
							nnz++;
						}
					}
					mRowPtr.at(i+1) = nnz;
				}

				mData.Resize(nnz);
				mCols.Resize(nnz);

			}

			virtual ~DiagCRSMat() {}

			real get(index row, index col) const {
				assert(row < mNumRows);
				assert(col < mNumCols);

				if (row == col) {
					return mDiagonal.at(row);
				}

				real val = 0.0;

				auto* Data = mData.getData();
				auto* RowPtr = mRowPtr.getData();
				auto* Cols = mCols.getData();

				for (index i = 0; i < mRowPtr.getSize() - 1; ++i) {
					for (index k = RowPtr[i]; k < RowPtr[i + 1]; ++k) {
						index j = Cols[k];
						if (i == row && j == col)	val += Data[k];
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

			const Vec<index, real>& getDiagonal() const {
				return mDiagonal;
			}

			const Vec<index, real>& getData() const {
				return mData;
			}

			const Vec<index, index>& getCols() const {
				return mCols;
			}

			const Vec<index, index>& getRowPtr() const {
				return mRowPtr;
			}

			void Resize(index, index) {
				assert(false);
			}

			void Scal(real alpha) {
				if (alpha == (real)1.0)	return;
				if (alpha == (real)0.0) {
					mDiagonal.clear();
					mData.clear();
					mRowPtr.clear();
					mCols.clear();
				}
				else {
					real* Data = mData.getData();
					real* Diagonal = mDiagonal.getData();
					for (index i = 0; i < mData.getSize(); ++i) {
						Data[i] *= alpha;
					}
					for (index i = 0; i < mDiagonal.getSize(); ++i) {
						Diagonal[i] *= alpha;
					}
				}
			}

			void Gemv(real alpha, const IVec<index, real>& x, real beta, IVec<index, real>& y) const {
				assert(x.getData());
				assert(y.getData());
				assert(x.getSize() == mNumCols);
				assert(y.getSize() == mNumRows);

				y.Scal(beta);

				auto* DataX = x.getData();
				auto* DataY = y.getData();

				auto* Data = mData.getData();
				auto* RowPtr = mRowPtr.getData();
				auto* Cols = mCols.getData();
				auto* Diag = mDiagonal.getData();

				for (index i = 0; i < mRowPtr.getSize() - 1; ++i) {
					for (index k = RowPtr[i]; k < RowPtr[i + 1]; ++k) {
						index j = Cols[k];
						DataY[i] += alpha*Data[k] * DataX[j];
					}
				}
				for (index i = 0; i < mDiagonal.getSize(); ++i) {
					DataY[i] += alpha*Diag[i] * DataX[i];
				}
			}
		protected:
			index mNumRows;
			index mNumCols;
			Vec<index, real> mDiagonal;
			Vec<index, real> mData;
			Vec<index, index> mRowPtr;
			Vec<index, index> mCols;
		};
	}
}