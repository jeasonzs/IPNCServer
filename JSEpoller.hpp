//
//  JSEpoller.hpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSEpoller_hpp
#define JSEpoller_hpp

#include <assert.h>
#include <sys/epoll.h>

class JSEpoller
{
public:
    JSEpoller(bool bEt = true);
    ~JSEpoller();
    void create(int max_connections);
    void add(int fd, long long data, unsigned int event);
    void mod(int fd, long long data, unsigned int event);
    void del(int fd, long long data, unsigned int event);
    int wait(int millsecond);
    struct epoll_event& get(int i) { assert( _pevs != 0); return _pevs [i]; }
    
protected:
    
    void ctrl(int fd, long long data, __uint32_t events, int op);
    
protected:
    int _iEpollfd;
    int   _max_connections;
    struct epoll_event *_pevs;
    bool _et;
};

#endif /* JSEpoller_hpp */
