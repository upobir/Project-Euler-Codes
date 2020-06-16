# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

 Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/

string digitSignature(ll number){
    string ret = to_string(number);
    sort(ret.begin(), ret.end());
    return ret;
}

ll firstNumberWithPermutedMultiples(int multiplyer){
    for(ll number = 1, digitBound = 10; ; number++){
        if(number*multiplyer >= digitBound){
            number = digitBound-1;
            digitBound *= 10;
            continue;
        }

        string signature = digitSignature(number);
        bool possible = true;
        for(ll multiple = number*multiplyer; possible && multiple > number; multiple -= number){
            if(signature != digitSignature(multiple)){
                possible = false;
                break;
            }
        }

        if(possible) return number;
    }
}

int main(){
    Time(
        cout<<firstNumberWithPermutedMultiples(6)<<endl;
    )
    return 0;
}

/*
Notes:
 We check all number for their digit signatures, there is one optimization of first checking if highest multiple has same number of digit
 or not.
 Complexity:O(X/n)
*/