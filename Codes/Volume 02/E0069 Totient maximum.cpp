# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of numbers less than n which are 
 relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
 
 n	Relatively Prime	φ(n)	n/φ(n)
 2	1	                1     	2
 3	1,2	                2	    1.5
 4	1,3	                2   	2
 5	1,2,3,4	            4   	1.25
 6	1,5	                2   	3
 7	1,2,3,4,5,6	        6   	1.1666...
 8	1,3,5,7	            4   	2
 9	1,2,4,5,7,8	        6   	1.5
 10	1,3,7,9	            4   	2.5
 
 It can be seen that n=6 produces a maximum n/φ(n) for n ≤ 10.
 
 Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.
*/

vector<int> phiSieveTill(int maxNum){
    vector<int> phi(maxNum+1);
    iota(phi.begin(), phi.end(), 0);

    for(int p = 2; p <= maxNum; p+=(p>2)+1){
        if(phi[p] != p) continue;

        for(int multiple = p; multiple <= maxNum; multiple += p)
            phi[multiple] -= phi[multiple]/p;
    }
    return phi;
}

int maxNbyPhiRationTill(int maxBound){
    int ans = 0;
    double best = 0;
    vector<int> phi = phiSieveTill(maxBound);
    for(int num = 1; num <= maxBound; num++){
        double candidate = double(num)/double(phi[num]);
        if(candidate > best){
            best = candidate;
            ans = num;
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<maxNbyPhiRationTill(1000000)<<endl;
    )
    return 0;
}

/*
Note:
 Just sieved to find the phi values and then checked the answers.
 Complexity: O(n * log log n)
*/