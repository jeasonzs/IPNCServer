//
//  JSNetPkgHandleP2P.hpp
//  ipncServer
//
//  Created by jeason on 15/12/11.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSNetPkgHandleP2P_hpp
#define JSNetPkgHandleP2P_hpp
#include <string>
#include <stdio.h>
#include "JSNetPkgHandleBase.hpp"
#include "JSTcpClientSession.hpp"
#include "JSPeerManager.hpp"


class JSNetPkgHandleP2P : public JSNetPkgHandleBase
{
public:
    JSNetPkgHandleP2P();
    virtual ~JSNetPkgHandleP2P();
private:
    virtual void handle(int fdToHandle);
    void heartResponse(int fd,int id);
    void registResponse(int fd,int id);
private:
    JSPeerManager* _peerManager;
};

#endif /* JSNetPkgHandleP2P_hpp */
