//
//  JSTcpServer.cpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include "JSTcpServer.hpp"
#include "JSNetPkgHandleBase.hpp"

using namespace std;

JSTcpServer::JSTcpServer()
{
    cout<<__func__<<endl;
    _clientManager = NULL;
    _fd = -1;
    
}


JSTcpServer::~JSTcpServer()
{
    cout<<__func__<<endl;
    stopServer();
}


int JSTcpServer::startServer(int port,JSNetPkgHandleBase* pkgHandle,int maxSessions)
{
    
    _fd = createSocket(port);
    if(_fd <= 0) {
        return _fd;
    }
    _clientManager = new JSTcpClientManager(pkgHandle,maxSessions);
    start();
    return 0;
}

int JSTcpServer::stopServer()
{
    stop();
    if(_fd >= 0) {
        close(_fd);
    }
    if(_clientManager) {
        delete _clientManager;
        _clientManager = NULL;
    }
    return 0;
}


void JSTcpServer::run()
{
    int acceptFd = -1;
    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(struct sockaddr_in);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    memset(&clientAddr,0,sizeof(struct sockaddr_in));
    setsockopt(_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));
    while(false == needExit()) {
        acceptFd = accept(_fd, (sockaddr*)&clientAddr, &len);
        if(acceptFd>=0) {
            cout<<"accept from:"<<inet_ntoa(clientAddr.sin_addr)<<":"<<clientAddr.sin_port<<endl;
            if(_clientManager) {
                cout<<"fd="<<acceptFd<<endl;
                _clientManager->addClient(acceptFd);
            }
        }
    }
}

int JSTcpServer::createSocket(int port)
{
    struct sockaddr_in s_add;
    int fd=-1;
    
    fd= socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        cout<<"Listen()>>socket error!!!!"<<endl;
        return -1;
    }
    
    bzero(&s_add,sizeof(struct sockaddr_in));
    
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr= INADDR_ANY;
    s_add.sin_port=htons(port);
    
    int flag = 1;
    if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0)
    {
        cout<<"Listen()>>setsockopt error!!!!"<<endl;
        close(fd);
        return -1;
    }
    
    if (bind(fd, (struct sockaddr *)&s_add, sizeof(s_add)) < 0)
    {
        cout<<"Listen()>>bind error!!!!"<<endl;
        close(fd);
        return -1;
    }
    if (listen(fd, 10) < 0)
    {
        cout<<"Listen()>>listen error!!!!"<<endl;
        close(fd);
        return -1;
    }
    return fd;
}
