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
#include "tree.hpp"
#include "patch.hpp"
#include "node.hpp"
#include <stdio.h>
#include "event.hpp"
#include <vector>
#include <list>
#include "random_generator.hpp"
#include "parameters.hpp"
class node;
class simulation{
    friend class merging_event;
    friend class change_pop_size_event;
protected:
    vector<node* > leave;
    parameters* my_parameters();
    vector<event* > all_events;
    list<patch* > all_patches;
    list<patch* > all_active_patches;
    random_generator* my_random_generator;
    void perform_simulation_until(double time);
    void perform_simulation_until_infinity();
    unsigned int current_individual_id;
    void merge_patch(unsigned int patch1_id,unsigned int patc2_id, double time);
    patch* get_patch_per_id(unsigned int patch_id);
    void remove_from_activ_patch(unsigned int patch_id);
public:
    simulation();
    simulation(parameters* my_parameters);
    inline random_generator* get_random_generator(){return my_random_generator;}
    void update_parameters();
    void perform_simulation();
    node* get_new_node(double current_time, node* ind1,node* ind2);
    node* get_new_node();
    vector<bool >get_genotype();
    void print_genotype();
};
#endif /* simulation_hpp */
