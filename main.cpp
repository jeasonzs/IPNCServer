//
//  main.cpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/time.h>

#include "JSThread.hpp"
#include "JSTcpServer.hpp"
#include "JSTcpClientManager.hpp"
#include "JSNetPkgHandleP2P.hpp"
#include "JSPeerProtocol.hpp"

using namespace std;
bool mainStopFlg = false;

void SigintCb(int iSigNum)
{
    mainStopFlg=true;
}


#if 1
int main(int argc, const char * argv[]) {
    // insert code here...
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start ipncServer!\n";
    JSNetPkgHandleP2P* pkgHandle = new JSNetPkgHandleP2P();
    
    JSTcpServer *tcpServer = new JSTcpServer();
    tcpServer->startServer(60000,pkgHandle,100);
    while (!mainStopFlg) {
        usleep(100*1000);
    }
    
    tcpServer->stopServer();
    delete tcpServer;
    delete pkgHandle;
    
    return 0;
}
#else



int main(int argc, const char * argv[]) {
    // insert code here...
//    signal(SIGINT,SigintCb);
//    signal(SIGALRM,SigintCb);
//    std::cout << "start ipncServer!\n";
//    char* dat = (char*)malloc(sizeof(JSPeerProtocolRegist));
//    JSPeerProtocolRegist* peer = (JSPeerProtocolRegist*)dat;
//    peer->test();
    
    //cout<<peer.bodyLen<<endl;
//	srand( (unsigned)time( NULL ) );          //初始化随机数
//	    for(int i = 0; i < 100;i++ )                          //打印出10个随机数
//	          printf( " %d\n", rand() );


	JSPeerManager peerManger;

	peerManger.add(100);
	peerManger.setFd(100,1000);

	cout<<"fd="<<peerManger.getFd(100)<<",size="<<peerManger.size()<<endl;
	peerManger.add(100);
	peerManger.setFd(100,100);
	cout<<"fd="<<peerManger.getFd(100)<<",size="<<peerManger.size()<<endl;
	return 0;

	for(int i=1;i<10002;i++) {
		peerManger.add(i);
		peerManger.setFd(i,i);
	}

	while(1) {
		struct timeval tpstart,tpend;
		float timeuse;
		int toFind = rand()%10000+1;
		gettimeofday(&tpstart,NULL);


		int fd = 0;//peerManger.getFd(toFind);
		for(int i =0;i<10000;i++) {
			//fd = peerManger.getFd(toFind);
		}

		gettimeofday(&tpend,NULL);
		timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
		tpend.tv_usec-tpstart.tv_usec;
		timeuse/=1000000;
		printf("toFind=%d,fd=%d,Used Time:%f\n",toFind,fd,timeuse);
		usleep(1000*20);
	}

    
    return 0;
}
#endif
