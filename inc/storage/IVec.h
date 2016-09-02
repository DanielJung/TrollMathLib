#pragma once

#include <iostream>

namespace troll {
namespace storage {
    template <typename index, typename real>
    class IVec {
        public:
        virtual real& at(index) = 0;
        virtual const real& at(index) const = 0;
        
        virtual real* getData() = 0;
        virtual const real* getData() const = 0;
        
        virtual index getSize() const = 0;
        
        virtual void Resize(index) = 0;
        
        virtual void Swap(IVec& y) = 0;
        
        virtual void Scal(real alpha) = 0;
        
        virtual void Copy(const IVec& y) = 0;
        
        virtual void Axpy(real alpha, const IVec& x) = 0;
        
        virtual real Dot(const IVec&) const = 0;
        
        virtual real Nrm2() const = 0;
        
        virtual real Asum() const = 0;
        
        virtual index Idamax() const = 0;
        
    };
}
}

template <typename index, typename real>
std::ostream& operator << (std::ostream& stream, const troll::storage::IVec<index, real>& vec) {
	stream <<"Vec - Size "<<vec.getSize()<<": ";
    for(index i=0; i<vec.getSize(); ++i) {
		stream <<vec.at(i)<<"\t";
    }
	stream <<std::endl;
	return stream;
}