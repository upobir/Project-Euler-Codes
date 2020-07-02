# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line adding to nine.
 
     <image>
 
 Working clockwise, and starting from the group of three with the numerically lowest external node (4,3,2 in this example), each solution 
 can be described uniquely. For example, the above solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.
 
 It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are eight solutions in total.
 
 Total	    Solution Set
   9	4,2,3; 5,3,1; 6,1,2
   9	4,3,2; 6,2,1; 5,1,3
   10	2,3,5; 4,5,1; 6,1,3
   10	2,5,3; 6,3,1; 4,1,5
   11	1,4,6; 3,6,2; 5,2,4
   11	1,6,4; 5,4,2; 3,2,6
   12	1,5,6; 2,6,4; 3,4,5
   12	1,6,5; 3,5,4; 2,4,6
 By concatenating each group it is possible to form 9-digit strings; the maximum string for a 3-gon ring is 432621513.
 
 Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit strings. What is the maximum 16-digit 
 string for a "magic" 5-gon ring?
 
     <image>
     
*/

template<class bidirIterator, class T>
bool next_combination(bidirIterator first, bidirIterator last, T bound){
    bidirIterator it = last;
    while(it != first){
        it--;
        if(*it < bound){
            T value = *it;
            while(it != last){
                value++;
                *it = value;
                it++;
            }
            return true;
        }
        bound--;
    }
    return false;
}

string maxMagicRingStringOfLen(int ringSides, int stringLength){
    map<vector<int>, map<vector<int>, vector<int>>> externalSignature, internalSignature;
    int bound = 2*ringSides;
    vector<int> combination(ringSides);
    iota(combination.begin(), combination.end(), 1);

    //creating signatures
    do{
        vector<int> permutation(combination);
        do{
            vector<int> signature(ringSides-1);
            for(int i = 0; i<ringSides-1; i++){
                int j = (i+1)%ringSides;
                signature[i] = permutation[i] - permutation[j];
            }
            externalSignature[combination][signature] = permutation;

            for(int i = 0; i<ringSides-1; i++){
                int j = (i+2)%ringSides;
                signature[i] = permutation[j] - permutation[i];
            }
            internalSignature[combination][signature] = permutation;

        }while(next_permutation(permutation.begin(), permutation.end()));
    }while(next_combination(combination.begin(), combination.end(), bound));

    //checking for each signature
    iota(combination.begin(), combination.end(), 1);
    string ans;
    do{
        vector<int> complement;
        for(int c = 1, j = 0; c<=bound; c++){
            while(j < ringSides && combination[j] < c) j++;
            if(combination[j] != c) complement.push_back(c);
        }

        for(auto &p : externalSignature[combination]){
            if(min_element(p.second.begin(), p.second.end()) != p.second.begin()) continue;

            if(internalSignature[complement].count(p.first) == 0) continue;
            auto &exterior = p.second;
            auto &interior = internalSignature[complement][p.first];

            string str;
            for(int i = 0; i<ringSides; i++){
                str.insert(str.size(), to_string(exterior[i]));
                str.insert(str.size(), to_string(interior[i]));
                str.insert(str.size(), to_string(interior[(i+1)%ringSides]));
            }
            if(str.size() == stringLength){
                if(ans.empty()) ans = str;
                else if(ans < str) ans = str;
            }
        }
    }while(next_combination(combination.begin(), combination.end(), bound));

    return ans;
}

int main(){
    Time(
        cout<<maxMagicRingStringOfLen(5, 16)<<endl;
    )
    return 0;
}

/*
Notes:
 Due to the structure of the ring, if e[] are the exterior and i[] are the interior then you will see that e[0]+i[0]+i[1] = e[1]+i[1]+i[2] 
 implies e[0] - e[1] = i[2] - i[0], this basically means for each permutation of numbers we can define the external signature as adjacent 
 differences and interal signature as 2-adjacent differences (with negative sign). And when complement partitions have same sign they can 
 form a magic ring, using that, we find signature for all permutation and keep them in maps, later for each signature we see if partition
 complement has same signature, we also make sure the exterior starts with the lowest element.
 Complexity: O((2n)!/n! * n * log n)
*/