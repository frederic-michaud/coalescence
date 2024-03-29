//
//  parameters.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef parameters_hpp
#define parameters_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
#include "event.hpp"
#include <numeric>
using namespace std;
class parameters{
protected:
    vector <string> user_input;
    void parse();
    void parse_mandatory_argument();
    void parse_optional_argument();
    void parse_single_argument(vector<string >  argument);
    void parse_patch_size(vector<string >  argument);
    void parse_merge_event(vector<string >  argument);
    void parse_initial_time(vector<string >  argument);
    void parse_change_size(vector<string >  argument);
    //argument to be saved
    unsigned int nb_sequence;
    unsigned int nb_individual;
    unsigned int nb_patch;
    vector<unsigned int> patch_sizes;
    bool is_given_patch_initial_times;
    vector<double > patch_initial_times;
    vector<event* > all_events;
    //validate that all parameters are consistent. 
    void validate();
    void order_event();
public:
    parameters(int argc, const char * argv[]);
    inline unsigned int get_nb_individual(){return nb_individual;}
    const inline unsigned int get_nb_patch(){return nb_patch;}
    const inline unsigned int get_patch_size(unsigned int patch_id){return patch_sizes[patch_id];}
    const inline double get_patch_initial_time(unsigned int patch_id){return patch_initial_times[patch_id];}
    const inline int get_nb_sequence(){return nb_sequence;}
    inline vector<event* > get_all_events(){return all_events;}
};

#endif /* parameters_hpp */
