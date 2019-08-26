//
//  patch.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "patch.hpp"
#include "iostream"
#include "simulation.hpp"
using namespace std;



patch::patch(vector<node* > all_sample, simulation* Simulation, unsigned int id, double time): effective_size(1.), current_time(time),my_simulation(Simulation),all_sample(all_sample), id(id)
{
    nb_sample = all_sample.size();
}

vector<node* > patch::get_sample() const{
    return(all_sample);
}

void patch::coalesce_two_node(){
    int ind1_index = my_simulation->get_random_generator()->uniform_int(nb_sample - 1);
    node* ind1(all_sample[ind1_index]);
    all_sample.erase(all_sample.begin() + ind1_index);
    nb_sample--;
    int ind2_index(my_simulation->get_random_generator()->uniform_int(nb_sample - 1));
    node* ind2(all_sample[ind2_index]);
    all_sample.erase(all_sample.begin() + ind2_index);
    node* new_sample = my_simulation->get_new_node(current_time, ind1,ind2);
    all_sample.push_back(new_sample);
}

void patch::coalesce_all_sample(){
    while (nb_sample > 1)
    {
        double time_event(my_simulation->get_random_generator()->exponential((nb_sample*(nb_sample+1))/(2*effective_size)));
        current_time = current_time + time_event;
        coalesce_two_node();
    }
}

bool patch::coalesce_until(double time_limit){
    bool is_too_long = false;
    while (nb_sample > 1 &! is_too_long ){
        double time_event(my_simulation->get_random_generator()->exponential((nb_sample*(nb_sample+1))/(2*effective_size)));
        double new_time(current_time + time_event);
        is_too_long = new_time > time_limit;
        if (!is_too_long){
            current_time = new_time;
            coalesce_two_node();
        }
    }
    current_time = time_limit;
    return(is_too_long);
}

void patch::merge(patch* external_patch, double merging_time){
    for (node* sample : (*external_patch).all_sample){
        all_sample.push_back(sample);
    }
    nb_sample = all_sample.size();
}

