#pragma once

#include "../storage/IMat.h"
#include "../storage/Vec.h"

namespace troll {
namespace solver {
	template <typename index, typename real>
	void cg(const storage::IMat<index, real>& A,
		const storage::IVec<index, real>& b,
		storage::IVec<index, real>& x,
		real tol, index maxit) {

		assert(b.getSize() == x.getSize());
		assert(b.getSize() == A.getNumCols());
		assert(A.getNumCols() == A.getNumRows());

		storage::Vec<index, real> r(b);

		A.Gemv(-1.0, x, 1.0, r);

		storage::Vec<index, real> d(r);
		storage::Vec<index, real> z(b.getSize());		
		real alpha, beta, top;

		for (index i = 0; i < maxit; ++i) {
			A.Gemv(1.0, d, 0.0, z);
			top = r.Dot(r);
			alpha = top/d.Dot(z);

			x.Axpy(alpha, d);
			r.Axpy(-alpha, z);
			if (r.Nrm2() < tol) {
				break;
			}

			beta = r.Dot(r) / top;
			d.Scal(beta);
			d.Axpy(1.0, r);
		}

	}
}
}