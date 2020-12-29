//
// Created by spl211 on 26/12/2020.
//

#include "../include/UserInputReader.h"

UserInputReader::UserInputReader(ConnectionHandler &clientConnectionHandler) : clientConnectionHandler(
        clientConnectionHandler) {}

int UserInputReader::run() {
    while (1)// TODO:check for terminate / interrupt configuration & solution
    {
        const short bufsize = 1024;
        char buf[bufsize]; //creating char array that will hold the keyboard input stream of chars
        std::cin.getline(buf, bufsize); // (cin included therefore blocking on keyboard) reading an entire line of input stream of chars and stored it in the buf char array
        std::string line(buf); //creating String obj from char array
        int len=line.length();
//        Operation a=OperationEncoderDecoder::decode(line);
        // TODO: Encode User command to a legal message/command type by assignment definitions
        // pars input to Operation Object
        // make toString & send - should be ok by standard encoder - IDO check bytes array
        // TODO:linking problem of Operation cpp - VV testing lines of Op class functionality
        /*
        AcknowledgementOp acknowledgementOp;
        acknowledgementOp.setArguments("Ido Rules!");
        line=acknowledgementOp.toString();

*/
        if (!clientConnectionHandler.sendLine(line)) { //passing string to send to server to the connectionHandler for sending
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefore we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
    }
    return 0;
}
