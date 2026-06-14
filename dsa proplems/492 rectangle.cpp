// Conditions
//1) L * W = area 
//l>=w
//L-W should be min
//If we try brute force complexity becomes O(area)



class solution{
    vector<int> constructrectangle(int area)
    {
        int w = sqrt(area);
        while(area%w !=0){
            w--;
        };
        return {area / w , w};
    }
}


// First look for underroot of n then mve outwards