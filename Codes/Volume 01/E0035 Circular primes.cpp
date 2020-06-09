# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

 There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

 How many circular primes are there below one million?
*/

class basedNumber{
private:
    map<char, int> digitMap;
    string digits;
    string number;
    int base;
public:
    basedNumber(string digits, string number = ""){
        base = digits.size();
        assert(base > 1);
        this->digits = digits;
        for(int pos = 0; pos<digits.size(); pos++)
            digitMap[digits[pos]] = pos;
        this->number = ((number.empty())? string(1, digits[0]) : number);
    }

    void increment(){
        bool carry = true;
        for(int pos = number.size()-1; pos >= 0; pos--){
            if(!carry) break;
            number[pos] = ((number[pos] == digits.back())? digits[0] : digits[digitMap[number[pos]]+1]);
            carry = (number[pos] == digits[0]);
        }

        if(carry) number.insert(number.begin(), digits[0]);
    }

    string toString(){
        return number;
    }
};

vector<int> primeSieveTill(int maxNum){
    if(maxNum == 1) return vector<int>();
    vector<bool> oddComposite(maxNum/2+1);  // oddComposite[i] = whether 2*i+1 is non-prime
    vector<int> primes{2};

    for(int p = 3; p <= maxNum; p+=2){
        if(oddComposite[p>>1]) continue;

        primes.push_back(p);

        if(maxNum/p < p) continue;
        for(int multiple = p*p; multiple <= maxNum; multiple += p+p)
            oddComposite[multiple/2] = true;
    }
    return primes;
}

int countCircularPrimeUntil(int maxNum){
    int bound = 1;
    while(bound < maxNum) bound *= 10;
    vector<int> primes = primeSieveTill(bound);

    enum FLAG{UNKNOWN, TRUE, FALSE};
    vector<FLAG> isCircularPrime(bound+1, FALSE);

    for(int p : primes) isCircularPrime[p] = UNKNOWN;

    basedNumber bNumber("1379");
    while(true){
        string sNumber = bNumber.toString();
        int number = stoi(sNumber), tmpNumber;

        bNumber.increment();

        if(number >= maxNum) break;
        if(isCircularPrime[number] != UNKNOWN) continue;

        do{
            rotate(sNumber.begin(), sNumber.begin()+1, sNumber.end());
            tmpNumber = stoi(sNumber);
            if(isCircularPrime[tmpNumber] == FALSE) break;
            isCircularPrime[tmpNumber] = FALSE;
        }while(tmpNumber != number);
        
        if(tmpNumber != number){
            isCircularPrime[number] = FALSE;
            continue;
        }

        do{
            rotate(sNumber.begin(), sNumber.begin()+1, sNumber.end());
            tmpNumber = stoi(sNumber);
            isCircularPrime[tmpNumber] = TRUE;
        }while(tmpNumber != number);
    }

    int count = (maxNum > 2) + (maxNum > 5); //counting 2 and 5
    for(int number = 1; number<maxNum; number++)
        count += (isCircularPrime[number] == TRUE);

    return count;
}

int main(){
    Time(
        cout<<countCircularPrimeUntil(1000*1000)<<endl;
    )
    return 0;
}

/*
Notes:
 Again I convoluted a simple program for the sake of generality, I created a class that basically traverses thorugh permuation with
 repetition, since the circular primes can't have 0, 2, 4, 5, 6, 8 in them, so we just use digits 1, 3, 7, 9. We also mark numbers while 
 doing the rotation s.t. we never come back to same number twice.
 Complexity:O(10^log n * log n + 4^log n * log n)
*/