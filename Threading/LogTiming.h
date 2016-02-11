//
//  LogTiming.h
//  Threading
//
//  Created by Amandeep Chawla on 11/02/16.
//  Copyright © 2016 Amandeep Chawla. All rights reserved.
//

#ifndef LogTiming_h
#define LogTiming_h
#include <ctime>

class LogTiming {
    
public:
    LogTiming( const char * timerTag );
    ~LogTiming();
    
private:
    std::string mTimerTag;
    std::time_t mStartTime;
};

#endif /* LogTiming_h */
