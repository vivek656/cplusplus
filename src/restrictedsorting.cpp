#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<vector<int>,vector<int>> readintArrayAndget(int length) {
  vector<int> k(length);
  vector<int> sorted(length);
  for (int i = 0 ; i < length ; i ++) {
    std::cin >> k[i];
    sorted[i] = k[i];
  }
  sort(sorted.begin(), sorted.end());
  return pair(k , sorted);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    std::cin >> t;

    for (int i = 0 ;  i < t ; i++) {
        int l ;
        std::cin >> l;
        pair<vector<int>, vector<int>> arrAndSorted = readintArrayAndget(l);
        vector<int> arr = arrAndSorted.first;
        vector<int> sorted = arrAndSorted.second;
        if (arr == sorted) {
            cout << -1 << '\n';
            continue;
        } 
        int maxint = sorted[l-1];
        int minInt = sorted[0];
        //1 4 3
        //1 3 4
        int minn = maxint - minInt;
        for (int i = 0 ; i < l ; i ++) {
            if(arr[i] != sorted[i]){
                minn = min(minn, max(abs(arr[i]-minInt), abs(arr[i] - maxint)));
            }
        }
        cout << minn << '\n';
    }
}