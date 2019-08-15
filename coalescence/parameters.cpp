//
//  parameters.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
#include "parameters.hpp"


parameters::parameters(int argc, const char * argv[]):nb_patch(1){
    user_input = vector<string >();
    for (int i = 1; i < argc; ++i) {
            user_input.push_back(argv[i]);
    }
    parse();
    if(nb_patch == 1){
        patch_sizes.push_back(nb_individual);
    }
}

void parameters::parse(){
    parse_mandatory_argument();
    parse_optional_argument();
}

void parameters::parse_mandatory_argument(){
  if(user_input.size() < 2){
      throw "At least two arguments should be provided";
  }
  try {
      nb_loci = stoi(user_input[0]);
      nb_individual = stoi(user_input[1]);
  } catch (const std::invalid_argument& ia) {
      throw "Invalid argument: the two first arguments should be integer\n";
  }
}

void parameters::parse_optional_argument(){
    vector<int > position_argument;
    for(int counter(2);counter < user_input.size();counter++){
        if (user_input[counter][0] == "-"[0]) position_argument.push_back(counter);
    }
    int nb_argument = position_argument.size();
    position_argument.push_back(user_input.size());
    for(int index_argument(0); index_argument < nb_argument;index_argument++){
        auto first = user_input.begin() + position_argument[index_argument];
        auto last =  user_input.begin() + position_argument[index_argument + 1];
        vector<string > specific_argument(first, last);
        parse_single_argument(specific_argument);
    }
}

void parameters::parse_single_argument(vector<string >  argument){
    if(argument[0] == "-I"){
        parse_patch_size(argument);
    }
    if(argument[0]== "-ej"){
        parse_merge_event(argument);
    }

}
//-I nb_patch n1 n2 n3 ...
void parameters::parse_patch_size(vector<string >  argument){
    if(argument.size() < 2){
        throw "Invalid argument: -I should be followed by an integer giving the number of patch\n";
    }
    try {
        nb_patch = stoi(argument[1]);
    } catch (const std::invalid_argument& ia) {
        throw "Invalid argument: -I should be followed by an integer giving the number of patch\n";
    }
    if(argument.size() <  2 + nb_patch){
        throw "Invalid argument: Not enough parameters provided to -I \n";
    }
    int nb_individual_in_all_patches = 0;
    for(int id_patch(0);id_patch < nb_patch;id_patch++){
        try{
            int nb_individual_in_patch(stoi(argument[2 + id_patch]));
            patch_sizes.push_back(nb_individual_in_patch);
            nb_individual_in_all_patches +=nb_individual_in_patch;
        }
        catch (const std::invalid_argument& ia) {
            throw "Invalid argument: Not able to convert one of the patch size \n";
        }
    }
    if(nb_individual_in_all_patches != nb_individual){
        throw "Invalid argument: The sum of all individual in all patches should be equal to the total number of individual \n";
    }
    
}

//-ej t id1 id2
void parameters::parse_merge_event(vector<string >  argument){
    double time = stof(argument[1]);
    unsigned int patch1_id = stoi(argument[2]);
    unsigned int patch2_id = stoi(argument[3]);
    merging_event* my_event = new merging_event(patch1_id, patch2_id, time);
    all_events.push_back(my_event);
}
