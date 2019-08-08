//
//  simulation.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "simulation.hpp"
#include <iostream>

ostream& operator<<(ostream& out, const patch& my_patch){
    vector<node* > all_sample(my_patch.get_sample());
    for (node* sample : all_sample){
        out << *sample;
    }
    return out;
}

simulation::simulation(){
    my_random_generator = new random_random_generator();
}

simulation::simulation(parameters* my_parameters){

    vector<node* > leave = vector<node* >();
    for(int i(0);i < my_parameters->get_nb_deme(); i++){
        leave.push_back(get_new_node());
    }
    all_patches.push_back(new patch(leave, this));
    my_random_generator = new random_random_generator();
}

void simulation::perform_simulation() {
    cout << "starting simulation" << endl;
    double time(0);
    for (event my_event : all_events){
        time = my_event.get_time();
        perform_simulation_until(time);
        my_event.update_parameters(this);
    }
    perform_simulation_until_infinity();
    cout << *all_patches[0] << endl;
}

void simulation::perform_simulation_until(double time){
    for (patch* my_patch : all_patches){
        my_patch->coalesce_until(time);
    }
}

void simulation::perform_simulation_until_infinity(){
    for (patch* my_patch : all_patches){
        my_patch->coalesce_all_sample();
    }
}

void simulation::add_patch(vector<node* > all_deme){
    all_patches.push_back(new patch(all_deme, this));
}

node* simulation::get_new_node(double current_time, node* ind1, node* ind2){
    node* new_deme = new node(current_individual_id, current_time, ind1, ind2);
    current_individual_id++;
    return new_deme;
}

node* simulation::get_new_node(){
    node* new_deme = new node(current_individual_id);
    current_individual_id++;
    return new_deme;
}
