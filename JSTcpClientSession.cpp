//
//  JSTcpClientSession.cpp
//  ipncServer
//
//  Created by jeason on 15/12/10.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <unistd.h>
#include <iostream>
#include "JSTcpClientSession.hpp"

using namespace std;

JSTcpClientSessionItem::JSTcpClientSessionItem(int fd)
:_fd(fd)
{
    _recvBuffer = new string();
    _lastRefreshTime = time(NULL);
}
JSTcpClientSessionItem::~JSTcpClientSessionItem()
{
    delete _recvBuffer;
    cout<<"close fd"<<_fd<<endl;
    close(_fd);
}

void JSTcpClientSessionItem::appendData(char* dat,int len)
{
    _recvBuffer->append(dat,len);
    _lastRefreshTime = time(NULL);
}
std::string* JSTcpClientSessionItem::getData()
{
    return _recvBuffer;
}
void JSTcpClientSessionItem::clearData()
{
    _recvBuffer->clear();
}
time_t JSTcpClientSessionItem::getSefreshTime()
{
    return _lastRefreshTime;
}




JSTcpClientSessionList::JSTcpClientSessionList(JSEpoller* epoller)
{
    _sessionMap = new JS_TCP_SESSION_MAP;
    _epoller = epoller;
}
JSTcpClientSessionList::~JSTcpClientSessionList()
{
    JS_TCP_SESSION_MAP::iterator it;
    for(it=_sessionMap->begin();it!=_sessionMap->end();++it) {
        JSTcpClientSessionItem* item = it->second;
        delete item;
    }
    delete _sessionMap;
}
void JSTcpClientSessionList::add(int fd)
{
    JSTcpClientSessionItem* item = new JSTcpClientSessionItem(fd);
    _sessionMap->insert(std::pair<int,JSTcpClientSessionItem*>(fd,item));
    _epoller->add(fd, fd, EPOLLIN);
}
void JSTcpClientSessionList::del(int fd)
{
    JS_TCP_SESSION_MAP::iterator it= _sessionMap->find(fd);
    if(it != _sessionMap->end()) {
        JSTcpClientSessionItem* item = it->second;;
        delete item;
        cout<<"delete item"<<endl;
        _sessionMap->erase(it);
    }
    _epoller->del(fd, fd, EPOLLIN);
}

JSTcpClientSessionItem* JSTcpClientSessionList::get(int fd)
{
    JS_TCP_SESSION_MAP::iterator it= _sessionMap->find(fd);
    if(it != _sessionMap->end()) {
        JSTcpClientSessionItem* item = it->second;;
        return item;
    }
    return NULL;
}


JSTcpClientSession::JSTcpClientSession(JSNetPkgHandleBase* pkgHandle,JSEpoller* epoller)
{
    cout<<__func__<<endl;
    _pkgHandle = pkgHandle;
    _sessionsList = new JSTcpClientSessionList(epoller);
}
JSTcpClientSession::~JSTcpClientSession()
{
    delete _sessionsList;
}
void JSTcpClientSession::add(int fd)
{
    _sessionsList->add(fd);
}
void JSTcpClientSession::del(int fd)
{
    _sessionsList->del(fd);
}

void JSTcpClientSession::appendData(int fd,char* dat,int len)
{
    _sessionsList->get(fd)->appendData(dat, len);
}
void JSTcpClientSession::handlePkg(int fd)
{
    _pkgHandle->handle(fd,_sessionsList);
}
void JSTcpClientSession::timeoutCheck(int timeoutSecond)
{
    
}

