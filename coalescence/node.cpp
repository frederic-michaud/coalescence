//
//  node.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//
using namespace std;
#include "node.hpp"
#include<string>
#include<vector>
#include<iostream>

node::node(int id):time(0), id(id),total_time_under(0),carry_mutation(false){
    
};

node::node(int id, double time, node* node1, node* node2):time(time),id(id),carry_mutation(false)
{
    vector<node *> temp;
    temp.push_back(node1);
    temp.push_back(node2);
    double T_total_under_right = (time - (*node1).time) + (*node1).total_time_under;
    double T_total_under_left = (time - (*node2).time) + (*node2).total_time_under;
    total_time_under = T_total_under_left + T_total_under_right;
    childrens = temp;
}


double node::get_time() const{
    return(time);
}



int node::get_id() const{
    return(id);
}


void node::shift_id(unsigned int shift){
    id+=shift;
    for (node* children : childrens){
        children->shift_id(shift);
    }
}

node* node::get_time_position(double time_given){
    node* output_node = NULL;
    if(childrens.size() == 0){
        cout << "something strange is going on" << endl;
        return this;
    }
    double length_left_branche = time - (*childrens[0]).time;
    double length_left_tree(length_left_branche+  (*childrens[0]).total_time_under);
    double length_right_branche = time - (*childrens[1]).time;
    if(time_given < length_left_branche) output_node = childrens[0];
    else if(time_given < length_left_tree) output_node = childrens[0]->get_time_position(time_given - length_left_branche);
    else if(time_given < length_left_tree + length_right_branche ) output_node = childrens[1];
    else output_node = childrens[1]->get_time_position(time_given - (length_left_tree + length_right_branche));
    return output_node;
}

void node::mutate(){
    carry_mutation = true;
    for (node* children : childrens){
        children->mutate();
    }
}

vector<node* > node::get_leaves(){
    vector<node* > all_leaves;
    if(childrens.size() ==0){
        all_leaves.push_back(this);
    }
    else{
        for (node* children : childrens){
            children->get_leaves(all_leaves);
        }
    }
    return all_leaves;
}

void node::get_leaves(vector<node* > &all_leaves){
    if(childrens.size() ==0){
        all_leaves.push_back(this);
    }
    else{
        for (node* children : childrens){
            children->get_leaves(all_leaves);
        }
    }
}
