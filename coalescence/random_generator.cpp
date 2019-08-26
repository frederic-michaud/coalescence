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
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = default_random_engine(seed);
}

random_generator::random_generator(){
    
}

double not_random_generator::exponential(double lambda){
    return(1/lambda);
}

int not_random_generator::uniform_int(int not_used){
    return(0);
}

double not_random_generator::uniform(double max){
    return(max/2);
}

double random_random_generator::exponential(double lambda){
    exponential_distribution<double> distrib_event(lambda);
    return bind(distrib_event, generator)(lambda);
}

int random_random_generator::uniform_int(int max){
    uniform_int_distribution<int> distribution1(0,max);
    return(distribution1(generator));
}

double random_random_generator::uniform(double max){
    uniform_real_distribution<> distribution1(0., max);
    return(distribution1(generator));
}
