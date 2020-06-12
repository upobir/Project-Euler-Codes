# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Using names.txt, a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out 
 the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

 For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the 
 list. So, COLIN would obtain a score of 938 × 53 = 49714.

 What is the total of all the name scores in the file?
*/

vector<string> tokenizeWithChar(string &text, char delim){
    vector<string> ret;
    stringstream ss(text);
    std::string parts;
    while(getline(ss, parts, delim))
        ret.push_back(parts);
    return ret;
}

int scoreString(string name){
    int sum = 0;
    for(char c : name){
        sum += toupper(c) - 'A' + 1;
    }
    return sum;
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

int scoreFileNames(string filePath){
    int score = 0;
    vector<string> names = readNaiveStringCSV(filePath);

    sort(names.begin(), names.end());
    
    for(int pos = 0; pos < names.size(); pos++){
        score += (pos+1) * scoreString(names[pos]);
    }

    return score;
}

int main(){
    Time(
        cout<<scoreFileNames("..\\..\\Data\\D0022 Names scores.txt")<<endl;
    )
    return 0;
}

/*
Notes:
 just basic file i/o, after tokenizing and taking away ", we just sort using C++ builtin sort and then just add the scores.
 Complexity: O(|s| * log n)
*/