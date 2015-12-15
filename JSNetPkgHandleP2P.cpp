//
//  JSNetPkgHandleP2P.cpp
//  ipncServer
//
//  Created by jeason on 15/12/11.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <iostream>
#include <unistd.h>
#include "JSNetPkgHandleP2P.hpp"

using namespace std;

JSNetPkgHandleP2P::JSNetPkgHandleP2P()
{
    cout<<__func__<<endl;
}
JSNetPkgHandleP2P::~JSNetPkgHandleP2P()
{
    cout<<__func__<<endl;
}
void JSNetPkgHandleP2P::handle(int fdToHandle,JSTcpClientSessionList* sessionList)
{
    cout<<"recv data:"<<*(sessionList->get(fdToHandle)->getData())<<endl;
    sessionList->get(fdToHandle)->clearData();
    sessionList->del(fdToHandle);
}
