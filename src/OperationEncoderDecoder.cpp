//
// Created by spl211 on 29/12/2020.
//

#include "../include/OperationEncoderDecoder.h"

#include <utility>

Operation OperationEncoderDecoder::decode(std::string usrCommand) {
    std::vector<std::string> commandParsedParts= Operation::splitString(std::move(usrCommand),' ');
    std::string commandName(commandParsedParts.at(0));//get interface command
    commandParsedParts.erase(commandParsedParts.begin());//cutting interface
    switch (getTypeOfString(commandName)) { //creating correct type of operation with given arguments
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
        case NONVALIDCOMMAND:
        {
            break;
        }
    }
    NonValidOperation nonValidOperation;
    throw nonValidOperation;
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
    return NONVALIDCOMMAND; //type of non valid command
}

int OperationEncoderDecoder::encode(const Operation& op,  char *bytes) {
    int writeCurrentPos(0);//writing position pointer
    shortToBytes(op.getOpCode(), bytes); //encoding opCode to the bytes array
    writeCurrentPos=2; //wrote 2 bytes of opCode
    switch (op.getOpCode()) {
        case 1: //admin reg
        case 2: //student reg
        case 3: //login
        {   //User and Password format messages
            //username encoding
            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
            writeCurrentPos=writeCurrentPos+(int)op.getArguments().at(0).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            //password encoding
            stringToCharArray(op.getArguments().at(1),bytes,writeCurrentPos);
            writeCurrentPos=writeCurrentPos+(int)op.getArguments().at(1).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            return writeCurrentPos;
        }

        case 4: //logout
        case 11: //my courses
        {   // no extra arguments format messages
            return writeCurrentPos;
        }

        case 5: //course reg
        case 6: //Kdam check
        case 7: //course stat
        case 9: //is reg
        case 10: //course un reg
        {   // course num argument format messages
            //encoding number to short
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

        case 8: //student stat
        {   // student user name argument format messages
            // student user name string encoding
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

void OperationEncoderDecoder::stringToCharArray(std::string stringToConvert, char *bytesArr,int arrayWriteFromPos) {
    for(unsigned int i=0 ; i<stringToConvert.length() ; i++){
        bytesArr[arrayWriteFromPos + i]=stringToConvert.at(i);
    }
}

short OperationEncoderDecoder::stringToShort(const std::string& stringToConvert) {
    try{
        return boost::lexical_cast<short>(stringToConvert); //converting short to string
    }
    catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
        return -1;
    }
}

bool OperationEncoderDecoder::decode(char *serverCommand,ReplyOp** decodedOp) {
    int readFromPoss(0); //reading position index
    short commandOpcode=bytesToShort(serverCommand);//getting opCode
    readFromPoss=2; //moving reading pointer
    if(commandOpcode==12) //ACK op
    {   //decoding message opCode
        char bytestoShort[2];
        bytestoShort[0]=serverCommand[readFromPoss];
        readFromPoss++;
        bytestoShort[1]=serverCommand[readFromPoss];
        readFromPoss++;
        short ackOfOpCode = bytesToShort(bytestoShort);
        *decodedOp=new AcknowledgementOp (ackOfOpCode); //creating Operation object
        (*decodedOp)->setArguments(Operation::charArrayTostring( serverCommand,'\0', readFromPoss) );
        return true;
    }
    if(commandOpcode==13) //Error op
    {   //decoding message opCode
        char bytestoShort[2];
        bytestoShort[0]=serverCommand[readFromPoss];
        readFromPoss++;
        bytestoShort[1]=serverCommand[readFromPoss];
        //readFromPoss++;
        short errorOfOpCode = bytesToShort(bytestoShort);
        *decodedOp=new ErrorOp(errorOfOpCode); //creating Operation object
        return true;
    }
    return false;
}

const char *NonValidOperation::what() const noexcept {
    return _errorCase.c_str(); //exception output string
}
