#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

string processCaesar(const string& text, int key, bool encrypt = true) {
    string result = "";
    int shiftKey = encrypt ? key : -key;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shifted = ((c - base + shiftKey) % 26 + 26) % 26;
            result += (char)(base + shifted);
        } else {
            result += c; 
        }
    }
    return result;
}

string toLowerStr(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

int main() {
    cout << "--- CHUONG TRINH 2: BRUTE-FORCE CAESAR ---\n";
    
    string ciphertext;
    cout << "Nhap van ban ma hoa (Ciphertext): ";
    getline(cin, ciphertext);
    
    vector<string> commonWords = {"the", "and", "is", "in", "to", "of", "a", "with", "for", "on"};
    int bestScore = 0;
    string bestPlaintext = "";
    int bestKey = 0;

    for (int key = 1; key < 26; ++key) {
        string plaintext = processCaesar(ciphertext, key, false);
        
        string tempText = plaintext;
        for (char &c : tempText) {
            if (ispunct(c)) c = ' ';
        }

        int score = 0;
        stringstream ss(tempText);
        string word;
        while (ss >> word) {
            word = toLowerStr(word);
            if (find(commonWords.begin(), commonWords.end(), word) != commonWords.end()) {
                score++;
            }
        }

        if (score > bestScore) {
            bestScore = score;
            bestPlaintext = plaintext;
            bestKey = key;
        }
    }

    cout << "Khoa K tim duoc: " << bestKey << endl;
    cout << "Van ban goc:\n" << bestPlaintext << endl;

    return 0;
}