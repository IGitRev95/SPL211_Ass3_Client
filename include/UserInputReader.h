//
// Created by spl211 on 26/12/2020.
//

#ifndef CLIENT_USERINPUTREADER_H
#define CLIENT_USERINPUTREADER_H


#include "Task.h"
#include "connectionHandler.h"
#include "Operation.h"
#include "OperationEncoderDecoder.h"

/**
 * This class is a task class which should be ran by a separate thread
 * The objective of the class is getting user commands and sending them to the server
 */

class UserInputReader: public Task {
private:
    ConnectionHandler &clientConnectionHandler;
    std::atomic_bool &terminate;
    std::atomic_bool &loggedIn;
public:
    /**
     * Constructor
     * @param clientConnectionHandler - connection handler for network communication functionalities
     * @param terminate - atomic bool which indicate termination
     * @param loggedIn - atomic bool which indicate that logging In has occurred
     */
    UserInputReader(ConnectionHandler &clientConnectionHandler,std::atomic_bool &terminate,std::atomic_bool &loggedIn);
    int run(); ////the "main" method to run in the thread
};


#endif //CLIENT_USERINPUTREADER_H
