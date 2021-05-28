#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// N : Next, G = greater, S : Smaller, L : Left, R : Right ===================================================================
void NGOR(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, n); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NGOL(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, -1); //Java :  Arrays.fill(ans,-1);

    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NSOR(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, n); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NSOL(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, -1); //Java :  Arrays.fill(ans,-1);

    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

//503 ======================================================================================
vector<int> nextGreaterElements(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < 2 * n; i++)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i % n])
        {
            ans[st.top()] = arr[i % n];
            st.pop();
        }
        if (i < n)
            st.push(i);
    }
    return ans;
}

// https://practice.geeksforgeeks.org/problems/stock-span-problem-1587115621/1 ===================================================
vector<int> NGOL(int arr[], int n)
{
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }

        st.push(i);
    }
    return ans;
}

vector<int> calculateSpan(int arr[], int n)
{
    vector<int> ans = NGOL(arr, n);
    for (int i = 0; i < n; i++)
        ans[i] = i - ans[i];
    return ans;
}

//901 =============================================================================================
class StockSpanner {
    public : 
        stack<vector<int>> st;
        int day;

        StockSpanner() {
            this -> day = 0;
            st.push({ -1, -1 }); // {day,Data}
        }

        int next(int price) {
            while (st.top()[0] != -1 && st.top()[1] <= price)
                st.pop();

            int span = day - st.top()[0];
            st.push({ day++, price });
            return span;
        }
};


//20 ================================================================
 bool isValid(string s) {
        stack<char> st;
        
        for(int i = 0; i < s.length(); ++i){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{')
                st.push(s[i]);
            else{
                if(st.size() == 0)
                    return false;
                
                if((s[i] == ')' && st.top() != '(') || (s[i] == ']' && st.top() != '[') || (s[i] == '}' && st.top() != '{'))
                    return false;
                else
                    st.pop();
            }
        }
        if(st.size() != 0)
            return false;
        return true;
    }

//946 =========================================================================
 bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> st;
        int n = pushed.size();
        
        int i = 0;
        
        for(int ele : pushed){
           st.push(ele);
           while(st.size() != 0 && st.top() == popped[i]){
               st.pop();
               i++;
           }
        }
        return i == n;
    }

//1249 ================================================================================
    string minRemoveToMakeValid(string s)
{
    vector<int> st;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        char ch = s[i];
        if (ch == '(')
            st.push_back(i);
        else if (ch == ')')
        {
            if (st.size() != 0 && s[st.back()] == '(')
                st.pop_back();
            else
                st.push_back(i);
        }
    }

    string ans = "";
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (idx < st.size() && st[idx] == i)
        {
            idx++;
            continue;
        }

        ans.push_back(s[i]);
    }

    return ans;
}

//32 =========================================================================
int longestValidParentheses(string s) {
        int n = s.length();
        stack<int> st;
        st.push(-1);
        int len = 0;
        for (int i = 0; i < n; i++) {
            if (st.top() != -1 && s[st.top()] == '(' && s[i] == ')') {
                st.pop();
                len = max(len, i - st.top());
            } else {
                st.push(i);
            }
        }

        return len;
    }