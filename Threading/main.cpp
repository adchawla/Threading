#include <iostream>
#include <thread>
using namespace std;

class myFunctor
{
public:
    void operator()()
    {
        cout << "This is my function object" << endl;
    }
    
    void publicFunction()
    {
        cout << "public function of myFunctor class is called" << endl;
    }
};

int main()
{
    //pass a function to thread
    myFunctor myFunc;
    thread funcTest1(&myFunctor::publicFunction, myFunc);
    if ( funcTest1.joinable())
        funcTest1.join();
}