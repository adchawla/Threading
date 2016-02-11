//
//  LogTiming.cpp
//  Threading
//
//  Created by Amandeep Chawla on 11/02/16.
//  Copyright © 2016 Amandeep Chawla. All rights reserved.
//

#include <iostream>
#include "LogTiming.h"

using namespace std;

LogTiming::LogTiming(const char * tagTimer ) {
    mTimerTag = tagTimer;
    mStartTime = time(NULL);
}

LogTiming::~LogTiming() {
    std::time_t endTime = time(NULL);
    std::cout<<mTimerTag<<" took about " << difftime(endTime, mStartTime )<< " seconds.\n";
}
