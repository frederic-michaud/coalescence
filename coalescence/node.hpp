//
//  node.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

class node{
private:
    double time;
    double total_time_under;
    int id;
    vector<node* > childrens;
    bool carry_mutation;
    void get_leaves(vector<node* > &leaves);
public:
    node(int id);
    node(int id, double time,node*, node*);
    double get_time() const;
    void set_time(double new_time);
    inline double get_total_time_under(){return total_time_under;}
    inline bool is_mutated(){return carry_mutation;}
    inline double get_time(){return time;}
    void mutate();
    int get_id() const;
    friend std::ostream& operator<< (std::ostream &out, const node &node);
    node* get_time_position(double time);
    node* get_time_position_with_time(double time, double &time_of_mutation);
    vector<node* > get_leaves();

};



#endif /* node_hpp */
