# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Consider quadratic Diophantine equations of the form:
 
 x^2 – Dy^2 = 1
 
 For example, when D=13, the minimal solution in x is 649^2 – 13×180^2 = 1.
 
 It can be assumed that there are no solutions in positive integers when D is square.
 
 By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
 
 3^2 – 2×2^2 = 1
 2^2 – 3×1^2 = 1
 9^2 – 5×4^2 = 1
 5^2 – 6×2^2 = 1
 8^2 – 7×3^2 = 1
 
 Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.
 
 Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.
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

class ContinuedFraction{
public:
    virtual ll get(ll pos) = 0;
    virtual string toString() = 0;
};

class PeriodicContinuedFraction : public ContinuedFraction{
private:
    vector<ll> initial, periodic;
public:
    // it only works with positive a, d, b for now
    // (p + sqrt(d))/q
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

    string toString() override{
        string ret;
        for(int i = 0; i<initial.size(); i++) ret += ((i==0)? "" : ",") + to_string(initial[i]);
        ret += ":";
        for(int i = 0; i<periodic.size(); i++) ret += ((i==0)? "" : ",") + to_string(periodic[i]);
        return ret;
    }

    int period(){ return periodic.size(); }
    int prefix(){ return initial.size(); }

    ll get(ll pos) override {
        if(pos < initial.size()) return initial[pos];
        if(periodic.empty()) return 0;
        else return periodic[(pos-initial.size())%periodic.size()];
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

pair<BigInteger, BigInteger> getFundamentalPellSolution(ll num){
    shared_ptr<ContinuedFraction> continuedFraction = make_shared<PeriodicContinuedFraction>(0, num, 1);
    Convergent convergent(continuedFraction);
    while(true){
        convergent.nextConvergent();
        BigInteger x = convergent.getNumerator();
        BigInteger y = convergent.getDenominator();
        if(x*x == y*y*num+1) return make_pair(x, y);
    }
}

int numWithMaxXForPellEqnUntil(int bound){
    int ans = -1;
    BigInteger best;
    for(int num = 1; num <= bound; num++){
        ll tmp;
        if(squareRoot(num, tmp)) continue;
        pair<BigInteger, BigInteger> solution = getFundamentalPellSolution(num);
        if(best < solution.first){
            best = solution.first;
            ans = num;
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<numWithMaxXForPellEqnUntil(1000)<<endl;
    )
    return 0;
}

/*
Notes:
 The solution to equation x^2-Dy^2 = 1 with minimal x is called fundamental solution and it is found via testing the convergents of sqrt(D).
 So we just simulated that.
 Complexity: O(n * sqrt(n) * log n + n * log^2(n))
*/