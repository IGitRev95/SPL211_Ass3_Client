//
// Created by spl211 on 26/12/2020.
//

#ifndef CLIENT_USERINPUTREADER_H
#define CLIENT_USERINPUTREADER_H


#include "Task.h"
#include "connectionHandler.h"
#include "Operation.h"

class UserInputReader: public Task {
private:
    ConnectionHandler &clientConnectionHandler;
public:
    UserInputReader(ConnectionHandler &clientConnectionHandler);
    int run();
};


#endif //CLIENT_USERINPUTREADER_H
