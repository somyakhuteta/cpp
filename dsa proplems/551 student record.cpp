// student attendance record
//if A more than 2 days false
//

bool solution(string s){
    int absent = 0;
    int late = 0;
    for(char c: s){
        if(c == 'A'){
            absent++;
            late = 0;

        }
        else if(c == 'L'){
            late++;
        }
        else(c == 'P'){
            late = 0;
        }
        
        if(absent >=2 || late >){
            return false;
        }
    }
    return true;
}