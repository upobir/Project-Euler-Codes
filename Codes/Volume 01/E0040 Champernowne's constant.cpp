# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 An irrational decimal fraction is created by concatenating the positive integers:

 0.123456789101112131415161718192021...

 It can be seen that the 12th digit of the fractional part is 1.

 If d_n represents the nth digit of the fractional part, find the value of the following expression.

 d_1 × d_10 × d_100 × d_1000 × d_10000 × d_100000 × d_1000000
*/

ll nthDigitChampernowne(ll pos, ll base = 10){
    ll numberDigit = 1, fixedDigitNumberCount = base-1;
    while(pos > fixedDigitNumberCount*numberDigit){
        pos -= fixedDigitNumberCount*numberDigit;
        fixedDigitNumberCount *= base;
        numberDigit++;
    }
    ll numberStart = fixedDigitNumberCount/(base-1);
    ll numberCount = (pos+numberDigit-1)/numberDigit;
    ll number = numberCount + numberStart - 1;

    pos -= (numberCount-1)*numberDigit;

    
    ll revPos = numberDigit - pos;
    for(int i = 0; i<revPos; i++) number /= 10;

    return number % 10;
}

ll productOfDigitsOfChampernowne(vector<ll> positions, ll base){
    ll ans = 1;
    for(int pos : positions){
        ans *= nthDigitChampernowne(pos);
    }
    return ans;
}

int main(){
    Time(
        cout<<productOfDigitsOfChampernowne({1, 10, 100, 1000, 10000, 100000, 1000000}, 10)<<endl;
    )
    return 0;
}

/*
Notes:
 We use a function to get the nth digit, which basically first checks if 1-digit numbers cover it to that position, if not 2-digit and so
 on.
 Complexity: O(|s| * log n)
*/