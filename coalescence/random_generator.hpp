//
//  random_generator.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 18.07.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef random_generator_hpp
#define random_generator_hpp

#include <stdio.h>
#include <random>
#endif /* random_generator_hpp */
class random_generator{
    public:
        random_generator();
        virtual double exponential(double) = 0;
        virtual int uniform(int) = 0;
};


class random_random_generator: public random_generator{
public:
    random_random_generator();
    double exponential(double);
    int uniform(int);
};

class not_random_generator: public random_generator{
public:
    not_random_generator();
    double exponential(double);
    int uniform(int);
};
