#include <iostream>
using namespace std;

template <class T>
class CArray3D {
    int _r;
    int _c;
    int _l;
    T ***mArray;
public:
    CArray3D(int a, int b, int c){
        _r = a;
        _c = b;
        _l = c;
        mArray = new T**[_r];
        for (int i = 0; i < _r; ++i) {
            mArray[i] = new T*[_c];
            for (int j = 0; j < _c; ++j) {
                mArray[i][j] = new T[_l];
            }
        }
    };
        
    T ** operator[] (int index)
    {
        return mArray[index];
    }
    
    ~CArray3D( ) {
        for (int i = 0; i < _r; ++i) {
            for (int j = 0; j < _c; ++j) {
                delete mArray[i][j];
            }
            delete mArray[i];
        }
        delete mArray;
    };
    
};

int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;
}

