//
//  JSEpoller.cpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include "JSEpoller.hpp"

JSEpoller::JSEpoller(bool bEt)
{
    _iEpollfd   = -1;
    _pevs       = NULL;
    _et         = bEt;
    _max_connections = 1024;
}

JSEpoller::~JSEpoller()
{
    if(_pevs != NULL)
    {
        delete[] _pevs;
        _pevs = NULL;
    }
    
    if(_iEpollfd > 0)
    {
        close(_iEpollfd);
    }
}

void JSEpoller::ctrl(int fd, long long data, __uint32_t events, int op)
{
    struct epoll_event ev;
    ev.data.u64 = data;
    if(_et)
    {
        ev.events   = events | EPOLLET ;
    }
    else
    {
        ev.events   = events;
    }
    
    epoll_ctl(_iEpollfd , op, fd, &ev);
}

void JSEpoller::create(int max_connections)
{
    _max_connections = max_connections;
    
    _iEpollfd = epoll_create(_max_connections + 1);
    
    if(_pevs != NULL)
    {
        delete[] _pevs;
    }
    
    _pevs = new epoll_event[_max_connections + 1];
}

void JSEpoller::add(int fd, long long data, __uint32_t event)
{
    ctrl(fd, data, event, EPOLL_CTL_ADD);
}

void JSEpoller::mod(int fd, long long data, __uint32_t event)
{
    ctrl(fd, data, event, EPOLL_CTL_MOD);
}

void JSEpoller::del(int fd, long long data, __uint32_t event)
{
    ctrl(fd, data, event, EPOLL_CTL_DEL);
}

int JSEpoller::wait(int millsecond)
{
    return epoll_wait(_iEpollfd , _pevs , _max_connections + 1, millsecond);
}