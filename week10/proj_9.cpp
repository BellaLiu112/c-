#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
    // 在此处补充你的代码

class A{
public:
    int m_age;
    char m_species;
    A(int k):m_age(k),m_species('A'){ }
};

class B: public A{
public:
    B(int k):A(k){A::m_species = 'B';}
};

struct Comp {
    bool operator() (A *lhs, A *rhs) const
    {return lhs->m_age < rhs->m_age;}
};

void Print(const A *a)
{
    cout << a->m_species << " " << a->m_age << endl;
}

int main()
{
    
    int t;
    cin >> t;
    set<A*,Comp> ct;
    while( t -- ) {
        int n;
        cin >> n;
        ct.clear();
        for( int i = 0;i < n; ++i)    {
            char c; int k;
            cin >> c >> k;
            
            if( c == 'A')
                ct.insert(new A(k));
            else
                ct.insert(new B(k));
        }
        for_each(ct.begin(),ct.end(),Print);
        cout << "****" << endl;
    }
}

