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
    random_generator* my_random_generator;
    void perform_simulation_until(double time);
    void perform_simulation_until_infinity();
public:
    simulation();
    simulation(vector<event >);
    inline random_generator* get_random_generator(){return my_random_generator;}
    void update_parameters();
    void perform_simulation();

    void add_patch(int nb_deme);
};
#endif /* simulation_hpp */
