
//
//  JSTcpClientProcess.cpp
//  ipncServer
//
//  Created by jeason on 15/12/9.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include "JSTcpClientManager.hpp"
using namespace std;
JSTcpClient::JSTcpClient(JSNetPkgHandleBase* pkgHandle,int maxSessions)
{
    cout<<__func__<<endl;
    _epoller = new JSEpoller();
    _epoller->create(maxSessions);
    _sessions = new JSTcpClientSession(pkgHandle,_epoller);
    start();
}
JSTcpClient::~JSTcpClient()
{
    cout<<__func__<<endl;
    stop();
    delete _sessions;
    delete _epoller;
}

int JSTcpClient::add(int fd)
{
    fcntl( fd, F_SETFL, O_NONBLOCK);
    _sessions->add(fd);
    return 0;
}

void JSTcpClient::run()
{
    int pollResult = 0;
    while (!needExit()) {
        pollResult = _epoller->wait(1*1000);
        for (int i=0; i<pollResult; i++) {
            struct epoll_event event = _epoller->get(i);
            int fd = event.data.fd;
            if ((event.events & EPOLLERR) || (event.events & EPOLLHUP) || (!(event.events & EPOLLIN))) {
                fprintf (stderr, "epoll error\n");
                close (fd);
                _sessions->del(fd);
                continue;
            }
            else {
                
                int needClose = 0;
                while (1) {
                    ssize_t count;
                    char buf[512];
                    count = read (fd, buf, sizeof(buf));
                    if (count == -1) {
                        if (errno != EAGAIN) {
                            needClose = 1;
                        }
                        break;
                    }
                    else if (count == 0) {
                        break;
                    }
                    _sessions->appendData(fd, buf, count);
                }
                _sessions->handlePkg(fd);
                
                if (needClose) {
                    close (fd);
                    _sessions->del(fd);
                }
        
            }
        }
        
    }
}




JSTcpClientManager::JSTcpClientManager(JSNetPkgHandleBase* pkgHandle,int maxSessions)
{
    _client = new JSTcpClient(pkgHandle,maxSessions);
}

JSTcpClientManager::~JSTcpClientManager()
{
    delete _client;
}


int JSTcpClientManager::addClient(int fd)
{
    _client->add(fd);
    return 0;
}