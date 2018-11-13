#include <list>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

typedef map< int, list<int> > Map;

int main()
{
    int id1, id2, num, n;
    char str[10];
    Map ml;
    list<int>::iterator i;
    cin >> n;
    while (n--)
        {
        cin >> str;
        switch (str[0])
            {
                case 'n':
                cin >> id1;
                ml.insert(Map::value_type(id1, list<int>()));
                break;
                case 'a':
                cin >> id1 >> num;
                ml[id1].push_back(num);
                break;
                case 'm':
                cin >> id1 >> id2;
                ml[id1].merge(ml[id2]);
                break;
                case 'u':
                cin >> id1;
                ml[id1].sort();
                ml[id1].unique();
                break;
                case 'o':
                cin >> id1;
                ml[id1].sort();
                for (i = ml[id1].begin(); i != ml[id1].end(); i++)
                    {
                    cout << *i << " ";
                    }
                cout << endl;
                break;
            }
        }
    
    return 0;
}

