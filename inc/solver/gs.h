#pragma once

#include "../storage/IMat.h"
#include "../storage/Vec.h"

namespace troll {
	namespace solver {
		template <typename index, typename real>
		void gs(const storage::IMat<index, real>& A,
			const storage::IVec<index, real>& b,
			storage::IVec<index, real>& x,
			real tol, index maxit) {

			assert(b.getSize() == x.getSize());
			assert(b.getSize() == A.getNumCols());
			assert(A.getNumCols() == A.getNumRows());

			

		}
	}
}