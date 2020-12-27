//
// Created by spl211 on 27/12/2020.
//

#ifndef CLIENT_OPERATION_H
#define CLIENT_OPERATION_H


#include <string>
#include <vector>

class Operation{
private:
    short _opCode;
    std::string _interfaceCommand;
    std::vector<std::string> _arguments;
protected:
    Operation(short opcode, std::string interface);
public:
    short getOpCode();//maybe protected
    std::string getInterfaceCommand(); //maybe protected
    std::string getArguments();//maybe protected
    std::string toString();
    void setArguments(std::string argsForOp);//gets the op arguments as string and splits them by the ' 'chat to the string arguments vector
};

class AdminRegOp: public Operation{
public:
    AdminRegOp();
};

class StudentRegOp: public Operation{
public:
    StudentRegOp();
};

class LoginReqOp: public Operation{
public:
    LoginReqOp();
};

class LogoutReqOp: public Operation{
public:
    LogoutReqOp();
};

class CourseRegOp: public Operation{
public:
    CourseRegOp();
};

class KdamCourseCheckOp: public Operation{
public:
    KdamCourseCheckOp();
};

class PrintCourseStatOp: public Operation{
public:
    PrintCourseStatOp();
};

class PrintStudentStatOp: public Operation{
public:
    PrintStudentStatOp();
};

class IsRegOp: public Operation{
public:
    IsRegOp();
};

class CourseUnRegOp : public Operation{
public:
    CourseUnRegOp();
};

class MyCoursesOp: public Operation{
public:
    MyCoursesOp();
};

class AcknowledgementOp: public Operation{
public:
    AcknowledgementOp();
};

class ErrorOp: public Operation{
public:
    ErrorOp();
};

#endif //CLIENT_OPERATION_H
