//
//  JSPeerProtocol.hpp
//  IPNCServer
//
//  Created by jeason on 15/12/20.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSPeerProtocol_hpp
#define JSPeerProtocol_hpp

#include <stdio.h>


#define JS_PEER_ID_SERVER           0x00000000
#define JS_PEER_ID_BROADCAST        0xffffffff




#define JS_PEER_MSG_REGIST          0x00000000
#define JS_PEER_MSG_HEART           0x00000001


#define JS_PEER_MSG_REGIST_RESPONSE 0x10000000
#define JS_PEER_MSG_HEART_RESPONSE  0x10000001


class JSPeerProtocolHeader
{
public:
    int type;
    int fromId;
    int toId;
    int bodyLen;
    JSPeerProtocolHeader(int iType,int iFromId,int iToId,int iBodyLen);
};


class JSPeerProtocolRegist : public JSPeerProtocolHeader
{
public:
    char peerName[32];
    char peerPasswd[32];
    JSPeerProtocolRegist(int iFromId,int iToId);
};

class JSPeerProtocolRegistResponse : public JSPeerProtocolHeader
{
public:
    int result;
    JSPeerProtocolRegistResponse(int iFromId,int iToId);
};


class JSPeerProtocolHeart : public JSPeerProtocolHeader
{
public:
    JSPeerProtocolHeart(int iFromId,int iToId);
};

class JSPeerProtocolHeartResponse : public JSPeerProtocolHeader
{
public:
    JSPeerProtocolHeartResponse(int iFromId,int iToId);;
};


#endif /* JSPeerProtocol_hpp */
