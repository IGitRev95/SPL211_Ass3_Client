//
// Created by spl211 on 29/12/2020.
//

#ifndef CLIENT_OPERATIONENCODERDECODER_H
#define CLIENT_OPERATIONENCODERDECODER_H

#include "Operation.h"
#include <iostream>
enum OpType
{
    ADMINREG, STUDENTREG, LOGIN, LOGOUT,
    COURSEREG, KDAMCHECK, COURSESTAT, STUDENTSTAT,
    ISREGISTERED, UNREGISTER, MYCOURSES//, ACK, Error
};

class OperationEncoderDecoder {
    //TODO: Add Exceptions about illegal input streams from user like non valid command include additional not needed extra arguments
public:
    static Operation decode(std::string usrCommand);
    static Operation decode(char serverCommand[]);
    static int encode(const Operation& op, char bytes[]); //Returns written length
    static short bytesToShort(char* bytesArr);
    static void shortToBytes(short num, char* bytesArr);

private:
    static OpType getTypeOfString(const std::string& typo);
    static void stringToCharArray(std::string stringToConvert,char* bytesArr, int arrayWritefromPos);
    static void stringToCharArray(std::string stringToConvert,char* bytesArr);
    static short stringToShort(const std::string& stringToConvert);
};


#endif //CLIENT_OPERATIONENCODERDECODER_H
