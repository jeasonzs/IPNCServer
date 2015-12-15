//
//  main.cpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "JSThread.hpp"
#include "JSTcpServer.hpp"
#include "JSTcpClientManager.hpp"
#include "JSNetPkgHandleP2P.hpp"
using namespace std;
bool mainStopFlg = false;

void SigintCb(int iSigNum)
{
    mainStopFlg=true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start ipncServer!\n";
    JSNetPkgHandleP2P* pkgHandle = new JSNetPkgHandleP2P();
    JSTcpClientManager* clientManager = new JSTcpClientManager(pkgHandle,100);
    
    JSTcpServer *tcpServer = new JSTcpServer(60000);
    tcpServer->startServer(clientManager);
    while (!mainStopFlg) {
        usleep(100*1000);
    }
    
    tcpServer->stopServer();
    delete tcpServer;
    delete clientManager;
    delete pkgHandle;
    
    return 0;
}
