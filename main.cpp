#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <array>
#include <queue>
#include <cmath>
using namespace std;

class newway {
public:
    int idx, idy;
    int bgn, end;
    double len;
    newway(int x, int y, double l, int ix, int iy):bgn(x), end(y), len(l), idx(ix), idy(iy){};
};

class mycomp{
public:
    bool operator() (const newway& w1, const newway& w2){
        return (w1.len > w2.len);
    }
};

double caldist(array<int, 2> p1, array<int, 2> p2){
    double l1 = (p1[0]-p2[0])*(p1[0]-p2[0]);
    double l2 = (p1[1]-p2[1])*(p1[1]-p2[1]);

    return sqrt(l1+l2);
}

int main() {
    int casenum;

    cin >> casenum;

    while (casenum--){
        int tnum;
        cin >> tnum;
        map<int, array<int, 2>> towns;

        for (int i = 1; i <= tnum; i++){
            array<int, 2> point{};
            cin >> point[0] >> point[1];
            towns[i] = point;
        }

        int hwynum;
        cin >> hwynum;
        vector<set<int>> connections;

        for (int i = 1; i <= hwynum; i++){
            int x, y;
            cin >> x >> y;

            int ix, iy;
            ix = iy = -1;

            for (int j = 0; j < connections.size(); j++){
                if (connections[j].count(x))
                    ix = j;
                else if (connections[j].count(y))
                    iy = j;
            }

            if (ix == -1 && iy == -1) {
                set<int> cnnt;
                cnnt.insert(x);
                cnnt.insert(y);
                connections.push_back(cnnt);
            }
            else if (ix == -1){
                connections[iy].insert(x);
            }
            else if (iy == -1){
                connections[ix].insert(y);
            }
            else{
                connections[ix].insert(connections[iy].begin(), connections[iy].end());
                connections.erase(connections.begin()+iy);
            }
        }

        for (int i = 1; i <= tnum; i++){
            bool isNew = true;

            for (auto &cnnt : connections){
                if(cnnt.count(i)) {
                    isNew = false;
                    break;
                }
            }
            if (isNew) {
                set<int> cnnt;
                cnnt.insert(i);
                connections.push_back(cnnt);
            }
        }

        priority_queue<newway, vector<newway>, mycomp> ways;

        for (int i = 0; i < connections.size()-1; i++){
            for (int j = i+1; j < connections.size(); j++){
                int x, y;
                double l;
                x = y = 0;
                l = 40000;

                for (auto &c1 : connections[i]){
                    for (auto &c2 : connections[j]){
                        if (caldist(towns[c1], towns[c2]) < l){
                            x = (c1 < c2) ? c1 : c2;
                            y = c1 + c2 - x;
                            l = caldist(towns[c1], towns[c2]);
                        }
                    }
                }
                newway way(x, y, l, i, j);
                ways.push(way);
            }
        }

        if (ways.empty()){
            cout << "No new highways need" << endl;
        }
        else {
            vector<set<int>> censor;
            for (int i = 0; i < connections.size(); i++){
                set<int> check;
                check.insert(i);
                censor.push_back(check);
            }

            while (censor.size() > 1){
                newway way = ways.top();
                ways.pop();
                int ix, iy;
                ix = iy = -1;
                for (int i = 0; i < censor.size(); i++){
                    if (censor[i].count(way.idx))
                        ix = i;
                    if (censor[i].count(way.idy))
                        iy = i;
                }

                if (ix != iy){
                    cout << way.bgn << " " << way.end << endl;
                    censor[ix].insert(censor[iy].begin(), censor[iy].end());
                    censor.erase(censor.begin()+iy);
                }
            }
        }

        if(casenum > 0)
            cout << endl;
    }

    return 0;
}

