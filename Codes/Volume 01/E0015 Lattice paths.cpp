# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom 
 right corner.
 <FIGURES>

 How many such routes are there through a 20×20 grid?
*/

ll nCr(ll n, ll r){
    if(2*r > n) 
        r = n - r;
    ll ret = 1;
    for(int i = 1; i<=r; n--, i++){
        ret *= n;
        ret /= i;
    }
    return ret;
}

ll countRouteLatticeGrid(int n, int m){
    ll ans = nCr(n+m, n);
    return ans;
}

int main(){
    Time(
        cout<<countRouteLatticeGrid(20, 20)<<endl;
    );
    return 0;
}

/*
Notes:
 This is a famous problem which reduces finding count of sequence of n+m R and D, where there are exactly m D's and n R's. So we just use
 nCr, by finding the products.
 Complexity(O(m))
*/