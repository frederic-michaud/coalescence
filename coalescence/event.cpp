//
//  event.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "event.hpp"
#include "simulation.hpp"
using namespace std;

event::event(double time):time(time){
}

void event::update_simulation(simulation* my_simulation){
}

merging_event::merging_event(unsigned int patch1_id, unsigned int patch2_id, double time):
patch1_id(patch1_id), patch2_id(patch2_id),event(time){
}

void merging_event::update_simulation(simulation* my_simulation){
    my_simulation->merge_patch(patch1_id,patch2_id, time);
}

change_pop_size_event::change_pop_size_event(unsigned int patch_id, double new_size, double time):
patch_id(patch_id), new_size(new_size),event(time){
}

void change_pop_size_event::update_simulation(simulation* my_simulation){
    my_simulation->get_patch_per_id(patch_id)->set_effective_size(new_size);
}
