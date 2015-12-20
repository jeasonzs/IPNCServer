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
    _peerManager = new JSPeerManager();
}
JSNetPkgHandleP2P::~JSNetPkgHandleP2P()
{
    cout<<__func__<<endl;
}
void JSNetPkgHandleP2P::handle(int fdToHandle)
{
    cout<<"recv data:"<<*(_sessionList->get(fdToHandle)->getData())<<endl;
    _sessionList->get(fdToHandle)->clearData();
    _sessionList->del(fdToHandle);
}
