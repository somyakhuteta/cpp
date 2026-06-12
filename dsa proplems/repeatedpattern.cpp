#include <iostream>

class solution{
    int n = s.size();
    for(int len=1; len<=n/2; len++){
        if(n % len !=0){
            continue;
        }
        string sub = s.substr(0, len);
        string temp ="";
        int times = n/len;
        for(int i = 0; i <times; i++ ){
            temp+=sub;
        }
        if(temp == s){
            return true;
        }
    }
    return false;