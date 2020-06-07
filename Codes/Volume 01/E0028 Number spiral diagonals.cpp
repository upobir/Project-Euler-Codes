# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

 21 22 23 24 25
 20  7  8  9 10
 19  6  1  2 11
 18  5  4  3 12
 17 16 15 14 13

 It can be verified that the sum of the numbers on the diagonals is 101.

 What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

ll sumTill(ll num){
    return num * (num+1)/2;
}

ll sumSquareTill(ll num){
    return num*(num+1)*(2*num+1)/6;
}

//sum of p(x) = ax^2+bx+c for x = 0 to num
ll sumQuadraticTill(ll num, ll a, ll b, ll c){
    ll sum = a * sumSquareTill(num) + b * sumTill(num) + c*(num+1);
    return sum;
}

ll sumDiagonalOfSpiral(ll side){
    ll sum = 0;
    ll index = side/2;
    //diagonal toward top-right is 4n^2+4n+1;
    sum += sumQuadraticTill(index, 4, 4, 1);
    //diagonal toward top-left is 4n^2+2n+1 
    sum += sumQuadraticTill(index, 4, 2, 1);
    //diagonal toward bottom-left is 4n^2+1
    sum += sumQuadraticTill(index, 4, 0, 1);
    //diagonal toward bottom-right is 4n^2-2n+1
    sum += sumQuadraticTill(index, 4, -2, 1);
    
    sum -= 3;

    return sum;
}

int main(){
    Time(
        cout<<sumDiagonalOfSpiral(1001)<<endl;
    )
    return 0;
}

/*
Notes:
 Each of the 4 diagonals form a sequence starting from 1, since the shapes are of square, the pattern of the sequence are just quaratic
 polynomials (node I assume starting at index 0). So we just find respective sum for terms 0 to index, for which we can sum the individual
 x's and x^2's and the constants.
 Complexity: O(1)
*/