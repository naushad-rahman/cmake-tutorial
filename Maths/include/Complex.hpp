#include "dataTypesdef/dataTypedef.hpp"

namespace dvsim
{
    namespace math
    {
        inline namespace DVSIM_MATH_VERSION_NAMESPACE
        {

            class Complex
            {
            private:
                /* data */

                Real real ;
                Real Imaginary ;
            public:
                Complex(/* args */):real(0.0),Imaginary(0.0){};
                 Complex(Real real , Real Imaginary):real(real),Imaginary(Imaginary){};
                ~Complex();

                Real norm(const Complex);
                void display();
            };
            
        }
    }
}