#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;


//最长公共子串（LCS）
//二维数组veca记录的是两个字符串Xi和Yj的LCS长度
int LCS_length_(const string &str1, const string &str2, vector<vector<int> > &veca) {
	unsigned int i, j;
    unsigned int m, n;
    m = str1.length();
    n = str2.length();
	if (str1 == "" || str2 == "")
		return 0;

	for (i = 0; i <= m; i++) {
		veca[i][0] = 0;
	}
	for (j = 0; j <= n; j++) {
		veca[0][j] = 0;
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				veca[i][j] = veca[i - 1][j - 1] + 1;
			}
			else {
				if (veca[i - 1][j] >= veca[i][j - 1])
					veca[i][j] = veca[i - 1][j];
				else
					veca[i][j] = veca[i][j-1];
			}
		}
	}
	return veca[str1.length()][str2.length()];
}


int lcs(const string &str1, const string &str2){
	//将veca初始化为一个二维数组,其行列值分别为str1和str2的长度加1
	//二维数组veca记录的是两个字符串Xi和Yj的LCS长度
	vector<vector<int> > veca(str1.length() + 1, vector<int>(str2.length() + 1));
    return LCS_length_(str1, str2, veca);
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


// TODO 最长公共子序列


namespace py = pybind11;


PYBIND11_MODULE(pylcs, m) {
    m.def("lcs", &lcs, R"pbdoc(
        Longest common subsequnce
    )pbdoc");

    m.def("lcs_of_list", &lcs_of_list, R"pbdoc(
        Longest common subsequnce of list
    )pbdoc");

}


/*
int main() {
	string input;
	getline(cin, input);
        stringstream ss(input);
        string str1, str2;
	ss >> str1;
	ss >> str2;
	cout << lcs(str1, str2) << endl;
	return 0;
}
*/

