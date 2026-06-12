public static void main{
    int left =0;
    int right = n;
    int solution = 0;
    while(left >right){
        int mid = left + (right - left)/ 2;
        if((mid * (mid+1)/2) == n ){
            return mid;
        }
        else if((mid * (mid+1)/2) < n){
            solution = mid;
            left = mid + 1;
        }
        else if{
            right = mid -1;
        }
    }
    return solution;
}