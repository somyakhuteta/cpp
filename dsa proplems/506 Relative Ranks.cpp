//given an array of size n where score[i] is the score of i th atlelete in a competetion

//score = [10,3,8,9,4]

vector<string> findReletiveRanks(vector<int>& score){
    int n= score.size();
    vector<string> ans(n);
    for(int i=0; i<n; i++){
        int rank = 1;
        for(int j = 0; j<n; j++){
            if(score[j] > score[i]){
                rank++;
            }
            if(rank == 1){
                ans[i]= "Gold Medal";
            }
            else if(rank == 2){
                ans[i] = "SilverMedal";
            }
            else if(rank == 3){
                ans[i] = "Bronze Medal";
            }
            else{
                ans[i] = to_string(rank);
            }
        }
        return ans;
    }
}

//optimized solution

vector<string> FindRelativeRanks(vector<int>& score){
    int n= score.size();
    vector<string> ans;
    unordered_map<string, int> mp;
    for(int i =0 ,i<n; i++){
        mp(score[i])=i;
    }
    vector<int> sorted = score;
    sort(sorted.begin(), sorted.end(), greater(<int>));

    for(int i =0 ,i<n; i++){
        int idx = mp(sorted[i]);
        if(i == 0){
            ans[idx] = "Gold Medal";
        }
        else if(i == 1){
            ans[idx] = "Silver Medal";
        }
        else if(i == 2){
            ans[idx] = "Bronze Medal";
        }
        else{
            ans[idx] = to_string(i+1):
        }
    }
    return ans;
}