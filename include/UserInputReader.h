//
// Created by spl211 on 26/12/2020.
//

#ifndef CLIENT_USERINPUTREADER_H
#define CLIENT_USERINPUTREADER_H


#include "Task.h"
#include "connectionHandler.h"
#include "Operation.h"
#include "OperationEncoderDecoder.h"

class UserInputReader: public Task {
private:
    ConnectionHandler &clientConnectionHandler;
    std::atomic_bool &terminate;
    std::atomic_bool &logedIn;
public:
    UserInputReader(ConnectionHandler &clientConnectionHandler,std::atomic_bool &terminate,std::atomic_bool &logedIn);
    int run();
};


#endif //CLIENT_USERINPUTREADER_H
