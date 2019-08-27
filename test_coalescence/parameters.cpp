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
#include "simulation_testables.hpp"


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

// -en allows to change the size of the population during the simulation
//-en t i x ... Set subpop i size a new size x at time t
TEST_CASE( "We can parse the optional parameters -en") {
    int nb_param = 7;
    //working case
    double epsilon = 0.0000001;
    double eff_size = 0.25;
    int nb_individual = 10;
    double time_first_event = 2*eff_size/(nb_individual*(1+nb_individual));

    char nb_individual_string[100];
    snprintf(nb_individual_string, 100, "%d", nb_individual);
    char eff_size_string[100];
    snprintf(eff_size_string, 100, "%f", eff_size);
    const char *params1[] = {"programName",nb_individual_string,"15","-en","0.5","1",eff_size_string};
    parameters_testable my_parameters(nb_param, params1);
    REQUIRE(my_parameters.get_event(0)->get_time() < 0.6);
    REQUIRE(my_parameters.get_event(0)->get_time() > 0.45);
    simulation_testable my_simulation(&my_parameters);
    my_parameters.get_event(0)->update_simulation(&my_simulation);
    int nb_indi = my_simulation.get_patch_per_id(0)->get_sample().size();
    REQUIRE(nb_indi == 10);
    my_simulation.perform_simulation_until(time_first_event + epsilon);
    nb_indi = my_simulation.get_patch_per_id(0)->get_sample().size();
    REQUIRE(nb_indi == 9);
    
    //The number of coalescent event decrease if I don't decrease the population size.
    const char *params2[] = {"programName",nb_individual_string,"15"};
    my_parameters = parameters_testable(3, params2);
    my_simulation = simulation_testable(&my_parameters);
    nb_indi = my_simulation.get_patch_per_id(0)->get_sample().size();
    REQUIRE(nb_indi == 10);
    my_simulation.perform_simulation_until(time_first_event + epsilon);
    nb_indi = my_simulation.get_patch_per_id(0)->get_sample().size();
    REQUIRE(nb_indi == 10);
}
