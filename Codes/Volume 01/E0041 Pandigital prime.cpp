# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit 
 pandigital and is also prime.

 What is the largest n-digit pandigital prime that exists?
*/

bool isPrime(ll number){
    if(number == 2) return true;
    if(number == 1 || number % 2 == 0) return false;

    for(ll divi = 3; divi*divi <= number; divi+=2){
        if(number % divi == 0) return false;
    }
    return true;
}

ll largestPandigitalPrimeToNthDigit(int maxDigit){
    int digitSum = 0;
    for(int i = 1; i<=maxDigit; i++) digitSum += i;
    if(digitSum % 3 == 0) return -1;

    string number(maxDigit, '0');
    iota(number.begin(), number.end(), '1');
    reverse(number.begin(), number.end());
    
    do{
        ll num = stoi(number);
        if(isPrime(num))
            return num;
    }while(prev_permutation(number.begin(), number.end()));
    return -1;
}

ll largestPandigitalPrime(){
    for(int digit = 9; digit >= 1; digit--){
        ll prime = largestPandigitalPrimeToNthDigit(digit);
        if(prime != -1)
            return prime;
    }
    return -1;
}

int main(){
    Time(
        cout<<largestPandigitalPrime()<<endl;
    )
    return 0;
}

/*
Notes:
 From largest digit count we check all permutations in reverse lexicographical order this ensures that the first prime we get is the 
 largest. We also use an optimization that sum of digits in a number mod 3 cannot be 0 for primes (in base 10) in those cases we return
 instantly that no prime.
 Complexity:O(n!*n*sqrt(n)) [actually much less]
*/