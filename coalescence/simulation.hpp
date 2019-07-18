//
//  simulation.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
using namespace std;

#ifndef simulation_hpp
#define simulation_hpp
#include "patch.hpp"
#include <stdio.h>
#include "event.hpp"
#include <vector>

#include "random_generator.hpp"
class simulation{
private:
    vector<event > all_events;
    vector<patch* > all_patches;
    random_random_generator* my_random_generator;
public:
    simulation();
    simulation(vector<event >);
    random_random_generator* get_random_generator();
    void update_parameters();
    void perform_simulation();
};
#endif /* simulation_hpp */
