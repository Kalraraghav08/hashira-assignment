#include <bits/stdc++.h>
using namespace std;


long long baseToDecimal(string value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = tolower(c) - 'a' + 10; // for hex, base>10
        else continue;
        result = result * base + digit;
    }
    return result;
}


vector<long long> multiplyPoly(vector<long long> poly, long long root) {
    vector<long long> newPoly(poly.size() + 1, 0);
    for (size_t i = 0; i < poly.size(); i++) {
        newPoly[i] += poly[i];
        newPoly[i + 1] -= poly[i] * root;
    }
    return newPoly;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line, json;
    while (getline(cin, line)) {
        json += line;
    }

    // Extract n and k
    int n, k;
    {
        size_t posN = json.find("\"n\"");
        size_t colonN = json.find(":", posN);
        n = stoi(json.substr(colonN + 1));

        size_t posK = json.find("\"k\"");
        size_t colonK = json.find(":", posK);
        k = stoi(json.substr(colonK + 1));
    }

    // Extract roots
    vector<long long> roots;
    for (int i = 1; i <= n; i++) {
        string key = "\"" + to_string(i) + "\"";
        size_t pos = json.find(key);
        if (pos == string::npos) continue;

        // Base
        size_t posBase = json.find("\"base\"", pos);
        size_t colonBase = json.find(":", posBase);
        int base = stoi(json.substr(colonBase + 1));

        // Value
        size_t posValue = json.find("\"value\"", pos);
        size_t colonValue = json.find(":", posValue);
        size_t quote1 = json.find("\"", colonValue + 1);
        size_t quote2 = json.find("\"", quote1 + 1);
        string value = json.substr(quote1 + 1, quote2 - quote1 - 1);

        long long decimalRoot = baseToDecimal(value, base);
        roots.push_back(decimalRoot);
    }

    // Degree of polynomial = k-1
    int degree = k - 1;

    // Use first (k-1) roots
    vector<long long> poly = {1}; // start with P(x) = 1
    for (int i = 0; i < degree; i++) {
        poly = multiplyPoly(poly, roots[i]);
    }

    // Print coefficients
    // Example: x^2 - 11x + 28 → 1 -11 28
    for (size_t i = 0; i < poly.size(); i++) {
        cout << poly[i];
        if (i + 1 < poly.size()) cout << " ";
    }
    cout << "\n";

    return 0;
}
