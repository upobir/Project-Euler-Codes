# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

 1634 = 1^4 + 6^4 + 3^4 + 4^4
 8208 = 8^4 + 2^4 + 0^4 + 8^4
 9474 = 9^4 + 4^4 + 7^4 + 4^4
 As 1 = 1^4 is not a sum it is not included.

 The sum of these numbers is 1634 + 8208 + 9474 = 19316.

 Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
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

ll sumOfNumberEqualPowerDigitSum(int exponent){
    vector<ll> powerMap(10);
    for(int digit = 0; digit<10; digit++){
        powerMap[digit] = 1;
        for(int i = 0; i<exponent; i++) powerMap[digit] *= digit;
    }

    vector<ll> numbers = listNumEqualDigitFuncSum(powerMap);

    ll sum = 0;
    for(ll num : numbers){
        if(num >= 10) sum += num;
    }

    return sum;
}

int main(){
    Time(
        cout<<sumOfNumberEqualPowerDigitSum(5)<<endl;
    )
}

/*
Notes:
 We first find digit by finding k digit bound such that even k 9's can't cross the lowest 10^(k-1), and then check for all number below 
 that. Note that we precompute powers to optimize the process
 Complexity: O(X * log n)
*/