# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Take the number 192 and multiply it by each of 1, 2, and 3:

 192 × 1 = 192
 192 × 2 = 384
 192 × 3 = 576

 By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

 The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the 
 concatenated product of 9 and (1,2,3,4,5).

 What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) 
 where n > 1?
*/

string pandigitalConcatMultiple(ll num, ll base){
    vector<bool> isUsed(base);
    stringstream res;
    for(int m = 1; ; m++){
        ll multiple = num * m;
        ll copyMultiple = multiple;
        bool possible = true;

        while(possible && multiple > 0){
            int digit = multiple % base;
            if(digit == 0) possible = false;
            else if(isUsed[digit]) possible = false;
            else isUsed[digit] = true;
            multiple /= base;
        }
        if(!possible) break;

        res << copyMultiple;
    }
    return res.str();
}

ll largestConcatMultiplePandigital(ll base){
    int bound = 1;
    for(int len = 0; len < (base-1)/2; len++) bound *= 10;
    ll ans = -1;
    for(ll num = 1; num < bound ; num++){
        string pandigitalNum = pandigitalConcatMultiple(num, base);
        if(pandigitalNum.size() == base-1)
            ans = max(ans, stoll(pandigitalNum));
    }
    return ans;
}

int main(){
    Time(
        cout<<largestConcatMultiplePandigital(10)<<endl;
    )
    return 0;
}

/*
Notes:
 Since the condition states that atleast one concatanation is required, so we only check using numbers upot half the digits, for each we 
 find the largest concatanation we can make without using same digit twice. 
 Complexity: O(n^(n/2))
*/