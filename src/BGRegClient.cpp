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

    UserInputReader usrKeyboardInputs(connectionHandler,terminate); //User Input Handling Task
    std::thread usrKeyboardInputsThread(&UserInputReader::run, &usrKeyboardInputs); //User Input Handling Task Thread


    // TODO:check for terminate / interrupt configuration & solution
    while (!terminate) {
        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        Operation* answer= nullptr;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        // TODO: Decode server reply to a valid string according to assignment definitions
        if (!connectionHandler.getOp(*answer)) { // getting answer string from server (bytes to string decoding included)
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        std::cout << answer->toString() << std::endl;

        if(answer->getOpCode()==12 && ((AcknowledgementOp*)answer)->getAckOf()==4)
        {
            terminate=true;
            usrKeyboardInputsThread.join();
        }
    }
    return 0;
}
