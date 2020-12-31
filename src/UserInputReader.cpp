//
// Created by spl211 on 26/12/2020.
//

#include "../include/UserInputReader.h"

UserInputReader::UserInputReader(ConnectionHandler &clientConnectionHandler,std::atomic_bool &terminate) : clientConnectionHandler(clientConnectionHandler),terminate(terminate) {}

int UserInputReader::run() {
    while (1)// TODO:check for terminate / interrupt configuration & solution
    {
        const short bufsize = 1024;
        char buf[bufsize]; //creating char array that will hold the keyboard input stream of chars
        std::cin.getline(buf, bufsize); // (cin included therefore blocking on keyboard) reading an entire line of input stream of chars and stored it in the buf char array
        std::string line(buf); //creating String obj from char array
        Operation userCommand=OperationEncoderDecoder::decode(line); //creating Operation Object from usr end

        if (!clientConnectionHandler.sendOp(userCommand)) { //passing string to send to server to the connectionHandler for sending
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        if(userCommand.getOpCode() == 4)
        {
            while (!terminate){std::this_thread::yield();}
            break;
        }
/*
        int len=OperationEncoderDecoder::encode(userCommand, buf);
        std::cout << "Sent " << len << " bytes to server" << std::endl;
*/
    }
    return 0;
}
