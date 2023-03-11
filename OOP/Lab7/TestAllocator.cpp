#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "Allocator.h"
// include header of your allocator here

template <class T>
using MyAllocator =
    Allocator<T>;  // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;
const int TestSize = 10000;
const int PickSize = 1000;
const int SmallSize = 100;

#define USE_MYCLASS

#ifdef USE_MYCLASS

class MyClass{
private:
    int x,y;
public:
    MyClass(int a,int b):x(a),y(b){}
    MyClass(){}
    ~MyClass(){}
    friend bool operator==(MyClass& lhs,MyClass& rhs);
    friend bool operator!=(MyClass& lhs,MyClass& rhs);
};
bool operator==(MyClass& lhs,MyClass& rhs){
    return (lhs.x==rhs.x&&lhs.y==rhs.y);
}
bool operator!=(MyClass& lhs,MyClass& rhs){
    return !(lhs==rhs);
}
#endif


int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);
    std::uniform_int_distribution<> dis_small(1, SmallSize);

    // vector creation

    using IntVec = std::vector<int, MyAllocator<int>>;
    std::vector<IntVec, MyAllocator<IntVec>> vecints(TestSize);
    for (int i = 0; i < TestSize; i++) vecints[i].resize(dis(gen));

    using PointVec = std::vector<Point2D, MyAllocator<Point2D>>;
    std::vector<PointVec, MyAllocator<PointVec>> vecpts(TestSize);
    for (int i = 0; i < TestSize; i++) vecpts[i].resize(dis(gen));


#ifdef USE_MYCLASS
    using MyVec = std::vector<MyClass, MyAllocator<MyClass>>;
    std::vector<MyVec, MyAllocator<MyVec>> vecmyclass(TestSize);
    for (int i = 0; i < TestSize; i++) vecmyclass[i].resize(dis(gen));
#endif

    // vector resize
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < PickSize; i++) {
        int idx = dis(gen) - 1;
        int size = dis_small(gen);
        vecints[idx].resize(size);
        // vecpts[idx].resize(size);
    }
    auto end = std::chrono::high_resolution_clock::now();

#ifdef USE_MYCLASS
    for (int i = 0; i < PickSize; i++) {
        int idx = dis(gen) - 1;
        int size = dis_small(gen);
        vecmyclass[idx].resize(size);
    }
#endif

    // vector element assignment
    {
        int val = 10;
        int idx1 = dis(gen) - 1;
        int idx2 = vecints[idx1].size() / 2;
        vecints[idx1][idx2] = val;
        if (vecints[idx1][idx2] == val)
            std::cout << "correct assignment in vecints: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecints: " << idx1
                      << std::endl;
    }
    {
        Point2D val(11, 15);
        int idx1 = dis(gen) - 1;
        int idx2 = vecpts[idx1].size() / 2;
        vecpts[idx1][idx2] = val;
        if (vecpts[idx1][idx2] == val)
            std::cout << "correct assignment in vecpts: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecpts: " << idx1
                      << std::endl;
    }
#ifdef USE_MYCLASS
    {
        MyClass val(11, 15);
        int idx1 = dis(gen) - 1;
        int idx2 = vecmyclass[idx1].size() / 2;
        // vecmyclass[idx1][idx2] = val;
        /**test whether the allocator supports ctors 
         * that has more than 1 argument. 
         * the program cannot pass the compilation.
        */
        vecmyclass[idx1].get_allocator().construct(&vecmyclass[idx1][idx2],11,15);
        if (vecmyclass[idx1][idx2] == val)
            std::cout << "correct assignment in vecmyclass: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecmyclass: " << idx1
                      << std::endl;
    }
#endif

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
              << std::endl;

    return 0;
}