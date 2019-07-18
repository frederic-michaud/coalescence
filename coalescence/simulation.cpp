//
//  simulation.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "simulation.hpp"

simulation::simulation(){
    
}

simulation::simulation(vector<event > History): all_events(History) {
    
}

void simulation::perform_simulation() {
    double time(0);
    for (event my_event : all_events){
        for (patch* my_patch : all_patches){
            my_patch->coalesce_until(time);
        }
    //update_parameters();
    //time = event.get_time();
    }
}


random_random_generator* simulation::get_random_generator(){
    return my_random_generator;
}
