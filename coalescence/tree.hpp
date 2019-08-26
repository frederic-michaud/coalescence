//
//  tree.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 04.07.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include "node.hpp"
#include <random>
#include "simulation.hpp"
class simulation;
using namespace std;
class tree{
private:
    node* upper_node;
    double total_tree_length;
    simulation* my_simulation;
public:
    tree(node* my_node, simulation* my_simulation);
    void add_mutation();
};

#endif /* tree_hpp */
