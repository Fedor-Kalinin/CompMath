#include <iostream>
#include <stdexcept>
#include <cmath> 
#include <array>
#include <fstream>
#include <cmath>
#include <vector>

template <typename Type>
struct SplinePolynomCoeffs {
    Type a, b, c, d; 
};

template <typename xType, typename yType>
class CubicSpline {
private:
    std::vector<xType> points_;
    std::vector<SplinePolynomCoeffs<double>> coeffs_; // Допустим, что используем double для коэффициентов

public:
    CubicSpline(const std::vector<xType>& points, const std::vector<yType>& values) 
    {
        if (points.size() != values.size() || points.size() < 2) 
        {
            throw std::invalid_argument("Недостаточно данных для построения сплайна.");
        }

        points_ = points;
        coeffs_.resize(points.size() - 1);
        calculateCoefficients(values);
    }

    void calculateCoefficients(const std::vector<yType>& values) 
    {
        size_t n = points_.size() - 1;
        std::vector<double> h(n), alpha(n), l(n + 1), mu(n), z(n + 1), c(n + 1);
        
        for (size_t i = 0; i < n; ++i) 
        {
            h[i] = points_[i + 1] - points_[i];
        }
        for (size_t i = 1; i < n; ++i) 
        {
            alpha[i] = (3.0 / h[i]) * (values[i + 1] - values[i]) - (3.0 / h[i - 1]) * (values[i] - values[i - 1]);
        }

        l[0] = 1;
        mu[0] = 0;
        z[0] = 0;

        for (size_t i = 1; i < n; ++i) 
        {
            l[i] = 2 * (points_[i + 1] - points_[i - 1]) - h[i - 1] * mu[i - 1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        l[n] = 1;
        z[n] = 0;
        c[n] = 0;

        for (size_t j = n - 1; j-- > 0;) 
        {
            c[j] = z[j] - mu[j] * c[j + 1];
            double b = (values[j + 1] - values[j]) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
            double d = (c[j + 1] - c[j]) / h[j];
            coeffs_[j] = { values[j], b, c[j], d }; 
        }
    }

    const std::vector<SplinePolynomCoeffs<double>>& getCoefficients() const 
    {
        return coeffs_;
    }

    yType interpolate(const xType& x) const noexcept
    {
        for (std::size_t i = 0; i < coeffs_.size(); ++i) 
        {
            if (points_[i] <= x && x <= points_[i + 1]) 
                return coeffs_[i].a + (x - points_[i + 1]) * (coeffs_[i].b  +  (x - points_[i + 1]) * (coeffs_[i].c / 2 + (x - points_[i + 1]) * coeffs_[i].d / 6));
        }
    }
};


void generateValues(double start, double end, size_t numPoints, std::ofstream& outputFile) 
{
    
    std::vector<double> points ;
    std::vector<double> values ;
    double step = (end - start +1) / numPoints;

    for (size_t i = 0; i <= numPoints; i++) 
    {
        double x = start + i * step;
        points.push_back(x);
        values.push_back(std::exp(x));
    }

    CubicSpline<double, double> spline(points, values);
    points.clear();
    values.clear();

    double step1 = (end - start) / 1000;
    for (size_t i = 0; i < 1000; i++) 
    {
        double x = start + i * step1;
        points.push_back( x );
        double z = spline.interpolate(x);
        values.push_back( z );
    }

    

    for (size_t i = 0; i < points.size(); ++i) 
    {
        outputFile << points[i] << ", " << values[i] << std::endl;
    }
}







int main() {
    std::vector<double> points = {1,2,3,4,5,6,7,8,9,10};
    std::vector<double> values = {
    0.71828183,
    7.38905610,
    20.0855369,
    54.5981500,
    148.413159,
    403.428793,
    1096.63316,
    2980.95799,
    8103.08393,
    22026.4658
    };

    CubicSpline<double, double> spline(points, values);
    
    const auto& coeffs = spline.getCoefficients();


    
    std::ofstream outputFile("N2.txt");

    if (!outputFile) 
    {
        std::cerr << "Ошибка при создании файла!" << std::endl;
        return 1;
    }

    double intervals[1][2] = {{0, 10}};
    for (int i = 0; i < 1; ++i) 
    {
        double start = intervals[i][0];
        double end = intervals[i][1];
        size_t numPoints = 1e6;

        generateValues(start, end, numPoints, outputFile);
    }
    outputFile.close();




    for (size_t i = 0; i < coeffs.size(); ++i) 
    {
        std::cout << "Segment " << i << ": a = " << coeffs[i].a 
                  << ", b = " << coeffs[i].b 
                  << ", c = " << coeffs[i].c 
                  << ", d = " << coeffs[i].d << std::endl;
    }

    return 0;
}