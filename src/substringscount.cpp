#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void count_sort(vector<int> &p , vector <int> &c){
    int n = p.size();
    vector<int> cnt(n);
    for (auto const &x : c) {cnt[x]++;}
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1 ; i <n ; i++ ) {
        pos[i] = pos[i-1] + cnt[i-1];
    }

    for (auto const &x : p){
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}
void radix_sort(vector<pair<pair<int, int>, int>> &a)
{
    int n = a.size();
    {
        vector<int> cnt(n);
        for (auto const &x : a)
        {
            cnt[x.first.second]++;
        }
        vector<pair<pair<int, int>, int>> a_new(n);
        vector<int> pos(n);
        pos[0] = 0;
        for (int i = 1; i < n; i++)
        {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }

        for (auto const &x : a)
        {
            int i = x.first.second;
            a_new[pos[i]] = x;
            pos[i]++;
        }
        a = a_new;
    }

    {
        vector<int> cnt(n);
        for (auto const &x : a)
        {
            cnt[x.first.first]++;
        }
        vector<pair<pair<int, int>, int>> a_new(n);
        vector<int> pos(n);
        pos[0] = 0;
        for (int i = 1; i < n; i++)
        {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }

        for (auto const &x : a)
        {
            int i = x.first.first;
            a_new[pos[i]] = x;
            pos[i]++;
        }
        a = a_new;
    }
}

vector<int> suffixArray(string &s) {
   s += '$';
    int n = s.size();
    vector<int> p(n), c(n); // permutation , c equivalenceClasses
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {s[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++)
            p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i].first == a[i - 1].first)
            {
                c[p[i]] = c[p[i - 1]];
            }
            else
            {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }
    int k = 0;
    while ((1 << k) < n)
    {

        for (int i = 0 ; i < n ; i++) {
            p[i] = (p[i] - (1 << k) + n) % n;

        }
        count_sort(p,c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1 ; i < n ; i++) {
            pair<int,int> prev = { c[p[i-1]], c[(p[i-1]+ (1 << k)) % n]};
            pair<int,int> now = { c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (now  == prev) {
                c_new[p[i]] = c_new[p[i-1]];
            } else {
                c_new[p[i]] = c_new[p[i-1]]+1;
            }
        }
        c = c_new;       
        k++;
    }
    return p;
}

//aa aaab
// aaa
vector<int> sameArrayWithOrderAndLengthAtleast(string &s , vector<int> &p , int size) {
    vector<int> resultant;
    resultant.reserve(p.size());
    int idx = 0;
    int sSize = s.size();
    for(auto const &i : p){
        if ((sSize - i ) >= size) {
            resultant.push_back(i);
            idx++;
        }
    }
    resultant.resize(idx);
    return resultant;
}

// ababba
// babba
// $
// a
// abba
// 
int compare(string &s , int start , string &subtring){
    for (int i = 0 ; i < subtring.size() ; i ++ ){
        if((i + start) >= s.size()) return -1;
        if (s[i+start] - subtring[i] != 0) {
            return s[i+start] - subtring[i];
        }
    }
    return 0;
}

// a
// aa
// aaa
// aaaa
int count(string &s, vector<int> &permute , string &substring){
    if(permute.size() == 0) return false;
    int low = 0;
    int high = permute.size()-1;
    int count = 0 ;
    
    int lowest = s.size() +1;
    bool has = false;
    while(low <= high) {
        int middle = low + (high - low) / 2;     
        int middelP = permute[middle];
        int middleCompare = compare(s, middelP, substring);
        if(middleCompare == 0) {
            lowest = middle;
            high = middle-1;
            has = true;
        }

        else if (middleCompare > 0){
            high = middle-1;
        } else {
            low = middle+1;
        }    
    }
    if(!has) return 0;
    low = 0;
    high = permute.size()-1;
    int highest = s.size() +1;
    while(low <= high) {
        int middle = low + (high - low) / 2;     
        int middelP = permute[middle];
        int middleCompare = compare(s, middelP, substring);
        if(middleCompare == 0) {
            highest = middle;
            low = middle+1;
        }

        else if (middleCompare > 0){
            high = middle-1;
        } else {
            low = middle+1;
        }    
    }
    return highest - lowest +1;
}

int main(){
     ios::sync_with_stdio(false);
    cin.tie(0);

    std::string s;
    std::cin >> s;

    int n ;
    std:cin >> n;
    vector<string> strings(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> strings[i];
    }

    vector<int> permute = suffixArray(s);
    s.pop_back();
    permute.erase(permute.begin());
    for (auto  &ss : strings) {
        int c = count(s, permute, ss);
        cout << c<< '\n';
    }
}