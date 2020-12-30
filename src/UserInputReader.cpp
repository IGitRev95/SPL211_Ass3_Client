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
        char enc[1024];
//        /*
///* ack decoder test from server

        char tmp[2];
        OperationEncoderDecoder::shortToBytes(12,enc);
        OperationEncoderDecoder::shortToBytes(6,tmp);
        enc[2]=tmp[0];
        enc[3]=tmp[1];
        for(int i=0;i<10;i=i+1)
            enc[4+i]=buf[i];
        enc[14]='\0';
//*/

//        OperationEncoderDecoder::encode(a,enc);
//        line=a.toString();
        Operation b=OperationEncoderDecoder::decode(enc);
        std::cout<<b.toString()<<std::endl;
//*/
        if (!clientConnectionHandler.sendLine(line)) { //passing string to send to server to the connectionHandler for sending
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefore we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
    }
    return 0;
}
