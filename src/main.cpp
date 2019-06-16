#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;


// 最长公共子序列（不连续）
int lcs_length_(const string &str1, const string &str2, vector<vector<int> > &dp) {
    unsigned int i, j;
    unsigned int m, n;
    m = str1.length();
    n = str2.length();
    if (str1 == "" || str2 == "")
        return 0;

    for (i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                if (dp[i - 1][j] >= dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[str1.length()][str2.length()];
}


// 最长公共子串（连续）
int lcs2_length_(const string &str1, const string &str2, vector<vector<int> > &dp) {
    unsigned int i, j;
    unsigned int m, n;
    unsigned int max = 0;
    m = str1.length();
    n = str2.length();
    if (str1 == "" || str2 == "")
        return 0;

    for (i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
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
    vector<vector<int> > dp(str1.length() + 1, vector<int>(str2.length() + 1));
    return lcs_length_(str1, str2, dp);
}


// TODO 返回子串
int lcs2(const string &str1, const string &str2){
    vector<vector<int> > dp(str1.length() + 1, vector<int>(str2.length() + 1));
    return lcs2_length_(str1, str2, dp);
}


vector<int> lcs_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        unsigned int l = lcs(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


vector<int> lcs2_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        unsigned int l = lcs2(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


// TODO 最长公共子串（连续）


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

}

