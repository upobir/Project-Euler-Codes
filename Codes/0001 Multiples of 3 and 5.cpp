# include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

/*
Statement
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
Find the sum of all the multiples of 3 or 5 below 1000.
*/

ll sumArithmetic(ll a, ll d, ll n){
    return n * (2*a + (n - 1) * d) / 2;
}

ll sumMultiplesBelow(ll maxNum, ll num1, ll num2){
    maxNum--;
    ll lcm = num1*num2/__gcd(num1, num2);
    ll ret = sumArithmetic(num1, num1, maxNum/num1) + sumArithmetic(num2, num2, maxNum/num2);
    ret -= sumArithmetic(lcm, lcm, maxNum/lcm);
    return ret;
}

int main(){
    //std::cout<<sumArithmetic(1, 1, 10);
    std::cout<<sumMultiplesBelow(1000, 3, 5)<<std::endl;    
    return 0;
}

/*
Notes:
We find sum of multiples of 3 and 5 together (which are just arithmetic series) and then subtract the multiples of 15 (lcm of 3 and 5)
*/