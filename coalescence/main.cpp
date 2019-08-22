//
//  main.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include <iostream>
#include "node.hpp"
#include "patch.hpp"
#include "event.hpp"
#include "simulation.hpp"
#include "tree.hpp"
using namespace std;




int main(int argc, const char * argv[]) {
    parameters* my_parameters;
    try{
        my_parameters = new parameters(argc, argv);
    }
    catch(const char* error){
        cerr << error;
        exit(1);
    }
    for (int index_sequence(0);index_sequence < my_parameters->get_nb_sequence();index_sequence++){
        simulation my_simulation(my_parameters);
        my_simulation.perform_simulation();
    }
    return 0;
}

