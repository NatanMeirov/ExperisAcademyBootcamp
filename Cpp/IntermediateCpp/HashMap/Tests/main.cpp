#include <iostream>
#include "../GenericHashMap/GenericHashMap.hpp"


struct TestHashHandler : public HashMap::KeyHashingHandler<int> {
public:
    ~TestHashHandler() = default;
    virtual size_t Hash(const int& a_key) const override { return a_key; }
};


int main() {
    TestHashHandler hasher;
    HashMap::HashMap<int, int> map(10, hasher);
    map.Insert(1, 10);
    map.Insert(78, 345);
    map.Insert(11, 22);
    map.Insert(4, -1);

    std::cout << "Copy Map:" << std::endl;
    HashMap::HashMap<int, int> mapCopy = map;
    std::cout << "Show MapCopy content from Begin() to End():" << std::endl;
    HashMap::HashMap<int,int>::Iterator itr = mapCopy.Begin();
    while(itr != mapCopy.End()) {
        std::cout << "-> ";
        std::cout << *itr << std::endl;
        ++itr;
    }

    itr = map.Find(1);

    if(itr != map.End()) {
        std::cout << "Find() key = 1 (should be 10):" << std::endl;
        std::cout << *itr << std::endl;
        *itr = 10000;
        std::cout << "Show *itr AFTER modifing key = 1 value from 10 to 10000:" << std::endl;
        std::cout << *itr << std::endl;
    }

    std::cout << "Find 1 again:" << std::endl;
    std::cout << *(map.Find(1)) << std::endl;

    itr = map.Begin();
    std::cout << "Set itr to Begin():" << std::endl;
    std::cout << *itr << std::endl;

    std::cout << "Show Map content from Begin() to End():" << std::endl;
    while(itr != map.End()) {
        std::cout << "*) ";
        std::cout << *itr << std::endl;
        ++itr;
    }

    map.Remove(1);
    std::cout << "Show Map content from Begin() to End(), AFTER Remove() of 10000 (key = 1):" << std::endl;
    itr = map.Begin();
    while(itr != map.End()) {
        std::cout << "*) ";
        std::cout << *itr << std::endl;
        ++itr;
    }

    std::cout << "Set itr to Begin() (should be pointing on 22 now (key = 11))" << std::endl;
    itr = map.Begin();
    std::cout << *itr << std::endl;

    std::cout << "Size() (should be 3 after -1 by remove()):" << std::endl;
    std::cout << map.Size() << std::endl;

    std::cout << "Insert() key = 0, val = -100 (should be new Begin())" << std::endl;
    map.Insert(0, -100);

    std::cout << "Show Map content from Begin() to End(), AFTER insert() of -100 (key = 0):" << std::endl;
    itr = map.Begin();
    while(itr != map.End()) {
        std::cout << "*) ";
        std::cout << *itr << std::endl;
        ++itr;
    }

    std::cout << "Size() (should be 4 after +1 be insert()):" << std::endl;
    std::cout << map.Size() << std::endl;

    std::cout << "Show MapCopy content from Begin() to End() again - should not be diffrent from the first time:" << std::endl;
    itr = mapCopy.Begin();
    while(itr != mapCopy.End()) {
        std::cout << "-> ";
        std::cout << *itr << std::endl;
        ++itr;
    }

    itr = mapCopy.Begin();
    std::cout << "Show MapCopy itr content of itr + 2 offset (should print -1)" << std::endl;
    std::cout << *(itr + 2) << std::endl;

    std::cout << "Show MapCopy itr content of itr += 1 offset (should print 22)" << std::endl;
    itr += 1;
    std::cout << *itr << std::endl;

    return 0;
}