#pragma once
#define _USE_MATH_DEFINES	
#include <math.h>
#include <functional>

namespace troll {
	namespace integration {
		enum Method {
			Trapezoid,
			Simpson,
			Pulcherrima,
			Milne
		};

		enum GaussPolynom {
			Legendre,
			Chebyshev
		};

		template <typename index, typename real>
		real NewtonCotes(std::function<real(real)> f, real a, real b, index N, Method method) {

			real Result = 0.0;

			real x = a;
			real fx = f(a);
			real step = (b - a) / (real)(N+1);

			switch (method) {
				case Trapezoid: {
					real tmp = 0.0;
					for (index i = 0; i < N; ++i) {
						x += step;
						tmp = f(x + step);  // save in tmp variable so only one function evaluation occurs
						Result += step*0.5*(fx + tmp);
						fx = tmp;
					}
					break;
				}
				case Simpson: {
					for (index i = 0; i < N; ++i) {
						x += step;
						Result += step*1.0 / 6.0*(f(x) + 4.0*f(x + 0.5*step) + f(x + step));
					}
					break;
				}
				case Pulcherrima: {
					for (index i = 0; i < N; ++i) {
						x += step;
						Result += step*1.0 / 8.0*(f(x) + 3 * f(x + step*1.0 / 3.0) + 3 * f(x + step*2.0 / 3.0) + f(x + step));
					}
					break;
				}
				case Milne: {
					for (index i = 0; i < N; ++i) {
						x += step;
						Result += step*1.0 / 90.0*(7.0*f(x) + 32.0*f(x + step*0.25) + 12.0*f(x + step*0.5) + 32.0*f(step*0.75) + 7.0*f(x + step));
					}
					break;
				}
			}

			return Result;
		}

		template <typename index, typename real>
		real GaussianQuadrature(std::function<real(real)> f, real a, real b, index N, GaussPolynom polynom) {

			real Result = 0.0;

			std::function<real(real)> ftransform = [&a, &b, &f](real x) {
				return f((b - a) / 2.0*x + (a + b) / 2.0);
			};

			switch (polynom) {
				case Legendre: {
					switch (N) {
						case 1: {
							Result = 2.0 * ftransform(0.0);
							break;
						}
						case 2: {
							Result = ftransform(-sqrt(1.0 / 3.0)) + ftransform(sqrt(1.0 / 3.0));
							break;
						}
						case 3: {
							Result = 5.0 / 9.0*ftransform(-sqrt(3.0 / 5.0)) + 8.0 / 9.0*ftransform(0.0) + 5.0 / 9.0*ftransform(sqrt(3.0 / 5.0));
							break;
						}
						case 4: {
							real a1 = (18.0 - sqrt(30.0)) / 36.0;
							real a2 = (18.0 + sqrt(30.0)) / 36.0;
							real x1 = sqrt(3.0 / 7.0 + 2.0 / 7.0*sqrt(6.0 / 5.0));
							real x2 = sqrt(3.0 / 7.0 - 2.0 / 7.0*sqrt(6.0 / 5.0));
							Result = a1*ftransform(-x1) + a2*ftransform(-x2) + a2*ftransform(x2) + a1*ftransform(x1);
							break;
						}
					}
					break;
				}
				case Chebyshev: {
					for (index i = 0; i < N; ++i) {
						real x = (2.0*(real)i - 1) / 2 / (real)N * M_PI;
						Result += ftransform(cos(x))*sin(x);
					}
					Result *= M_PI / (real)N;
					break;
				}
			}

			return (b - a) / 2.0*Result;
		}
}
}