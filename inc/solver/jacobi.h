#pragma once

#include "../storage/IMat.h"
#include "../storage/DiagCRSMat.h"
#include "../storage/Vec.h"

namespace troll {
	namespace solver {
		template <typename index, typename real>
		void jacobi(const storage::DiagCRSMat<index, real>& A,
			const storage::IVec<index, real>& b,
			storage::IVec<index, real>& x,
			real tol, index maxit) {

			assert(b.getSize() == x.getSize());
			assert(b.getSize() == A.getNumCols());
			assert(A.getNumCols() == A.getNumRows());

			storage::Vec<index, real> tmp(x.getSize(), 0.0);
			const real* diag = A.getDiagonal().getData();
			const real* data = A.getData().getData();
			const index* cols = A.getCols().getData();
			const index* rowptr = A.getRowPtr().getData();

			index m = A.getNumRows();
			index n = A.getNumCols();
			index nnz = A.getData().getSize();

			for (index k = 0; k < maxit; ++k) {
				for (index i = 0; i < m; ++i) {  // sum(a_ij*x_j)
					for (index l = rowptr[i]; l < rowptr[i + 1]; ++l) {
						index j = cols[l];
						tmp.at(i) += x.at(j)*data[l];
					}
				}
				real sum = 0.0;
				real val = 0.0;
				for (index i = 0; i < n; ++i) {
					val = 1.0 / diag[i] * (b.at(i) - tmp.at(i));
					sum += abs(val - x.at(i));
					x.at(i) = val;
				}
				
				if (sum < tol)	break;

				tmp.Fill(0.0);
			}
		}
	}
}