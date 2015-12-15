//
//  JSTcpServer.hpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSTcpServer_hpp
#define JSTcpServer_hpp

#include <stdio.h>
#include "JSThread.hpp"
#include "JSTcpClientManager.hpp"


class JSTcpServer : public JSThread
{
public:
    JSTcpServer(int port);
    ~JSTcpServer();

public:
    int startServer(JSTcpClientManager *clientManager);
    int stopServer();

private:
    virtual void run();
    int createSocket(int port);
    
    
private:
    int _port;
    int _fd;
    JSTcpClientManager *_clientManager;
    
};
#endif /* JSTcpServer_hpp */
