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


tree::tree(node* my_node,simulation* my_simulation):upper_node(my_node),my_simulation(my_simulation){
    total_tree_length = upper_node->get_total_time_under();
}


void tree::add_mutation(){
    double mutation_happening_at = my_simulation->get_random_generator()->uniform(total_tree_length);
    double when(0);
    node* where = upper_node->get_time_position_with_time(mutation_happening_at, when);
  //  cout << when << " ";
    where->mutate();
}
