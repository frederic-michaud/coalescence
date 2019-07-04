//
//  tree.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 04.07.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "tree.hpp"
#include <iostream>
using namespace std;


tree::tree(node* my_node):upper_node(my_node){
    total_tree_length = upper_node->get_total_time_under();
}


void tree::add_mutation(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<> dis(0., total_tree_length);
    double mutation_happening_at = dis(generator);
    node* where = upper_node->get_time_position(mutation_happening_at);
    cout << (*where) << endl;
    
}
