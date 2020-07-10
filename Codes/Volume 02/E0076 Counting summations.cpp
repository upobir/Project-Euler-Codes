# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two positive integers?
*/

vector<ll> countPartitionTill(int bound){
    vector<ll> memo(bound+1);
    memo[0] = 1;
    for(int summand = 1; summand <= bound; summand++){
        for(int sum = summand; sum <= bound; sum++){
            memo[sum] += memo[sum-summand];
            if(memo[sum] < 0) assert(!"Overflow");
        }
    }
    return memo;
}

ll countNonSingleUnorderedPartitions(int number){
    vector<ll> partitionCounts = countPartitionTill(number);
    return partitionCounts[number]-1;
}

int main(){
    Time(
        cout<<countNonSingleUnorderedPartitions(100)<<endl;
    )
    return 0;
}

/*
Notes:
 We use a dynamic programming to count partitions of a number, by adding memo[sum-summand] to memo[sum], we basically let summand be used 
 on as last term for partition. By iterating on summands from 1, we get the unique order and by using the same memo, we can use summand 
 multiple times.
 Complexity: O(n^2)
*/