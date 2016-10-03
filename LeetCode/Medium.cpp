//
//  Medium.cpp
//  LeetCode
//
//  Created by roneil on 9/20/16.
//  Copyright © 2016 Minghao Pu. All rights reserved.
//

#include "Header.h"
class Solution {
public:

    /*
     *
     *      151  Reverse Words in a String
     *
     */
    void reverseWords(string &s) {
        vector<string> stack;
        string newS = "";
        int i, j;
        for (i = 0, j = 0; i < s.length(); i++) {
            if (s[i] == ' ') {
                if (i != j) {
                    stack.push_back(s.substr(j, i - j));
                    j = i + 1;
                }else {
                    j++;
                }
            }
        }
        if (i != j) stack.push_back(s.substr(j, i - j));
        for (i = stack.size() - 1; i > -1 ; i--) {
            newS += stack[i] + ' ';
        }
        s = newS.substr(0, newS.length() - 1);
    }
    /*
     *
     *      3  Longest Substring Without Repeating Characters
     *
     */
    int lengthOfLongestSubstring(string s) {
        int map[128];
        memset(map, -1, sizeof(map));
        int res = 0;
        int cur, last;
        for (cur = 0, last = -1; cur < s.length(); cur++) {
            if (map[s[cur]] > last) last = map[s[cur]];
            map[s[cur]] = cur;
            res = max(res, cur - last);
        }
        if (cur != last) res = max(res, last - cur);
        return res;
    }
    
    /*
     *
     *      5   Longest Palindromic Substring
     *
     */
    string longestPalindrome(string s) {
        int l = s.length();
        int longestBegin = 0;
        int max = 1;
        bool table[1000][1000] = {false};
        for (int i = 0; i < l; i++) {
            table[i][i] = true;
        }
        for (int i = 0; i < l; i++) {
            if (s[i] == s[i+1]) {
                table[i][i+1] = true;
                longestBegin = i;
                max = 2;
            }
        }
        for (int len = 3; len <= l; len++) {
            for (int i = 0; i < l - len + 1; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && table[i+1][j-1]) {
                    table[i][j] = true;
                    longestBegin = i;
                    max = len;
                }
            }
        }
        return s.substr(longestBegin, max);
    }
    /*
     *
     *      15   3sum
     *
     */
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        
        int a;
        int b;
        int c;
        int len = nums.size();
        
        for (int i = 0; i < len - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            a = nums[i];
            
            int l = i + 1;
            int r = len - 1;
            while (l < r) {
                b = nums[l];
                c = nums[r];
                if (a + b + c == 0) {
                    vector<int> temp = {a, b, c};
                    result.push_back(temp);
                    while (nums[l]==nums[l+1]) l++;
                    while (nums[r]==nums[r-1]) r--;
                    l++;
                    r--;
                } else if (a + b + c < 0) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return result;
    }
    
    /*
     *
     *      148     Sort List
     *
     */
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* h2 = slow->next;
        slow->next = NULL;
        return mergeList(sortList(head),sortList(h2));
    }
    ListNode* mergeList(ListNode* h1, ListNode* h2) {
        ListNode* newHead = new ListNode(0);
        ListNode* n = newHead;
        while (h1 != NULL && h2 != NULL) {
            if (h1->val < h2->val) {
                n->next = h1;
                h1 = h1->next;
            } else {
                n->next = h2;
                h2 = h2->next;
            }
            n = n->next;
        }
        if (h1 != NULL) {
            n->next = h1;
        }
        if (h2 != NULL) {
            n->next = h2;
        }
        return newHead->next;
    }
    
    /*
     *
     *      53     Maximum Subarray
     *
     */
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0], sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            ans = max(ans, sum);
            sum = max(0, sum);
        }
        return ans;
    }
    /*
     *
     *      139. Word Break
     *
     */
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if (wordDict.size() == 0) return false;
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= s.length(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (dp[j]) {
                    string sub = s.substr(j, i - j);
                    if (wordDict.find(sub) != wordDict.end()) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[s.length()];
    }
    /*
     *
     *      11. Container With Most Water
     *
     */
    int maxArea(vector<int>& height) {
        int water = 0;
        int l = 0, r = height.size() - 1;
        while (l < r) {
            int h = min(height[r], height[l]);
            water = max(water, h * (r - l));
            while (height[l] <= h && l < r) l++;    // <= means l++ will stop if find a larger height than h
            while (height[r] <= h && l < r) r--;
        }
        return water;
    }
    /*
     *
     *      153. Find Minimum in Rotated Sorted Array
     *
     */
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size() - 1;
        while (start < end) {
            int mid = (end - start)/2;
            if (nums[mid] < nums[end]) end = mid;
            else start = mid + 1;
        }
        return nums[start];
    }
    /*
     *
     *      150. Evaluate Reverse Polish Notation
     *
     */
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        
        for (int i = 0; i < tokens.size(); i++) {
            string t = tokens[i];
            if (t == "+" || t == "-" || t == "*" || t == "/") {
                int op1 = s.top();
                s.pop();
                int op2 = s.top();
                s.pop();
                if(t=="+") s.push(op1 + op2);
                else if(t=="-") s.push(op2 - op1);
                else if(t=="*") s.push(op1 * op2);
                else if(t=="/") s.push(op2 / op1);
            } else {
                s.push(atoi(t.c_str()));
            }
        }
        return s.top();
    }
    /*
     *
     *      49. Group Anagrams
     *
     */
    string countSortString(string& s) {
        int c[26] = {0}, len = s.length();
        for (int i = 0; i < len; i++) {
            c[s[i] - 'a']++;
        }
        string sortedString = "";
        for (int i = 0; i < 26; i++) {
            for (int j = c[i]; j > 0; j--) {
                sortedString += char('a' + i);
            }
        }
        return sortedString;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> hash;
        for (int i = 0; i < strs.size(); i++) {
            string temp = countSortString(strs[i]);
            hash[temp].push_back(strs[i]);
        }
        for (auto it:hash) {
            result.push_back(it.second);
        }
        return result;
    }
    /*
     *
     *      122. Best Time to Buy and Sell Stock II
     *
     */
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len < 2) return 0;
        int max = 0;
        for (int i = 1; i < len; i++) {
            max += prices[i] > prices[i-1]?prices[i] - prices[i-1]:0;
        }
        return max;
    }
    /*
     *
     *      17. Letter Combinations of a Phone Number
     *
     */
    vector<string> letterCombinations(string digits) {
        vector<string> board = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result;
        if (digits.length() == 0) {
            return result;
        }
        result.push_back("");
        for (int i = 0; i < digits.length(); i++) {
            int num = digits[i] - '0';
            string add = board[num];
            if (add == "") {
                continue;
            }
            vector<string> tmp;
            for (int j = 0; j < result.size(); j++) {
                for (int k = 0; k < add.length(); k++) {
                    tmp.push_back(result[j] + add[k]);
                }
            }
            result.swap(tmp);
        }
        return result;
    }
    /*
     *
     *      152. Maximum Product Subarray
     *
     */
//    Fist we assume there is no zero in the A[]. The answer must be A[0] A[1] .... A[i] OR A[j] *A[j+1] A[n - 1]. (Try to prove yourself)
//    
//    Then when we have zero in the A[] (assum A[k] == 0). We could see A[0],A[1]...A[k - 1 ] As An Array and A[k + 1] A[k + 2]...A[n-1] is another.
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) return 0;
        int result = INT_MIN;
        for (int i = 0, frontproduct = 1, backproduct = 1; i < len; i++) {
            frontproduct *= nums[i];
            backproduct *= nums[len - i - 1];
            result = max(result, max(frontproduct, backproduct));
            if (frontproduct == 0) frontproduct = 1;
            if (backproduct == 0) backproduct = 1;
        }
        return result;
    }
    /*
     *
     *      179. Largest Number
     *
     */
    static bool compareString(int a, int b) {
        string str_a = to_string(a);
        string str_b = to_string(b);
        return str_a + str_b > str_b + str_b;                   // descending
    }
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), compareString);
        string res = "";
        for (int i = 0; i < nums.size(); i++) {
            res += nums[i];
        }
        return res[0] == '0'?"0":res;
    }
    unsigned long getNumberLength(int num) {
        return to_string(num).length();
    }
    /*
     *
     *      127. Word Ladder
     *
     */
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        queue<string> q;
        q.push(beginWord);
        wordList.erase(beginWord);
        int dist = 2;
        while (!q.empty()) {
            int l = q.size();
            for (int i = 0; i < l; i++) {
                beginWord = q.front();
                q.pop();
                for (int i = 0; i < beginWord.length(); i++) {
                    string tmp = beginWord;
                    for (int j = 0; j < 26; j++) {
                        tmp[i] = 'a' + j;
                        if (tmp == endWord) return dist;
                        if (tmp != beginWord && wordList.find(tmp) != wordList.end()) {
                            q.push(tmp);
                            wordList.erase(tmp);
                        }
                    }
                }
                
            }
            dist++;
        }
        return 0;
    }
    /*
     *
     *      12. Integer to Roman
     *
     */
    string intToRoman(int num) {
        string M[4] = {"", "M", "MM", "MMM"};
        string I[10] = {"","I","II","III","IV","V", "VI", "VII", "VIII", "IX"};
        string X[10] = {"","X","XX","XXX","XL","L", "LX", "LXX", "LXXX", "XC"};
        string C[10] = {"","C","CC","CCC","DC","D", "DC", "DCC", "DCCC", "CM"};
        return  M[num/1000] + C[(num%1000)/100] + X[(num%100)/10] + I[(num%10)];
    }
    /*
     *
     *      79. Word Search
     *
     */
    static bool isFound(vector<vector<char>>& board, string word,int start, int x, int y, int m, int n) {
        if (start == word.length()) {
            return true;
        }
        if (x < 0 || y < 0 || x >= m || y >= n) {
            return false;
        }
        
        char t = board[x][y];
        bool res = false;
        if (t != word[start] || t == '*') return false;
        
        board[x][y] = '*';
        if (!res) res = isFound(board, word, start+1, x-1, y, m, n);
        if (!res) res = isFound(board, word, start+1, x, y-1, m, n);
        if (!res) res = isFound(board, word, start+1, x+1, y, m, n);
        if (!res) res = isFound(board, word, start+1, x, y+1, m, n);
        
        board[x][y] = t;
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isFound(board, word.c_str(), 0, i, j, m, n)) return true;
            }
        }
        return false;
        
    }
};