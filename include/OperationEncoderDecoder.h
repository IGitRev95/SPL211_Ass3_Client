//
// Created by spl211 on 29/12/2020.
//

#ifndef CLIENT_OPERATIONENCODERDECODER_H
#define CLIENT_OPERATIONENCODERDECODER_H

#include "Operation.h"
#include <boost/asio.hpp>
#include <iostream>
enum OpType
{
    ADMINREG, STUDENTREG, LOGIN, LOGOUT,
    COURSEREG, KDAMCHECK, COURSESTAT, STUDENTSTAT,
    ISREGISTERED, UNREGISTER, MYCOURSES//, ACK, Error
    , NONVALIDCOMMAND
};

class OperationEncoderDecoder {
    //TODO: Add Exceptions about illegal input streams from user like non valid command include additional not needed extra arguments
public:
    static Operation decode(const std::string& usrCommand); //making an operation object from user command input string
    static bool decode(char serverCommand[],ReplyOp** decodedOp); //setting the pointer to an operation object decoded from (bytes)char array
    static int encode(const Operation& op, char bytes[]); //Returns written length and writing operation to the bytes array

    static short bytesToShort(const char* bytesArr);
    static void shortToBytes(short num, char* bytesArr);

private:
    static OpType getTypeOfString(const std::string& typo); //Return Operation enum type
    static void stringToCharArray(std::string stringToConvert,char* bytesArr, int arrayWriteFromPos);
    static short stringToShort(const std::string& stringToConvert);
};
/**
 * class of exception in case of non valid command by user
 */
class NonValidOperation: public std::exception{
private:
    std::string _errorCase="Non Valid Command";
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;
};

#endif //CLIENT_OPERATIONENCODERDECODER_H
