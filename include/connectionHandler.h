#ifndef CONNECTION_HANDLER__
#define CONNECTION_HANDLER__
                                           
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "OperationEncoderDecoder.h"

using boost::asio::ip::tcp;

class ConnectionHandler {
private:
	const std::string host_;
	const short port_;
	boost::asio::io_service io_service_;   // Provides core I/O functionality
	tcp::socket socket_; 
 
public:
    ConnectionHandler(std::string host, short port); //TODO:DO NOT TOUCH!!!
    virtual ~ConnectionHandler(); //TODO:DO NOT TOUCH!!!
 
    // Connect to the remote machine
    bool connect(); //TODO:DO NOT TOUCH!!!
 
    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead); //TODO:DO NOT TOUCH!!!
 
	// Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite); //TODO:DO NOT TOUCH!!!

    // Close down the connection properly.
    void close(); //TODO:DO NOT TOUCH!!!

    //--------------------------------self addition to connection handler

    //sending Operation to server
    bool sendOp(Operation& opToSend); //TODO:NOT FULLY TESTED

    //setting opReceived with the decoded operation received from server
    bool getOp(ReplyOp** opReceived); //TODO:NOT TESTED

    //gathering all the necessary bytes for operation decoding
    bool buildBytesArray(char bytes[]); //TODO:NOT TESTED
}; //class ConnectionHandler
 
#endif