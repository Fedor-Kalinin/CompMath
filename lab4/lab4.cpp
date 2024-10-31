#include <array>
#include <type_traits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

    
template<std::size_t N>
constexpr std::array<double, N> gauss_weights() 
{
    if constexpr (N == 1) 
    {
        return {2.0};
    } 
    else if constexpr (N == 2) 
    {
        return {1.0, 1.0};
    } 
    else if constexpr (N == 3) 
    {
        return {5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0};
    }
    return {};
}

template<std::size_t N>
constexpr std::array<double, N> gauss_points() 
{
    if constexpr (N == 1) 
    {
        return {0.0};
    } 
    else if constexpr (N == 2) 
    {
        return {-1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0)};
    } 
    else if constexpr (N == 3) 
    {
        return {-std::sqrt(3.0 / 5.0), 0.0, std::sqrt(3.0 / 5.0)};
    }
   
    return {};
}

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> 
{
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

template<typename Callable, std::size_t N>
decltype(auto) integrate(
    const Callable& func, 
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end) 
{
    using ArgType = typename ArgumentGetter<Callable>::Argument;
    static_assert(N > 0);
    
    auto weights = gauss_weights<N>();
    auto points = gauss_points<N>();
    
    double integral = 0.0;
    double half_length = 0.5 * (end - start);
    double midpoint = 0.5 * (end + start);

    for (std::size_t i = 0; i < N; ++i) 
    {
        integral += weights[i] * func(midpoint + half_length * points[i]);
    }

    return half_length * integral;
}

template<typename Callable, std::size_t N>
decltype(auto) integrate(
    const Callable& func, 
    const typename ArgumentGetter<Callable>::Argument& start, 
    const typename ArgumentGetter<Callable>::Argument& end, 
    const Dif<typename ArgumentGetter<Callable>::Argument>& dx) 
{
    using ArgType = typename ArgumentGetter<Callable>::Argument;

    double total_integral = 0.0;
    ArgType current_start = start;

    while (current_start < end) 
    {
        ArgType current_end = std::min(current_start + dx, end);
        total_integral += integrate<Callable, N>(func, current_start, current_end);
        current_start = current_end;
    }

    return total_integral;
}


double sin_function(double x) {
    return std::sin(x);  
}

int main() 
{
   
    double start = 0.0;  
    double end = 10;   
    
    double dx = 10;     

    constexpr std::size_t N = 3;
    for(int i = 2; i <= N; i++)
    {
        std::ofstream outputFile("outputN" + std::to_string(i) + ".txt");
        
        if (!outputFile) {
            std::cerr << "Ошибка при создании файла output_" << i << ".txt!" << std::endl;
            return 1;
        }

        for(float j = 0; j < dx;)
        {
            j += 0.1;
            double integral_value = integrate<decltype(sin_function), N>(sin_function, start, end, j);
            outputFile << j << ", " << integral_value << std::endl;
        }
        outputFile.close();
    }
    
    double integral_value = integrate<decltype(sin_function), N>(sin_function, start, end, dx);
    double integral_value1 = integrate<decltype(sin_function), N>(sin_function, start, end);
    // double diff = integral_value - integer;
    std::cout << integral_value <<std::endl;
    std::cout << integral_value1 <<std::endl;
    // std::cout << integer <<std::endl;
    // std::cout << diff <<std::endl;
    // std::cout<< std::log(dx) << ", "<< std::endl;

    // std::cout << "Значение интеграла sin(x) от " << start << " до " << end << " равно: " << integral_value << std::endl;

    return 0;
}