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
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start ipncServer!\n";
    char* dat = (char*)malloc(sizeof(JSPeerProtocolRegist));
    JSPeerProtocolRegist* peer = (JSPeerProtocolRegist*)dat;
    peer->test();
    
    //cout<<peer.bodyLen<<endl;
    
    return 0;
}
#endif