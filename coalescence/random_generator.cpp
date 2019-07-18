//
//  random_generator.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 18.07.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
using namespace std;
#include "random_generator.hpp"

not_random_generator::not_random_generator(){
    
}

random_random_generator::random_random_generator(){
    
}

random_generator::random_generator(){
    
}

double not_random_generator::exponential(double lambda){
    return(1/lambda);
}

int not_random_generator::uniform(int not_used){
    return(0);
}


double random_random_generator::exponential(double lambda){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    exponential_distribution<double> distrib_event(lambda);
    return(distrib_event(generator));
}

int random_random_generator::uniform(int max){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    uniform_int_distribution<int> distribution1(0,max);
    return(distribution1(generator));
}
