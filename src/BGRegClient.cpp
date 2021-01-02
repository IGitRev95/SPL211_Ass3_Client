//
// Created by spl211 on 26/12/2020.
//
#include <stdlib.h>
#include <thread>
#include "../include/connectionHandler.h"
#include "../include/UserInputReader.h"


int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    std::atomic_bool terminate(false); // Indicator of termination for user keyboard listening thread
    std::atomic_bool loggedIn(false); // Indicator of LoggedIn status

    UserInputReader usrKeyboardInputs(connectionHandler, terminate, loggedIn); //User Input Handling Task
    std::thread usrKeyboardInputsThread(&UserInputReader::run, &usrKeyboardInputs); //User Input Handling Task Thread

    while (!terminate) {
        ReplyOp* answer= nullptr; //current answer holder
        if (!connectionHandler.getOp(&answer)) { // getting answer operation from server (bytes to Operation decoding included)
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        std::cout << answer->toString() << std::endl; //printing to user end

        if(answer->getOpCode()==12) //ACK which trigger extra consequences
        {
            switch (answer->getReplyOpOf()) {
                case 3: // ACK of logging in
                {
                    loggedIn=true;
                    break;
                }
                case 4: // ACK of logging out
                {
                    terminate=true; //signaling other thread to terminate
                    usrKeyboardInputsThread.join(); //waiting for it to terminate
                    break;
                }
                default: break;
            }
        }
        delete answer; //free the answer holder which allocated on the heap
    }
    return 0;
}
