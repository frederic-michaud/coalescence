//
//  node.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef node_hpp
#define node_hpp
using namespace std;
#include <stdio.h>
#include <vector>
#include <string>     // std::string, std::to_string

class node;
class node{
private:
    double time;
    double T_total_under;
    int id;
    vector<node* > childrens;
public:
    node(int id);
    node(int id, double time,node*, node*);
    double get_time() const;
    int get_id() const;
    friend std::ostream& operator<< (std::ostream &out, const node &node);
    
};



#endif /* node_hpp */
