# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

 By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. 
 For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a 
 triangle word.

 Using words.txt, a 16K text file containing nearly two-thousand common English words, how many are triangle words?
*/

vector<string> tokenizeWithChar(string &text, char delim){
    vector<string> ret;
    stringstream ss(text);
    std::string parts;
    while(getline(ss, parts, delim))
        ret.push_back(parts);
    return ret;
}

//reads strings which have " around them and only one line of csv
vector<string> readNaiveStringCSV(string filePath){
    fstream file(filePath, fstream::in);
    string fullString;
    if(file.is_open()){
        if(file.good()){
            file>>fullString;
        }
        file.close();
    }
    vector<string> values = tokenizeWithChar(fullString, ',');
    for(string &name: values){
        name.erase(name.begin());
        name.erase(name.end()-1);
    }
    return values;
}

int scoreString(string name){
    int sum = 0;
    for(char c : name){
        sum += toupper(c) - 'A' + 1;
    }
    return sum;
}

ll invPolygonalNum(ll polygonalNum, ll sides){
    double C = sides - 2;
    double desc = C*C/2.0 - C + 1.0 + 2.0*C*polygonalNum;
    if(desc < 0) return -1;
    ll num = llround((C/2.0-1.0+sqrtl(desc))/C);
    if ((sides-2)*num*(num-1)/2 + num == polygonalNum)
        return num;
    return -1;
}

int countWordWithTriangleScore(string filePath){
    vector<string> names = readNaiveStringCSV(filePath);
    int count = 0;

    for(string &name : names){
        int score = scoreString(name);
        if(invPolygonalNum(score, 3) != -1)
            count++;
    }
    return count;
}

int main(){
    Time(
        cout<<countWordWithTriangleScore("..\\..\\Data\\D0042 Coded triangle numbers.txt");
    )
    return 0;
}

/*
Notes:
 Using the polygonal number formula which is a quadratic, we solve the equation to get inverse solution and then check to see if it's 
 correct. Otherwise everything else is same as 0022.
 Complexity: O(|s|)
*/