/**
    @file
    @author  Alexander Sherikov

    @copyright 2024 Alexander Sherikov, Licensed under the Apache License,
    Version 2.0. (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#include "numdata/numdata.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>


void print_vector(const std::vector<double> &dv)
{
    for (const double d : dv)
    {
        std::cout << " " << d << "\n";
    }
    std::cout << std::endl;
}


int main()
{
    std::vector<double> dv = { 0.0,
                               std::numeric_limits<double>::infinity(),
                               std::numeric_limits<double>::quiet_NaN(),
                               std::numeric_limits<double>::min(),
                               std::numeric_limits<double>::max(),
                               1.0,
                               100000000000,
                               0.1111111,
                               0.000000000000001,
                               0.3000020000001 };


    std::cout << "numdata:" << std::endl;
    std::cout << numdata::On();
    print_vector(dv);
    std::cout << numdata::Off();


    std::cout << "default:" << std::endl;
    print_vector(dv);


    std::cout << "std::scientific:" << std::scientific << std::endl;
    print_vector(dv);
    std::cout << std::defaultfloat;


    std::cout << "std::setprecision:" << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::endl;
    print_vector(dv);
    std::cout << std::defaultfloat;


    std::cout << "std::showpoint + std::setprecision:" << std::showpoint << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::endl;
    print_vector(dv);
    std::cout << std::defaultfloat;
}
