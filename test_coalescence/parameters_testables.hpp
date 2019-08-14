//
//  parameters_testables.hpp
//  test_coalescence
//
//  Created by Frédéric Michaud on 08.08.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef parameters_testables_hpp
#define parameters_testables_hpp

#include <stdio.h>
#include "parameters.hpp"
class parameters_testable: public parameters{
    public:
    using parameters::parameters;
    inline unsigned int get_nb_loci(){return nb_loci;}
    inline unsigned int get_nb_deme(){return nb_individual;}
};
#endif /* parameters_testables_hpp */
