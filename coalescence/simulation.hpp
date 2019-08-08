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
#include "node.hpp"
#include <stdio.h>
#include "event.hpp"
#include <vector>
#include "random_generator.hpp"
#include "parameters.hpp"
class node;
class simulation{
private:
    parameters* my_parameters();
    vector<event > all_events;
    vector<patch* > all_patches;
    random_generator* my_random_generator;
    void perform_simulation_until(double time);
    void perform_simulation_until_infinity();
    unsigned int current_individual_id;
public:
    simulation();
    simulation(parameters* my_parameters);
    inline random_generator* get_random_generator(){return my_random_generator;}
    void update_parameters();
    void perform_simulation();
    node* get_new_node(double current_time, node* ind1,node* ind2);
    node* get_new_node();
    void add_patch(vector<node* > all_deme);
};
#endif /* simulation_hpp */
