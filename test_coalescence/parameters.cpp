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
TEST_CASE( "We can parse mandatory parameters") {
    int nb_param = 3;
    const char *params1[] = {"programName", "15"};
    const char *params2[] = {"programName", "21","15"};
    const char *params3[] = {"programName", "15","hello"};
    REQUIRE_THROWS_WITH(parameters(2, params1), Contains( "two arguments" ));
    REQUIRE_THROWS_WITH(parameters(3, params3), Contains( "the two first arguments should be integer" ));
    parameters_testable my_parameters(3, params2);
    REQUIRE(my_parameters.get_nb_deme() == 21);
    REQUIRE(my_parameters.get_nb_loci() == 15);
}

TEST_CASE( "We can parse the optional parameters -I") {
    int nb_param = 7;
    //working case
    const char *params1[] = {"programName", "12","15","-I","2","5","7"};
    parameters_testable my_parameters(nb_param, params1);
    REQUIRE(my_parameters.get_nb_patch() == 2);
    REQUIRE(my_parameters.get_patch_size(0) == 5);
    REQUIRE(my_parameters.get_patch_size(1) == 7);
    //Failing case
    const char *params2[] = {"programName", "12","15","-I","2","7","7"};
    REQUIRE_THROWS_WITH(parameters(nb_param, params2), Contains( "The sum of all individual"));
    const char *params3[] = {"programName", "12","15","-I"};
    REQUIRE_THROWS_WITH(parameters(4, params3), Contains( " -I should be followed by an integer"));
    const char *params4[] = {"programName", "12","15","-I","hey"};
    REQUIRE_THROWS_WITH(parameters(5, params4), Contains( " -I should be followed by an integer"));
    const char *params5[] = {"programName", "12","15","-I","2","1"};
    REQUIRE_THROWS_WITH(parameters(6, params5), Contains( "Not enough parameters provided"));
    const char *params6[] = {"programName", "12","15","-I","2"};
    REQUIRE_THROWS_WITH(parameters(5, params6), Contains( "Not enough parameters provided"));
    const char *params7[] = {"programName", "12","15","-I","2","7","hey"};
    REQUIRE_THROWS_WITH(parameters(nb_param, params7), Contains( "Not able to convert one of the patch size"));
}

// -it allows to change the initial time of each patch.
TEST_CASE( "We can parse the optional parameters -it") {
    int nb_param = 10;
    //working case
    const char *params1[] = {"programName", "12","15","-I","2","5","7","-it","0.5","0.2"};
    parameters_testable my_parameters(nb_param, params1);
    REQUIRE(my_parameters.get_nb_patch() == 2);
    REQUIRE(my_parameters.get_patch_initial_time(0) == 0.5);
    REQUIRE(my_parameters.get_patch_initial_time(1) == 0.2);
    //Failing case
    nb_param = 9;
    const char *params2[] = {"programName", "12","15","-I","2","5","7","-it","0.5"};
    REQUIRE_THROWS_WITH(parameters(nb_param, params2), Contains( "The number of time provided in -it"));

}


//-ej t id1 id2 ... merging time between patch move id1 to id2
TEST_CASE( "The events are well ordered") {
    int nb_param = 16;
    //All ready ordered in input
    const char *params1[] = {"programName", "15","10","-I","3","5","5","5","-ej","0.5","1","2","-ej","0.6","3","2"};
    parameters_testable my_parameters(nb_param, params1);
    REQUIRE(my_parameters.get_event(0)->get_time() < my_parameters.get_event(1)->get_time());
    //not ordered in input
    const char *params2[] = {"programName", "15","10","-I","3","5","5","5","-ej","0.5","1","2","-ej","0.6","3","2"};
    parameters_testable my_parameters2(nb_param, params2);
    REQUIRE(my_parameters.get_event(0)->get_time() < my_parameters.get_event(1)->get_time());
    
}
