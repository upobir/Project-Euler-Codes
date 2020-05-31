# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 
 = 28. The first ten terms would be:

 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

 Let us list the factors of the first seven triangle numbers:

  1: 1
  3: 1,3
  6: 1,2,3,6
 10: 1,2,5,10 
 15: 1,3,5,15
 21: 1,3,7,21
 28: 1,2,4,7,14,28
 We can see that 28 is the first triangle number to have over five divisors.

 What is the value of the first triangle number to have over five hundred divisors?
*/

ll polygonalNum(ll n, ll sides){
    return (sides - 2) * n * (n-1) / 2 + n;
}

vector<int> tauSieveTill(int maxNum){
    vector<int> tau(maxNum+1);

    for(int d = 1; d <= maxNum; d++){
        for(int multiple = d; multiple <= maxNum; multiple += d)
            tau[multiple]++;
    }
    return tau;
}

ll firstTriNumWithMinDivisors(ll targetDiviCount){
    int guessBound = 1.5 * pow(targetDiviCount+1, 1.0/2.0 * 3.0);
    vector<int> tau = tauSieveTill(guessBound);

    int num = 0, currentDiviCount = -1;
    do{
        num++;
        int term1 = (num % 2 == 0)? num/2 : num;
        int term2 = (num % 2 == 0)? num+1 : (num+1)/2;
        currentDiviCount = tau[term1] * tau[term2];
    }while(num < guessBound && currentDiviCount < targetDiviCount);

    if(num >= guessBound) return -1;
    return polygonalNum(num, 3);
}

int main(){
    Time(
        cout<<firstTriNumWithMinDivisors(500)<<endl;
    );
    return 0;
}

/*
Notes:
 We know that triangle(n) = n*(n+1)/2, product of two coprimes, so we assume for existance their contribution will be equal resulting in 
 d^(0.5) divisor count for ~n, and we know divisor count till n can be maximum n^(1/3), so we set guessbound to be constant * d^(3/2).
 After that we precompute the divisor counts with sieve and just for each triangle(i), check with just the coprime terms.
 Complexity: O(n^(3/2) * log n)
*/