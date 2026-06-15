// 


// word.length< 100

//method 1 direct counting 

bool detectcapitalUse(string word) {
    int capitals = 0;
    for(char c: word){
        if(ch>= 'A' && ch <= 'Z'){
            capitals++;
        }
    }
    if(capital == 0){
        return true;
    }
    if(capitals == word.size()){
        return true;
    }
    if(capitals == 1 && word[0] >= 'A' && word[0] <='Z'){
        return true;
    }
    return false;
}


// method 2 follow up pattern 

bool DetectCapital(string word){
    bool allcaps = word.size > 1 && isupper(word[0]) && isuppar(word[1]);
    for(int i =1; i< word.size(); i++){
        if(allCaps){
            if(!isupper(word[i])){
                return false;
            }
        }
        else{
            if(!islower(word[i])){
                return false;
            }
        }
    } 
    return true;

}