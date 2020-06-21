# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred
 zeros. Despite their size, the sum of the digits in each number is only 1.

 Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/

class BigInteger{
    const static int BASE = 1000*1000*1000;
    const static int BASELENGTH = 9;
    vector<int> parts;

    int get(int i){
        return (i < parts.size())? parts[i] : 0;
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
        while(number.back() == 0) number.pop_back();
    }

    string toString() const {
        stringstream number;
        number << (parts.empty()? 0 : parts.back());
        for(int i = int(parts.size()) - 2; i>=0; i--){
            number<<setfill('0')<<setw(BASELENGTH)<<parts[i];
        }
        return number.str();
    }

    int digitSumBase10() const {
        int sum = 0;
        for(int part : parts){
            while(part){
                sum += part%10;
                part /= 10;
            }
        }
        return sum;
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
        while(!res.parts.empty() && res.parts.back() == 0) 
            res.parts.pop_back();
        return res;
    }
};

int maxDigitSumPoweredNumbesrTill(int baseMax, int exponentMax){
    int ans = 0;
    for(int base = 1; base < baseMax; base++){
        BigInteger num(base);
        for(int exponent = 1; exponent < exponentMax; exponent++, num = num * base){
            ans = max(ans, num.digitSumBase10());
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<maxDigitSumPoweredNumbesrTill(100, 100)<<endl;
    )
    return 0;
}

/*
Notes:
 A normal problem that just needs to be bruted. Note that instead of using binary exponentiation, I normally multiplied, this is due to the
 fact that we were gonna need each power anyway.
 Complexity:O(n * m^2 * log n)
*/