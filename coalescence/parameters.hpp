//
//  parameters.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
using namespace std;
#ifndef parameters_hpp
#define parameters_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
#include "event.hpp"

class parameters{
protected:
    vector <string> user_input;
    void parse();
    void parse_mandatory_argument();
    void parse_optional_argument();
    int parse_single_argument(int position_in_input);
    int parse_patch_size(int position_in_input);
    int parse_merge_event(int position_in_input);
    unsigned int nb_loci;
    unsigned int nb_individual;
    unsigned int nb_patch;
    vector<unsigned int> patch_sizes;
    vector<event* > all_events;
    
public:
    parameters(int argc, const char * argv[]);
    inline unsigned int get_nb_individual(){return nb_individual;}
    inline unsigned int get_nb_patch(){return nb_patch;}
    inline unsigned int get_patch_size(unsigned int patch_id){return patch_sizes[patch_id];}
    inline vector<event* > get_all_events(){return all_events;}
};

#endif /* parameters_hpp */
