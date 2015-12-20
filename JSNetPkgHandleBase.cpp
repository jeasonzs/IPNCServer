//
//  JSNetPkgHandleBase.cpp
//  ipncServer
//
//  Created by jeason on 15/12/9.
//  Copyright © 2015年 letv. All rights reserved.
//

#include "JSNetPkgHandleBase.hpp"


JSNetPkgHandleBase::JSNetPkgHandleBase()
{
    _sessionList = NULL;
}
JSNetPkgHandleBase::~JSNetPkgHandleBase()
{
    _sessionList = NULL;
}

void JSNetPkgHandleBase::setSessionList(JSTcpClientSessionList* sessionList)
{
    _sessionList = sessionList;
}