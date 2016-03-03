#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>

#include "AutoReleaseLock.hpp"
#include "LogTiming.h"

using namespace std;

#define N 100
char buffer[ N ];
size_t countOfItmes = 0;
mutex mx;

#include <stdlib.h>

void Producer() {
	while ( true ) {
		char item = rand() % 26 + 'A';
		{
			AutoReleaseLock lock( mx );
			if ( countOfItmes == N - 1 ) {
				std::cerr << "Could not Push anything \n";
				continue;
			}
			buffer[ countOfItmes++ ] = item;
			std::cerr << "Pushed " << item << " at " << countOfItmes - 1 << " location\n";
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( rand() % 1000 ) );
	}
}

void Consumer() {
	while ( true ) {
		{
			AutoReleaseLock lock( mx );
			if ( countOfItmes == 0 ) {
				std::cerr << "Could not Pull anything \n";
				continue;
			}
			char item = buffer[ --countOfItmes ];
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