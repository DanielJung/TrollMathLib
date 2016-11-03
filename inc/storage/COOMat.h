#pragma once

#include <assert.h>
#include <vector>

#include "IMat.h"

namespace troll {
namespace storage {
	template <typename index, typename real>
	class COOMat : public IMat<index, real> {
	public:
		COOMat(index NumRows, index NumCols) :
			mNumRows(NumRows),
			mNumCols(NumCols) {
			assert(mNumRows > 0 && mNumCols > 0);
		}

		COOMat(index NumRows, index NumCols, const std::vector<real>& Data, const std::vector<index>& RowPtr, const std::vector<index>& ColPtr) :
			mNumRows(NumRows),
			mNumCols(NumCols),
			mData(Data),
			mRowPtr(RowPtr),
			mColPtr(ColPtr) {
			assert(mNumRows > 0 && mNumCols > 0);
			assert(mData.size() == mRowPtr.size());
			assert(mData.size() == mColPtr.size());
		}

		virtual ~COOMat() {}

		real get(index i, index j) const {
			assert(i < mNumRows);
			assert(j < mNumCols);

			real val = 0.0;

			auto* Data = mData.data();
			auto* RowPtr = mRowPtr.data();
			auto* ColPtr = mColPtr.data();

			for (index k = 0; k < mData.size(); ++k) {
				if (i == RowPtr[k] && j == ColPtr[k]) {
					val += Data[k];
				}
			}

			return val;
		}

		void set(index i, index j, real val) {
			assert(i < mNumRows);
			assert(j < mNumCols);

			mData.push_back(val);
			mRowPtr.push_back(i);
			mColPtr.push_back(j);
		}

		index getNumRows() const {
			return mNumRows;
		}

		index getNumCols() const {
			return mNumCols;
		}

		void Resize(index m, index n) {
			assert(m > 0);
			assert(n > 0);

			mNumRows = m;
			mNumCols = n;
		}

		void Scal(real alpha) {
			if (alpha == (real)1.0)	return;
			if (alpha == (real)0.0) {
				mData.clear();
				mRowPtr.clear();
				mColPtr.clear();
			}
			else {
				real* Data = mData.data();
				for (index i = 0; i < mData.size(); ++i) {
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

			auto* DataX = x.getData();
			auto* DataY = y.getData();

			auto* Data = mData.data();
			auto* RowPtr = mRowPtr.data();
			auto* ColPtr = mColPtr.data();

			for (index i = 0; i < mData.size(); ++i) {
				DataY[RowPtr[i]] += alpha*Data[i] * DataX[ColPtr[i]];
			}
		}
	private:
		index mNumRows;
		index mNumCols;
		std::vector<real> mData;
		std::vector<index> mRowPtr;
		std::vector<index> mColPtr;
	};
}
}