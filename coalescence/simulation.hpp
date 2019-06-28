//
//  simulation.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
using namespace std;
#ifndef simulation_hpp
#define simulation_hpp

#include <stdio.h>
#include "event.hpp"
#include <vector>
class simulation{
private:
    vector<event > history;
public:
    simulation();
    simulation(vector<event >);
};
#endif /* simulation_hpp */
