#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Hàm tìm Uoc chung lon nhat (GCD)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Hàm tìm nghich dao modulo (Modular Multiplicative Inverse)
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Hàm ma hoa Affine
string encryptAffine(const string& text, int a, int b) {
    string cipher = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int p = c - base;
            int C = (a * p + b) % 26;
            cipher += (char)(C + base);
        } else {
            cipher += c; 
        }
    }
    return cipher;
}

// Hàm giai ma Affine
string decryptAffine(const string& text, int a, int b) {
    string plain = "";
    int a_inv = modInverse(a, 26);
    
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int C = c - base;
            int p = (a_inv * (C - b)) % 26;
            if (p < 0) p += 26; 
            
            plain += (char)(p + base);
        } else {
            plain += c;
        }
    }
    return plain;
}

int main() {
    cout << "=== CHUONG TRINH MA HOA / GIAI MA AFFINE CIPHER ===\n";
    cout << "Chon che do (e: Ma hoa | d: Giai ma): ";
    char mode;
    cin >> mode;
    
    int a, b;
    while (true) {
        cout << "Nhap khoa a (nguyen to cung nhau voi 26): ";
        cin >> a;
        if (gcd(a, 26) == 1) break;
        cout << "Loi: Khoa a khong hop le. Vui long nhap lai!\n";
    }
    
    cout << "Nhap khoa b: ";
    cin >> b;
    cin.ignore(); 
    
    cout << "Nhap van ban: ";
    string text;
    getline(cin, text);
    
    if (mode == 'e' || mode == 'E') {
        cout << "\n=> Van ban ma hoa (Ciphertext): \n" << encryptAffine(text, a, b) << "\n";
    } else if (mode == 'd' || mode == 'D') {
        cout << "\n=> Van ban giai ma (Plaintext): \n" << decryptAffine(text, a, b) << "\n";
    } else {
        cout << "Che do khong hop le!\n";
    }
    
    return 0;
}