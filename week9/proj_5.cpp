#include <set>
#include <iostream>
using namespace std;

typedef struct player {
    int _id;
    unsigned _force;
    player( ) { }
    player(int id, int force):_id(id), _force(force){ }
} candidate;

bool operator < (const candidate &a1, const candidate &a2){
    return a1._force < a2._force;
}

typedef set<candidate>::iterator IT;

int main(int argc, char *argv[]){
    candidate facer(1, 1000000000);
    set<candidate> players;
    players.insert(facer);
    int n;
    cin >> n;
    int id, force;
    while (n--) {
        cin >> id >> force;
        candidate player(id, force);
        pair<IT,bool> ret;
        ret = players.insert(player);
        IT tmp = ret.first;
        candidate enemy;
        if (ret.first == players.begin()) {
            IT enemt_it = ++tmp;
            enemy._id = enemt_it->_id;
            enemy._force = enemt_it->_force;
        } else if (++tmp == players.end()){
            IT enemt_it = --tmp;
            enemy._id = enemt_it->_id;
            enemy._force = enemt_it->_force;
        } else {
            tmp--;
            IT prev = --tmp;
            ++tmp;
            IT next = ++tmp;
            if (force - prev->_force < next->_force - force) {
                IT enemt_it = prev;
                enemy._id = enemt_it->_id;
                enemy._force = enemt_it->_force;
            } else if (force - prev->_force > next->_force - force){
                IT enemt_it = next;
                enemy._id = enemt_it->_id;
                enemy._force = enemt_it->_force;
            } else {
                IT enemt_it = prev;
                enemy._id = enemt_it->_id;
                enemy._force = enemt_it->_force;
            }
        }
        cout << id << " " << enemy._id << endl;
    }
    return 0;
}



