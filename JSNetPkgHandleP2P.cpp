//
//  JSNetPkgHandleP2P.cpp
//  ipncServer
//
//  Created by jeason on 15/12/11.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
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
    delete _peerManager;
}
void JSNetPkgHandleP2P::heartResponse(int fd,int id)
{
    JSPeerProtocolHeartResponse response(JS_PEER_ID_SERVER,id);
    send(fd,(char*)&response,sizeof(response),0);
}
void JSNetPkgHandleP2P::registResponse(int fd,int id)
{
    JSPeerProtocolRegistResponse response(JS_PEER_ID_SERVER,id);
    send(fd,(char*)&response,sizeof(response),0);
}

void JSNetPkgHandleP2P::handle(int fdToHandle)
{
    JSPeerProtocolHeader* header = NULL;
    string* recvData = _sessionList->get(fdToHandle)->getData();
    int pos = 0;
    header = JSPeerProtocolHeader::mapPkg(recvData->c_str(), recvData->length(), pos);
    if(header) {
        switch (header->type) {
			case JS_PEER_MSG_REGIST:{
				cout<<"regist msg"<<endl;
				_peerManager->add(header->fromId);
				_peerManager->setFd(header->fromId,fdToHandle);
				cout<<"fd="<<fdToHandle<<",_peerManager->size()="<<_peerManager->size()<<endl;
				registResponse(fdToHandle, header->fromId);
			}
				break;


			case JS_PEER_MSG_HEART:{
				cout<<"heart msg"<<endl;
				heartResponse(fdToHandle, header->fromId);
			}
				break;


			case JS_PEER_MSG_CONNECT_RESPONSE:{
				cout<<"Connect response msg"<<endl;
				JSPeerProtocolConnectResponse* connectResponse = (JSPeerProtocolConnectResponse*)(header);
				int fdSend = _peerManager->getFd(connectResponse->toId);
				send(fdSend,(char*)connectResponse,sizeof(JSPeerProtocolConnectResponse),0);
			}
				break;

			case JS_PEER_MSG_CONNECT:{
				cout<<"Connect msg"<<endl;
				JSPeerProtocolConnect* connect = (JSPeerProtocolConnect*)header;
				int fdSend = _peerManager->getFd(connect->toId);
				if(fdSend >= 0) {
					send(fdSend,(char*)connect,sizeof(JSPeerProtocolConnect),0);
				}
				else {
					JSPeerProtocolConnectResponse response(JS_PEER_ID_SERVER,connect->fromId);
					response.status = JS_PEER_CONNECT_STATUS_OFFLINE;
					response.iceInfo[0] = '\0';
					send(fdToHandle,(char*)&response,sizeof(JSPeerProtocolConnectResponse),0);
				}
			}
				break;

            default:
                break;
        }
    }
    cout<<"recv data:"<<_sessionList->get(fdToHandle)->getData()->length()<<endl;
    _sessionList->get(fdToHandle)->clearData();
}
