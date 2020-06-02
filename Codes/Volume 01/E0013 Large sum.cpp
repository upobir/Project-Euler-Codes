# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
 <DATA>
*/

class BigInteger{
    const static int BASE = 1000*1000*1000;
    const static int BASELENGTH = 9;
    vector<int> parts;

    int get(int i){
        return (i < parts.size())? parts[i] : 0;
    }

public:
    BigInteger(){}

    BigInteger(ll number){
        while(number){
            parts.push_back(number % BASE);
            number /= BASE;
        }
    }

    BigInteger(string number){
        for(int done = int(number.size()); done > 0; done -= 9){
            int startPos = (done >= BASELENGTH)? done - BASELENGTH : 0;
            int part = stoi(number.substr(startPos, BASELENGTH));
            parts.push_back(part);
        }
    }

    string toString(){
        stringstream number;
        number << (parts.empty()? 0 : parts.back());
        for(int i = int(parts.size()) - 2; i>=0; i--){
            number<<setfill('0')<<setw(BASELENGTH)<<parts[i];
        }
        return number.str();
    }

    BigInteger operator+(BigInteger other){
        BigInteger res;
        int carry = 0;
        for(int i = 0; i<parts.size() || i<other.parts.size() || carry != 0; i++){
            res.parts.push_back(carry + get(i) + other.get(i));
            carry = (res.parts.back() >= BASE);
            if(carry != 0)
                res.parts.back() -= BASE;
        }
        return res;
    }
};

string fileSumFirstDigits(string filePath, int digits){
    fstream file(filePath, fstream::in);
    vector<BigInteger> list;
    if(file.is_open()){
        while(file.good()){
            string num;
            file>>num;
            list.emplace_back(num);
        }
        file.close();
    }

    BigInteger sum(0);
    for(BigInteger &num : list)
        sum = (sum + num);

    return sum.toString().substr(0, digits);
}

int main(){
    Time(
        cout<<fileSumFirstDigits("..\\..\\Data\\D0013 Large sum.txt", 10)<<endl;
    )
    return 0;
}

/*
Notes:
 We use file cause the data's too big, and then read the files and use custom Biginteger for summing
 Complexity: O(|s|)
*/