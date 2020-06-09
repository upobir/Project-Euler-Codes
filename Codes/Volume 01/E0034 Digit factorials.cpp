# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

 Find the sum of all numbers which are equal to the sum of the factorial of their digits.

 Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
 
 ll sumFuncDigits(ll num, vector<ll> &funcMap){
    ll sum = 0;
    while(num){
        int digit = num % 10;
        sum += funcMap[digit];
        num /= 10;
    }
    return sum;
}

vector<ll> listNumEqualDigitFuncSum(vector<ll> &funcMap){
    ll guessBound = 1;
    for(int digitCount = 1; ; digitCount++, guessBound*=10){
        if(funcMap[9]*digitCount < guessBound) break;
    }

    vector<ll> list;
    for(ll num = 0; num < guessBound; num++){
        if(sumFuncDigits(num, funcMap) == num)
            list.push_back(num);
    }
    return list;
}

ll sumOfNumberEqualFactorialDigitSum(){
    vector<ll> factorialMap(10);
    factorialMap[0] = 1;
    for(int digit = 1; digit<10; digit++){
        factorialMap[digit] = factorialMap[digit-1] * digit;
    }

    vector<ll> numbers = listNumEqualDigitFuncSum(factorialMap);

    ll sum = 0;
    for(ll num : numbers){
        if(num >= 10) sum += num;
    }

    return sum;
}

int main(){
    Time(
        cout<<sumOfNumberEqualFactorialDigitSum()<<endl;
    )
    return 0;
}

/*
Notes:
 Exactly like problem 30, we just use factorial map for function on digits.
*/