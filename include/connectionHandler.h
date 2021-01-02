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
    ConnectionHandler(std::string host, short port); //// NOT CHANGED
    virtual ~ConnectionHandler(); //// NOT CHANGED
 
    // Connect to the remote machine
    bool connect(); //// NOT CHANGED
 
    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead); //// NOT CHANGED
 
	// Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite); //// NOT CHANGED

    // Close down the connection properly.
    void close(); //// NOT CHANGED

    //--------------------------------self addition to connection handler

    /**
     * sending Operation to server
     * @param opToSend
     * @return - successfulness
     */
    bool sendOp(Operation& opToSend);

    /**
     * setting opReceived with the decoded operation received from server
     * @param opReceived
     * @return - successfulness
     */
    bool getOp(ReplyOp** opReceived);

    /**
     * Gathering all the necessary bytes for operation decoding
     * @param bytes - char array to stored the socket read bytes
     * @return - successfulness
     */
    bool buildBytesArray(char bytes[]);
};
 
#endif