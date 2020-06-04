# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper 
 divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

 A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

 As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers 
 is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. 
 However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be 
 expressed as the sum of two abundant numbers is less than this limit.

 Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

vector<ll> sigmaSieveTill(int maxNum){
    vector<ll> sigma(maxNum+1);

    for(int d = 1; d <= maxNum; d++){
        for(int multiple = d; multiple <= maxNum; multiple += d)
            sigma[multiple]+=d;
    }
    return sigma;
}

ll sumNonAbundantSumNumbers(){
    const int bound = 28123;
    int count = 0;
    vector<ll> sigma = sigmaSieveTill(bound);
    bitset<bound+1> abundants, sumPossible;
    for(int num = 1; num <= bound; num++)
        if(sigma[num] > 2*num) abundants[num] = 1;

    for(int num = 1; num <= bound; num++)
        if(abundants[num]) sumPossible |= abundants << num; 
    ll ret = 0;

    for(int num = 1; num <= bound; num++)
        if(!sumPossible[num]) ret += num;
    return ret;
}

int main(){
    Time(
        cout<<sumNonAbundantSumNumbers()<<endl;
    )
    return 0;
}

/*
Notes:
 Since a bound has already been given, we first use sieve to find the numbers till that bound that are abandunt. Afterwards, we need to find
 the numbers which are sum of two abandunt numbers, if one wants to optimize the most, one can use FFT here, however I opted for easier code
 with using bitset shifts.
 Complexity: O(A(n)*n/W)
*/