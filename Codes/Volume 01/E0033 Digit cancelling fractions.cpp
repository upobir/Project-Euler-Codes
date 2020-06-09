# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 
 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

 We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

 There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator 
 and denominator.

 If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

class fraction{
private:
    ll numerator, denominator;
    void normalize(){
        if(denominator < 0) 
            numerator = -numerator, denominator = -denominator;
        ll gcd = __gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
public:
    fraction(ll numerator = 0, ll denominator = 1, bool normalized = false){
        assert(denominator != 0);
        this->numerator = numerator;
        this->denominator = denominator;
        if(!normalized)
            normalize();
    }

    ll getNumerator(){ return numerator;}
    ll getDenominator(){ return denominator;}

    bool operator==(fraction other){
        return numerator == other.numerator && denominator == other.denominator;
    }

    fraction operator*(fraction other){
        ll gcd1 = __gcd(numerator, other.denominator);
        ll gcd2 = __gcd(denominator, other.numerator);

        ll prodNumerator = (numerator/gcd1) * (other.numerator/gcd2);
        ll prodDenominator = (denominator/gcd2) * (other.denominator/gcd1);
        return fraction(prodNumerator, prodDenominator, true);
    }
};

ll prdouctDenomDigitCancelFractions(){
    fraction res(1);
    for(int a = 1; a <=9; a++)
        for(int c = a+1; c <= 9; c++)
            for(int b = 1; b <= 9; b++){
                if(b == a || b == c) continue;
                int num1, num2;

                num1 = 10*a+b, num2 = b*10+c;
                if(fraction(num1, num2) == fraction(a, c)){
                    res = res * fraction(num1, num2);
                }

                num1 = 10*b+a, num2 = c*10+b;
                if(fraction(num1, num2) == fraction(a, c)){
                    res = res * fraction(num1, num2);
                }
            }
    return res.getDenominator();
}

int main(){
    Time(
        cout<<prdouctDenomDigitCancelFractions()<<endl;
    )
}

/*
Notes:
 since one digit must be common we let that be b, and find choose all a, c pair, the numbers should be ab/bc or ba/bc as if b being in same
 position implies a = c i.e. 1. And finally since the fractions are less than 1, a < c. And we use a fraction class just cause we can
 Complexity:O(1)
*/