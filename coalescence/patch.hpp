//
//  patch.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef patch_hpp
#define patch_hpp

#include <stdio.h>
#include "node.hpp"
class patch{
    private:
        vector<node* > all_sample;
        unsigned int nb_sample;
        double effective_size;
        double current_time;
        unsigned int next_individual_id;
        void coalesce_two_node();
    public:
        patch(unsigned int nb_sample);
        vector<node* > get_sample() const;
        void coalesce_all_sample();
        bool coalesce_until(double time);
        inline void set_effective_size(double Effective_size){effective_size = Effective_size;}
        void merge_patch(patch* external_patch, double merge_time);
        void shift_id(unsigned int shift);
    
    inline node* get_last_node(){return all_sample.back();}
};


#endif /* patch_hpp */
