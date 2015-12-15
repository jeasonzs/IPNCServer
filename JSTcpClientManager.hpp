//
//  JSTcpClientProcess.hpp
//  ipncServer
//
//  Created by jeason on 15/12/9.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSTcpClientManager_hpp
#define JSTcpClientManager_hpp

#include <stdio.h>

#include <string>
#include "JSThread.hpp"
#include "JSNetPkgHandleBase.hpp"
#include "JSTcpClientSession.hpp"
#include "JSEpoller.hpp"
class JSTcpClient : public JSThread
{
public:
    JSTcpClient(JSNetPkgHandleBase* pkgHandle,int maxSessions);
    virtual ~JSTcpClient();

public:
    int add(int fd);

private:
    virtual void run();
   
private:
    JSTcpClientSession* _sessions;
    JSEpoller* _epoller;
};

class JSTcpClientManager
{
public:
    JSTcpClientManager(JSNetPkgHandleBase* pkgHandle,int maxSessions);
    virtual ~JSTcpClientManager();

public:
    int addClient(int fd);

private:
    JSTcpClient* _client;
};
#endif /* JSTcpClientManager_hpp */
