//cryptoArithmetic
string s1 = "send";
string s2 = "more";
string s3 = "money";
vector<int> mapping;
vector<bool> isNumberTaken;

int stringToNumber(string str)
{
    int res = 0;
    for (int i = 0; i < str.length(); i++)
    {
        res = res * 10 + mapping[str[i] - 'a'];
    }

    return res;
}
int cryptoArith(string &str, int idx)
{
    if (idx == str.length())
    {
        int num1 = stringToNumber(s1);
        int num2 = stringToNumber(s2);
        int num3 = stringToNumber(s3);
        // if (num1 + num2 == num3 && mapping[s1[0] - 'a'] != 0 && mapping[s2[0] - 'a'] != 0 && mapping[s3[0] - 'a'] != 0)
        if (num1 + num2 == num3)
        {

            cout << to_string(num1) << endl
                 << "+" + to_string(num2) << endl
                 << "----" << endl
                 << num3 << endl
                 << endl;
            return 1;
        }

        return 0;
    }

    char ch = str[idx];
    int count = 0;
    for (int num = 0; num <= 9; num++)
    {
        if ((ch == s1[0] || ch == s2[0] || ch == s3[0]) && num == 0)
            continue;

        if (!isNumberTaken[num])
        {
            isNumberTaken[num] = true;
            mapping[ch - 'a'] = num;
            count += cryptoArith(str, idx + 1);
            isNumberTaken[num] = false;
            mapping[ch - 'a'] = -1;
        }
    }
    return count;
}
void input()
{
    mapping.resize(26, -1);
    isNumberTaken.resize(10, 0);

    string str = s1 + s2 + s3;
    int uniqueChar = 0;
    for (int i = 0; i < str.length(); i++)
    {
        uniqueChar |= (1 << (str[i] - 'a'));
    }

    str = "";
    for (int i = 0; i < 26; i++)
    {
        int mask = (1 << i);
        if ((uniqueChar & mask) != 0)
            str += (char)(i + 'a');
    }

    // cout << str << endl;
    cout << cryptoArith(str, 0) << endl;
}