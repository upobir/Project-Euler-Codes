# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

 Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

 (Please note that the palindromic number, in either base, may not include leading zeros.)
*/

ll nthEvenOddPalindrome(ll num, bool oddlength, ll base = 10){
    ll ret = num;
    if(oddlength) num /= base;
    while(num){
        ret *= base;
        ret += num % base;
        num /= base;
    }
    return ret;
}

ll reverseNum(ll num, ll base = 10){
    ll rev = 0;
    while(num){
        rev *= base;
        rev += num % base;
        num /= base;
    }
    return rev;
}

ll sumTwoBasePalindromeUntil(ll maxNum, ll base1, ll base2){
    ll sum = 0;
    //oddlength cases
    for(ll num = 1; ;num++){
        ll palNum = nthEvenOddPalindrome(num, true, base1);
        if(palNum >= maxNum) break;
        if(palNum == reverseNum(palNum, base2))
            sum += palNum;
    }
    //evenlength cases
    for(ll num = 1; ;num++){
        ll palNum = nthEvenOddPalindrome(num, false, base1);
        if(palNum >= maxNum) break;
        if(palNum == reverseNum(palNum, base2))
            sum += palNum;
    }
    return sum;
}

int main(){
    Time(
        cout<<sumTwoBasePalindromeUntil(1000*1000, 10, 2)<<endl;
    )
    return 0;
}

/*
Notes:
 for the two bases, we generate all palindromes in one base and then check if that's also palindrome in second base
 Complexity: O(sqrt(n) * log n)
*/