/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include <dvsimMath/Complex.hpp>

using namespace std::literals;

using namespace dvsim::math;

    TEST(xvariant, basic)
    {

        EXPECT_EQ(1,1);
        // xtl::variant<int, float> v, w;
        // v = 12;
        // int i = xtl::get<int>(v);
        // EXPECT_EQ(12, i);

        // w = xtl::get<int>(v);
        // EXPECT_EQ(12, xtl::get<int>(w));
        // w = xtl::get<0>(v);
        // EXPECT_EQ(12, xtl::get<int>(w));
        // w = v;
        // EXPECT_EQ(12, xtl::get<int>(w));
    }

    

