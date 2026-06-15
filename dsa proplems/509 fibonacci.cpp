// find the pattern for fibonnaci

class solution{
    if(n< 2){
        return n
    }
    return fib(n-1) + fib(n-2);
}

//optimized version
//store already calculated answers

class solutioon {
    vector<int> dp;
    int solve(int n){
        if(n<2){
            return n;
        }
        if(dp[n] != -1){
            return dp[n];
        }
        return dp[n] = solve(n-1) + solve(n - 2);
    }
    int fib (int n){
        dp.resize(n+1, -1);
        return solve(n);
    }
}



// more optimized through tabulation(bottom- UP dp)

class Solution{
    int fib(int n){

    }
}

//Space optimized DP

int fib(int n){
    if(n < 2){
        return n;

    }
    int prev2 = 0;
    int prev1 = 1;
    for(int i = 2; i<= n; i++){
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}