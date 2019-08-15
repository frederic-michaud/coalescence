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
protected:
        double time;
public:
    inline double get_time(){return time;}
    event(double time);
    virtual void update_simulation(simulation*);
    
};

class merging_event: public event {
private:
    unsigned int patch1_id;
    unsigned int patch2_id;
public:
    merging_event(unsigned int patch1_id, unsigned int patch2_id, double time);
    void update_simulation(simulation*);
};

#endif /* event_hpp */
