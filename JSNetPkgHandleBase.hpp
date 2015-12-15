//
//  JSNetPkgHandleBase.hpp
//  ipncServer
//
//  Created by jeason on 15/12/9.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSNetPkgHandleBase_hpp
#define JSNetPkgHandleBase_hpp

#include <stdio.h>
#include <string>

class JSTcpClientSessionList;

class JSNetPkgHandleBase
{
public:
    JSNetPkgHandleBase();
    virtual ~JSNetPkgHandleBase();

public:
    virtual void handle(int fdToHandle,JSTcpClientSessionList* sessionList)=0;
};
#endif /* JSNetPkgHandleBase_hpp */
