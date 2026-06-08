#include <iostream>
using namespace std;

vector<int> countBits(int n){
    vector<int> ans(n+1, 0);
    for(int i =0; i<=n; i++){
        ans[i] = ans[i>>1] + (i & 1); 
    }
    return ans;
}


// count(i) = count(i >> 1) + (i & 1)
