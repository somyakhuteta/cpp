#include <iostream>
using namespace std;

bool isPerfectSquare(long long num) {
    if (num < 0) return false;
    long long left = 0;
    long long right = num;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long square = mid * mid;
        if (square == num) return true;
        if (square < num) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

int main() {
    long long n;
    while (cin >> n) {
        cout << (isPerfectSquare(n) ? "true" : "false") << endl;
    }
    return 0;
}

