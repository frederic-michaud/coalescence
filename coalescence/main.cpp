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
    for (auto sample : all_sample){
        out << *sample;
    }
    return out;
}

int main(int argc, const char * argv[]) {
    vector<node* > all_sample;
    int nb_element = 50;
    for (int i(0);i< nb_element;i++){
        node* a = new node(i);
        all_sample.push_back(a);
    }
    patch my_patch(all_sample);
    //cout << my_patch;
    my_patch.coalesce_all_node();
    cout << my_patch;
    return 0;
}
