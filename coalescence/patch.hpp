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
        vector<node* > sample;
        unsigned int nb_sample;
        double effective_size;
        double current_time;
        unsigned int next_individual_id;
        void coalesce_two_node();
    public:
        patch(vector<node* > sample);
        vector<node* > get_sample() const;
        void coalesce_all_node();
        bool coalesce_until(double time);
        inline void set_effective_size(double Effective_size){effective_size = Effective_size;}
};


#endif /* patch_hpp */
