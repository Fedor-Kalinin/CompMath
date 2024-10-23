#include <array>
#include <eigen3/Eigen/Dense>
#include <iostream>

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


int main()
{
    unsigned int N = 3;
    std::array<double, 2> points {-1, 1};
    DerivativeCoef<double, 2> test = calcDerivativeCoef<double, 2> (points) ;

    std::cout << test.centralCoef << std::endl;
    std::cout << test.otherCoefs[0] << std::endl;
    std::cout << test.otherCoefs[1] << std::endl;



    // unsigned int N = 3;
    // std::array<double, 3> points {-1, 1, 2};
    // DerivativeCoef<double, 3> test = calcDerivativeCoef<double, 3> (points) ;

    // std::cout << test.centralCoef << std::endl;
    // std::cout << test.otherCoefs[0] << std::endl;
    // std::cout << test.otherCoefs[1] << std::endl;
    // std::cout << test.otherCoefs[2] << std::endl;
}
