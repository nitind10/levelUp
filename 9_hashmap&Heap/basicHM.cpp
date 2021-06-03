#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

void test1()
{
    //hasmap stores data in a random/unordered manner in both cpp and java, only unique keys are there

    unordered_map<string, int> map;
    map["USA"] = 1000;
    map["IND"] = 10000;
    map["NEP"] = 90;
    map["usa"] = 9000;

    //**************************************
    //since "BAN" was not present in HM, now this statement will add this key to the map with defalut value of zero
    cout << map["BAN"] << endl; //ans will be 0
    //**************************************

    //will only print value of "usa" if its present in the map
    if (map.find("usa") != map.end())
        cout << map["usa"] << endl;

    for (pair<string, int> p : map)
        cout << p.first << " -> " << p.second << endl;
}

// Frequency map of given string
void test2(string str)
{
    unordered_map<char, int> map;
    for (char ch : str)
    {
        //if a char is initially not present in map, then map[ch] will add it with value 0 and the ++ will make it 1, if present -> val+1
        map[ch]++;
    }
}

// Index of all character
void test3(string str)
{
    unordered_map<char, vector<int>> map;
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        //if a char is initially not present in map, then map[ch] will put it with an empty vector eg: 'a' -> [], then push_back will work
        map[ch].push_back(i);
    }

    for (auto &key : map)
    {
        char k = key.first;
        vector<int> val = key.second;
        cout << k << " -> ";
        for (int ele : val)
            cout << ele << ", ";
        cout << endl;
    }
}

int main()
{
    test3("abcaksjbabaabadabab");
    return 0;
}