#include <array>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include<fstream>

using uint = unsigned int;


template<typename RealType, unsigned int N>
struct DerivativeCoef {
    RealType centralCoef;
    std::array<RealType, N> otherCoefs;
};

template<typename RealType, unsigned int N>
DerivativeCoef<RealType, N> calcDerivativeCoef( std::array<RealType, N> points) noexcept 
{
    Eigen::Matrix<RealType, N, N> A;
    Eigen::Matrix<RealType, N, 1> x;
    Eigen::Matrix<RealType, N, 1> b;
    for(uint i = 0; i < N; i++)
    {
        if ( i == 0)
            b(i) = 1;
        else
            b(i) = 0;

        for(uint j = 0; j < N; j++)
        {
            if ( j == 0 )
                A(j,i) = points[i];
            else
                A(j,i) = A(j - 1, i) * points[i]; 
        }
    }

    // x = A.colPivHouseholderQr().solve(b);
    x = A.householderQr().solve(b);
    RealType centralCoef = - x.sum();
    std::array<RealType, N> otherCoefs;
    for( uint i = 0; i < N; i++)
    {
        otherCoefs.at(i) = x(i);
    }

    return {centralCoef, otherCoefs};
}


template<typename RealType, unsigned int N>
RealType d_e(const RealType x0, const RealType h, const std::array<RealType, N>& points) {
	DerivativeCoef<double, N> coefs = calcDerivativeCoef<RealType, N>(points);

	RealType de_x0 = coefs.centralCoef * exp(x0) / h;
	for (unsigned int i = 0; i < N; i++) {
		de_x0 += coefs.otherCoefs[i] * exp(x0 + points[i] * h) / h;
	}

	return de_x0;
}









int main() {

	const double x0 = 1;
	const std::array< double, 16> step = { 1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14, 1e-15 };
	const double e = exp(1);

	// Task 1

	
	std::array<double, 18> ln_step;
	ln_step[0] = -35;

	for (int i = 1; i < 18; i++) {
		double delta = 2.11;
		ln_step[i] = ln_step[i - 1] + delta;
	}

	std::ofstream data3("data3.txt");

	if (!data3) {
		return -1;
	}
	data3.precision(10);

	for (double x : ln_step) {
		data3 << x << " " << log(abs(d_e<double, 2>(x0, exp(x), { -1, 1 }) - e)) << std::endl;
	}

	data3.close();

	std::ofstream data4("data4.txt");

	if (!data4) {
		return -1;
	}
	data4.precision(10);

	for (double x : ln_step) {
		data4 << x << " " << log(abs(d_e<double, 3>(x0, exp(x), { -1, 1, 2 }) - e)) << std::endl;
	}

	data4.close();

	std::ofstream data5("data5.txt");

	if (!data5) {
		return -1;
	}
	data5.precision(10);

	for (double x : ln_step) {
		data5 << x << " " << log(abs(d_e<double, 4>(x0, exp(x), { -2, -1, 1, 2 }) - e)) << std::endl;
	}

	data5.close();
	
	return 0;
}