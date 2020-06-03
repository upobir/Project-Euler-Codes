# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
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
            int part = stoi(number.substr(startPos, BASELENGTH));
            parts.push_back(part);
        }
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
};

int sumFactorialDigits(int num){
    BigInteger fact(1);
    for(int i = 1; i<=num; i++)
        fact = fact * i;
    string factString = fact.toString();
    int sum = 0;
    for(char c : factString)
        sum += c - '0';
    return sum;
}

int main(){
    Time(
        cout<<sumFactorialDigits(100)<<endl;
    )
    return 0;
}

/*
Notes:
 This is just use of bigint library
 Complexity: O(n^2 * log n)
*/