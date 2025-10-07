class Solution {
public:
    string shortestCommonSupersequence(string &s, string &ss) {
    int n = s.size(), m = ss.size();

    // Step 1: Build LCS dp table
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == ss[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Step 2: Extract LCS string
    string ans = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i - 1] == ss[j - 1]) {
            ans.push_back(s[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) i--;
        else j--;
    }
    reverse(ans.begin(), ans.end());
    int nn = ans.size();

    // Step 3: Mark LCS characters with '*'
    int l = 0;
    for (int k = 0; k < n && l < nn; k++) {
        if (s[k] == ans[l]) {
            s[k] = '*';
            l++;
        }
    }
    l = 0;
    for (int k = 0; k < m && l < nn; k++) {
        if (ss[k] == ans[l]) {
            ss[k] = '*';
            l++;
        }
    }

    // Step 4: Merge to form shortest common supersequence
    string res = "";
    int si = 0, ssi = 0, idx = 0;
    while (si < n || ssi < m) {
        if (si < n && ssi < m && s[si] == '*' && ss[ssi] == '*') {
            // Same LCS character → add once
            res += ans[idx++];
            si++; ssi++;
        } 
        else if (si < n && s[si] != '*'
                 && (ssi >= m || s[si] != ss[ssi])) {
            res += s[si++];
        } 
        else if (ssi < m && ss[ssi] != '*'
                 && (si >= n || s[si] != ss[ssi])) {
            res += ss[ssi++];
        } 
        // else if (si < n && ssi < m && s[si] == ss[ssi]) {
        //     // Coincidental equal but not marked as LCS — add once
        //     res += s[si];
        //     si++; ssi++;
        // } 
        // else {
        //     // Exhausted one string
        //     if (si < n) res += s[si++];
        //     if (ssi < m) res += ss[ssi++];
        // }
    }

    return res;
}

};
