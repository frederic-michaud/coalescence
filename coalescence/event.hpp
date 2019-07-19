//
//  event.hpp
//  coalescence
//
//  Created by Frédéric Michaud on 28.06.19.
//  Copyright © 2019 Frédéric Michaud. All rights reserved.
//

#ifndef event_hpp
#define event_hpp
class simulation;
#include <stdio.h>
class event {
private:
        double time;
public:
    inline double get_time(){return time;}
    event(double time);
    void update_parameters(simulation*);
    
};


#endif /* event_hpp */
