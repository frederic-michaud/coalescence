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
    parse_mandatory_argument();
    parse_optional_argument();
}

void parameters::parse_mandatory_argument(){
  if(user_input.size() < 2){
      throw "At least two arguments should be provided";
  }
  try {
      nb_loci = stoi(user_input[0]);
      nb_deme = stoi(user_input[1]);
  } catch (const std::invalid_argument& ia) {
      throw "Invalid argument: the two first arguments should be integer\n";
  }
}

void parameters::parse_optional_argument(){
      int counter = 2;
      while(user_input.size() > counter){
          counter = parse_single_argument(counter);          
              }
}

int parameters::parse_single_argument(int position_in_input){
    if(user_input[position_in_input] == "-I"){
        if(user_input.size() < position_in_input + 1){
            throw "Invalid argument: -I should be followed by an integer giving the number of patch\n";
        }
        try {
            nb_patch = stoi(user_input[position_in_input + 1]);
        } catch (const std::invalid_argument& ia) {
            throw "Invalid argument: -I should be followed by an integer giving the number of patch\n";
        }
        if(user_input.size() < position_in_input + 2 + nb_patch){
            throw "Invalid argument: Not enough parameters provided to -I \n";
        }
        int nb_individual_in_all_patches = 0;
        for(int id_patch(0);id_patch < nb_patch;id_patch++){
            try{
                    int nb_individual_in_patch(stoi(user_input[position_in_input + 2 + id_patch]));
                    patch_sizes.push_back(nb_individual_in_patch);
                    nb_individual_in_all_patches +=nb_individual_in_patch;
                }
            catch (const std::invalid_argument& ia) {
                throw "Invalid argument: Not able to convert one of the patch size \n";
                }
        }
       if(nb_individual_in_all_patches != nb_deme){
           throw "Invalid argument: The sum of all individual in all patches should be equal to the total number of individual \n";
       }
      position_in_input += 2 + nb_patch;
    }
    return position_in_input;
}

