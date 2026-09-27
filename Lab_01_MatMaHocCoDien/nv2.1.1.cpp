#include <iostream>
#include <string>
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

int main() {
    cout << "--- CHUONG TRINH 1: MA HOA / GIAI MA CAESAR ---\n";
    cout << "Ban muon ma hoa (e) hay giai ma (d)? [e/d]: ";
    char action;
    cin >> action;
    cin.ignore(); 

    cout << "Nhap van ban: ";
    string text;
    getline(cin, text);

    cout << "Nhap khoa K (so nguyen): ";
    int key;
    cin >> key;

    bool encrypt = (action == 'e');
    cout << "Ket qua: " << processCaesar(text, key, encrypt) << "\n";

    return 0;
}