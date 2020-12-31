//
// Created by spl211 on 26/12/2020.
//

#ifndef CLIENT_TASK_H
#define CLIENT_TASK_H

#include <thread>

class Task {
protected:
    virtual int run()=0;
    virtual ~Task()=default;

};


#endif //CLIENT_TASK_H
