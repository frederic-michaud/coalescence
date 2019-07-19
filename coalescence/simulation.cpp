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
    add_patch(20);
    my_random_generator = new random_random_generator();
}

simulation::simulation(vector<event > events): all_events(events) {
    add_patch(20);
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

random_generator* simulation::get_random_generator(){
    return my_random_generator;
}

void simulation::add_patch(int nb_deme){
    all_patches.push_back(new patch(nb_deme,this));
}
