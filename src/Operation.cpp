//
// Created by spl211 on 27/12/2020.
//

#include "../include/Operation.h"

Operation::Operation(short opcode, std::string interface): _opCode(opcode), _interfaceCommand(interface){

}

short Operation::getOpCode() const{
    return _opCode;
}

std::string Operation::getInterfaceCommand() {
    return _interfaceCommand;
}

std::string Operation::getArgumentsAsString() { //return argument of operation as string
    std::string argumentsLine("");
    for (int i = 0; i < _arguments.size(); ++i) {
        argumentsLine+=(_arguments.at(i));
        argumentsLine+=(' ');
    }
    argumentsLine.resize(argumentsLine.size()-1); //cutting last ' '
    return argumentsLine;
}

std::string Operation::toString() { //Operation to string
    std::string opInLine;
    switch (_opCode) {
        case 12:
            return ((AcknowledgementOp*)this)->ackToString();
        case 13:
            return ((ErrorOp*)this)->errorToString();
    }
    opInLine+=(std::to_string(_opCode)+' ');
    opInLine+=getArgumentsAsString();
    return opInLine;
}

void Operation::setArguments(std::string argsForOp) {
    int i(0);
    while(argsForOp.at(i)==' ') //cutting firsts ' ' if are there by mistake
    {
        argsForOp=argsForOp.substr(i+1);
        i++;
    }
    std::vector<std::string> splitArgsForOp=Operation::splitString(argsForOp,' ');
    for( int j=0;j<splitArgsForOp.size();j++)
        _arguments.push_back(splitArgsForOp.at(j));

}

std::vector<std::string> Operation::splitString(const std::string toSplit, char delimiter) {
    std::vector<std::string> splitStringVector;
    unsigned long curpos=0;
    for ( unsigned long lastpos=0; lastpos < toSplit.length(); lastpos=curpos) {
        curpos=toSplit.find_first_of(delimiter, lastpos);
        splitStringVector.push_back(toSplit.substr(lastpos, curpos - lastpos));
        curpos++;//to jump over the @delimiter before new cycle
        if (curpos==0)
            break;
    }
    return splitStringVector;
}

void Operation::setArguments(std::vector<std::string> argsForOp) {
    for( int j=0;j<argsForOp.size();j++)
        _arguments.push_back(argsForOp.at(j));
}

Operation::Operation(short opcode, std::string interface, std::vector<std::string> argsForOp):_opCode(opcode), _interfaceCommand(interface) {
    this->setArguments(argsForOp);
}

const std::vector<std::string> &Operation::getArguments() const {
    return _arguments;
}

std::string Operation::charArrayTostring(const char *charArrayToConvert, char delimiter, int poss_s) {
    std::string convertedDataString;
    while (charArrayToConvert[poss_s] != delimiter)
    {
        convertedDataString+=charArrayToConvert[poss_s];
        poss_s=poss_s+1;
    }
    return convertedDataString;
}

AdminRegOp::AdminRegOp():Operation(1,"ADMINREG") {

}

AdminRegOp::AdminRegOp(std::vector<std::string> argsForOp):Operation(1,"ADMINREG",argsForOp) {

}

StudentRegOp::StudentRegOp():Operation(2,"STUDENTREG") {

}

StudentRegOp::StudentRegOp(std::vector<std::string> argsForOp):Operation(2,"STUDENTREG",argsForOp) {

}

LoginReqOp::LoginReqOp():Operation(3,"LOGIN") {

}

LoginReqOp::LoginReqOp(std::vector<std::string> argsForOp):Operation(3,"LOGIN",argsForOp) {

}

LogoutReqOp::LogoutReqOp():Operation(4,"LOGOUT") {

}

LogoutReqOp::LogoutReqOp(std::vector<std::string> argsForOp):Operation(4,"LOGOUT",argsForOp) {

}

CourseRegOp::CourseRegOp():Operation(5,"COURSEREG") {

}

CourseRegOp::CourseRegOp(std::vector<std::string> argsForOp):Operation(5,"COURSEREG",argsForOp) {

}

KdamCourseCheckOp::KdamCourseCheckOp():Operation(6,"KDAMCHECK") {

}

KdamCourseCheckOp::KdamCourseCheckOp(std::vector<std::string> argsForOp):Operation(6,"KDAMCHECK",argsForOp) {

}

PrintCourseStatOp::PrintCourseStatOp():Operation(7,"COURSESTAT") {

}

PrintCourseStatOp::PrintCourseStatOp(std::vector<std::string> argsForOp):Operation(7,"COURSESTAT",argsForOp) {

}

PrintStudentStatOp::PrintStudentStatOp():Operation(8,"STUDENTSTAT") {

}

PrintStudentStatOp::PrintStudentStatOp(std::vector<std::string> argsForOp):Operation(8,"STUDENTSTAT",argsForOp) {

}

IsRegOp::IsRegOp():Operation(9,"ISREGISTERED") {

}

IsRegOp::IsRegOp(std::vector<std::string> argsForOp):Operation(9,"ISREGISTERED",argsForOp) {

}

CourseUnRegOp::CourseUnRegOp():Operation(10,"UNREGISTER") {

}

CourseUnRegOp::CourseUnRegOp(std::vector<std::string> argsForOp):Operation(10,"UNREGISTER",argsForOp) {

}

MyCoursesOp::MyCoursesOp():Operation(11,"MYCOURSES") {

}

MyCoursesOp::MyCoursesOp(std::vector<std::string> argsForOp):Operation(11,"MYCOURSES",argsForOp) {

}

AcknowledgementOp::AcknowledgementOp():Operation(12,"ACK"),_ackOf(0) {

}

AcknowledgementOp::AcknowledgementOp(std::vector<std::string> argsForOp):Operation(12,"ACK",argsForOp),_ackOf(0) {

}

AcknowledgementOp::AcknowledgementOp(short ackOf):Operation(12,"ACK"),_ackOf(ackOf) {

}

std::string AcknowledgementOp::ackToString() {
    std::string output(this->getInterfaceCommand()+' '+std::to_string(getAckOf()));
    if(!this->getArguments().empty())
    {
        output+=("\n"+this->getArgumentsAsString());
    }
    return output;
}

short AcknowledgementOp::getAckOf() const {
    return _ackOf;
}

ErrorOp::ErrorOp():Operation(13,"Error"),_errorOf(0) {

}

ErrorOp::ErrorOp(std::vector<std::string> argsForOp):Operation(13,"Error",argsForOp),_errorOf(0) {

}

short ErrorOp::getErrorOf() const {
    return _errorOf;
}

ErrorOp::ErrorOp(short errorOf):Operation(13,"Error"),_errorOf(errorOf) {

}

std::string ErrorOp::errorToString() {
    std::string output(this->getInterfaceCommand()+' '+std::to_string(getErrorOf()));
    return output;
}
