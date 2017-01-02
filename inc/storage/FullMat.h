#pragma once

#define _USE_MATH_DEFINES	

#include <cstdlib>
#include <assert.h>
#include <cstring>
#include <algorithm>
#include <cmath>

#include "IMat.h"

namespace troll {
namespace storage {
	template <typename index, typename real>
	class FullMat : public IMat<index, real> {
	public:
		FullMat(index NumRows, index NumCols, bool IsRowMajor = true) : 
			mData(NULL),
			mNumRows(NumRows),
			mNumCols(NumCols),
			mIsRowMajor(IsRowMajor) {

			assert(mNumRows > 0 && mNumCols > 0);

			mData = (real*)malloc(mNumRows*mNumCols * sizeof(real));
			assert(mData);
		}

		FullMat(index NumRows, index NumCols, real* Data, bool IsRowMajor = true) : 
			mData(NULL),
			mNumRows(NumRows),
			mNumCols(NumCols),
			mIsRowMajor(IsRowMajor) {

			assert(mNumRows > 0 && mNumCols > 0);

			mData = (real*)malloc(mNumRows*mNumCols * sizeof(real));
			assert(mData);
			std::memcpy(mData, Data, mNumRows*mNumCols * sizeof(real));
		}

		FullMat(index NumRows, index NumCols, real Fill, bool IsRowMajor = true) : 
			mData(NULL),
			mNumRows(NumRows),
			mNumCols(NumCols),
			mIsRowMajor(IsRowMajor) {

			assert(mNumRows > 0 && mNumCols > 0);

			mData = (real*)malloc(mNumRows*mNumCols * sizeof(real));
			assert(mData);
			for (index i = 0; i < mNumRows*mNumCols; ++i) {
				mData[i] = Fill;
			}
		}

		FullMat(const FullMat& m) : 
			mData(NULL),
			mNumRows(m.mNumRows),
			mNumCols(m.mNumCols),
			mIsRowMajor(m.mIsRowMajor) {

			assert(mNumRows > 0 && mNumCols > 0);

			mData = (real*)malloc(mNumRows*mNumCols * sizeof(real));
			assert(mData);

			std::memcpy(mData, m.mData, mNumRows*mNumCols * sizeof(real));
		}

		virtual ~FullMat() {
			if (mData)	free(mData);
			mData = NULL;
			mNumRows = 0;
			mNumCols = 0;
			mIsRowMajor = true;
		}

		real get(index i, index j) const {
			assert(i < mNumRows);
			assert(j < mNumCols);
			assert(mData);

			if (mIsRowMajor) {
				return mData[i*mNumCols + j];
			}
			else {
				return mData[i + j*mNumRows];
			}
		}

		void set(index i, index j, real val) {
			assert(i < mNumRows);
			assert(j < mNumCols);
			assert(mData);

			if (mIsRowMajor) {
				mData[i*mNumCols + j] = val;
			}
			else {
				mData[i + j*mNumRows] = val;
			}
		}

		index getNumRows() const {
			return mNumRows;
		}

		index getNumCols() const {
			return mNumCols;
		}

		bool isRowMajor() const {
			return mIsRowMajor;
		}

		void Resize(index m, index n) {
			assert(mData);
			assert(m > 0);
			assert(n > 0);

			if (m == mNumRows && n == mNumCols)	return;

			mNumRows = m;
			mNumCols = n;


			mData = (real*)realloc(mData, mNumRows*mNumCols * sizeof(real));
			assert(mData);
		}

		void Scal(real alpha) {
			assert(mData);

			if (alpha == (real)1.0)	return;
			if (alpha == (real)0.0) {
				for (index i = 0; i < mNumRows*mNumCols; ++i) {
					mData[i] = 0.0;
				}
			}
			else {
				for (index i = 0; i < mNumRows*mNumCols; ++i) {
					mData[i] *= alpha;
				}
			}
		}

		void Gemv(real alpha, const IVec<index, real>& x, real beta, IVec<index, real>& y) const {
			assert(mData);
			assert(x.getData());
			assert(y.getData());
			assert(x.getSize() == mNumCols);
			assert(y.getSize() == mNumRows);

			y.Scal(beta);

			auto* DataX = x.getData();
			auto* DataY = y.getData();

			if (mIsRowMajor) {
				for (index i = 0; i < mNumRows; ++i) {
					for (index j = 0; j < mNumCols; ++j) {
						DataY[i] += alpha*mData[i*mNumCols + j] * DataX[j];
					}
				}
			}
		}
	private:
		real* mData;
		index mNumRows;
		index mNumCols;
		bool mIsRowMajor;
	};
}
}