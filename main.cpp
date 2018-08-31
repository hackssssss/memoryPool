#include <iostream>
#include<list>
#include <cstring>


class Pool {
public:
    Pool(int num, size_t size) {
        for(int i = 0; i < num; i++) {
            void * p = malloc(size);
            unUsed.push_back(p);
        }
    }
    ~Pool(){
        for (auto p : unUsed) {
            free(p);
        }
        for (auto p : inUsed) {
            free(p);
        }
    }
    size_t available() {
        return unUsed.size();
    }
    void *get() {
        if (unUsed.size() == 0) return nullptr;
        auto p = *unUsed.begin();
        unUsed.erase(unUsed.begin());
        inUsed.push_back(p);
        return p;
    }
    void back(void *p) {
        for (auto it = inUsed.begin(); it != inUsed.end(); it++) {
            if (p == *it) {
                inUsed.erase(it);
                unUsed.push_back(p);
                break;
            }
        }
    }
private:
    std::list<void *> unUsed;
    std::list<void *> inUsed;
};

int main() {
    std::ios::sync_with_stdio(false);
    Pool pool(5, 32);
    std::cout << pool.available() << std::endl;
    char * p = (char *)pool.get();
    if (p == nullptr) {
        std::cout << "p == null" << std::endl;
        return 0;
    }
    char *value = "123456";
    std::cout << "sizeof value " << sizeof(value) << " strlen(vlaue) " << strlen(value) << std::endl;
    memcpy(p, value, strlen(value));
    p[strlen(value)] = 0;
    std::cout << "p : " << p << std::endl;
    printf("p is %p\n", p);
    std::cout << pool.available() << std::endl;
    pool.back(p);
    std::cout << pool.available() << std::endl;
    p = (char *)pool.get();
    printf("p is %p\n", p);
    std::cout << pool.available() << std::endl;
    p = (char *)pool.get();
    printf("p is %p\n", p);
    std::cout << pool.available() << std::endl;
    p = (char *)pool.get();
    printf("p is %p\n", p);
    std::cout << pool.available() << std::endl;
    p = (char *)pool.get();
    printf("p is %p\n", p);
    std::cout << pool.available() << std::endl;
    p = (char *)pool.get();
    printf("p is %p\n", p);
    std::cout << pool.available() << std::endl;

    pool.back(p);
    std::cout << pool.available() << std::endl;
    return 0;
}