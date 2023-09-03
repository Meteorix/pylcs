#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
#include <algorithm>
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
int lcs_sequence_length(const string &str1, const string &str2) {
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


vector<int> lcs_sequence_idx(const string &str, const string &ref) {
    vector<string> s1 = utf8_split(str);
    vector<string> s2 = utf8_split(ref);
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    vector<vector<char>> direct(m + 1, vector<char>(n + 1));
    vector<int> res(m, -1);
    if (m == 0 || n == 0)
        return res;

    int i, j;
    for (i = 0; i <= m; i++) dp[i][0] = 0;
    for (j = 0; j <= n; j++) dp[0][j] = 0;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                direct[i][j] = 'm';     // match
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    direct[i][j] = 's';     // str+1
                }
                else {
                    dp[i][j] = dp[i][j-1];
                    direct[i][j] = 'r';     // ref+1
                }
            }
        }
    }
    for (i = m, j = n; i > 0 && j > 0; ){
        if (direct[i][j] == 'm') {
            res[i-1] = j-1;
            i--; j--;
        }
        else if (direct[i][j] == 's') i--;
        else if (direct[i][j] == 'r') j--;
    }
    return res;
}


// 最长公共子串（连续）
int lcs_string_length(const string &str1, const string &str2) {
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


vector<int> lcs_string_idx(const string &str, const string &ref) {
    vector<string> s1 = utf8_split(str);
    vector<string> s2 = utf8_split(ref);
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    vector<int> res(m, -1);
    if (m == 0 || n == 0)
        return res;

    int i, j;
    int max_i = 0, max_j = 0;
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
                if (dp[i][j] > dp[max_i][max_j]){
                    max_i = i; max_j = j;
                }
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    for (i = 0; i < dp[max_i][max_j]; i++) {
        res[max_i-i-1] = max_j-i-1;
    }
    return res;
}


vector<int> lcs_sequence_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        int l = lcs_sequence_length(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


vector<int> lcs_string_of_list(const string &str1, vector<string> &str_list){
    int size = str_list.size();
    vector<int> ls(size);
    for (int i = 0; i < size; i++){
        int l = lcs_string_length(str1, str_list[i]);
        ls[i] = l;
    }
    return ls;
}


// 编辑距离
int levenshtein_distance(const string &str1, const string &str2) {
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


bool inline __contains(map<string, map<string, float>> m, string k1, string k2) {
    return m.find(k1) != m.end() && m[k1].find(k2) != m[k1].end();
}

float levenshtein_distance_weighted(const string &str1, const string &str2, map<string, map<string, float>> &weight) {
    vector<string> s1 = utf8_split(str1);
    vector<string> s2 = utf8_split(str2);
    string __("");
    int m = s1.size();
    int n = s2.size();
    vector<vector<float>> dp(m + 1, vector<float>(n + 1));
    int i, j;
    float si, sj, sij;

    dp[0][0] = 0;
    for (i = 1; i <= m; i++) {
        dp[i][0] = dp[i-1][0] + (__contains(weight, s1[i-1], __) ? weight[s1[i-1]][__] : 1);
    }
    for (j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j-1] + (__contains(weight, __, s2[j-1]) ? weight[__][s2[j-1]] : 1);
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            si = __contains(weight, s1[i-1], __) ? weight[s1[i-1]][__] : 1;
            sj = __contains(weight, __, s2[j-1]) ? weight[__][s2[j-1]] : 1;
            sij = __contains(weight, s1[i-1], s2[j-1]) ? weight[s1[i-1]][s2[j-1]] : (s1[i-1] == s2[j-1] ? 0 : 1);
            dp[i][j] = min({dp[i-1][j] + si, dp[i][j-1] + sj, dp[i-1][j-1] + sij});
        }
    }
    return dp[m][n];
}


vector<int> levenshtein_distance_idx_weighted(const string &str, const string &ref, map<string, map<string, float>> &weight) {
    vector<string> s1 = utf8_split(str);
    vector<string> s2 = utf8_split(ref);
    string __("");
    int m = s1.size();
    int n = s2.size();
    vector<vector<float>> dp(m + 1, vector<float>(n + 1));
    vector<vector<char>> direct(m + 1, vector<char>(n + 1));
    vector<int> res(m, -1);
    int i, j;
    float si, sj, sij;

    dp[0][0] = 0;
    for (i = 1; i <= m; i++) {
        dp[i][0] = dp[i-1][0] + (__contains(weight, s1[i-1], __) ? weight[s1[i-1]][__] : 1);
        direct[i][0] = 's';
    }
    for (j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j-1] + (__contains(weight, __, s2[j-1]) ? weight[__][s2[j-1]] : 1);
        direct[0][j] = 'r';
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            si = __contains(weight, s1[i-1], __) ? weight[s1[i-1]][__] : 1;
            sj = __contains(weight, __, s2[j-1]) ? weight[__][s2[j-1]] : 1;
            sij = __contains(weight, s1[i-1], s2[j-1]) ? weight[s1[i-1]][s2[j-1]] : (s1[i-1] == s2[j-1] ? 0 : 1);
            if (dp[i-1][j-1] + sij <= dp[i-1][j] + si && dp[i-1][j-1] + sij <= dp[i][j-1] + sj) {
                dp[i][j] = dp[i-1][j-1] + sij;
                direct[i][j] = 'm';
            }
            else if (dp[i-1][j] + si <= dp[i][j-1] + sj) {
                dp[i][j] = dp[i-1][j] + si;
                direct[i][j] = 's';
            }
            else {
                dp[i][j] = dp[i][j-1] + sj;
                direct[i][j] = 'r';
            }
        }
    }

    for (i = m, j = n; i > 0 && j > 0; ){
        if (direct[i][j] == 'm') {
            res[i-1] = j-1;
            i--; j--;
        }
        else if (direct[i][j] == 's') i--;
        else if (direct[i][j] == 'r') j--;
    }
    return res;
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


PYBIND11_MODULE(_pylcs, m) {
    m.def("lcs", &lcs_sequence_length, R"pbdoc(Longest common subsequence)pbdoc");
    m.def("lcs_sequence_length", &lcs_sequence_length, R"pbdoc(Longest common subsequence)pbdoc");
    m.def("lcs_sequence_idx", &lcs_sequence_idx, R"pbdoc(Longest common subsequence indices mapping from str to ref)pbdoc",
        py::arg("s"), py::arg("ref"));
    m.def("lcs_of_list", &lcs_sequence_of_list, R"pbdoc(Longest common subsequence of list)pbdoc");
    m.def("lcs_sequence_of_list", &lcs_sequence_of_list, R"pbdoc(Longest common subsequence of list)pbdoc");

    m.def("lcs2", &lcs_string_length, R"pbdoc(Longest common substring)pbdoc");
    m.def("lcs_string_length", &lcs_string_length, R"pbdoc(Longest common substring)pbdoc");
    m.def("lcs_string_idx", &lcs_string_idx, R"pbdoc(Longest common substring indices mapping from str to ref)pbdoc",
        py::arg("s"), py::arg("ref"));
    m.def("lcs2_of_list", &lcs_string_of_list, R"pbdoc(Longest common substring of list)pbdoc");
    m.def("lcs_string_of_list", &lcs_string_of_list, R"pbdoc(Longest common substring of list)pbdoc");

    m.def("levenshtein_distance", &levenshtein_distance, R"pbdoc(Levenshtein Distance of Two Strings)pbdoc");
    m.def("levenshtein_distance", &levenshtein_distance_weighted, R"pbdoc(Levenshtein Distance of Two Strings. A weight dict<str, dict<str, float>> can be used.)pbdoc",
        py::arg("str1"), py::arg("str2"), py::arg("weight"));
    m.def("levenshtein_distance_idx", &levenshtein_distance_idx_weighted, R"pbdoc(Levenshtein Distance indices mapping from str to ref)pbdoc",
        py::arg("s"), py::arg("ref"), py::arg("weight")=map<string, map<string, float>>());
    m.def("edit_distance", &levenshtein_distance, R"pbdoc(Same As levenshtein_distance(): Levenshtein Distance of Two Strings)pbdoc");
    m.def("edit_distance", &levenshtein_distance_weighted, R"pbdoc(Same As levenshtein_distance(): Levenshtein Distance of Two Strings)pbdoc",
        py::arg("str1"), py::arg("str2"), py::arg("weight"));
    m.def("edit_distance_idx", &levenshtein_distance_idx_weighted, R"pbdoc(Edit Distance indices mapping from str to ref)pbdoc",
        py::arg("s"), py::arg("ref"), py::arg("weight")=map<string, map<string, float>>());
    m.def("levenshtein_distance_of_list", &levenshtein_distance_of_list, R"pbdoc(Levenshtein Distance of one string to a list of strings)pbdoc");
    m.def("edit_distance_of_list", &levenshtein_distance_of_list, R"pbdoc(Levenshtein Distance of one string to a list of strings)pbdoc");
}
