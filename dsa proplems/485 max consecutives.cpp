//my sollution

class solution{
    int maxlen = 0;
    int ans = 0;
    for(int num: nums){
        if(num!= 1){
            maxlen =max(maxlen, ans);
            ans =0;
        }
        else{
            ans++;
        }
    }
    maxlen = max(maxlen, ans);
    return maxlen;
}