#include <cassert>

class Entity 
{
private:
    void privateMethod1() {}
    void privateMethod2(int value){}

    friend class AttorneyForMethod1;
    friend class AttorneyForMethod2;
};

class AttorneyForMethod1 
{
public:
    static void callPrivateMethod1(Entity& entity) 
    {
        entity.privateMethod1();
    }
};

class AttorneyForMethod2 
{
public:
    static void callPrivateMethod2(Entity& entity, int value) 
    {
        entity.privateMethod2(value);
    }
};

class Tester1 
{
public:
    void test(Entity& entity) 
    {
        AttorneyForMethod1::callPrivateMethod1(entity);
    }
};


class Tester2 
{
public:
    void test(Entity& entity) 
    {
        AttorneyForMethod2::callPrivateMethod2(entity, 42);
    }
};

int main() {
    Entity entity;
    Tester1 tester1;
    Tester2 tester2;

    tester1.test(entity);
    tester2.test(entity);

    return 0;
}