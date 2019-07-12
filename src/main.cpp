#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;


vector<string> utf8_split(const string &str){
    vector<string> split;
    int len = str.length();
    int left = 0;
    int right = 1;

    for (int i = 0; i < len; i++){
        if (right >= len || ((str[right] & 0xc0) != 0x80)){
            string s = str.substr(left, right - left);
            split.push_back(s);
            // printf("%s %d %d\n", s.c_str(), left, right);
            left = right;
        }
        right ++;
    }
    return split;
}


// 最长公共子序列（不连续）
int lcs_length_(const string &str1, const string &str2) {
    if (str1 == "" || str2 == "")
        return 0;
    vector<string> s1 = utf8_split(str1);
    vector<string> s2 = utf8_split(str2);
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    int i, j;
    // printf("%d %d\n", m, n);

    for (i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[m][n];
}


// 最长公共子串（连续）
int lcs2_length_(const string &str1, const string &str2) {
    if (str1 == "" || str2 == "")
        return 0;
    vector<string> s1 = utf8_split(str1);
    vector<string> s2 = utf8_split(str2);
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    int i, j;
    int max = 0;

    for (i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max){
                    max = dp[i][j];
                }
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    return max;
}


// TODO 返回子序列
int lcs(const string &str1, const string &str2){
    return lcs_length_(str1, str2);
}


// TODO 返回子串
int lcs2(const string &str1, const string &str2){
    return lcs2_length_(str1, str2);
}


vector<int> lcs_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        int l = lcs(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


vector<int> lcs2_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        int l = lcs2(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


// 编辑距离
int levenshtein_distance(const string &str1, const string &str2) {
    if (str1 == "" || str2 == "")
        return 0;
    vector<string> s1 = utf8_split(str1);
    vector<string> s2 = utf8_split(str2);
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    int i, j;

    for (i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n];
}


vector<int> levenshtein_distance_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        int l = levenshtein_distance(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


namespace py = pybind11;


PYBIND11_MODULE(pylcs, m) {
    m.def("lcs", &lcs, R"pbdoc(
        Longest common subsequence
    )pbdoc");

    m.def("lcs_of_list", &lcs_of_list, R"pbdoc(
        Longest common subsequence of list
    )pbdoc");

    m.def("lcs2", &lcs2, R"pbdoc(
        Longest common substring
    )pbdoc");

    m.def("lcs2_of_list", &lcs2_of_list, R"pbdoc(
        Longest common substring of list
    )pbdoc");

    m.def("levenshtein_distance", &levenshtein_distance, R"pbdoc(
        Levenshtein Distance of Two Strings
    )pbdoc");

    m.def("edit_distance", &levenshtein_distance, R"pbdoc(
        Same As levenshtein_distance(): Levenshtein Distance of Two Strings
    )pbdoc");

    m.def("levenshtein_distance_of_list", &levenshtein_distance_of_list, R"pbdoc(
        Levenshtein Distance of one string to a list of strings
    )pbdoc");

    m.def("edit_distance_of_list", &levenshtein_distance_of_list, R"pbdoc(
        Levenshtein Distance of one string to a list of strings
    )pbdoc");
}
