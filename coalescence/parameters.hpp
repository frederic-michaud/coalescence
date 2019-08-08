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


class parameters{
protected:
    vector <string> user_input;
    void parse();
    unsigned int nb_loci;
    unsigned int nb_deme;
public:
    parameters(int argc, const char * argv[]);
    inline unsigned int get_nb_deme(){return nb_deme;}
};

#endif /* parameters_hpp */
