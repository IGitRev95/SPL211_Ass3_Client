//
// Created by spl211 on 29/12/2020.
//

#include "../include/OperationEncoderDecoder.h"

Operation OperationEncoderDecoder::decode(std::string usrCommand) {
    std::vector<std::string> commandParsedParts=Operation::splitString(usrCommand,' ');
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
        case ACK:
            return AcknowledgementOp(commandParsedParts);
        case Error:
            return ErrorOp(commandParsedParts);
    }
}

OpType OperationEncoderDecoder::getTypeOfString(std::string typo) {
    if (typo.compare("ADMINREG")==0)
        return ADMINREG;
    if (typo.compare("STUDENTREG")==0)
        return STUDENTREG;
    if (typo.compare("LOGIN")==0)
        return LOGIN;
    if (typo.compare("LOGOUT")==0)
        return LOGOUT;
    if (typo.compare("COURSEREG")==0)
        return COURSEREG;
    if (typo.compare("KDAMCHECK")==0)
        return KDAMCHECK;
    if (typo.compare("COURSESTAT")==0)
        return COURSESTAT;
    if (typo.compare("STUDENTSTAT")==0)
        return STUDENTSTAT;
    if (typo.compare("ISREGISTERED")==0)
        return ISREGISTERED;
    if (typo.compare("UNREGISTER")==0)
        return UNREGISTER;
    if (typo.compare("MYCOURSES")==0)
        return MYCOURSES;
    if (typo.compare("ACK")==0)
        return ACK;
    if (typo.compare("Error")==0)
        return Error;
    // TODO throw exception in case of non valid command
}

bool OperationEncoderDecoder::encode(Operation op,  char *bytes) {
    int writeCurrentPos(0);
    shortToBytes(op.getOpCode(), bytes);
    writeCurrentPos=2;
    switch (op.getOpCode()) {
        case 1:
        case 2:
        case 3:
        {
            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
            writeCurrentPos=writeCurrentPos+op.getArguments().at(0).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            stringToCharArray(op.getArguments().at(1),bytes,writeCurrentPos);
            writeCurrentPos=writeCurrentPos+op.getArguments().at(1).length();
            bytes[writeCurrentPos]='\0';
            writeCurrentPos++;
            return true;
        }

        case 4:
        case 11:
            return true;

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
            return true;
        }

        case 8:
        {
            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
            writeCurrentPos=writeCurrentPos+op.getArguments().at(0).length();
            bytes[writeCurrentPos]='\0';
            return true;
        }
        default:
            return false;
    }
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

void OperationEncoderDecoder::stringToCharArray(std::string stringToConvert, char *bytesArr,int arrayWritefromPos) {//TODO:not Tested
    for(int i=0;i<stringToConvert.length();i++){
        bytesArr[arrayWritefromPos + i]=stringToConvert.at(i);
    }
}

void OperationEncoderDecoder::stringToCharArray(std::string stringToConvert, char *bytesArr) {
    stringToCharArray(stringToConvert,bytesArr,0);
}

short OperationEncoderDecoder::stringToShort(std::string stringToConvert) {
    try{
        return boost::lexical_cast<short>(stringToConvert);
    }
    catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
        return -1;
    }
}

Operation OperationEncoderDecoder::decode(char *serverCommand) {//TODO:not Tested and needs cleaning and default
    int readFromPoss(0);
    short commandOpcode=bytesToShort(serverCommand);
    readFromPoss=2;
    Operation* decodedOp= nullptr;
    std::string args("");
    switch (commandOpcode) { //TODO: usage of new be sure to free allocated memory
//        case 1:
//            decodedOp=new AdminRegOp();
//            break;
//        case 2:
//            decodedOp=new StudentRegOp();
//            break;
//        case 3:
//            decodedOp=new LoginReqOp();
//            break;
//        {
//            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
//            writeCurrentPos=writeCurrentPos+op.getArguments().at(0).length();
//            bytes[writeCurrentPos]='\0';
//            writeCurrentPos++;
//            stringToCharArray(op.getArguments().at(1),bytes,writeCurrentPos);
//            writeCurrentPos=writeCurrentPos+op.getArguments().at(1).length();
//            bytes[writeCurrentPos]='\0';
//            writeCurrentPos++;
//            return true;
//        }
//
//        case 4:
//            decodedOp=new LogoutReqOp();
//            break;
//        case 11:
//            decodedOp=new MyCoursesOp();
//            break;
//            return true;
//
//        case 5:
//            decodedOp=new CourseRegOp();
//            break;
//        case 6:
//            decodedOp=new KdamCourseCheckOp();
//            break;
//        case 7:
//            decodedOp=new PrintCourseStatOp();
//            break;
//        case 9:
//            decodedOp=new IsRegOp();
//            break;
//        {
//            short num=stringToShort(op.getArguments().at(0));
//            if(num==-1)
//                break;
//            char numAsBytes[2];
//            shortToBytes(num,numAsBytes);
//            bytes[writeCurrentPos]=numAsBytes[0];
//            writeCurrentPos++;
//            bytes[writeCurrentPos]=numAsBytes[1];
//            writeCurrentPos++;
//            return true;
//        }
//        case 10:
//            decodedOp=new CourseUnRegOp();
//            break;
//
//        case 8:
//            decodedOp=new PrintStudentStatOp();
//            break;
//        {
//            stringToCharArray(op.getArguments().at(0),bytes,writeCurrentPos);//return curr pos of writing
//            writeCurrentPos=writeCurrentPos+op.getArguments().at(0).length();
//            bytes[writeCurrentPos]='\0';
//            return true;
//        }
//        default:
//            return false;
        case 12:
        {
            decodedOp=new AcknowledgementOp();
            char bytestoShort[2];
            bytestoShort[0]=serverCommand[readFromPoss];
            readFromPoss++;
            bytestoShort[1]=serverCommand[readFromPoss];
            readFromPoss++;
            short ackOfOpCode = bytesToShort(bytestoShort);
            args+=(std::to_string(ackOfOpCode)+' ');
            args+=(Operation::charArrayTostring(serverCommand,'\0',readFromPoss));
            decodedOp->setArguments(args);
            break;
        }
        case 13:
        {
            decodedOp=new ErrorOp();
            char bytestoShort[2];
            bytestoShort[0]=serverCommand[readFromPoss];
            readFromPoss++;
            bytestoShort[1]=serverCommand[readFromPoss];
            readFromPoss++;
            short ackOfOpCode = bytesToShort(bytestoShort);
            args+=(std::to_string(ackOfOpCode));
            break;
        }
    }
    return *decodedOp;
}
