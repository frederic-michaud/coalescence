//
//  patch.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "patch.hpp"
#include <random>
#include "iostream"
using namespace std;

patch::patch(unsigned int nb_sample): effective_size(1.), current_time(0),nb_sample(nb_sample)
{
    for (int i(0);i< nb_sample;i++){
        node* a = new node(i);
        all_sample.push_back(a);
    }
    all_leave = all_sample;
    next_individual_id = nb_sample;
}

vector<node* > patch::get_sample() const{
    return(all_sample);
}

void patch::coalesce_two_node(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    uniform_int_distribution<int> distribution1(0,nb_sample -1);
    int ind1_index(distribution1(generator));
    node* ind1(all_sample[ind1_index]);
    all_sample.erase(all_sample.begin() + ind1_index);
    nb_sample--;
    uniform_int_distribution<int> distribution2(0,nb_sample -1);
    int ind2_index(distribution2(generator));
    node* ind2(all_sample[ind2_index]);
    all_sample.erase(all_sample.begin() + ind2_index);
    node* new_sample = new node(next_individual_id,current_time, ind1,ind2);
    all_sample.push_back(new_sample);
    next_individual_id++;

    
}

void patch::coalesce_all_sample(){
    while (nb_sample > 1)
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator (seed);
        exponential_distribution<double> distrib_event((nb_sample*(nb_sample+1))/(2*effective_size));
        double time_event = distrib_event(generator);
        current_time = current_time + time_event;
        coalesce_two_node();
    }
}

bool patch::coalesce_until(double time_limit){
    bool is_too_long = false;
    while (nb_sample > 1 &! is_too_long ){
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator (seed);
        exponential_distribution<double> distrib_event((nb_sample*(nb_sample+1))/(2*effective_size));
        double time_event = distrib_event(generator);
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

void patch::merge_patch(patch* external_patch, double merging_time){
    external_patch->shift_id(next_individual_id);
    next_individual_id = (*external_patch).next_individual_id;
    for (node* sample : (*external_patch).all_sample){
        all_sample.push_back(sample);
    }
    for (node* leave : (*external_patch).all_leave){
        all_leave.push_back(leave);
    }
    nb_sample = all_sample.size();
    
}

void patch::shift_id(unsigned int shift)
{
    for (node* sample : all_sample){
        sample->shift_id(shift);
    }
    next_individual_id += shift;
}

vector<bool > patch::get_genotype(){
    vector<bool > genotype;
    for (node* leave : this->get_leaves()){
        genotype.push_back(leave->is_mutated());
    }
    return genotype;
}

vector<node* > patch::get_leaves(){
    return(all_leave);
}
