# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

 Find the largest palindrome made from the product of two 3-digit numbers.
*/

ll reverseNum(ll num, ll base = 10){
    ll rev = 0;
    while(num){
        rev *= base;
        rev += num % base;
        num /= base;
    }
    return rev;
}

ll largestProductPalindrome(int len){
    ll st = 1;
    for(int i = 1; i<len; i++) st *= 10;
    ll fn = 10*st-1;

    ll bestPalindrome = -1;
    for(ll bigNum = fn; bigNum >= st && bigNum*bigNum > bestPalindrome; bigNum--){
        for(ll smallNum = bigNum; smallNum >= st && bigNum*smallNum > bestPalindrome; smallNum--){
            ll product = smallNum * bigNum;
            if(product == reverseNum(product))
                bestPalindrome = product;
        }
    }
    return bestPalindrome;
}

int main(){
    Time(
        cout<<largestProductPalindrome(3);
    );
    return 0;
}

/*
Notes:
 we basically just find all products of len digit numbers and check if they are palindromes, we however do it from reverse to find the
 largest product faster and stop when product can no longer be larger. Using property of 3 digit product, the answer can be optimized more,
 but did not use it.
 Complexity: O(10^(2n))
*/