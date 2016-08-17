#pragma once

#include <cstdlib>
#include <assert.h>
#include <cstring>
#include <algorithm>
#include <cmath>

#include "IVec.h"

namespace troll {
namespace storage {
    template <typename index, typename real>
    class Vec : public IVec<index, real> {
        public:
            Vec(index Size) :
                mData(NULL),
                mSize(Size) {
                    
                assert(mSize>0);

                mData = (real*)std::malloc(mSize*sizeof(real));
                assert(mData);
            }
                
            Vec(index Size, real* Data) :
                mData(NULL),
                mSize(Size) {

                assert(mSize>0);

                mData = (real*)std::malloc(mSize*sizeof(real));
                assert(mData);
                std::memcpy(mData, Data, mSize*sizeof(real));
            }
                
            Vec(index Size, real Fill) :
                mData(NULL),
                mSize(Size) {
                
                assert(mSize>0);
                
                mData = (real*)std::malloc(mSize*sizeof(real));
                assert(mData);
                for(index i=0; i<mSize; ++i) {
                    mData[i] = Fill;
                }
            }
                
            Vec(const Vec& v) :
                mData(NULL),
                mSize(v.mSize) {

                assert(mSize>0);

                mData = (real*)std::malloc(mSize*sizeof(real));
                assert(mData);

                memcpy(mData, v.mData, mSize*sizeof(real));
            }
                
            ~Vec() {
                if(mData)   free(mData);
                mData = NULL;
                mSize = 0;
            }
            
            index getSize() const {
                return mSize;
            }
            
            real* getData() {
                assert(mData);
                return mData;
            }
            
            const real* getData() const {
                assert(mData);
                return mData;
            }
            
            real& at(index i) {
                assert(i>=0 && i<mSize);
                assert(mData);
                return mData[i];
            }
            
            const real& at(index i) const {
                assert(i>=0 && i<mSize);
                assert(mData);
                return mData[i];
            }
            
            void Resize(index Size) {
                assert(mData);
                assert(Size>0);
                
                if(Size==mSize) return;
                
                mSize = Size;
                mData = (real*)realloc(mData, mSize*sizeof(real));
                assert(mData);
            }
            
            void Swap(IVec<index, real>& y) {
                assert(mData);
                assert(y.getData());
                
                assert(y.getSize()==mSize);
                
                std::swap_ranges(mData, mData+mSize*sizeof(real), y.getData());
            }
        
            void Scal(real alpha) {
                assert(mData);
                
                if(alpha==(real)1.0)    return;
                if(alpha==(real)0.0) {
                    for(index i=0; i<mSize; ++i) {
                        mData[i] = 0.0;
                    }
                } else {
                    for(index i=0; i<mSize; ++i) {
                        mData[i]*=alpha;
                    }
                }
            }

            void Copy(const IVec<index, real>& y) {
                assert(mData);
                assert(y.getData());
                assert(mSize==y.getSize());
                
                std::memcpy(mData, y.getData(), mSize*sizeof(real));
            }

            void Axpy(real alpha, const IVec<index, real>& x) {
                assert(mData);
                assert(x.getData());
                assert(mSize==x.getSize());
                
                real* ptr = x.getData();
                
                if(alpha==(real)0.0)    return;
                if(alpha==(real)1.0) {
                    for(index i=0; i<mSize; ++i) {
                        mData[i]+=ptr[i];
                    }
                } else {
                    for(index i=0; i<mSize; ++i) {
                        mData[i]+=ptr[i];
                    }
                }
            }

            real Dot(const IVec<index, real>& y) const {
                assert(mData);
                assert(y.getData());
                assert(mSize==y.getSize());
                                
                real* ptr = y.getData();
                
                real sum = 0.0;
                for(index i=0; i<mSize; ++i) {
                    sum+=mData[i]*ptr[i];
                }
                return sum;
            }

            real Nrm2() const {
                assert(mData);
                                
                real sum = 0.0;
                for(index i=0; i<mSize; ++i) {
                    sum+=mData[i]*mData[i];
                }
                return sqrt(sum);
            }

            real Asum() const {
                assert(mData);
                
                real sum = 0.0;
                for(index i=0; i<mSize; ++i) {
                    sum+=fabs(mData[i]);
                }
                return sum;
            }

            index Idamax() const {
                assert(mData);
                
                index max = 0;
                real val = 0.0;
                real tmp = 0.0;
                
                for(index i=0; i<mSize; ++i) {
                    tmp = fabs(mData[i]);
                    if(tmp>val) {
                        max = i;
                        val = tmp;
                    }
                }
                return max;
            }
            
        private:
            real* mData;
            index mSize;
    };
}
}