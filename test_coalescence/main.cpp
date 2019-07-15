//
//  main.cpp
//  test_coalescence
//
//  Created by Frédéric Michaud on 11.07.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include <iostream>
#include "../coalescence/node.hpp"
#include "../coalescence/patch.hpp"
#include "../coalescence/tree.hpp"
#include "../coalescence/node.cpp"
#include "../coalescence/patch.cpp"
#include "../coalescence/tree.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
        patch my_patch1(10);
        patch my_patch2(10);
        double merging_time(0.2);
        my_patch1.coalesce_until(merging_time);
        my_patch2.coalesce_until(merging_time);
        my_patch1.merge_patch(&my_patch2, merging_time);
        my_patch1.coalesce_all_sample();
    REQUIRE( my_patch1.get_last_node()->get_id() == 38);
}

