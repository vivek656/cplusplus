#include <vector>
#include <iostream>

using namespace std;
#include <unordered_map>
#include <unordered_set>

#include <climits>

long long x, y;
long long mn, p, q;

struct pair_hash {
    inline size_t operator()(const pair<int, int> & v) const {
        return v.first * 31 + v.second; // Simple hash combination
    }
};

int getOrAddDefualtPair(unordered_map<pair<int,int>,int,pair_hash> maps , int tom, int jerry) {
    pair<int,int> p = make_pair(tom,jerry);

    if(maps.find(p) == maps.end()){
        maps[p] = 0;
        return 0;
    }
    else return maps.find(p) -> second;
}

int solve(
    int n, unordered_map<int,int> extraEdges)
{
    int sum = 0;
    
    unordered_map<pair<int,int>,int,pair_hash> maps;
    for (int tom = n ; tom >= 1 ; tom -- ){
        for (int jerry = n ; jerry >= 1 ; jerry-- ){
            if(tom == jerry) continue;

            unordered_set<int> tomCan = {tom};
            unordered_set<int> jerryCan = {};

            int tomExtraNext = -1;
            int jerryExtraNext = -1;
            if(jerry != n) {
                jerryCan.insert(jerry +1);
            } else jerryCan.insert(jerry);

            if(tom != n) tomCan.insert(tom +1);
            if(extraEdges.find(tom) != extraEdges.end()){
                tomCan.insert(extraEdges.find(tom) -> second);
                tomExtraNext = extraEdges.find(tom) -> second;
            };

            if(extraEdges.find(jerry) != extraEdges.end()){
                jerryCan.insert(extraEdges.find(jerry) -> second);
                jerryExtraNext = extraEdges.find(jerry) -> second;
            };

            if(jerry < tom && jerryCan.size() > 1) {
                if(jerryCan.find(tom) != jerryCan.end()) {
                    jerryCan.erase(tom);
                } else {
                    if(jerryCan.find(tom+1) != jerryCan.end()){
                        jerryCan.erase(tom+1);
                    } else if(jerryCan.find(tomExtraNext) != jerryCan.end()){
                        jerryCan.erase(tomExtraNext);
                    }
                }
            }

            int currentScore = getOrAddDefualtPair(maps, tom, jerry);
            if(currentScore != 0) continue;
            int minTom = INT_MAX;
            for (int tt: tomCan) {
                for (int jj: jerryCan) {
                    if(jj == tt){
                        if(tt = tom){
                            minTom = 0;
                        } else {
                            minTom = min(minTom, 1);
                        }
                    } else {
                        if(tt == tom){
                            minTom = min(minTom, 0 + getOrAddDefualtPair(maps, tt, jj) );
                        }
                        else minTom = min(minTom, 1 + getOrAddDefualtPair(maps, tt, jj));
                    }
                }
            }
            maps[make_pair(tom,jerry)] = minTom;
            sum += minTom;
        }
    } 
    return sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t, n, m;
    std::cin >> t;

    while (t--)
    {
        std::cin >> n >> m;
        unordered_map<int,int> extraEdges;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::cin >> u >> v;
            extraEdges[u] = v;      
        }
        int result = solve(n, extraEdges);
        std::cout << result << "\n";
    }
}