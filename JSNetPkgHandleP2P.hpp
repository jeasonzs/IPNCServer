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

class JSNetPkgHandleP2P : public JSNetPkgHandleBase
{
public:
    JSNetPkgHandleP2P();
    virtual ~JSNetPkgHandleP2P();
private:
    virtual void handle(int fdToHandle,JSTcpClientSessionList* sessionList);
};

#endif /* JSNetPkgHandleP2P_hpp */
