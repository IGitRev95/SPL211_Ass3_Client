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

void OperationEncoderDecoder::encode(Operation op, const char *bytes) {


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
