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
    //creating all final node and putting them in the leave vector
    leave = vector<node* >();
    for(int i(0);i < my_parameters->get_nb_individual(); i++){
        leave.push_back(get_new_node());
    }
    //adding all the node in the patch where they belong
    int id_first_individual_of_patch(0);
    for(int patch_id(0); patch_id < my_parameters->get_nb_patch();patch_id++){
        int patch_dimension = my_parameters->get_patch_size(patch_id);
        int id_last_individual_of_patch(id_first_individual_of_patch + patch_dimension);
        vector<node* >::const_iterator first = leave.begin() + id_first_individual_of_patch;
        vector<node* >::const_iterator last = leave.begin() + id_last_individual_of_patch;
        vector<node* > all_node(first, last);
        all_patches.push_back(new patch(all_node, this, patch_id));
    }
    all_active_patches = all_patches;
    my_random_generator = new random_random_generator();
}

void simulation::perform_simulation() {
    cout << "starting simulation" << endl;
    double time(0);
    all_events.push_back(new merging_event(0,1,0.5));
    for (event* my_event : all_events){
        time = my_event->get_time();
        perform_simulation_until(time);
        my_event->update_simulation(this);
    }
    perform_simulation_until_infinity();
    tree my_tree(all_active_patches.front()->get_last_node());
    my_tree.add_mutation();
    print_genotype();
}

void simulation::perform_simulation_until(double time){
    for (patch* my_patch : all_active_patches){
        my_patch->coalesce_until(time);
    }
}

void simulation::perform_simulation_until_infinity(){
    for (patch* my_patch : all_active_patches){
        my_patch->coalesce_all_sample();
    }
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

void simulation::merge_patch(unsigned int patch1_id, unsigned int patch2_id, double time)
{
    patch* patch1 = get_patch_per_id(patch1_id);
    patch* patch2 = get_patch_per_id(patch2_id);
    patch1->merge(patch2, time);
    remove_from_activ_patch(patch2_id);
}

patch* simulation::get_patch_per_id(unsigned int patch_id){
    patch* correct_patch =NULL;
    for (patch* my_patch : all_patches){
        if (my_patch->get_id() == patch_id){
            correct_patch = my_patch;
        }
    }
    return correct_patch;
}

void simulation::remove_from_activ_patch(unsigned int patch_id){
    patch* patch_to_remove = get_patch_per_id(patch_id);
    all_active_patches.remove(patch_to_remove);
}


vector<bool > simulation::get_genotype(){
    vector<bool > genotype;
    for (node* leave : leave){
        genotype.push_back(leave->is_mutated());
    }
    return genotype;
}

void simulation::print_genotype(){
    
    for (node* leave : leave){
        cout << leave->is_mutated();
    }
    cout << endl;
}
