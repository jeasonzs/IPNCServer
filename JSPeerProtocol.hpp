//
//  JSPeerProtocol.hpp
//  IPNCServer
//
//  Created by jeason on 15/12/20.
//  Copyright 漏 2015骞� letv. All rights reserved.
//

#ifndef JSPeerProtocol_hpp
#define JSPeerProtocol_hpp

#include <stdio.h>


#define JS_PEER_START_CODE          	0x91bd3a74

#define JS_PEER_ID_SERVER           	0x00000000
#define JS_PEER_ID_BROADCAST        	0xffffffff




#define JS_PEER_MSG_REGIST          	0x00000000
#define JS_PEER_MSG_HEART           	0x00000001
#define JS_PEER_MSG_CONNECT         	0x00000002

#define JS_PEER_MSG_REGIST_RESPONSE 	0x10000000
#define JS_PEER_MSG_HEART_RESPONSE 		0x10000001
#define JS_PEER_MSG_CONNECT_RESPONSE  	0x10000002

class JSPeerProtocolHeader
{
public:
    int startCode;
    int type;
    int fromId;
    int toId;
    int bodyLen;
    JSPeerProtocolHeader(int iType,int iFromId,int iToId,int iBodyLen);
    static JSPeerProtocolHeader* mapPkg(const char* dat,int len,int& pos);
};


class JSPeerProtocolRegist : public JSPeerProtocolHeader
{
public:
    char peerName[32];
    char peerPasswd[32];
    JSPeerProtocolRegist(int iFromId,int iToId);
    void test(){peerName[12] = 'd';};
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
    JSPeerProtocolHeartResponse(int iFromId,int iToId);
};

class JSPeerProtocolConnect : public JSPeerProtocolHeader
{
public:
	char iceInfo[512];
	JSPeerProtocolConnect(int iFromId,int iToId);
};

class JSPeerProtocolConnectResponse : public JSPeerProtocolHeader
{
public:
	char iceInfo[512];
	JSPeerProtocolConnectResponse(int iFromId,int iToId);
};


#endif /* JSPeerProtocol_hpp */
