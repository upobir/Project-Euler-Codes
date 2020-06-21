# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
 
 Not all numbers produce palindromes so quickly. For example,
 
 349 + 943 = 1292,
 1292 + 2921 = 4213
 4213 + 3124 = 7337
 
 That is, 349 took three iterations to arrive at a palindrome.
 
 Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome. A number that never forms a 
 palindrome through the reverse and add process is called a Lychrel number. Due to the theoretical nature of these numbers, and for the 
 purpose of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition you are given that for every number 
 below ten-thousand, it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power 
 that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require over fifty iterations 
 before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).
 
 Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
 
 How many Lychrel numbers are there below ten-thousand?
 
 NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.
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

    BigInteger reverseBase10() const {
        string sBig = toString();
        reverse(sBig.begin(), sBig.end());
        return BigInteger(sBig);
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

    bool operator==(BigInteger other){
        return parts == other.parts;
    }
    
};

bool isLychrelUntil(ll num, int maxIteration){
    BigInteger number(num);
    BigInteger revNumber = number.reverseBase10();
    for(int i = 1; i<maxIteration; i++){
        number = number + revNumber;
        revNumber = number.reverseBase10();
        if(number == revNumber) return false;
    }
    return true;
}

int countLychrelBoundedUntil(int maxNum, int maxIteration){
    int count = 0;
    for(int num = 1; num < maxNum; num++){
        if(isLychrelUntil(num, maxIteration))
            count++;
    }
    return count;
}

int main(){
    Time(
        cout<<countLychrelBoundedUntil(10*1000, 50)<<endl;
    )
    return 0;
}

/*
Notes:
 Since the numbers can get big, I used biginteger, this is possibly overkill, but eh. just simulate the process
 Complexity: O(n*m*log n)
*/