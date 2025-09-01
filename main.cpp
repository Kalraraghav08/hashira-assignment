#include <bits/stdc++.h>
using namespace std;

// Function to convert string "val" of given base to decimal integer
long long convertToDecimal(string val, int base) {
    return stoll(val, nullptr, base);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line, json;
    while (getline(cin, line)) json += line;  // read full JSON file as string

    // Find "n" and "k"
    int n = 0, k = 0;
    {
        size_t posN = json.find("\"n\"");
        if (posN != string::npos) {
            size_t colon = json.find(":", posN);
            n = stoi(json.substr(colon + 1));
        }
        size_t posK = json.find("\"k\"");
        if (posK != string::npos) {
            size_t colon = json.find(":", posK);
            k = stoi(json.substr(colon + 1));
        }
    }

    vector<long long> roots;
    size_t pos = 0;
    while (true) {
        size_t basePos = json.find("\"base\"", pos);
        if (basePos == string::npos) break;
        size_t colon1 = json.find(":", basePos);
        size_t comma1 = json.find(",", colon1);
        int base = stoi(json.substr(colon1 + 1, comma1 - colon1 - 1));

        size_t valPos = json.find("\"value\"", comma1);
        size_t colon2 = json.find(":", valPos);
        size_t quote1 = json.find("\"", colon2);
        size_t quote2 = json.find("\"", quote1 + 1);
        string val = json.substr(quote1 + 1, quote2 - quote1 - 1);

        long long num = convertToDecimal(val, base);
        roots.push_back(num);

        pos = quote2;
    }

    // Polynomial expansion
    vector<long long> poly = {1}; // start with constant polynomial "1"
    for (long long root : roots) {
        vector<long long> newPoly(poly.size() + 1, 0);
        for (size_t i = 0; i < poly.size(); i++) {
            newPoly[i] += -root * poly[i];
            newPoly[i + 1] += poly[i];
        }
        poly = newPoly;
    }

    // Print coefficients
    for (size_t i = 0; i < poly.size(); i++) {
        cout << poly[i] << (i + 1 == poly.size() ? '\n' : ' ');
    }
    return 0;
}
