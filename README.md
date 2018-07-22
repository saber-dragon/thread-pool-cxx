# Thread Pool in C++

This repo implements a simple thread pool in C++, which is learned from the book "C++ Concurrency in Action" (Page 275).

## Usage 

```c++
#include <iostream>
#include "thread_pool.hh"

std::mutex gm;

void func() {
    gm.lock();
    std::cout << "Hello! I am " << std::this_thread::get_id() << std::endl;
    gm.unlock();
}

int
main(){
    ThreadPool thp;
    for (int i = 0;i < 10;++ i)
        thp.submit(func);

    gm.lock();
    std::cout << "main done\n" << std::endl;
    gm.unlock();

    return 0;
}
```

