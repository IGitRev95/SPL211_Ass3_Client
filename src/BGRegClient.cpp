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

    std::atomic_bool terminate(false);
    std::atomic_bool logedIn(false);

    UserInputReader usrKeyboardInputs(connectionHandler,terminate,logedIn); //User Input Handling Task
    std::thread usrKeyboardInputsThread(&UserInputReader::run, &usrKeyboardInputs); //User Input Handling Task Thread


    // TODO:check for terminate / interrupt configuration & solution
    while (!terminate) {
        ReplyOp* answer= nullptr;
        if (!connectionHandler.getOp(&answer)) { // getting answer string from server (bytes to Operation decoding included)
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        std::cout << answer->toString() << std::endl;

        if(answer->getOpCode()==12)
        {
            switch (answer->getReplyOpOf()) {
                case 3:
                {
                    logedIn=true;
                    break;
                }
                case 4:
                {
                    terminate=true;
                    usrKeyboardInputsThread.join();
                    break;
                }
                default: break;
            }
        }
        delete answer;
    }
    return 0;
}
