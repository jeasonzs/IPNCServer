//
//  JSTcpClientSession.hpp
//  ipncServer
//
//  Created by jeason on 15/12/10.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSTcpClientSession_hpp
#define JSTcpClientSession_hpp


#include <string>
#include <map>
#include <stdio.h>
#include "JSEpoller.hpp"
#include "JSNetPkgHandleBase.hpp"
class JSTcpClientSessionItem
{
public:
    JSTcpClientSessionItem(int fd);
    ~JSTcpClientSessionItem();
public:
    void appendData(char* dat,int len);
    std::string* getData();
    void clearData();
    time_t getSefreshTime();
public:
    int _fd;
    std::string* _recvBuffer;
    time_t _lastRefreshTime;
};

typedef std::map<int, JSTcpClientSessionItem*> JS_TCP_SESSION_MAP;

class JSTcpClientSessionList
{
public:
    JSTcpClientSessionList(JSEpoller* epoller);
    ~JSTcpClientSessionList();
    
public:
    void add(int fd);
    void del(int fd);
    JSTcpClientSessionItem* get(int fd);
private:
    JS_TCP_SESSION_MAP* _sessionMap;
    JSEpoller* _epoller;
};

class JSTcpClientSession
{
public:
    JSTcpClientSession(JSNetPkgHandleBase* pkgHandle,JSEpoller* epoller);
    virtual ~JSTcpClientSession();

public:
    void add(int fd);
    void del(int fd);
    void appendData(int fd,char* dat,int len);
    void handlePkg(int fd);
    void timeoutCheck(int timeoutSecond);
    
protected:
    JSTcpClientSessionList* _sessionsList;
    JSNetPkgHandleBase* _pkgHandle;
};

#endif /* JSTcpClientSession_hpp */
