# include <bits/stdc++.h>
# include "TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will 
 be:

 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

 By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
*/

vector<ll> fibonacciTill(ll maxVal){
    vector<ll> fibs;
    ll fnow = 0, fnxt = 1, fnxt2;
    while(fnow <= maxVal){
        fibs.push_back(fnow);
        fnxt2 = fnow + fnxt;
        fnow = fnxt;
        fnxt = fnxt2;
    }
    return fibs;
}

ll sumEvenFibonacciTill(ll maxVal){
    vector<ll> fibs = fibonacciTill(maxVal);
    ll sum = 0;
    for(ll f : fibs){
        if(f % 2 == 0)
            sum += f;
    }
    
    return sum;
}

int main(){
    Time(    
        std::cout<<sumEvenFibonacciTill(4*1000*1000)<<endl;
    );
    return 0;
}

/*
Notes:
 Fibonaccis are made with a running dp, since there are only logarithmic fibonacci below 4 million, so we just make them all and sum the 
 even ones.
 Complexity: O(log n)
*/
