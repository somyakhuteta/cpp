#include <iostream>

class solution{
    int count =0;
    while(x>0 || y>0){
        if((x&1) != (y&1)){
            count++;
        }
        x>>=1;
        y>>=1;
    }
    return count;
};

class optimizedSolution{
    int n = x^y;
    int count =0;
    while(n){
        count += n&1;
        n>>=;
    }
    return count;
}

class mostOptimized{
    int n = x^y;
    int count = 0;
    while(n){
        count++;
        n = n & (n-1);
    }
}