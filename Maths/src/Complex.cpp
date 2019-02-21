/**
 * @file EliminationSet.h
 * @ingroup cad
 * @author Gereon Kremer <gereon.kremer@cs.rwth-aachen.de>
 */

#include <Complex.hpp>
#include <dataTypesdef/dataTypedef.hpp>
#include <iostream>

using namespace dvsim::math;

Complex::~Complex() { std::cout << " Destruction " << std::endl; }

Real Complex::norm(const Complex c) {
  Real value = c.real * c.real + c.Imaginary * c.Imaginary;
  return value;
}
void Complex::display() {
  std::cout << this->real << "+" << this->Imaginary << "i" << std::endl;
}

Complex::Complex(const Complex &complex) {
  real = complex.real;
  Imaginary = complex.Imaginary;
}