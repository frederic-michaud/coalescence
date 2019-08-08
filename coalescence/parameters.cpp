//
//  parameters.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
#include "parameters.hpp"


parameters::parameters(int argc, const char * argv[]){
    user_input = vector<string >();
    for (int i = 1; i < argc; ++i) {
            user_input.push_back(argv[i]);
    }

    parse();
}
void parameters::parse(){
    if(user_input.size() < 2){
        throw "At least two arguments should be provided";
    }
    try {
        nb_loci = stoi(user_input[0]);
        nb_deme = stoi(user_input[1]);
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: the two first arguments should be integer\n";
        throw ia;
    }
}
