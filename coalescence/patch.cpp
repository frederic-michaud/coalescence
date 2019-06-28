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
patch::patch(vector<node* > sample): sample(sample), effective_size(1.), current_time(0)
{
    nb_sample = sample.size();
    next_individual_id = nb_sample;
}

vector<node* > patch::get_sample() const{
    return(sample);
}

void patch::coalesce_two_node(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    uniform_int_distribution<int> distribution1(0,nb_sample -1);
    int ind1_index(distribution1(generator));
    node* ind1(sample[ind1_index]);
    sample.erase(sample.begin() + ind1_index);
    nb_sample--;
    uniform_int_distribution<int> distribution2(0,nb_sample -1);
    int ind2_index(distribution2(generator));
    node* ind2(sample[ind2_index]);
    sample.erase(sample.begin() + ind2_index);
    node* new_sample = new node(next_individual_id,current_time, ind1,ind2);
    sample.push_back(new_sample);
    next_individual_id++;

    
}

void patch::coalesce_all_node(){
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
    return(is_too_long);
}
