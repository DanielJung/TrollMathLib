#pragma once

#include <assert.h>

#include "IInterpolation.h"
#include "../storage/Vec.h"
#include "../storage/COOMat.h"
#include "../solver/cg.h"

#include <iostream>

namespace troll {
namespace interpolation {
	template <typename index, typename real>
	class CubicSpline : public IInterpolation<index, real> {
	public:
		CubicSpline() {

		}

		virtual ~CubicSpline() {
			if (mX) delete mX;
			if (mA) delete mA;
			if (mB) delete mB;
			if (mC) delete mC;
			if (mD) delete mD;

			mX = NULL;
			mA = NULL;
			mB = NULL;
			mC = NULL;
			mD = NULL;
		}

		void Compute(storage::IVec<index, real>& x, storage::IVec<index, real>& y) {
			assert(x.getSize() == y.getSize());

			mX = new storage::Vec<index, real>(x);

			storage::Vec<index, real> h(x.getSize()-1);
			for (index i = 0; i < h.getSize(); ++i) {
				h.at(i) = x.at(i + 1) - x.at(i);
			}

			index n = y.getSize();
			storage::COOMat<index, real> A(n, n);
			A.set(0, 0, 1.0);
			A.set(n - 1, n - 1, 1.0);

			for (index i = 1; i < n - 1; ++i) {
				A.set(i, i - 1, h.at(i-1));
				A.set(i, i, 2.0*(h.at(i-1)+h.at(i)));
				A.set(i, i + 1, h.at(i));
			}

			storage::Vec<index, real> b(n, 0.0);
			for (index i = 1; i < n-1; ++i) {
				b.at(i) = 6.0 / h.at(i)*(y.at(i + 1) - y.at(i)) - 6.0 / h.at(i - 1)*(y.at(i) - y.at(i - 1));
			}

			storage::Vec<index, real> ddy(n, 0.0);
			
			solver::cg<index, real>(A, b, ddy, 1e-10, 1000);

			mA = new storage::Vec<index, real>(n - 1);
			mB = new storage::Vec<index, real>(n - 1);
			mC = new storage::Vec<index, real>(n - 1);
			mD = new storage::Vec<index, real>(n - 1);

			for (index i = 0; i < n - 1; ++i) {
				mA->at(i) = 1.0 / (6.0*h.at(i))*(ddy.at(i + 1) - ddy.at(i));
				mB->at(i) = 0.5*ddy.at(i);
				mC->at(i) = 1.0 / h.at(i)*(y.at(i + 1) - y.at(i)) - 1.0 / 6.0*h.at(i)*(ddy.at(i + 1) + 2.0*ddy.at(i));
				mD->at(i) = y.at(i);
			}
		}

		real Eval(real x) {
			assert(mX);
			assert(mA);
			assert(mB);
			assert(mC);
			assert(mD);
			assert(x >= mX->at(0) && x <= mX->at(mX->getSize() - 1));

			for (index i = 0; i < mX->getSize()-1; ++i) {
				if (x >= mX->at(i) && x <= mX->at(i + 1)) {
					x -= mX->at(i);
					real val = mA->at(i)*x*x*x + mB->at(i)*x*x + mC->at(i)*x + mD->at(i);
					return val;
				}
			}
		}

		storage::Vec<index, real> Eval(const storage::Vec<index, real>& x) {
			storage::Vec<index, real> Result(x.getSize());
			for (index i = 0; i < x.getSize(); ++i) {
				Result.at(i) = Eval(x.at(i));
			}
			return Result;
		}
	private:
		storage::Vec<index, real>* mX;
		storage::Vec<index, real>* mA;
		storage::Vec<index, real>* mB;
		storage::Vec<index, real>* mC;
		storage::Vec<index, real>* mD;
	};
}
}