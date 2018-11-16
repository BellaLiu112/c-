#include <iostream>
#include <string>
using namespace std;

template <class _T>
class  CMyistream_iterator{
    istream &m_i;
    bool has_content = false;
    _T _t;
public:
    CMyistream_iterator(istream& i):m_i(i){ };
    _T operator *( ){
        if (has_content) {
            return _t;
        }
        m_i >> _t;
        has_content = true;
        return _t;
    }
    void operator++(int){
        has_content = false;
    }
};

int main()
{
    CMyistream_iterator<int> inputInt(cin);
    int n1,n2,n3;
    n1 = * inputInt; //读入 n1
    int tmp = * inputInt;
    cout << tmp << endl;
    inputInt ++;
    n2 = * inputInt; //读入 n2
    inputInt ++;
    n3 = * inputInt; //读入 n3
    cout << n1 << "," << n2<< "," << n3 << endl;
    CMyistream_iterator<string> inputStr(cin);
    string s1,s2;
    s1 = * inputStr;
    inputStr ++;
    s2 = * inputStr;
    cout << s1 << "," << s2 << endl;
    return 0;
}

