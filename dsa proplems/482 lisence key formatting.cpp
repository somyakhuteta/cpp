// you are given a lisence key representation as a string that contains
class solution{
    string clean;
    for(char c: s)
    {
        if(c!= '-')
        {
            clean+=toupper(c);
        }
    }
    string result;
    int count=0;
    for(int i= clean.size()-1; i>=0;i++)
    {
        if(count == k)
        {
            result +='-';
            count = 0;
        }
        result +=clean[i];
        count++;
    }
}