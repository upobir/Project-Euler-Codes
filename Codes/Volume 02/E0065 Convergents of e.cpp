# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
The square root of 2 can be written as an infinite continued fraction.

√2=1+1/(2+1/(2+1/(2+1/(2+...))))

The infinite continued fraction can be written, √2=[1;(2)], (2) indicates that 2 repeats ad infinitum. In a similar way, √23=[4;(1,3,1,8)].

It turns out that the sequence of partial values of continued fractions for square roots provide the best rational approximations. Let us 
consider the convergents for √2.

1+1/2=3/2
1+1/(2+1/2)=7/5
1+1/(2+1/(2+1/2))=17/12
1+1/(2+1/(2+1/(2+1/2)))=41/29

Hence the sequence of the first ten convergents for √2 are:

1,3/2,7/5,17/12,41/29,99/70,239/169,577/408,1393/985,3363/2378,...

What is most surprising is that the important mathematical constant,
e=[2;1,2,1,1,4,1,1,6,1,...,1,2k,1,...].

The first ten terms in the sequence of convergents for e are:

2,3,8/3,11/4,19/7,87/32,106/39,193/71,1264/465,1457/536,...
The sum of digits in the numerator of the 10th convergent is 1+4+5+7=17.

Find the sum of digits in the numerator of the 100th convergent of the continued fraction for e.
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

    static void swap(BigInteger &first, BigInteger &second){
        std::swap(first.parts, second.parts);
    }
};

class ContinuedFraction{
public:
    virtual ll get(ll pos) = 0;
    virtual string toString() = 0;
};

class PatternedContinuedFraction : public ContinuedFraction {
private:
    function<ll(ll)> pattern;
    int toStringBound;
public:
    PatternedContinuedFraction(function<ll(ll)> pattern, int toStringBound = 20){
        this->pattern = pattern;
        this->toStringBound = toStringBound;
    }

    ll get(ll pos) override {
        return pattern(pos);
    }

    string toString() override {
        string ret;
        for(int pos = 0; pos<toStringBound; pos++){
            ret += to_string(get(pos)) + ",";
        }
        ret += "...";
        return ret;
    }
};

class Convergent{
private:
    shared_ptr<ContinuedFraction> continuedFraction;
    BigInteger numerator, denominator;
    BigInteger prevNumerator, prevDenominator;
    int iteration;
public:
    Convergent(shared_ptr<ContinuedFraction> continuedFraction){
        this->continuedFraction = continuedFraction;
        numerator = BigInteger(1);
        prevDenominator = BigInteger(1);
        iteration = 0;
    }

    const BigInteger& getNumerator(){ return numerator; }
    const BigInteger& getDenominator(){ return denominator; }

    int order(){ return iteration-1; };

    void nextConvergent(){
        BigInteger newNumerator = numerator * continuedFraction->get(iteration) + prevNumerator;
        BigInteger newDenominator = denominator * continuedFraction->get(iteration) + prevDenominator;

        BigInteger::swap(prevNumerator, numerator);
        BigInteger::swap(numerator, newNumerator);
        BigInteger::swap(prevDenominator, denominator);
        BigInteger::swap(denominator, newDenominator);
        iteration++;
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

ll sumNumeratorDigitsOfConvergentsOfE(int nth){
    shared_ptr<ContinuedFraction> continuedFraction = make_shared<PatternedContinuedFraction>([](ll pos){
        if(pos == 0) return 2ll;
        return (pos % 3 == 2)? (pos/3+1)*2ll : 1ll;
    });
    Convergent convergent(continuedFraction);

    for(int order = 1; order <= nth; order++){
        convergent.nextConvergent();
    }
    ll sum = convergent.getNumerator().digitSumBase10();
    return sum;
}


int main(){
    Time(
        cout<<sumNumeratorDigitsOfConvergentsOfE(100)<<endl;
    )
    return 0;
}

/*
Notes:
 We have code for convergent, just needed to define a new kind of continued fraction, patterned which works with patterned fucntion.
 Complexity: O(n^2)
*/