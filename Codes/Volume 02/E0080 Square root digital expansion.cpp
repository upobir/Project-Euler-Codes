# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 It is well known that if the square root of a natural number is not an integer, then it is irrational. The decimal expansion of such square 
 roots is infinite without any repeating pattern at all.
 
 The square root of two is 1.41421356237309504880..., and the digital sum of the first one hundred decimal digits is 475.
 
 For the first one hundred natural numbers, find the total of the digital sums of the first one hundred decimal digits for all the 
 irrational square roots.
*/

class BigInteger{
    const static int BASE = 1000*1000*1000;
    const static int BASELENGTH = 9;

    vector<int> parts;

    int get(int i){
        return (i < parts.size())? parts[i] : 0;
    }

    void fix(){
        while(parts.size() > 1 && parts.back() == 0) parts.pop_back();
    }

public:
    BigInteger(){}

    BigInteger(ll number){
        while(number){
            parts.push_back(number % BASE);
            number /= BASE;
        }
    }

    BigInteger(string number){
        for(int done = int(number.size()); done > 0; done -= 9){
            int startPos = ((done >= BASELENGTH)? done - BASELENGTH : 0);
            int length = ((startPos != 0)? BASELENGTH : done);
            int part = stoi(number.substr(startPos, length));
            parts.push_back(part);
        }
        fix();
    }

    static BigInteger tenPower(int zeros){
        BigInteger ret;
        ret.parts.resize(zeros/BASELENGTH);
        zeros %= BASELENGTH;
        ret.parts.push_back(1);
        for(int i = 0; i<zeros; i++) ret.parts.back() *= 10;
        return ret;
    }

    string toString() const {
        stringstream number;
        number << (parts.empty()? 0 : parts.back());
        for(int i = int(parts.size()) - 2; i>=0; i--){
            number<<setfill('0')<<setw(BASELENGTH)<<parts[i];
        }
        return number.str();
    }

    BigInteger operator+(BigInteger other){
        BigInteger res;
        int carry = 0;
        for(int i = 0; i<parts.size() || i<other.parts.size() || carry != 0; i++){
            res.parts.push_back(carry + get(i) + other.get(i));
            carry = (res.parts.back() >= BASE);
            if(carry != 0)
                res.parts.back() -= BASE;
        }
        return res;
    }

    BigInteger operator*(BigInteger other){
        BigInteger res;
        res.parts.resize(parts.size() + other.parts.size());
        for(int i = 0; i<parts.size(); i++){
            for(int j = 0, carry = 0; j<other.parts.size() || carry != 0; j++){
                ll cur = res.parts[i+j] + ll(get(i))*ll(other.get(j)) + carry;
                res.parts[i+j] = int(cur % BASE);
                carry = int(cur / BASE);
            }
        }
        res.fix();
        return res;
    }

    static void swap(BigInteger &first, BigInteger &second){
        std::swap(first.parts, second.parts);
    }

    bool operator==(BigInteger other){
        return parts == other.parts;
    }

    bool operator<(BigInteger other){
        if(parts.size() != other.parts.size())
            return parts.size() < other.parts.size();
        for(int pos = int(parts.size())-1; pos >= 0; pos--){
            if(parts[pos] < other.parts[pos]) return true;
            if(parts[pos] > other.parts[pos]) return false;
        }
        return false;
    }

    pair<BigInteger, BigInteger> divide(int divisor){
        int remainder = 0;
        BigInteger quotient(*this);
        for(int i = (int)quotient.parts.size()-1; i>=0; i--){
            ll cur = quotient.parts[i] + ll(remainder)*ll(BASE);
            quotient.parts[i] = int(cur/divisor);
            remainder = int(cur % divisor);
        }
        quotient.fix();
        return {quotient, BigInteger(remainder)};
    }

    pair<BigInteger, BigInteger> divide(BigInteger divisor){
        BigInteger quotient, remainder(*this);
        int scale = BASE/(divisor.parts.back()+1), len = divisor.parts.size();
        divisor = divisor*scale; remainder = remainder*scale;   //scale to make the division process optimal

        for(int shift = int(remainder.parts.size())-len; shift >= 0; shift--){
            int digit = (remainder.get(len+shift)*ll(BASE) + remainder.get(len+shift-1))/divisor.parts.back();
            quotient.parts.push_back(digit = min(digit, BASE-1));
            BigInteger tmp(divisor);

            //make tmp = divisor * digit
            for(int i = 0, carry = 0; i<tmp.parts.size() || carry; i++){
                if(i == tmp.parts.size()) tmp.parts.push_back(0);
                ll cur = carry + ll(tmp.parts[i])*digit;
                tmp.parts[i] = cur % BASE;
                carry = cur / BASE;
            }

            while(true){
                int j1, j2;
                for(j1 = remainder.parts.size()-1, j2 = j1-shift; j1 >= shift; j1--, j2--)
                    if(remainder.get(j1) != tmp.get(j2)) break;
                if(j1 < shift || remainder.get(j1) > tmp.get(j2)) break;       //check if tmp > part of dividend
                //if too large subtract divisor
                for(int i = 0, carry = 0; i<divisor.parts.size() || carry; i++){
                    tmp.parts[i] -= carry + divisor.get(i);
                    if(carry = (tmp.parts[i] < 0)) tmp.parts[i] += BASE;
                }
                tmp.fix();
                quotient.parts.back()--;
            }
            //subtract tmp from actual remainder
            for(int i1 = shift, i2 = 0, carry = 0; i1 < remainder.parts.size(); i1++, i2++){
                remainder.parts[i1] -= carry + tmp.get(i2);
                if(carry = (remainder.parts[i1] < 0)) remainder.parts[i1] += BASE;
            }
            while(remainder.parts.size() >= shift + len && remainder.parts.back() == 0) remainder.parts.pop_back();
        }

        reverse(quotient.parts.begin(), quotient.parts.end());
        quotient.fix();
        remainder = remainder.divide(scale).first;
        return {quotient, remainder};
    }

    BigInteger squareRoot(){
        BigInteger curGuess((*this+1).divide(2).first), prvGuess(*this);
        while(curGuess < prvGuess){
            swap(curGuess, prvGuess);
            curGuess = (prvGuess + divide(prvGuess).first).divide(2).first;
        }
        return prvGuess;
    }    
};

bool squareRoot(ll x, ll &y){
    y = sqrtl(x);
    for(y = max(0ll, y-1); ;y++){
        if(y*y>x){
            y = y-1;
            return false;
        }
        if(y*y == x) return true;
    }
}

ll sumSquareRootDigits(int bound, int digits){
    BigInteger shift = BigInteger::tenPower(digits*2);
    ll ans = 0;
    for(int num = 1; num <= bound; num++){
        ll root;
        if(squareRoot(num, root)) continue;
        BigInteger tmp = (shift * num).squareRoot();
        string rootString = tmp.toString();
        for(int i = 0; i<digits; i++) ans += rootString[i] - '0';
    }
    return ans;
}

int main(){
    Time(
        cout<<sumSquareRootDigits(100, 100)<<endl;
    )
    return 0;
}

/*
Notes:
 To find square root in decimal expansion, first we expand every number to 10^(2*digit), this is to make sure root has 'digits' count, then
 we find square root using Newton's method, it's a little slow, but I'll go with it.
*/