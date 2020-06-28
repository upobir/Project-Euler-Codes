# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 All square roots are periodic when written as continued fractions and can be written in the form:
 
 √N=a0+1/(a1+1/(a2+1/(a3+…)))
 For example, let us consider √23:√23=4+√23−4=4+1/(1/(√23−4))=4+1/(1+(√23−3)/7)
 If we continue we would get the following expansion:
 
 √23=4+1/(1+1/(3+1/(1+1/(8+…))))
 The process can be summarised as follows:
 
 a0=4,1/(√23−4)=(√23+4)/7=1+(√23−3)/7
 a1=1,7/(√23−3)=7(√23+3)/14=3+(√23−3)/2
 a2=3,2/(√23−3)=2(√23+3)/14=1+(√23−4)/7
 a3=1,7/(√23−4)=7(√23+4)/7=8+√23−4
 a4=8,1/(√23−4)=(√23+4)7=1+(√23−3)/7
 a5=1,7/(√23−3)=7(√23+3)/14=3+(√23−3)/2
 a6=3,2/(√23−3)=2(√23+3)/14=1+(√23−4)/7
 a7=1,7/(√23−4)=7(√23+4)/7=8+√23−4
 It can be seen that the sequence is repeating. For conciseness, we use the notation 23−−√=[4;(1,3,1,8)], to indicate that the block 
 (1,3,1,8) repeats indefinitely.
 
 The first ten continued fraction representations of (irrational) square roots are:
 
 √2=[1;(2)], period=1
 √3=[1;(1,2)], period=2
 √5=[2;(4)], period=1
 √6=[2;(2,4)], period=2
 √7=[2;(1,1,1,4)], period=4
 √8=[2;(1,4)], period=2
 √10=[3;(6)], period=1
 √11=[3;(3,6)], period=2
 √12=[3;(2,6)], period=2
 √13=[3;(1,1,1,1,6)], period=5
 
 Exactly four continued fractions, for N≤13, have an odd period.
 
 How many continued fractions for N≤10000 have an odd period?
*/

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

int countSqrtContFracOddPeriodUntil(int bound){
    int count = 0;
    for(int num = 1; num <= bound; num++){
        PeriodicContinuedFraction frac(0, num);
        if(frac.period() % 2 == 1) count++;
    }
    return count;
}

int main(){
    Time(
        cout<<countSqrtContFracOddPeriodUntil(10000)<<endl;
    )
    return 0;
}

/*
Notes:
 We already know how to compute periodic fractions of quadratic surds, so using that made the period for all numbers until bound and checked
 the period. Note that period length for (p+sqrt(d))/q is O(sqrt(d)*log(d)).
 Complexity: O(n * sqrt(n) * log n)
*/