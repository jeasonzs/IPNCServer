//
//  JSPeerManager.hpp
//  IPNCServer
//
//  Created by jeason on 15/12/19.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSPeerManager_hpp
#define JSPeerManager_hpp

#include <stdio.h>
#include <map>
class JSPeerListItem
{
public:
    JSPeerListItem(int id):_id(id){};
    ~JSPeerListItem() {};

public:
    void setFd(int fd) {_fd = fd;};
    int getFd() {return _fd;};
    
private:
    int _id;
    int _fd;
};

typedef std::map<int, JSPeerListItem*> JS_PEER_LIST_MAP;

class JSPeerManager : public JS_PEER_LIST_MAP
{
public:
    JSPeerManager();
    ~JSPeerManager();
    
public:
    void add(int id);
    void del(int id);
    void setFd(int id,int fd);
    int getFd(int id);
};
#endif /* JSPeerManager_hpp */
