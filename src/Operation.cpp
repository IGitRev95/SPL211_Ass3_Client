//
// Created by spl211 on 27/12/2020.
//

#include "../include/Operation.h"

#include <utility>

Operation::Operation(short opcode, std::string interface): _opCode(opcode), _interfaceCommand(std::move(interface)),_arguments(){

}

short Operation::getOpCode() const{
    return _opCode;
}

std::string Operation::getInterfaceCommand() {
    return _interfaceCommand;
}

std::string Operation::getArgumentsAsString() { //return argument of operation as string
    std::string argumentsLine;
    for (auto & _argument : _arguments) { //chaining all arguments to one string separating with ' '
        argumentsLine+=_argument;
        argumentsLine+=(' ');
    }
    argumentsLine.resize(argumentsLine.size()-1); //cutting last ' '
    return argumentsLine;
}

std::string Operation::toString() { //Operation to string
    std::string opInLine;
    if(_opCode==12||_opCode==13)
        return ((ReplyOp*)this)->replyToString();
    //For general printing
    opInLine+=(std::to_string(_opCode)+' ');
    opInLine+=getArgumentsAsString();
    return opInLine;
}

void Operation::setArguments(std::string argsForOp) {
    int i(0);
    if(!argsForOp.empty()) {

        while (argsForOp.at(i) == ' ') //cutting firsts ' ' if are there by mistake
        {
            argsForOp = argsForOp.substr(i + 1);
            i++;
        }
        std::vector<std::string> splitArgsForOp = Operation::splitString(argsForOp, ' ');//separating the arguments from being in one string
        for (auto & j : splitArgsForOp)
            _arguments.push_back(j);
    }
}

std::vector<std::string> Operation::splitString(const std::string& toSplit, char delimiter) {
    std::vector<std::string> splitStringVector;
    unsigned long curpos;
    for ( unsigned long lastpos=0; lastpos < toSplit.length(); lastpos=curpos) {
        curpos=toSplit.find_first_of(delimiter, lastpos); //find the index of the next delimiter char
        splitStringVector.push_back(toSplit.substr(lastpos, curpos - lastpos)); //add the argument sub stringed from the last position for 'cur-last' chars
        curpos++; //jump over the @delimiter before new cycle
        if (curpos==0) // curposs is 0 after looking for next delimiter index if there's non therefore loop should end
            break;
    }
    return splitStringVector;
}

Operation::Operation(short opcode, std::string interface, std::vector<std::string> argsForOp):_opCode(opcode), _interfaceCommand(std::move(interface)),_arguments(std::move(argsForOp)){
}

const std::vector<std::string> &Operation::getArguments() const {
    return _arguments;
}

std::string Operation::charArrayTostring(const char *charArrayToConvert, char delimiter, int poss_s) {
    std::string convertedDataString;
    while (charArrayToConvert[poss_s] != delimiter) //writing from starting point until reaching the delimiter
    {
        convertedDataString+=charArrayToConvert[poss_s];
        poss_s=poss_s+1;
    }
    return convertedDataString;
}

AdminRegOp::AdminRegOp():Operation(1,"ADMINREG") {

}

AdminRegOp::AdminRegOp(std::vector<std::string> argsForOp):Operation(1,"ADMINREG",std::move(argsForOp)) {

}

StudentRegOp::StudentRegOp():Operation(2,"STUDENTREG") {

}

StudentRegOp::StudentRegOp(std::vector<std::string> argsForOp):Operation(2,"STUDENTREG",std::move(argsForOp)) {

}

LoginReqOp::LoginReqOp():Operation(3,"LOGIN") {

}

LoginReqOp::LoginReqOp(std::vector<std::string> argsForOp):Operation(3,"LOGIN",std::move(argsForOp)) {

}

LogoutReqOp::LogoutReqOp():Operation(4,"LOGOUT") {

}

LogoutReqOp::LogoutReqOp(std::vector<std::string> argsForOp):Operation(4,"LOGOUT",std::move(argsForOp)) {

}

CourseRegOp::CourseRegOp():Operation(5,"COURSEREG") {

}

CourseRegOp::CourseRegOp(std::vector<std::string> argsForOp):Operation(5,"COURSEREG",std::move(argsForOp)) {

}

KdamCourseCheckOp::KdamCourseCheckOp():Operation(6,"KDAMCHECK") {

}

KdamCourseCheckOp::KdamCourseCheckOp(std::vector<std::string> argsForOp):Operation(6,"KDAMCHECK",std::move(argsForOp)) {

}

PrintCourseStatOp::PrintCourseStatOp():Operation(7,"COURSESTAT") {

}

PrintCourseStatOp::PrintCourseStatOp(std::vector<std::string> argsForOp):Operation(7,"COURSESTAT",std::move(argsForOp)) {

}

PrintStudentStatOp::PrintStudentStatOp():Operation(8,"STUDENTSTAT") {

}

PrintStudentStatOp::PrintStudentStatOp(std::vector<std::string> argsForOp):Operation(8,"STUDENTSTAT",std::move(argsForOp)) {

}

IsRegOp::IsRegOp():Operation(9,"ISREGISTERED") {

}

IsRegOp::IsRegOp(std::vector<std::string> argsForOp):Operation(9,"ISREGISTERED",std::move(argsForOp)) {

}

CourseUnRegOp::CourseUnRegOp():Operation(10,"UNREGISTER") {

}

CourseUnRegOp::CourseUnRegOp(std::vector<std::string> argsForOp):Operation(10,"UNREGISTER",std::move(argsForOp)) {

}

MyCoursesOp::MyCoursesOp():Operation(11,"MYCOURSES") {

}

MyCoursesOp::MyCoursesOp(std::vector<std::string> argsForOp):Operation(11,"MYCOURSES",std::move(argsForOp)) {

}

AcknowledgementOp::AcknowledgementOp():ReplyOp(12,"ACK") {

}

AcknowledgementOp::AcknowledgementOp(short ackOf):ReplyOp(12,"ACK",ackOf) {

}

std::string AcknowledgementOp::replyToString() {
    std::string output(this->getInterfaceCommand()+' '+std::to_string(getAckOf()));
    if(!this->getArguments().empty())//adding arguments if needed
    {
        output+=("\n"+this->getArgumentsAsString());
    }
    return output;
}

short AcknowledgementOp::getAckOf() const {
    return getReplyOpOf();
}

ErrorOp::ErrorOp():ReplyOp(13,"Error",0){

}

short ErrorOp::getErrorOf() const {
    return getReplyOpOf();
}

ErrorOp::ErrorOp(short errorOf):ReplyOp(13,"Error",errorOf){

}

std::string ErrorOp::replyToString() {
    std::string output(this->getInterfaceCommand()+' '+std::to_string(getErrorOf()));
    return output;
}

ReplyOp::ReplyOp(short opCod,std::string interface):Operation(opCod,std::move(interface)),_replyOf(0) {

}

ReplyOp::ReplyOp(short opCod, std::string interface, short replyOf):Operation(opCod,std::move(interface)),_replyOf(replyOf) {

}

short ReplyOp::getReplyOpOf() const {
    return _replyOf;
}





