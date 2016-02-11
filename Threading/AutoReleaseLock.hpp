//
//  AutoReleaseLock.hpp
//  Threading
//
//  Created by Amandeep Chawla on 11/02/16.
//  Copyright © 2016 Amandeep Chawla. All rights reserved.
//

#ifndef AutoReleaseLock_hpp
#define AutoReleaseLock_hpp

#include <mutex>

class AutoReleaseLock {
public:
    AutoReleaseLock( std::mutex & mutex );
    ~AutoReleaseLock();
    
    void Lock();
    void Unlock();
    
private:
    std::mutex & mMutex;
};

#endif /* AutoReleaseLock_hpp */
