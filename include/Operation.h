//
// Created by spl211 on 27/12/2020.
//

#ifndef CLIENT_OPERATION_H
#define CLIENT_OPERATION_H


#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

/**
 * command class type
 */

class Operation{
private:
    short _opCode;
    std::string _interfaceCommand; //command string as expected to receive by user or be printed to user

protected:
    std::vector<std::string> _arguments; //theres no reason derived class could not direct interact with it

    // Constructors which only be called by derived classes because there's no operation without a specific type
    Operation(short opcode, std::string interface);
    Operation(short opcode, std::string interface, std::vector<std::string> argsForOp);

    std::string getArgumentsAsString();//returning arguments in one string

public:
    //Getters
    short getOpCode() const;
    std::string getInterfaceCommand();
    const std::vector<std::string> &getArguments() const;
    //Setters
    void setArguments(std::string argsForOp);//gets the op arguments as string and splits them by the ' 'chat to the string arguments vector
    /**
     * receives a string toSplit and a char delimiter and split the string to a vector of strings
     * where the splitting is defend by the delimiter char.
     * @param toSplit
     * @param delimiter
     * @return
     */
    static std::vector<std::string> splitString(const std::string& toSplit,char delimiter);
    /**
     * returning a string which constructed from the charArrayToConvert
     * starting from index poss_s and stopping by the delimiter char.
     * @param charArrayToConvert
     * @param delimiter
     * @param poss_s
     * @return
     */
    static std::string charArrayTostring(const char *charArrayToConvert, char delimiter, int poss_s);
    std::string toString();
    virtual ~Operation()=default;
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

/**
 * class of server replies operations.
 * used as base class for ACK & ERROR operations
 */
class ReplyOp: public Operation{
private:
    short _replyOf;
protected:
    //those constructors are protected from the same reason the Operation constructors are protected
    ReplyOp(short opCod,std::string interface);
    ReplyOp(short opCod,std::string interface,short replyOf);

public:
    virtual std::string replyToString()=0;
    virtual ~ReplyOp()=default;

    short getReplyOpOf() const; // Getter
};

class AcknowledgementOp: public ReplyOp{
public:
    AcknowledgementOp();
    AcknowledgementOp(short ackOf);

    std::string replyToString();

    short getAckOf() const;
};

class ErrorOp: public ReplyOp{
public:
    ErrorOp();
    ErrorOp(short errorOf);

    std::string replyToString();

    short getErrorOf() const;
};

#endif //CLIENT_OPERATION_H
