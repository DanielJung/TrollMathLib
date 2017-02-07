#pragma once

#define _USE_MATH_DEFINES	

#include <cstdlib>
#include <assert.h>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

#include "IVec.h"

namespace troll {
namespace storage {
    template <typename index, typename real>
    class Vec : public IVec<index, real> {
        public:
			Vec() : 
				mData(NULL),
				mSize(0) {

			}
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

                std::memcpy(mData, v.mData, mSize*sizeof(real));
            }

			Vec(const IVec& v) : 
				mData(NULL),
				mSize(v.getSize()) {

				assert(mSize > 0);

				mData = (real*)std::malloc(mSize * sizeof(real));
				assert(mData);

				std::memcpy(mData, v.getData(), mSize * sizeof(real));
			}

			Vec(const std::vector<real>& v) : 
				mData(NULL),
				mSize((index)v.size()) {

				assert(mSize > 0);

				mData = (real*)std::malloc(mSize * sizeof(real));
				assert(mData);

				std::memcpy(mData, v.data(), mSize * sizeof(real));
			}

			Vec(const std::initializer_list<real>& v) : 
				mData(NULL),
				mSize(v.size()) {
				
				assert(mSize > 0);

				mData = (real*)std::malloc(mSize * sizeof(real));
				assert(mData);

				index i = 0;
				for (auto t = v.begin(); t != v.end(); ++t) {
					mData[i] = *t;
					i++;
				}
			}
                
            virtual ~Vec() {
                if(mData)   free(mData);
                mData = NULL;
                mSize = 0;
            }

			Vec& operator = (const Vec& v) {
				if (mData)	free(mData);
				mSize = v.mSize;

				mData = (real*)std::malloc(mSize * sizeof(real));
				assert(mData);

				std::memcpy(mData, v.mData, mSize * sizeof(real));
				return *this;
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
                assert(Size>0);
                
                if(Size==mSize) return;
                
                mSize = Size;
				if (mData) {
					mData = (real*)realloc(mData, mSize * sizeof(real));
				}
				else {
					mData = (real*)malloc(mSize * sizeof(real));
				}

                assert(mData);
            }

			void Fill(real num) {
				assert(mData);
				assert(mSize>0);

				for (index i = 0; i<mSize; ++i) {
					mData[i] = num;
				}
			}
            
            void Swap(IVec<index, real>& y) {
                assert(mData);
                assert(y.getData());
                
                assert(y.getSize()==mSize);
                
                //std::swap_ranges(mData, mData+(mSize-1)*sizeof(real), y.getData());
				for (index i = 0; i < mSize; ++i) {
					std::swap(mData[i], y.getData()[i]);
				}
            }
        
            void Scal(real alpha) {
                assert(mData);
                
                if(alpha==(real)1.0)    return;
                if(alpha==(real)0.0) {
                    for(index i=0; i<mSize; ++i) {
                        mData[i] = (real)0.0;
                    }
                } else {
#pragma omp parallel for
                    for(index i=0; i<mSize; ++i) {
                        mData[i]*=alpha;
                    }
                }
            }

			void Scal_1(real alpha) {
				assert(mData);

				if (alpha == (real)1.0)    return;
				if (alpha == (real)0.0) {
					for (index i = 0; i<mSize; ++i) {
						mData[i] = 0.0;
					}
				}
				else {
#pragma omp parallel for
					for (index i = 0; i < mSize / 4; ++i) {
						mData[4 * i] *= alpha;
						mData[4 * i + 1] *= alpha;
						mData[4 * i + 2] *= alpha;
						mData[4 * i + 3] *= alpha;
					}
					for (index i = mSize-mSize%4; i < mSize; ++i) {
						mData[i] *= alpha;
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
                
                const real* ptr = x.getData();
                
                if(alpha==(real)0.0)    return;
                if(alpha==(real)1.0) {
#pragma omp parallel for
                    for(index i=0; i<mSize; ++i) {
                        mData[i]+=ptr[i];
                    }
                } else {
                    for(index i=0; i<mSize; ++i) {
                        mData[i]+=alpha*ptr[i];
                    }
                }
            }

            real Dot(const IVec<index, real>& y) const {
                assert(mData);
                assert(y.getData());
                assert(mSize==y.getSize());
                                
                const real* ptr = y.getData();
                
                real sum = (real)0.0;
                for(index i=0; i<mSize; ++i) {
                    sum+=mData[i]*ptr[i];
                }
                return sum;
            }

            real Nrm2() const {
                assert(mData);
                                
                real sum = (real)0.0;
                for(index i=0; i<mSize; ++i) {
                    sum+=mData[i]*mData[i];
                }
                return (real)sqrt(sum);
            }

            real Asum() const {
                assert(mData);
                
                real sum = (real)0.0;
                for(index i=0; i<mSize; ++i) {
                    sum += (real)fabs(mData[i]);
                }
                return sum;
            }

            index Idamax() const {
                assert(mData);
                
                index max = 0;
                real val = (real)0.0;
                real tmp = (real)0.0;
                
                for(index i=0; i<mSize; ++i) {
                    tmp = (real)fabs(mData[i]);
                    if(tmp>val) {
                        max = i;
                        val = tmp;
                    }
                }
                return max;
            }

			void push_back(real val) {
				if (mData) {
					Resize(mSize + 1);
					mData[mSize - 1] = val;
				}
				else {
					mData = (real*)std::malloc(1 * sizeof(real));
					mSize = 1;
					mData[0] = val;
				}
			}

			void clear() {
				if (mData)   free(mData);
				mData = NULL;
				mSize = 0;
			}
            
        private:
            real* mData;
            index mSize;
    };
}
}