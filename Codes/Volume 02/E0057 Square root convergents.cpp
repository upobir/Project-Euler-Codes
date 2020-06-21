# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 It is possible to show that the square root of two can be expressed as an infinite continued fraction.
 
 2–√=1+1/(2+1/(2+1/2+…)))
 By expanding this for the first four iterations, we get:
 
 1+1/2=3/2=1.5
 1+1/(2+1/2)=7/5=1.4
 1+1/(2+1/(2+1/2))=17/12=1.41666…
 1+1/(2+1/(2+1/(2+1/2)))=41/29=1.41379…
 
 The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, is the first example where the number of 
 digits in the numerator exceeds the number of digits in the denominator.
 
 In the first one-thousand expansions, how many fractions contain a numerator with more digits than the denominator?
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

    int lengthInBase10() const{
        if(parts.empty()) return 0;
        int ans = (parts.size()-1)*BASELENGTH;
        int prefix = parts.back();
        while(prefix){
            prefix /= 10;
            ans++;
        }
        return ans;
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

class PeriodicContinuedFraction{
private:
    vector<ll> initial, periodic;
public:
    // it only works with positive a, d, b for now
    PeriodicContinuedFraction(ll p = 0, ll d = 0, ll q = 1){
        assert(q > 0 && p >= 0 && d >= 0);
        if((d-p*p) % q != 0){
            p *= q, d *= q*q, q *= q;
        }
        map<pair<ll, ll>, int> mp;
        while(q != 0 && mp.count({p, q}) == 0){
            mp[{p, q}] = initial.size();
            ll floorDesc;
            squareRoot(d, floorDesc);
            ll a = (p+floorDesc)/q;
            initial.push_back(a);
            p = a*q-p;
            q = (d - p*p)/q;
        }
        if(q != 0){
            periodic.assign(initial.begin()+mp[{p, q}], initial.end());
            initial.resize(mp[{p, q}]);
        }
    }

    string toString(){
        string ret;
        for(int i = 0; i<initial.size(); i++) ret += ((i==0)? "" : ",") + to_string(initial[i]);
        ret += ":";
        for(int i = 0; i<periodic.size(); i++) ret += ((i==0)? "" : ",") + to_string(periodic[i]);
        return ret;
    }

    int period(){ return periodic.size(); }
    int prefix(){ return initial.size(); }

    ll get(ll pos){
        if(pos < initial.size()) return initial[pos];
        if(periodic.empty()) return 0;
        else return periodic[(pos-initial.size())%periodic.size()];
    }
};

class Convergent{
private:
    PeriodicContinuedFraction continuedFraction;
    BigInteger numerator, denominator;
    BigInteger prevNumerator, prevDenominator;
    int iteration;
public:
    Convergent(PeriodicContinuedFraction number){
        continuedFraction = number;
        numerator = BigInteger(1);
        prevDenominator = BigInteger(1);
        iteration = 0;
    }

    const BigInteger& getNumerator(){ return numerator; }
    const BigInteger& getDenominator(){ return denominator; }

    int order(){ return iteration-1; };

    bool isComplete(){
        if(continuedFraction.period() != 0) return false;
        if(iteration >= continuedFraction.prefix()) return true;
        return false;
    }

    void nextConvergent(){
        BigInteger newNumerator = numerator * continuedFraction.get(iteration) + prevNumerator;
        BigInteger newDenominator = denominator * continuedFraction.get(iteration) + prevDenominator;

        BigInteger::swap(prevNumerator, numerator);
        BigInteger::swap(numerator, newNumerator);
        BigInteger::swap(prevDenominator, denominator);
        BigInteger::swap(denominator, newDenominator);
        iteration++;
    }
};

int countSqrtConvergantWithLongerNumeratorUntil(ll num, int convergentCount){
    PeriodicContinuedFraction continuedFraction(0, num, 1);
    Convergent convergent(continuedFraction);
    int ans = 0;
    convergent.nextConvergent();
    for(int i = 1; i<=convergentCount; i++){
        convergent.nextConvergent();
        if(convergent.getNumerator().lengthInBase10() > convergent.getDenominator().lengthInBase10())
            ans++;
    }
    return ans;
}

int main(){
    Time(
        cout<<countSqrtConvergantWithLongerNumeratorUntil(2, 1000)<<endl;
    )
    return 0;
}

/*
Notes:
 First I made a class to handle continued fractions which will create the reperesentation given (a+sqrt(d))/b, after doing that I made a 
 class to handle the convergants which uses bigints to find the next convergant, finally I just simulated finding the first m convergant
 and checking which ones have longer numerator. This is obviously more complex than necessary, but I wanted to make it general.
 Complexity: O(sqrt(n) * log^2 n + m^2)
*/