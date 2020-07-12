# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Let p(n) represent the number of different ways in which n coins can be separated into piles. For example, five coins can be separated into 
 piles in exactly seven different ways, so p(5)=7.
 
 OOOOO
 OOOO O
 OOO OO
 OOO O O
 OO OO O
 OO O O O
 O O O O O
 Find the least value of n for which p(n) is divisible by one million.
*/
class modPartition{
private:
    vector<ll> partitions;
    ll mod;
    void calculateNext(){
        int number = partitions.size();
        partitions.push_back(0);
        for(int i = 1; ;i++){
            int recurTerm = number - i*(3*i-1)/2;
            if(recurTerm < 0) break;
            partitions.back() += ((i&1)? partitions[recurTerm] : -partitions[recurTerm]);
            if(partitions.back() >= mod) partitions.back() -= mod;
            if(partitions.back() < 0) partitions.back() += mod;
        }
        for(int i = -1; ;i--){
            int recurTerm = number - i*(3*i-1)/2;
            if(recurTerm < 0) break;
            partitions.back() += ((i&1)? partitions[recurTerm] : -partitions[recurTerm]);
            if(partitions.back() >= mod) partitions.back() -= mod;
            if(partitions.back() < 0) partitions.back() += mod;
        }
    }
public:
    modPartition(ll mod){
        this->mod = mod;
        partitions.push_back(1%mod);
    }
    ll partitionCount(int number){
        while(partitions.size() <= number) calculateNext();
        return partitions[number];
    }
};

int firstNumberWithPartitionCountDivisibleBy(int mod){
    modPartition partitions(mod);
    for(int number = 1; ;number++){
        int partitionCount = partitions.partitionCount(number);
        if(partitionCount == 0) return number;
    }
}

int main(){
    Time(
        cout<<firstNumberWithPartitionCountDivisibleBy(1'000'000)<<endl;
    )
    return 0;
}

/*
Notes:
 We use a surprising recurrence relation for n, which is p(n) = sum of (-1)^(i+1) p(n-i*(3i-1)/2) over all positive and negative i (not 0).
 And p(-ve) = 0. This lets us compute n in sqrt(n) time with previous terms, we compute them in modulo the given number to find the answer.
 Complexity: O(X*sqrt(X))
*/