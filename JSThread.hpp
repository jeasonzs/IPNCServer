//
//  thread.hpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSThread_hpp
#define JSThread_hpp

#include <pthread.h>


class JSThread
{
protected:
    JSThread();
    virtual ~JSThread();
    
public:
    void start();
    void stop();
    bool isRuning() const;
    
protected:
    virtual void run() = 0;
    bool needExit() const;
private:
    pthread_t _thread_t;
    static void* threadFunc(void *);
    volatile bool _isRuning;
    volatile bool _needExit;
};

#endif /* JSThread_hpp */
