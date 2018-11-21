#include <iostream>
using namespace std;
    // 在此处补充你的代码
class CType{
    int m_n;
public:
    CType( ){ }
    CType(const CType &ct){m_n = ct.m_n;}
    void setvalue(int n){m_n = n;}
    friend ostream & operator<<(ostream &o, const CType& ct){
        o << ct.m_n;
        return o;
    }
    CType operator++(int n){
        CType tmp(*this);
        m_n *= m_n;
        return tmp;
    };
};

int main(int argc, char* argv[]) {
    CType obj;
    int n;
    cin>>n;
    while ( n ) {
        obj.setvalue(n);
        cout<<obj++<<" "<<obj<<endl;
        cin>>n;
    }
    return 0;
}

