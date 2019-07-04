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
    double total_time_under;
    int id;
    vector<node* > childrens;
public:
    node(int id);
    node(int id, double time,node*, node*);
    double get_time() const;
    inline double get_total_time_under(){return total_time_under;}
    int get_id() const;
    friend std::ostream& operator<< (std::ostream &out, const node &node);
    void shift_id(unsigned int shift);
    node* get_time_position(double time);
};



#endif /* node_hpp */
