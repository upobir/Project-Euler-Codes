# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three 
 terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.

 There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit 
 increasing sequence.

 What 12-digit number do you form by concatenating the three terms in this sequence?
*/

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

vector<tuple<int, int, int>> getArithmeticTriple(vector<int> numbers){
    sort(numbers.begin(), numbers.end());
    vector<tuple<int, int, int>> triples;
    for(int i = 0; i<numbers.size(); i++){
        for(int j = 0, k = 0; j<i; j++){
            while(k < numbers.size() && 2*numbers[k] < numbers[i]+numbers[j]) 
                k++;
            if(2*numbers[k] == numbers[i] + numbers[j])
                triples.emplace_back(numbers[j], numbers[k], numbers[i]);
        }
    }
    return triples;
}

string digitSignature(ll number){
    string ret = to_string(number);
    sort(ret.begin(), ret.end());
    return ret;
}

string concatenatedPermutedArithmaticNumbers(int digits, vector<string> except){
    int start = 1;
    for(int i = 1; i<digits; i++) start *= 10;
    int finish = start*10;
    vector<int> primes = primeSieveTill(finish-1);
    string res = "";

    unordered_map<string, vector<int>> digitBin;
    int index = lower_bound(primes.begin(), primes.end(), start) - primes.begin();
    while(index < primes.size()){
        int prime = primes[index];

        string signature = digitSignature(prime);
        digitBin[signature].push_back(prime);

        index++;
    }

    for(auto entry : digitBin){
        if(find(except.begin(), except.end(), entry.first) != except.end())
            continue;
        auto triples = getArithmeticTriple(entry.second);
        if(triples.empty()) continue;
        res += to_string(get<0>(triples.front()));
        res += to_string(get<1>(triples.front()));
        res += to_string(get<2>(triples.front()));
        return res;
    }

    return res;
}

int main(){
    Time(
        cout<<concatenatedPermutedArithmaticNumbers(4, {"1478"});
    )
    return 0;
}

/*
Notes:
 First we use sieve to get all the primes upto 4 digits, then in the range of 4 digits, we iterate on those primes and put them in their 
 'digit bins' i.e. by sorting their digits as characters we get an unique permutation and place these numbers in a unordered map using that
 sorted form as key. In this way this map's bins contain number of same digit permutation. Afterwards, we check each bin for a arithmetic 
 sequence using two pointer
 Complexity: O(n! * 10^n / n)
*/