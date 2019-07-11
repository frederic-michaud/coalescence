//
//  main.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include <iostream>
#include "node.hpp"
#include "patch.hpp"
#include "event.hpp"
#include "simulation.hpp"
#include "tree.hpp"
using namespace std;

ostream& operator<<(ostream& out, const node& my_node){
    out << to_string(my_node.get_id());
    if(my_node.childrens.size() == 2){
        out << "(" << *my_node.childrens[0] << ":" <<  my_node.time - (*my_node.childrens[0]).time << "," << *my_node.childrens[1]<< ":" <<  my_node.time - (*my_node.childrens[1]).time << ")";
    }
    return out;
}

ostream& operator<<(ostream& out, const patch& my_patch){
    vector<node* > all_sample(my_patch.get_sample());
    for (node* sample : all_sample){
        out << *sample;
    }
    return out;
}

int main(int argc, const char * argv[]) {
    patch my_patch1(10);
    patch my_patch2(10);
    my_patch1.coalesce_until(2);
    my_patch2.coalesce_until(2);
    my_patch1.merge_patch(&my_patch2, 2);
    my_patch1.coalesce_all_sample();
    tree my_tree(my_patch1.get_last_node());
    vector<node* > all_leave = my_patch1.get_last_node()->get_leaves();
    for (node* leave : all_leave){
        cout << leave->get_id() << endl;
    }
    my_tree.add_mutation();
    cout << my_patch1;
    return 0;
}
