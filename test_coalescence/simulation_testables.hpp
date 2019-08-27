//
//  simulation_testables.hpp
//  test_coalescence
//
//  Created by Frédéric Michaud on 27.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef simulation_testables_hpp
#define simulation_testables_hpp

#include <stdio.h>
#include "simulation.hpp"
#include "parameters_testables.hpp"
class simulation_testable: public simulation{
public:
    simulation_testable(parameters_testable* my_parameters):simulation(my_parameters){
        this->my_random_generator = new not_random_generator();
    };
    using simulation::get_patch_per_id;
    using simulation::perform_simulation_until;
};

#endif /* simulation_testables_hpp */
