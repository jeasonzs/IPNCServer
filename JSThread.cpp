//
//  thread.cpp
//  ipncServer
//
//  Created by jeason on 15/12/8.
//  Copyright © 2015年 letv. All rights reserved.
//
#include <iostream>
#include <pthread.h>
#include "JSThread.hpp"

using namespace std;
/**
 *  JSThread
 */
JSThread::JSThread()
:_needExit(false),
_isRuning(false),
_thread_t(0)
{
}

/**
 *  ~JSThread
 */
JSThread::~JSThread(void)
{

}

/**
 *  start the thread
 */
void JSThread::start()
{
    _needExit = false;
    _isRuning = true;
    pthread_create(&_thread_t, NULL, threadFunc, this);
}

/**
 *  stop the thread
 */
void JSThread::stop()
{
    _needExit = true;
    pthread_join(_thread_t,NULL);
}

/**
 *  judge if the thread is runing
 *
 *  @return : thread runing state
 */
bool JSThread::isRuning() const
{
    return _isRuning;
}

/**
 *  judge is need to stop the thread
 *
 *  @return : need exit
 */
bool JSThread::needExit() const
{
    return _needExit;
}

/**
 *  the thread func to run
 *
 *  @param This : the function is a static,so give a instance
 *
 *  @return : NULL
 */
void*  JSThread::threadFunc(void *This)
{
    JSThread* This_ = reinterpret_cast<JSThread*>(This);
    This_->run();
    This_->_isRuning = false;
    return NULL;
}

