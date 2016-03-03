#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
#include <condition_variable>

#include "AutoReleaseLock.hpp"
#include "LogTiming.h"

using namespace std;

#define N 100
char buffer[ N ];
size_t countOfItmes = 0;
mutex mx;
condition_variable cvProducer, cvConsumer;

#include <stdlib.h>

void Producer() {
	while ( true ) {
		char item = rand() % 26 + 'A';
		{
			std::unique_lock<std::mutex> lck( mx );
			if ( countOfItmes == N - 1 ) {
				cvProducer.wait( lck );
			}
			buffer[ countOfItmes++ ] = item;
			cvConsumer.notify_one();
			std::cerr << "Pushed " << item << " at " << countOfItmes - 1 << " location\n";
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( rand() % 1000 ) );
	}
}

void Consumer() {
	while ( true ) {
		{
			std::unique_lock<std::mutex> lck( mx );
			if ( countOfItmes == 0 ) {
				cvConsumer.wait( lck );
			}
			char item = buffer[ --countOfItmes ];
			cvProducer.notify_one();
			std::cerr << "Pulled " << item << " from " << countOfItmes << " location\n";
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( rand() % 1000 ) );
	}
}

int main()
{
    thread t1(Producer);
	thread t2( Consumer);
    if ( t1.joinable() )
        t1.join();
    if ( t2.joinable() )
        t2.join();
}