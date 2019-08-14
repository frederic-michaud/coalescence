//
//  main.cpp
//  test_coalescence
//
//  Created by Frédéric Michaud on 11.07.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include <iostream>
#include "patch.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "simulation.hpp"

TEST_CASE( "We can merge patch") {
    simulation* my_simulation = new simulation();
        /*patch my_patch1(10, my_simulation);
        patch my_patch2(10, my_simulation);
        my_patch1.merge(&my_patch2, 0);
        REQUIRE(my_patch1.get_last_node()->get_id() == 19);*/
}

