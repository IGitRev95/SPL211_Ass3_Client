//
// Created by spl211 on 29/12/2020.
//

#include "../include/OperationEncoderDecoder.h"

#include <utility>

Operation OperationEncoderDecoder::decode(std::string usrCommand) {
    std::vector<std::string> commandParsedParts= Operation::splitString(std::move(usrCommand),' ');
    std::string commandName(commandParsedParts.at(0));//cutting interface
    commandParsedParts.erase(commandParsedParts.begin());
    switch (getTypeOfString(commandName)) {
        case ADMINREG:
            return AdminRegOp(commandParsedParts);
        case STUDENTREG:
            return StudentRegOp(commandParsedParts);
        case LOGIN:
            return LoginReqOp(commandParsedParts);
        case LOGOUT:
            return LogoutReqOp(commandParsedParts);
        case COURSEREG:
            return CourseRegOp(commandParsedParts);
        case KDAMCHECK:
            return KdamCourseCheckOp(commandParsedParts);
        case COURSESTAT:
            return PrintCourseStatOp(commandParsedParts);
        case STUDENTSTAT:
            return PrintStudentStatOp(commandParsedParts);
        case ISREGISTERED:
            return IsRegOp(commandParsedParts);
        case UNREGISTER:
            return CourseUnRegOp(commandParsedParts);
        case MYCOURSES:
            return MyCoursesOp(commandParsedParts);
/*
        case ACK:
            return AcknowledgementOp(commandParsedParts);
        case Error:
            return ErrorOp(commandParsedParts);
*/
    }
}

OpType OperationEncoderDecoder::getTypeOfString(const std::string& typo) {
    if (typo=="ADMINREG")
        return ADMINREG;
    if (typo=="STUDENTREG")
        return STUDENTREG;
    if (typo=="LOGIN")
        return LOGIN;
    if (typo=="LOGOUT")
        return LOGOUT;
    if (typo=="COURSEREG")
        return COURSEREG;
    if (typo=="KDAMCHECK")
        return KDAMCHECK;
    if (typo=="COURSESTAT")
        return COURSESTAT;
    if (typo=="STUDENTSTAT")
        return STUDENTSTAT;
    if (typo=="ISREGISTERED")
        return ISREGISTERED;
    if (typo=="UNREGISTER")
        return UNREGISTER;
    if (typo=="MYCOURSES")
        return MYCOURSES;
/*
    if (typo=="ACK")
        return ACK;
    if (typo=="Error")
        return Error;
*/
    // TODO throw exception in case of non valid command + delete returnVVV
    return STUDENTREG;
}

int OperationEncoderDecoder::encode(const Operation& op,  char *bytes) {
//    int writeCurrentPos(0);
    shortToBytes(op.getOpCode(), bytes);
    int writeCurrentPos(2);
    switch (op.getOpCode()) {
        case 1:
        case 2:
        case 3:
        {
            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
            writeCurrentPos=writeCurrentPos+(int)op.getArguments().at(0).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            stringToCharArray(op.getArguments().at(1),bytes,writeCurrentPos);
            writeCurrentPos=writeCurrentPos+(int)op.getArguments().at(1).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            return writeCurrentPos;
        }

        case 4:
        case 11:
            return writeCurrentPos;

        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        {
            short num=stringToShort(op.getArguments().at(0));
            if(num==-1)
                break;
            char numAsBytes[2];
            shortToBytes(num,numAsBytes);
            bytes[writeCurrentPos]=numAsBytes[0];
            writeCurrentPos++;
            bytes[writeCurrentPos]=numAsBytes[1];
            writeCurrentPos++;
            return writeCurrentPos;
        }

        case 8:
        {
            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
            writeCurrentPos=writeCurrentPos+(int)op.getArguments().at(0).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            return writeCurrentPos;
        }
    }
    return -1;
}

short OperationEncoderDecoder::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void OperationEncoderDecoder::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void OperationEncoderDecoder::stringToCharArray(std::string stringToConvert, char *bytesArr,int arrayWritefromPos) {
    for(unsigned int i=0;i<stringToConvert.length();i++){
        bytesArr[arrayWritefromPos + i]=stringToConvert.at(i);
    }
}

short OperationEncoderDecoder::stringToShort(const std::string& stringToConvert) {
    try{
        return boost::lexical_cast<short>(stringToConvert);
    }
    catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
        return -1;
    }
}

bool OperationEncoderDecoder::decode(char *serverCommand,ReplyOp** decodedOp) {//TODO:needs cleaning and default
    int readFromPoss(0);
    short commandOpcode=bytesToShort(serverCommand);
    readFromPoss=2;
    if(commandOpcode==12)
    {
        char bytestoShort[2];
        bytestoShort[0]=serverCommand[readFromPoss];
        readFromPoss++;
        bytestoShort[1]=serverCommand[readFromPoss];
        //readFromPoss++;
        short ackOfOpCode = bytesToShort(bytestoShort);
        *decodedOp=new AcknowledgementOp (ackOfOpCode);
        (*decodedOp)->setArguments(Operation::charArrayTostring(serverCommand,'\0',readFromPoss));
        return true;
    }
    if(commandOpcode==13)
    {
        char bytestoShort[2];
        bytestoShort[0]=serverCommand[readFromPoss];
        readFromPoss++;
        bytestoShort[1]=serverCommand[readFromPoss];
        //readFromPoss++;
        short errorOfOpCode = bytesToShort(bytestoShort);
        *decodedOp=new ErrorOp(errorOfOpCode);
        return true;
    }
    return false;
}
