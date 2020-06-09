# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

 The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

 Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

 HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/

ll sumPandigitalProductOfDigits(int digits){
    string allDigits(digits, '1');
    iota(allDigits.begin(), allDigits.end(), '1');
    int prodPart = (digits+1)/2;
    set<int> pandigitalNums;

    do{
        int num = stoi(allDigits.substr(prodPart));
        for(int firstPart = 1; firstPart <= prodPart/2; firstPart++){
            int prod1 = stoi(allDigits.substr(0, firstPart));
            int prod2 = stoi(allDigits.substr(firstPart, prodPart - firstPart));
            if(prod1*prod2 == num)
                pandigitalNums.insert(num);
        }
    }while(next_permutation(allDigits.begin(), allDigits.end()));

    ll sum = accumulate(pandigitalNums.begin(), pandigitalNums.end(), 0ll);

    return sum;
}

int main(){
    Time(
        cout<<sumPandigitalProductOfDigits(9)<<endl;
    )
    return 0;
}

/*
Notes:
 Since we know the a*b as digits = digit(a)+digit(b) + 0 or 1, so from this we can infer digit(a)+digit(b), after that we test all 
 permutation. This'd probably be faster with divisors, but this is less code.
 Complexity: O(n! * n)
*/