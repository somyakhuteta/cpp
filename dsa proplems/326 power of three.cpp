#include <iostream>
using namespace std;

// bool isPowerOfThree(int n){
//     unordered_set<int> cube;
//     for(int i = 0; i< 30; i++){
//         pow(3, i);
//     }
//     if (cube.count(n)){
//             return true;
//         }
//     return false;
// };
// range outside of representable values so 
// No loops and no recursion

bool isPowerofThree(int n){
    return n >0 && 1162261467 % n ==0;
};