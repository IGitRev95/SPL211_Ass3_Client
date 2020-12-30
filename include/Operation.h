//
// Created by spl211 on 27/12/2020.
//

#ifndef CLIENT_OPERATION_H
#define CLIENT_OPERATION_H


#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_array.hpp>

class Operation{
private:
    short _opCode;
    std::string _interfaceCommand;
    std::vector<std::string> _arguments;
protected:
    Operation(short opcode, std::string interface);
    Operation(short opcode, std::string interface, std::vector<std::string> argsForOp);
public:
    short getOpCode() const;//maybe protected
    std::string getInterfaceCommand(); //maybe protected
    const std::vector<std::string> &getArguments() const;
    std::string getArgumentsAsString();//maybe protected
    std::string toString();//TODO:not Tested
    void setArguments(std::string argsForOp);//gets the op arguments as string and splits them by the ' 'chat to the string arguments vector
    void setArguments(std::vector<std::string> argsForOp);
    static std::vector<std::string> splitString(const std::string toSplit,char delimiter);
    static std::string charArrayTostring(const char *charArrayToConvert, char delimiter, int poss_s); //TODO:not Tested
};

class AdminRegOp: public Operation{
public:
    AdminRegOp();
    AdminRegOp(std::vector<std::string> argsForOp);
};

class StudentRegOp: public Operation{
public:
    StudentRegOp();
    StudentRegOp(std::vector<std::string> argsForOp);
};

class LoginReqOp: public Operation{
public:
    LoginReqOp();
    LoginReqOp(std::vector<std::string> argsForOp);
};

class LogoutReqOp: public Operation{
public:
    LogoutReqOp();
    LogoutReqOp(std::vector<std::string> argsForOp);
};

class CourseRegOp: public Operation{
public:
    CourseRegOp();
    CourseRegOp(std::vector<std::string> argsForOp);
};

class KdamCourseCheckOp: public Operation{
public:
    KdamCourseCheckOp();
    KdamCourseCheckOp(std::vector<std::string> argsForOp);
};

class PrintCourseStatOp: public Operation{
public:
    PrintCourseStatOp();
    PrintCourseStatOp(std::vector<std::string> argsForOp);
};

class PrintStudentStatOp: public Operation{
public:
    PrintStudentStatOp();
    PrintStudentStatOp(std::vector<std::string> argsForOp);
};

class IsRegOp: public Operation{
public:
    IsRegOp();
    IsRegOp(std::vector<std::string> argsForOp);
};

class CourseUnRegOp : public Operation{
public:
    CourseUnRegOp();
    CourseUnRegOp(std::vector<std::string> argsForOp);
};

class MyCoursesOp: public Operation{
public:
    MyCoursesOp();
    MyCoursesOp(std::vector<std::string> argsForOp);
};

class AcknowledgementOp: public Operation{
public:
    AcknowledgementOp();
    AcknowledgementOp(std::vector<std::string> argsForOp);
};

class ErrorOp: public Operation{
public:
    ErrorOp();
    ErrorOp(std::vector<std::string> argsForOp);
};

#endif //CLIENT_OPERATION_H
