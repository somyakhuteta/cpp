// given an integer num, return a string of its base

class solution{
    if(num==0){
        return "0";
    }
    bool negative = num < 0;
    num abs(num);
    string result;
    while(num){
        result +=num%7 + '0';
        num/=7;
    }
    if(negative){
        result += '-'
    }
    reverse(result.begin(), result.end());
    return result;
}
// teaches the most important trick