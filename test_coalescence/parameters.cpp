//
//  parameters.cpp
//  test_coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "catch.hpp"
#include "simulation.hpp"
#include "parameters_testables.hpp"
using Catch::Matchers::Contains;
TEST_CASE( "We can parse parameters") {
    int nb_param = 3;
    const char *params1[] = {"programName", "15"};
    const char *params2[] = {"programName", "15","21"};
    const char *params3[] = {"programName", "15","hello"};
    REQUIRE_THROWS_WITH(parameters(2, params1), Contains( "two arguments" ));
    REQUIRE_THROWS_WITH(parameters(3, params3), Contains( "stoi: no conversion" ));
    parameters_testable my_parameters(3, params2);
    REQUIRE(my_parameters.get_nb_deme() == 21);
    REQUIRE(my_parameters.get_nb_loci() == 15);

}

