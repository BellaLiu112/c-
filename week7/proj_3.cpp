#include <iostream>
#include<iomanip>
using namespace std;

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    cout << setbase(16) << n << endl;
    cout << setbase(10) << setw(10) << setfill('0') << n << endl;
    
    return 0;
}
