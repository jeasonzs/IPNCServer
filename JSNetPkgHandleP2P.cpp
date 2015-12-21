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
#include "JSPeerProtocol.hpp"

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
    JSPeerProtocolHeader* header = NULL;
    string* recvData = _sessionList->get(fdToHandle)->getData();
    int pos = 0;
    header = JSPeerProtocolHeader::mapPkg(recvData->c_str(), recvData->length(), pos);
    if(header) {
        switch (header->type) {
                case JS_PEER_MSG_REGIST:
                cout<<"regist msg"<<endl;
                break;
                
            default:
                break;
        }
    }
    cout<<"recv data:"<<*(_sessionList->get(fdToHandle)->getData())<<endl;
    _sessionList->get(fdToHandle)->clearData();
    _sessionList->del(fdToHandle);
}
