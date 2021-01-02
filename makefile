CC:=g++
CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread

all: BGRSclient

#add more dependencies files of the main (practicly every thing else)

BGRSclient: bin/connectionHandler.o bin/BGRegClient.o bin/UserInputReader.o bin/Operation.o bin/OperationEncoderDecoder.o
	@echo 'Building target: BGRSclient'
	@echo 'Invoking: C++ Linker'
#Building and linking (add all object (.o) files)    
	$(CC) -o bin/BGRSclient bin/connectionHandler.o bin/BGRegClient.o bin/UserInputReader.o bin/Operation.o bin/OperationEncoderDecoder.o $(LDFLAGS) #add dependencies .o files for linking !Before $(LDFLAGS)
	@echo 'Finishing building target: BGRSclient'
	@echo ' '

bin/connectionHandler.o: src/connectionHandler.cpp
	$(CC) $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp
	@echo 'Building .o from connectionHandler'

bin/BGRegClient.o: src/BGRegClient.cpp
	$(CC) $(CFLAGS) -o bin/BGRegClient.o src/BGRegClient.cpp
	@echo 'Building .o from BGRegClient'

bin/UserInputReader.o: src/UserInputReader.cpp
	$(CC) $(CFLAGS) -o bin/UserInputReader.o src/UserInputReader.cpp
	@echo 'Building .o from UserInputReader'
	
bin/Operation.o: src/Operation.cpp
	$(CC) $(CFLAGS) -o bin/Operation.o src/Operation.cpp
	@echo 'Building .o from Operation'

bin/OperationEncoderDecoder.o: src/OperationEncoderDecoder.cpp
	$(CC) $(CFLAGS) -o bin/OperationEncoderDecoder.o src/OperationEncoderDecoder.cpp
	@echo 'Building .o from OperationEncoderDecoder'

#make dependencies as well like above

#Clean the build directory
clean:
	rm -f bin/*
