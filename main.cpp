#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#define print(x) std::cout << x << std::endl

std::mutex mtx;

std::vector<int> sharedData;

void showData() {
    // most optimized -> pointer to memory location
    for(auto itr = sharedData.begin(); itr != sharedData.end(); itr++) {
        print(*itr);
    }
}

void ExpensiveWork(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // t1, t2, t3 will all try to push at same time
    // causing issue and curruption in shareddata

    // lock the mtx
    {
        std::lock_guard<std::mutex> lock(mtx);
        sharedData.push_back(id);
    }
    // same as :
    // mtx.lock() sharedData.push_back(id) mtx.unlock()

    print("work done: " << id);
}

int main() {
    std::thread t1(ExpensiveWork, 1);
    std::thread t2(ExpensiveWork, 2);
    std::thread t3(ExpensiveWork, 3);
    print("rest of the work...");

    t1.join();
    t2.join();
    t3.join();

    print("all work done: ");
    showData();
}
