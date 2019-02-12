#include "../include/dataTypesdef/dataTypedef.hpp"
#include "../include/Complex.hpp"
#include <iostream>


using namespace dvsim::math;

Complex::~Complex()
{
    std::cout <<" Destruction "<<std::endl ;
}

Real Complex::norm(const Complex c)
{
    Real value = c.real * c.real + c.Imaginary * c.Imaginary ;
    return value ;
}
void Complex::display()
{
    std::cout <<this->real<<"+"<<this->Imaginary<<"i"<<std::endl;
}