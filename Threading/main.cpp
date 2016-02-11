#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>

#include "AutoReleaseLock.hpp"
#include "LogTiming.h"

using namespace std;
mutex mx;
size_t throughput = 0;

void CopyFile(const char * source, const char * destination, size_t bufferSize ) {
    
    char * buffer = new char[ bufferSize ];
 
    ifstream sourceFile( source, ios::in | ios::binary );
    ofstream destinationFile( destination, ios::out | ios::binary );
    
    while ( sourceFile.is_open() ) {
        sourceFile.read( buffer, bufferSize );
        size_t bytesRead = sourceFile.gcount();
        if ( bytesRead > 0 ) {
            destinationFile.write( buffer, bytesRead );
            AutoReleaseLock lock(mx);
            throughput += bytesRead;
        } else {
            sourceFile.close();
            destinationFile.close();
            break;
        }
        if ( sourceFile.bad() || sourceFile.eof() || sourceFile.fail() ) {
            sourceFile.close();
            destinationFile.close();
            break;
        }
    }
}

int main()
{
    LogTiming timer = LogTiming("main");
    //pass a function to thread
    size_t bufferSize = 20 * 1024 * 1024;
    throughput = 0;
    thread t1(CopyFile, "/Users/amandeep/temp/1.mp4", "/Users/amandeep/temp/dest/1.mp4", bufferSize);
    thread t2(CopyFile, "/Users/amandeep/temp/2.mp4", "/Users/amandeep/temp/dest/2.mp4", bufferSize);
    if ( t1.joinable() )
        t1.join();
    if ( t2.joinable() )
        t2.join();
    std::cout<<"Total bytes transferred: "<<throughput<<"\n";
}