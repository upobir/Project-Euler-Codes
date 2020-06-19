# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 
 What is the sum of the digits of the number 2^1000?
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
            int startPos = (done >= BASELENGTH)? done - BASELENGTH : 0;
            int length = ((startPos != 0)? BASELENGTH : done);
            int part = stoi(number.substr(startPos, length));
            parts.push_back(part);
        }
        while(number.back() == 0) number.pop_back();
    }

    string toString(){
        stringstream number;
        number << (parts.empty()? 0 : parts.back());
        for(int i = int(parts.size()) - 2; i>=0; i--){
            number<<setfill('0')<<setw(BASELENGTH)<<parts[i];
        }
        return number.str();
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

    BigInteger expo(ll e){
        BigInteger ret = 1, b = *this;
        while(e){
            if(e&1) ret = ret * b;
            b = b * b;
            e >>= 1;
        }
        return ret;
    }
};

int sumOfDigitsOfPower(ll num, ll exponent){
    BigInteger bigNum = BigInteger(num).expo(exponent);
    string numString = bigNum.toString();
    int digitSum = 0;
    for(char digit : numString)
        digitSum += digit - '0';
    return digitSum;
}

int main(){
    Time(
        cout<<sumOfDigitsOfPower(2, 1000)<<endl;
    );
    return 0;
}

/*
Notes:
 Using bigintger we can find the powered number. To optimize the process, we use binary exponentiating to get the result faster. Then just sum the digits.
 Complexity: O(m^2 * log m)
*/