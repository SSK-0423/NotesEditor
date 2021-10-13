#include <iostream>

class A
{
private:
public:
    void draw() { std::cout << "class A" << std::endl; }
};
class B
{
private:

public:
    void draw(){std::cout << "class B" << std::endl;}
};
int main()
{
    A* a = new A();
    B* b = (B*)a;
    b->draw();
    return 0;
}