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

event::event(){
}

void event::update_simulation(simulation* my_simulation){
}

merging_event::merging_event(unsigned int patch1_id, unsigned int patch2_id, double time):
patch1_id(patch1_id), patch2_id(patch2_id),time(time){
}

void merging_event::update_simulation(simulation* my_simulation){
    my_simulation->merge_patch(patch1_id,patch2_id, time);
}
