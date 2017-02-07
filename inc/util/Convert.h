#pragma once

#include "../storage/FullMat.h"
#include "../storage/COOMat.h"

namespace troll {
namespace util {
	template <typename index, typename real>
	storage::FullMat<index, real> ConvertCooToFull(const storage::COOMat<index, real>& rMat) {
		storage::FullMat<index, real> oResult(rMat.getNumRows(), rMat.getNumCols(), 0.0);

		for(index i=0; i<rMat.)

		return oResult;
	}
}
}