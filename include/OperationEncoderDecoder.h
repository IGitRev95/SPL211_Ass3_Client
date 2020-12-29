//
// Created by spl211 on 29/12/2020.
//

#ifndef CLIENT_OPERATIONENCODERDECODER_H
#define CLIENT_OPERATIONENCODERDECODER_H

#include "Operation.h"
enum OpType
{
    ADMINREG, STUDENTREG, LOGIN, LOGOUT,
    COURSEREG, KDAMCHECK, COURSESTAT, STUDENTSTAT,
    ISREGISTERED, UNREGISTER, MYCOURSES, ACK, Error
};

class OperationEncoderDecoder {
public:
    static Operation decode(std::string usrCommand);
    static Operation decode(char serverCommand[]);
    static void encode(Operation op,const char bytes[]);

private:
    static OpType getTypeOfString(std::string typo);
};


#endif //CLIENT_OPERATIONENCODERDECODER_H
