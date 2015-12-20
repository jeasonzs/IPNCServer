//
//  JSPeerManager.cpp
//  IPNCServer
//
//  Created by jeason on 15/12/19.
//  Copyright © 2015年 letv. All rights reserved.
//

#include "JSPeerManager.hpp"


JSPeerManager::JSPeerManager()
{

}
JSPeerManager::~JSPeerManager()
{
    JS_PEER_LIST_MAP::iterator it;
    for(it=begin();it!=end();++it) {
        JSPeerListItem* item = it->second;
        delete item;
    }
}

void JSPeerManager::add(int id)
{
    JSPeerListItem* item = new JSPeerListItem(id);
    insert(std::pair<int,JSPeerListItem*>(id,item));
}
void JSPeerManager::del(int id)
{
    JS_PEER_LIST_MAP::iterator it= find(id);
    if(it != end()) {
        JSPeerListItem* item = it->second;;
        delete item;
        erase(it);
    }
}
void JSPeerManager::setFd(int id,int fd)
{
    JS_PEER_LIST_MAP::iterator it= find(id);
    if(it != end()) {
        JSPeerListItem* item = it->second;;
        item->setFd(fd);
    }
}
int JSPeerManager::getFd(int id)
{
    int fd = -1;
    JS_PEER_LIST_MAP::iterator it= find(id);
    if(it != end()) {
        JSPeerListItem* item = it->second;;
        fd =item->getFd();
    }
    return fd;
}


