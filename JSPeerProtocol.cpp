//
//  JSPeerProtocol.cpp
//  IPNCServer
//
//  Created by jeason on 15/12/20.
//  Copyright © 2015年 letv. All rights reserved.
//

#include "JSPeerProtocol.hpp"


JSPeerProtocolHeader::JSPeerProtocolHeader(int iType,int iFromId,int iToId,int iBodyLen) {
    type = iType;
    fromId = iFromId;
    toId = iToId;
    bodyLen = iBodyLen;
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
