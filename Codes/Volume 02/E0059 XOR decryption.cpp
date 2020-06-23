# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Each character on a computer is assigned a unique code and the preferred standard is ASCII (American Standard Code for Information 
 Interchange). For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.
 
 A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret 
 key. The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; for example, 
 65 XOR 42 = 107, then 107 XOR 42 = 65.
 
 For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes. The user would 
 keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the 
 message.
 
 Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key. If the password is shorter 
 than the message, which is likely, the key is repeated cyclically throughout the message. The balance for this method is using a 
 sufficiently long password key for security, but short enough to be memorable.
 
 Your task has been made easy, as the encryption key consists of three lower case characters. Using p059_cipher.txt, a file containing the 
 encrypted ASCII codes, and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the 
 ASCII values in the original text.
*/

vector<string> tokenizeWithChar(string &text, char delim){
    vector<string> ret;
    stringstream ss(text);
    std::string parts;
    while(getline(ss, parts, delim))
        ret.push_back(parts);
    return ret;
}

vector<int> readNaiveNumbersCSV(string filePath){
    fstream file(filePath, fstream::in);
    string fullString;
    if(file.is_open()){
        if(file.good()){
            file>>fullString;
        }
        file.close();
    }
    vector<int> ret;
    vector<string> tokens = tokenizeWithChar(fullString, ',');
    for(string &t : tokens){
        ret.push_back(stoi(t));
    }
    return ret;
}

int findSubstituionKeyByFrequency(vector<char> cipherText, char commonChar, function<int(char, char)> keyGenerator){
    vector<int> frequency(256);
    for(char c : cipherText){
        frequency[c]++;
    }
    char cipherCommonChar = max_element(frequency.begin(), frequency.end()) - frequency.begin();
    int key = keyGenerator(commonChar, cipherCommonChar);
    return key;
}

pair<string, vector<int>> DecipherXorCipher(vector<int> cipherText, int keyLength){
    string key;
    for(int i = 0; i<keyLength; i++){
        vector<char> cipherPart;
        for(int pos = i; pos < cipherText.size(); pos += keyLength){
            cipherPart.push_back(cipherText[pos]);
        }
        char keyChar = findSubstituionKeyByFrequency(cipherPart, ' ', [](char p, char c){
            return c ^ p;
        });

        key.push_back(keyChar);
    }

    vector<int> plainText;
    for(int pos = 0; pos < cipherText.size(); pos++){
        plainText.push_back(cipherText[pos] ^ key[pos % keyLength]);
    }
    return make_pair(key, plainText);
}

int sumASCIIofXorCipher(string filePath, int keyLength, bool showPlainText){
    vector<int> cipherText = readNaiveNumbersCSV(filePath);
    vector<int> plainText;
    string key;

    tie(key, plainText) = DecipherXorCipher(cipherText, keyLength);

    if(showPlainText){
        cout<<"Key="<<key<<endl;
        cout<<"plaintext:"<<endl;
        for(char p : plainText)
            cout<<p;
        cout<<endl;
    }

    int ans = accumulate(plainText.begin(), plainText.end(), 0);
    return ans;
}

int main(){
    Time(
        cout<<sumASCIIofXorCipher("..\\..\\Data\\D0059 XOR decryption.txt", 3, false)<<endl;
    )
    return 0;
}

/*
Notes:
 We use frequency analysis to solve the problem, first we divide the text to charecter sets with same key and each one, we search for most
 common character, which we hope is ' ', and using that we get key letters.
 Complexity: O(|S|)
*/