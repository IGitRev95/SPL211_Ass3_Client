//
// Created by spl211 on 27/12/2020.
//

#include "../include/Operation.h"

Operation::Operation(short opcode, std::string interface): _opCode(opcode), _interfaceCommand(interface){

}

short Operation::getOpCode() {
    return _opCode;
}

std::string Operation::getInterfaceCommand() {
    return _interfaceCommand;
}

std::string Operation::getArguments() { //return argument of operation as string
    std::string argumentsLine();
    for (int i = 0; i < _arguments.size(); ++i) {
        argumentsLine()+=(_arguments.at(i));
        argumentsLine()+=(' ');
    }
    argumentsLine().resize(argumentsLine().size()-1); //cutting last ' '
    return argumentsLine();
}

std::string Operation::toString() { //Operation to string
    std::string opInLine();
    if(_opCode==12||_opCode==13)
    {
        opInLine()+=(_interfaceCommand+' ');
    } else{
        opInLine()+=(_opCode+' ');
    }
    opInLine()+=getArguments();
    return opInLine();
}

void Operation::setArguments(std::string argsForOp) {
    if(argsForOp.at(0) == ' ') //cutting first ' ' if its there by mistake
        argsForOp=argsForOp.substr(1);
    unsigned long curpos=0;
    for (unsigned long lastpos=0; lastpos < argsForOp.length(); lastpos=curpos) {
        curpos=argsForOp.find_first_of(' ', lastpos);
        _arguments.push_back(argsForOp.substr(lastpos, curpos - lastpos));
        curpos++;//to jump over the ' ' before new cycle
    }
}

AdminRegOp::AdminRegOp():Operation(1,"ADMINREG") {

}

StudentRegOp::StudentRegOp():Operation(2,"STUDENTREG") {

}

LoginReqOp::LoginReqOp():Operation(3,"LOGIN") {

}

LogoutReqOp::LogoutReqOp():Operation(4,"LOGOUT") {

}

CourseRegOp::CourseRegOp():Operation(5,"COURSEREG") {

}

KdamCourseCheckOp::KdamCourseCheckOp():Operation(6,"KDAMCHECK") {

}

PrintCourseStatOp::PrintCourseStatOp():Operation(7,"COURSESTAT") {

}

PrintStudentStatOp::PrintStudentStatOp():Operation(8,"STUDENTSTAT") {

}

IsRegOp::IsRegOp():Operation(9,"ISREGISTERED") {

}

CourseUnRegOp::CourseUnRegOp():Operation(10,"UNREGISTER") {

}

MyCoursesOp::MyCoursesOp():Operation(11,"MYCOURSES") {

}

AcknowledgementOp::AcknowledgementOp():Operation(12,"ACK") {

}

ErrorOp::ErrorOp():Operation(13,"Error") {

}
