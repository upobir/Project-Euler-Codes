# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The sum of the squares of the first ten natural numbers is,
 
 12+22+...+102=385
 The square of the sum of the first ten natural numbers is,

 (1+2+...+10)2=552=3025
 Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025−385=2640.

 Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

ll sumTill(ll num){
    return num * (num+1)/2;
}

ll sumSquareTill(ll num){
    return num*(num+1)*(2*num+1)/6;
}


ll squareSumMinusSumSquare(ll num){
    ll sum = sumTill(num);
    ll sumSq = sumSquareTill(num);
    return sum*sum - sumSq;
}

int main(){
    Time(
        cout<<squareSumMinusSumSquare(100)<<endl;
    );
    return 0;
}

/*
Notes:
 sum of natural numbers and sum of their squares have well known formulas, just used those.
 Complexity: O(1)
*/