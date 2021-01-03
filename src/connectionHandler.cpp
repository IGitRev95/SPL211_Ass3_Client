#include "../include/connectionHandler.h"

#include <utility>

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
 
ConnectionHandler::ConnectionHandler(string host, short port): host_(std::move(host)), port_(port), io_service_(), socket_(io_service_){}
    
ConnectionHandler::~ConnectionHandler() {
    close();
}
 
bool ConnectionHandler::connect() {
    std::cout << "Starting connect to " 
        << host_ << ":" << port_ << std::endl;
    try {
		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
		boost::system::error_code error;
		socket_.connect(endpoint, error);
		if (error)
			throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
 
bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
			tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);			
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
			tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}

bool ConnectionHandler::sendOp(Operation &opToSend) {
    char bytesBuff[1024]; // bytes array to encode to
    int amountOfBytesToWrite=OperationEncoderDecoder::encode(opToSend, bytesBuff); //encode Operation to the bytes Array
    if(amountOfBytesToWrite!=-1)
    {
        return sendBytes(bytesBuff,amountOfBytesToWrite); //write the encoded operation to the socket for sending
    }
    return false;
}

bool ConnectionHandler::getOp(ReplyOp** opReceived) {
    char bytesBuff[1024]; // bytes array for storing gathered received message bytes
    if(!buildBytesArray(bytesBuff)) // gather entire message bites
        return false;
    if(OperationEncoderDecoder::decode(bytesBuff,opReceived)) // decode operation from bytes array
        return true;
    return false;
}

bool ConnectionHandler::buildBytesArray(char bytes[]) {
    char ch;
    int readingIndex=0;
    try {
        //reading opCode + MessageOpCode
        for(;readingIndex<4;readingIndex++)
        {
            if(!getBytes(&ch, 1))
            {
                return false;
            }
            bytes[readingIndex]=ch;
        }
        short opCode=OperationEncoderDecoder::bytesToShort(bytes);
        //if it's ACK read extra necessary data
        if(opCode==12)
        {
            do{
                if(!getBytes(&ch, 1))
                {
                    return false;
                }
                bytes[readingIndex]=ch;
                readingIndex++;
            }while ('\0' != ch);
        }
    } catch (std::exception& e) {
        std::cerr << "recv failed2 (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
