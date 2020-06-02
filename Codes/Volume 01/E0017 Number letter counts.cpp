# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

 If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

 NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen)
 contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*/

namespace Numeral
{
    const map<int, string> wordMap{
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"},
        {10, "ten"}, {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, 
        {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"},
        {20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}
    };

    string tripleDigits[] = {"", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion"};

    string toWord(ll number, bool useAnd = false){
        if(number == 0) return "zero";
        string ret = "";
        bool negative = (number < 0);
        if(negative) number = -number;
        int period = 0;
        while(number){  //triples are abc
            string triple = "";
            int bc = number % 100;
            while(bc){
                auto it = --wordMap.upper_bound(bc);
                if(!triple.empty()) triple += "-";
                triple += it->second;
                bc -= it->first;
            }
            number /= 100;

            if(useAnd && !triple.empty() && number > 0) triple = "and "+triple;
            int a = number % 10;
            if(a != 0){
                string part = wordMap.at(a) + " hundred";
                if(!triple.empty()) part += " ";
                triple = part + triple;
            }
            number /= 10;

            if(!triple.empty() && period > 0) triple += " " + tripleDigits[period];
            if(!triple.empty() && !ret.empty()) triple += " ";
            ret = triple + ret;
            period++;
        }
        return (negative)? "minus " + ret : ret;
    }
};


int sumLettersNumeralsTill(int maxNum){
    int sum = 0;
    for(int num = 1; num <= maxNum; num++){
        string numeral = Numeral::toWord(num, true);
        for(char c : numeral)
            if(isalpha(c)) sum++;
    }
    return sum;
}

int main(){
    Time(
        cout<<sumLettersNumeralsTill(1000)<<endl;
    )
    return 0;
}

/*
Notes:
 Made a function to map numbers to string with lots of if-else. For the problem only number till thousand was needed, but made one that
 works upto a long long int's range.
 Complexity: O(n)
*/