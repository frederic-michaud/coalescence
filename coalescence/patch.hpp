//
//  patch.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//



#ifndef patch_hpp
#define patch_hpp
class simulation;
class random_random_generator;
#include <stdio.h>
#include "node.hpp"

class patch{
    private:
        simulation* my_simulation;
        vector<node* > all_sample;
        unsigned int nb_sample;
        double effective_size;
        double current_time;
        void coalesce_two_node();
        unsigned int id;
    public:
        patch(vector<node* > all_sample, simulation* my_simulation, unsigned int id);
        vector<node* > get_sample() const;
        void coalesce_all_sample();
        bool coalesce_until(double time);
        inline void set_effective_size(double Effective_size){effective_size = Effective_size;}
        void merge(patch* external_patch, double merge_time);
        void shift_id(unsigned int shift);
        vector<node* > get_all_leave();
        inline node* get_last_node(){return all_sample.back();}
        inline int get_id(){return id;}
};


#endif /* patch_hpp */
