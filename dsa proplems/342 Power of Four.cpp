#include <iostream>

class solution(int n){
    return n>0 && (n & (n -1))==0 && (n & 0x55555555);
    //n > 0 && (n & (n - 1)) == 0
// 0x55555555 is 101010101010101010101010101return  
}