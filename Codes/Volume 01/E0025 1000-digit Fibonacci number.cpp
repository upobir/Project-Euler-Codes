# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The Fibonacci sequence is defined by the recurrence relation:

 F_n = F_(n−1) + F_(n−2), where F_1 = 1 and F_2 = 1.
 Hence the first 12 terms will be:

 F_1 = 1
 F_2 = 1
 F_3 = 2
 F_4 = 3
 F_5 = 5
 F_6 = 8
 F_7 = 13
 F_8 = 21
 F_9 = 34
 F_10 = 55
 F_11 = 89
 F_12 = 144
 The 12th term, F12, is the first term to contain three digits.
 
 What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
*/

//index > 0
ll digitsOfFibonacci(ll index){
    if(index == 1) return 1;
    long double phi = (1.0l+sqrtl(5.0l))/2.0l;
    long double logOfFib = index * log10l(phi) - 0.5l * log10l(5.0l);
    ll digitCount = llround(floorl(logOfFib))+1;
    return digitCount;
}

ll firstNDigitFibonacciIndex(int digits){
    long double phi = (1.0l+sqrtl(5.0l))/2.0l;
    int guess = ((digits-1) + 0.5l * log10l(5.0l)) / log10l(phi) - 5;
    if(guess < 1) guess = 1;
    while(true){
        if(digitsOfFibonacci(guess) == digits)
            break;
        guess++;
    }
    return guess;
}

int main(){
    Time(
        cout<<firstNDigitFibonacciIndex(1000)<<endl;
    )
    return 0;
}

/*
Notes:
 We know nth fibonacci is round(phi^n/sqrt(5)), and x has floor(log10(x))+1 digits, so using this we can reverse engineer n, assuming that 
 the round part won't create problems, and it doesn't since fibonacci doesn't become 10^n or 10^n-0.5 (conjectured). So using the guess then
 we can check for first index to have requrired digits
 Complexity: O(1)
*/