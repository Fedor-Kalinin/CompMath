#include <array>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
/**
* xType - тип аргумента x.
* yType - тип значения функции y
* N - количество точек для интерполяции
*(x0,x1,x2,x3) N=5
* Рекомедую обратить внимание. Разность (xType - xType) не обязана быть типом xType
*/

template<typename xType, typename yType, unsigned int N>
class NewtonInterpolator {
    /*** Какие-то поля ***/
    std::array<xType, N> xi;
    std::array<yType, N> RR;
    public:
        NewtonInterpolator(const std::array<xType, N> &points, const std::array<yType, N>& values) noexcept : xi{points} , RR(values)
        {   
            for( int j = 0; j < N - 1; j++)
            {
                for(int i = N - 1; i > j; i--)
                {
                    RR[i]= ( RR[ i ] - RR[i - 1] ) / ( xi[i] - xi[i - j - 1]);
                }
            }
        }
        
        yType interpolate(const xType& x) const noexcept
        {

            yType y = 0 ;
            for(int i = N - 1; i >= 1; i--)
            {
                y = (RR[i] + y) * (x - xi[i - 1]);
            }
            y += RR[0];
            return y;

        }
};




void generateValues(double start, double end, size_t numPoints, std::ofstream& outputFile) 
{
    std::array<double,5> xValues;
    std::array<double,5> yValues;
    double step = (end - start) / numPoints;

    for (size_t i = 0; i < numPoints; i++) 
    {
        double x = start + i * step;
        xValues.at(i) = x;
        yValues.at(i) = std::exp(x);
    }

    NewtonInterpolator<double,double,5> ex (xValues, yValues);

    std::array<double,1000> xValuesall;
    std::array<double,1000> yValuesall;
    double step1 = (end - start) / 1000;
    for (size_t i = 0; i < 1000; i++) 
    {
        double x = start + i * step1;
        xValuesall.at(i) = x;
        double z = ex.interpolate(x);
        yValuesall.at(i) = z;
    }

    

    for (size_t i = 0; i < xValuesall.size(); ++i) 
    {
        outputFile << xValuesall[i] << ", " << yValuesall[i] << std::endl;
    }
}

int main() {
    std::ofstream outputFile("N5.txt");

    if (!outputFile) 
    {
        std::cerr << "Ошибка при создании файла!" << std::endl;
        return 1;
    }

    double intervals[1][2] = {
        {0, 2}};
        // {0, 1.0 / 2},
        // {0, 1.0 / 3},
        // {0, 1.0 / 4},
        // {0, 1.0 / 5},
        // {0, 1.0 / 6},
        // {0, 1.0 / 7},
        // {0, 1.0 / 8},
        // {0, 1.0 / 9},
        // {0, 1.0 / 10},
        // {0, 1.0 / 11},
        // {0, 1.0 / 12},
        // {0, 1.0 / 13},
        // {0, 1.0 / 14},
        // {0, 1.0 / 15},
        // {0, 1.0 / 16}
    // };

    for (int i = 0; i < 1; ++i) 
    {
        double start = intervals[i][0];
        double end = intervals[i][1];
        size_t numPoints = 5;

        generateValues(start, end, numPoints, outputFile);
    }
    outputFile.close();

    return 0;
}
