#pragma once

#include <iostream>
#include "IVec.h"

namespace troll {
namespace storage {
	template <typename index, typename real>
	class IMat {
	public:
		virtual real get(index, index) const = 0;
		virtual void set(index, index, real) = 0;

		virtual index getNumRows() const = 0;
		virtual index getNumCols() const = 0;

		virtual void Resize(index, index) = 0;

		virtual void Scal(real) = 0;

		virtual void Gemv(real alpha, const IVec<index, real>& x, real beta, IVec<index, real>& y) const = 0;
	};
}
}

template <typename index, typename real>
std::ostream& operator << (std::ostream& stream, const troll::storage::IMat<index, real>& mat) {
	stream << "Mat - Size " << mat.getNumRows() << " | " << mat.getNumCols() << " : " << std::endl;
	for (index i = 0; i<mat.getNumRows(); ++i) {
		for (index j = 0; j < mat.getNumCols(); ++j) {
			std::printf("%6.2f", mat.get(i, j));
			//std::cout << mat.get(i, j)<<" ";
		}
		stream << std::endl;
	}
	stream << std::endl;
	return stream;
}