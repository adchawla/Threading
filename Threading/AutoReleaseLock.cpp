//
//  AutoReleaseLock.cpp
//  Threading
//
//  Created by Amandeep Chawla on 11/02/16.
//  Copyright © 2016 Amandeep Chawla. All rights reserved.
//

#include "AutoReleaseLock.hpp"

AutoReleaseLock::AutoReleaseLock(std::mutex & mutex )
    : mMutex(mutex)
{
    mMutex.lock();
}

AutoReleaseLock::~AutoReleaseLock() {
    mMutex.unlock();
}

void AutoReleaseLock::Lock() {
    mMutex.lock();
}

void AutoReleaseLock::Unlock() {
    mMutex.unlock();
}