# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;
typedef long double ld;

/*
Statement:
 The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.

 How many n-digit positive integers exist which are also an nth power?
*/

ll countDigitLengthPoweredNumber(int base){
    ll count = 0;
    for(int digit = 1; digit < base; digit++){
        ld logdigit = logl(digit)/logl(base);
        ld bound = 1.0l/(1.0l - logdigit);

        ll countForDigit = llround(floor(bound));
        count += countForDigit;
    }
    return count;
}

int main(){
    Time(
        cout<<countDigitLengthPoweredNumber(10)<<endl;
    )
    return 0;
}

/*
Notes: 
 We use the well known bound for length of two numbers (len(a)-1 + len(b)-1)+1 <= len(ab) <= len(a)+len(b), this tess us that if b^n has n
 digits then, b must be a 1 digit number, and since b^n has floor(n * log_base(b))+1 digits, using this we get a bound that for a digit d
 we solve n <= 1/(1-log_base(d)), which gives us the answer for each digit, summing which gives us the actual answer.
 Complexity: O(n)
*/