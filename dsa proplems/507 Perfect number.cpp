// a perfect number is a positive integer that is eeequal to the sum of its positive divisors, excluding the number itself 

// brute force

bool checkForPerfectNumber(int num){
    int  sum = 0;
    for(int i = 1; i<num ; i++){
        if(num% i ==0){
            sum+=i;

        }
    }
    return sum == num;
}
//made the iteration only till num/2

bool checkForPerfectNumber(int num){
    int  sum = 0;
    for(int i = 1; i<=num/2 ; i++){
        if(num% i ==0){
            sum+=i;
        }
    }
    return sum == num;
}

//more optimized 

bool checkPerfect number(int num){
    if(num == 1){
        return false;
    }
    int sum = 1;
    for( int i =2; i * i<=num; i++){
        if(num% i ==0){
            sum ==i;
            if(i !=  num/i){
                sum+= num/i;
            }
        }
    }
    return sum == num;
}

//even more optimized only 5 numbers exist as perfect for leetcode 6, 28, 496, 8128, 33550336.




