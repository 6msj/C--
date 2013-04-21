#include <iostream>
using namespace std;

#define SIZE 256
bool isPalindrome(char *str, int len);
char * findPalindromeStrings(char * s, int curr_len, int lengthString);

int main() {
    char stringToCheck[] = "FourscoreandsevenyearsagoourfaathersbroughtforthonthiscontainentanewnationconceivedinzLibertyanddedicatedtothepropositionthatallmenarecreatedequalNowweareengagedinagreahtcivilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
    int lengthString = strlen(stringToCheck);
    char * palindrome;
    char result[SIZE];
    for (int i=lengthString; i>1; i--) {
        palindrome = findPalindromeStrings(stringToCheck, i, lengthString);
        if(palindrome) {
            strncpy(result, palindrome, i);
            result[i] = '\0';
            cout << result << endl;
            break;
        }
    }
    return 0;
}

bool isPalindrome(char *str, int len) {
    int start = 0;
    int end = len - 1;
    for (int start = 0; start < end; start++, end--) {
        if(str[start] != str[end])
            return false;
    }
    return true;
}

char * findPalindromeStrings(char * s, int curr_len, int lengthString) {
    for(int i=0; i<lengthString; i++)
        if(isPalindrome(&s[i], curr_len))
            return &s[i];
    return NULL;
}
