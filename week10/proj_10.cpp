#include <iostream>
#include <map>
using namespace std;
    // 在此处补充你的代码
class A
{
public:
    int nbr;
    static int count;
    A(int k):nbr(k){count++;}
    A(A &a) { }
    A( ){count++;}
    virtual ~A( ){
        count--;
        cout << "A::destructor" << endl;
    }
};

class B:public A{
public:
    B(int k):A(k){ }
    B(B &b) { }
    virtual ~B( ){
        cout << "B::destructor" << endl;
    };
};


int A::count = 0;
void func(B b) { }
int main()
{
    A a1(5),a2;
    cout << A::count << endl;
    B b1(4);
    cout << A::count << endl;
    func(b1);
    cout << A::count << endl;
    A * pa = new B(4);
    cout << A::count << endl;
    delete pa;
    cout << A::count << endl;
    return 0;
}

