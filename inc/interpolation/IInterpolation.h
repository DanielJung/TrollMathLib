#pragma once

#include "../storage/Vec.h"

namespace troll {
namespace interpolation {
	template <typename index, typename real>
	class IInterpolation {
	public:
		virtual void Compute(storage::IVec<index, real>& x, storage::IVec<index, real>& y) = 0;

		virtual real Eval(real x) const = 0;
		virtual storage::Vec<index, real> Eval(const storage::Vec<index, real>& x) const = 0;
	};
}
}