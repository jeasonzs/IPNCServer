//
//  JSPeerProtocol.cpp
//  IPNCServer
//
//  Created by jeason on 15/12/20.
//  Copyright © 2015年 letv. All rights reserved.
//

#include "JSPeerProtocol.hpp"


JSPeerProtocolHeader::JSPeerProtocolHeader(int iType,int iFromId,int iToId,int iBodyLen) {
    startCode = JS_PEER_START_CODE;
    type = iType;
    fromId = iFromId;
    toId = iToId;
    bodyLen = iBodyLen;
}


JSPeerProtocolHeader* JSPeerProtocolHeader::mapPkg(const char* dat,int len,int& pos)
{
    pos = 0;
    JSPeerProtocolHeader* header = NULL;
    while((len-pos) >= sizeof(JSPeerProtocolHeader)) {
        header = (JSPeerProtocolHeader*)(dat+pos);
        if(header->startCode == JS_PEER_START_CODE) {
            if((len-pos) >= (sizeof(JSPeerProtocolHeader)+header->bodyLen)) {
                return header;
            }
            else {
                return NULL;
            }
        }
        pos += 4;
    }
    return NULL;
}

JSPeerProtocolRegist::JSPeerProtocolRegist(int iFromId,int iToId)
:JSPeerProtocolHeader(JS_PEER_MSG_REGIST,
                      iFromId,
                      iToId,
                      sizeof(*this)-sizeof(JSPeerProtocolHeader)){
    peerName[0] = '\0';
    peerPasswd[0] = '\0';
}

JSPeerProtocolRegistResponse::JSPeerProtocolRegistResponse(int iFromId,int iToId)
:JSPeerProtocolHeader(JS_PEER_MSG_REGIST_RESPONSE,
                      iFromId,
                      iToId,
                      sizeof(*this)-sizeof(JSPeerProtocolHeader)){
    result = 0;
}
    


JSPeerProtocolHeart::JSPeerProtocolHeart(int iFromId,int iToId)
:JSPeerProtocolHeader(JS_PEER_MSG_HEART,
                      iFromId,
                      iToId,
                      sizeof(*this)-sizeof(JSPeerProtocolHeader)){
}


JSPeerProtocolHeartResponse::JSPeerProtocolHeartResponse(int iFromId,int iToId)
:JSPeerProtocolHeader(JS_PEER_MSG_HEART_RESPONSE,
                      iFromId,
                      iToId,
                      sizeof(*this)-sizeof(JSPeerProtocolHeader)){
}
