#include <queue>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

#define NUM 10000000

unsigned int isprime[10000];

void Prime( )
{
    for (unsigned i = 0; i < 10000; ++i)
        isprime[i] = 1;
    for (unsigned i = 2; i < 10000; ++i)
        if (isprime[i])
            for (unsigned j = 2*i; j < 10000;j += i)
                isprime[j] = 0;
}

int calNumPrime(int val)
{
    int n = 0;
    int tmp = val;
    int i;
    for (i = 2; i <= tmp && i < 10000; ++i)
        if (isprime[i])
            if (! (val % i) ){
                n++;
                tmp /= i;
            }
    if (!n)
        return n;
    if (tmp > 10000 && tmp != val)
        n++;
    if (--i == val) {
        n--;
    }
    return n;
}



class myless{
public:
    bool operator( ) (int a, int b){
        int num_a = calNumPrime(a);
        int num_b = calNumPrime(b);
        if (num_a == num_b)
            return a < b;
        return num_a < num_b;
    }
};
        
class mygreat{
public:
    bool operator( ) (int a, int b){
        int num_a = calNumPrime(a);
        int num_b = calNumPrime(b);
        if (num_a == num_b)
            return a > b;
        return num_a > num_b;
    }
};


int main(int argc, char *argv[])
{
    Prime( );
    priority_queue<int, vector<int>, myless> min_queue;
    priority_queue<int, vector<int>, mygreat> max_queue;

    int num;
    cin >> num;

    while (num--) {
        for (int i = 0; i < 10; ++i) {
            int n;
            cin >> n;
            min_queue.push(n);
            max_queue.push(n);
        }
        cout << min_queue.top() << " " << max_queue.top() << endl;
        min_queue.pop();
        max_queue.pop();
    }
    
//    cout << calNumPrime(6581) << endl;
//    cout << calNumPrime(19793) << endl;
    return 0;
}

