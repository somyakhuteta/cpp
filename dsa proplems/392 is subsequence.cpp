// for later;)
// current solution
int lengthOfLongestSubstring(string s){
    int ans = 0;
    for(int i =0; i, s.size(); i++){
        unordered_set<char> st;
        for(int j = i; j< s.size(); j++){
            if(st.count(s[j])){
                break;
            }
            st.insert(s[j]);
            ans = max(ans, j - i +1);
        }
    }
    return ans;

}

//optimized solution 
// s = "abcabcbb"
// we keep a window [left .. right] and then if any char repeats we move right until the repeated char disappears 

int lengthOfLongestSubstring{
    unordere_set<char> st;
    int left =0;
    int maxlen = 0;
    for(int right = 0; right< s.size(); right++){
        while(st.count(s[right])){
            st.erase(s[left]);
            left++;
        }
        st.insert(s{right});
        maxlen = max(maxlen, right -left + 1);
    }
    return maxlen;

}

//even more optimized solution
//hashset, hashmap

int lengthOfLongestSubstring{
    unordere_map<char,int> mp;
    int left =0;
    int maxlen = 0;
    for(int right = 0; right< s.size(); right++){
        if(mp.count(mp[right])){
            left = max(left, mp(s[right])+1);
        }
        mp[s[right]] = right;
        maxlen = max(maxlen, right -left + 1);  
    }
    return maxlen;
}