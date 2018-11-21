#include <bitset>
#include <iostream>
using namespace std;

int main(int argc, const char* argv[])
{
    int t;
    cin >> t;
    while (t--) {
        int n, i, j;
        bitset<32> k;
        k.reset();
        cin >> n >> i >> j;
        int n_i = n >> i;
        int n_j = n >> j;
        int i_bit, j_bit;
        if (n_i % 2){
            i_bit = 1;
            k.set(i);
        } else {
            i_bit = 0;
        }
        if (n_j % 2)
            j_bit = 1;
        else {
            j_bit = 0;
            k.set(j);
        }
        for (int w = i+1; w < j; ++w)
            k.set(w);
        unsigned long ret = k.to_ulong();
        cout << hex << ret << endl;
    }
    
    return 0;
}

