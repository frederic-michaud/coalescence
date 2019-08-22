//
//  parameters.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
#include "parameters.hpp"

parameters::parameters(int argc, const char * argv[]):nb_patch(1),is_given_patch_initial_times(false){
    user_input = vector<string >();
    for (int i = 1; i < argc; ++i) {
            user_input.push_back(argv[i]);
    }
    parse();
    if(nb_patch == 1){
        patch_sizes.push_back(nb_individual);
    }
    if(!is_given_patch_initial_times){
        patch_initial_times = vector<double >(nb_patch, 0.);
    }
    validate();
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
      nb_individual = stoi(user_input[0]);
      nb_sequence = stoi(user_input[1]);
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
    if(argument[0]== "-it"){
        parse_initial_time(argument);
    }

}
//-I nb_patch n1 n2 n3 ... number of individual per patch
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

//-ej t id1 id2 ... merging time between patch move id1 to id2
void parameters::parse_merge_event(vector<string >  argument){
    double time = stof(argument[1]);
    unsigned int patch1_id = stoi(argument[3]) - 1; //user interface should label patch from 1 to n, while inner code has it from 0 to n-1
    unsigned int patch2_id = stoi(argument[2]) - 1;
    merging_event* my_event = new merging_event(patch2_id, patch1_id, time);
    all_events.push_back(my_event);
}

//-it t1 t2 t3 ( the various time, looking backward in time, at which the patch appear)
void parameters::parse_initial_time(vector<string >  argument){
    is_given_patch_initial_times = true;
    for (int argument_index(1);argument_index < argument.size();argument_index++){
        try {
            double time = stod(argument[argument_index]);
            patch_initial_times.push_back(time);
        } catch (const std::invalid_argument& ia) {
            throw "Invalid argument: -it should be followed by a set of float number \n";
        }
    }
}


void parameters::validate(){
    int nb_individual_in_all_patches = accumulate(patch_sizes.begin(),patch_sizes.end(),0);
    if(nb_individual_in_all_patches != nb_individual){
        throw "Invalid argument: The sum of all individual in all patches should be equal to the total number of individual \n";
    }
    if(patch_initial_times.size() != nb_patch){
        throw "Invalid argument: The number of time provided in -it should be the same as the number of patch \n";
    }
}
