#include "reactor.h"
#include "protocol.h"
#include<vector>
#include<iostream>
#include<time.h>
#include<stdlib.h>

void printLater(void* arg){
	time_t currentTime;
	time(&currentTime);
	std::cout<<"call in the timeEvent and currentTime :"<<currentTime<<std::endl;
	return;
}

class myProtocol:public Protocol{
public:
	virtual void dataReceived(std::string data);
	virtual void connectionMade() ;
	virtual void connectionLost() ;
};


void myProtocol::dataReceived(std::string data){
	// writeToClient(data);
	// closeConnect();
	// return;

	//测试定时器
	int sleepTime = rand() % 20;
	time_t currentTime;
	time(&currentTime);
	std::cout<<"currentTime: "<<currentTime<<"----sleep time:"<<sleepTime<<std::endl;
	callLater(printLater, (void*)NULL, sleepTime);
	return;
}

void myProtocol::connectionMade(){
	std::cout<<"client["<<clientHost<<":"<<clientPort<<"]  connected "<<std::endl;
}

void myProtocol::connectionLost(){
	std::cout<<"client["<<clientHost<<":"<<clientPort<<"]  disconnected "<<std::endl;
}



int main(){
	srand(time(NULL));
	Reactor<myProtocol> reactor;
	reactor.listenPort(12345);
	reactor.run();

}