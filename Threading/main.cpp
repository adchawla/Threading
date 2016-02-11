#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>


#include "LogTiming.h"
using namespace std;

mutex m;

void CopyFile(const char * source, const char * destination, char * bufferToUse, size_t bufferSize ) {
    
    ifstream sourceFile( source, ios::in | ios::binary );
    ofstream destinationFile( destination, ios::out | ios::binary );
    
    while ( sourceFile.is_open() ) {
        m.lock();
        sourceFile.read( bufferToUse, bufferSize );
        size_t bytesRead = sourceFile.gcount();
        if ( bytesRead > 0 ) {
            destinationFile.write( bufferToUse, bytesRead );
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
        m.unlock();
    }
}

int main()
{
    LogTiming timer = LogTiming("main");
    //pass a function to thread
    size_t bufferSize = 20 * 1024 * 1024;
    char * buffer = new char[bufferSize];
    thread t1(CopyFile, "/Users/amandeep/temp/1.mp4", "/Users/amandeep/temp/dest/1.mp4", buffer, bufferSize);
    thread t2(CopyFile, "/Users/amandeep/temp/2.mp4", "/Users/amandeep/temp/dest/2.mp4", buffer, bufferSize);
    if ( t1.joinable() )
        t1.join();
    if ( t2.joinable() )
        t2.join();
}