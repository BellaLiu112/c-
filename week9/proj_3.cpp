#include <iostream>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]){
    multiset<int> _set;
    set<int> _record;
    int n;
    int x;
    cin >> n;
    char ch[4] = {0};
    while (n--) {
        cin >> ch;
        if (!strncmp(ch, "add", 3)) {
            cin >> x;
            _set.insert(x);
            _record.insert(x);
            size_t n_x = _set.count(x);
            cout << n_x <<endl;
        } else if (!strncmp(ch, "del", 3)){
            cin >> x;
            size_t num_x = count(_set.begin(), _set.end(), x);
            _set.erase(x);
            cout << num_x << endl;
        } else {
            cin >> x;
            size_t has_added = count(_record.begin(), _record.end(), x);
            size_t num_x = count(_set.begin(), _set.end(), x);
            if (has_added)
                cout << 1 << " " << num_x << endl;
            else
                cout << 0 << " " << num_x << endl;
        }
    }
    
}

