//
//  node.cpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#include "node.hpp"
#include<string>
node::node(int id):time(0), id(id){
    
};
node::node(int id, double time, vector<node* > children):childrens(childrens),time(time),id(0)
{
    
}

node::node(int id, double time, node* node1, node* node2):time(time),id(id)
{
    vector<node *> temp;
    temp.push_back(node1);
    temp.push_back(node2);
    childrens = temp;
}


double node::get_time() const{
    return(time);
}



int node::get_id() const{
    return(id);
}


