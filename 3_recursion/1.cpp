// keypad extention, 10 = "+-*" , 11 = "/%^"
static String keypad[] = {
    ".;",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tu",
    "vwx",
    "yz",
    "+-*",
    "/%^"
};
void printKPC(string qsf, string asf) {
    if (qsf.length() == 0) {
        cout << asf;
        return;
    }
    char c = qsf[0];
    string ros = qsf.substr(1);
    int key = c - '0';
    string word = keypad[key];

    for (int i = 0; i < word.length(); ++i) {
        char inhand = word[i];
        printKPC(ros, asf + inhand);
    }
    
    if(qsf.length() >= 2){
        if( (qsf[0] - '0') * 10 + (qsf[1] - '0') == 10 || (qsf[0] - '0') * 10 + (qsf[1] - '0') == 11 ){
            string word2 = keypad[(qsf[0] - '0') * 10 + (qsf[1] - '0')];

            for (int i = 0; i < word2.length(); ++i) {
                char inhand = word2[i];
                printKPC(qsf.substr(2), asf + inhand);
            } 
        }
    }

}

//unique permutations in string
int printPermutationUnique(string str, string ans) {
    if (str.length() == 0) {
        cout << ans;
        return 1;
    }
    
    int count = 0;
    bool vis[26];
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (!vis[ch - 'a']) {
            vis[ch - 'a'] = true;
            String ros = str.substr(0, i) + str.substr(i + 1); // ros : rest of the string
            count += printPermutationUnique(ros, ans + ch);
        }
    }
    return count;
}



