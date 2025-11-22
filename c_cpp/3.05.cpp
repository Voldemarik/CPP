#include <iostream>
#include <cassert>

class Entity_v1
{
public:
    virtual int test() const { return 1; }
};

class Entity_v2
{
public:
    virtual int test() const { return 2; }
};

class Adapter_v1 : public Entity_v1
{
public:
    virtual int test_v1() const { return Entity_v1::test(); }
};

class Adapter_v2 : public Entity_v2
{
public:
    virtual int test_v2() const { return Entity_v2::test(); }
};

class Client : public Adapter_v1, public Adapter_v2
{
};

int main()
{
    Client client = Client{};
    assert(client.test_v1() == 1);
    assert(client.test_v2() == 2);
}