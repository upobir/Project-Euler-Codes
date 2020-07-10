# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle triangle in exactly one way, 
 but there are many more examples.
 
 12 cm: (3,4,5)
 24 cm: (6,8,10)
 30 cm: (5,12,13)
 36 cm: (9,12,15)
 40 cm: (8,15,17)
 48 cm: (12,16,20)
 
 In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle, and other lengths allow more 
 than one solution to be found; for example, using 120 cm it is possible to form exactly three different integer sided right angle 
 triangles.
 
 120 cm: (30,40,50), (20,48,52), (24,45,51)
 
 Given that L is the length of the wire, for how many values of L ≤ 1,500,000 can exactly one integer sided right angle triangle be formed?
*/

vector<int> pyTripleSumCountSieveTill(int bound){
    vector<int> primitiveTripleCount(bound+1), pyTripleCount(bound+1);
    for(int M = 1, bound2 = bound/2; M < bound2; M++, bound2 = bound/2/M){
        for(int MplusN = M+1+(M&1); MplusN <= bound2 && MplusN < M+M; MplusN+=2){
            if(__gcd(M, MplusN) != 1) continue;
            int num = M*MplusN;
            primitiveTripleCount[num]++;
        }
    }

    for(int divi = 1; divi <= bound; divi++){
        if(primitiveTripleCount[divi] == 0) continue;
        for(int num = divi*2; num <= bound; num += divi+divi){
            pyTripleCount[num]+=primitiveTripleCount[divi];
        }
    }
    return pyTripleCount;
}

int countSinglePythagoreanTripleWithSumTill(int bound){
    vector<int> tripleCount = pyTripleSumCountSieveTill(bound);
    int ans = 0;
    for(int num = 1; num <= bound; num++){
        if(tripleCount[num] == 1) ans++;
    }
    return ans;
}

int main(){
    Time(
        cout<<countSinglePythagoreanTripleWithSumTill(1'500'000)<<endl;
    )
    return 0;
}

/*
Notes:
 We know that sum = 2*m*(m+n)*g represents a triple using (m, n) iff m+n is odd, m > n and gcd(m,n) = 1. So using that we can find a sieve
 like algorithm first we count up all possible m*(m+n) by fixing m and iterating on m+n (which will only go upto bound/2/m), the gcd check 
 is a little costly. then afterwards we propagate these counts to their muliples (multiplying 2*g) this way for each sum we know the 
 exact count of solution.
 Complexity: O(n * log^2 n)
*/