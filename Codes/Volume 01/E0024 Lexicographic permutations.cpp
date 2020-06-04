# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of 
 the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 
 are:

 012   021   102   120   201   210

 What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/

//little-endian rep. in factorial base
vector<int> factoradic(ll num){
    vector<int> ret;
    int pos = 1;
    while(num){
        ret.push_back(num % pos);
        num /= pos;
        pos++;
    }
    return ret;
}

vector<int> nthPermuation(int permSize, ll n){
    vector<int> perm(permSize), permSet(permSize);
    iota(permSet.begin(), permSet.end(), 0);

    vector<int> factoradicNum = factoradic(n);
    factoradicNum.resize(permSize);
    reverse(factoradicNum.begin(), factoradicNum.end());
    for(int pos = 0; pos < permSize; pos++){
        perm[pos] = permSet[factoradicNum[pos]];
        permSet.erase(permSet.begin() + factoradicNum[pos]);
    }
    return perm;
}

string nthLexPermOfDigits(int maxDigit, ll n){
    vector<int> perm = nthPermuation(maxDigit+1, n-1);
    string ret = "";
    for(int x : perm)
        ret += to_string(x);
    return ret;
}

int main(){
    Time(
        cout<<nthLexPermOfDigits(9, 1000*1000);
    )
    return 0;
}

/*
Note:
 for n-th lexicographical permutation (0-based), we change n to factoradic base, in this base reading the digits left to right tell us 
 which element of remaining ones should be put after last s.t. the nth permutation is created. For example 4 in factoradic is 200. So 
 from 0, 1, 2 take 2nd, then 0th, then 0th -> 201
 Complexity: O(n^2 + log m / log log m)
*/