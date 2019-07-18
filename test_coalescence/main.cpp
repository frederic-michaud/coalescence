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


TEST_CASE( "We can merge patch") {
        patch my_patch1(10);
        patch my_patch2(10);
        my_patch1.merge_patch(&my_patch2, 0);
        REQUIRE(my_patch1.get_last_node()->get_id() == 19);
}

