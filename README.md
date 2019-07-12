# pylcs
**pylcs** is a super fast c++ library which adopts dynamic programming(DP) algorithm to solve two classic LCS problems as below .  
  
[The longest common subsequence](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem) problem is the problem of finding the longest subsequence common to all sequences in a set of sequences (often just two sequences).  
  
[The longest common substring](https://en.wikipedia.org/wiki/Longest_common_substring_problem) problem is to find the longest string (or strings) that is a substring (or are substrings) of two or more strings.

[Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance), aka ``edit distance`` is also supported. Emm...forget the package name. Example usage is in [tests](./tests/test_pylcs.py).

We also support Chinese(or any UTF-8) string.


Install
-------

To install, simply do ``pip install pylcs`` to pull down the latest version from [PyPI](https://pypi.org/project/pylcs/).


Python code example
-------------------

```python
import pylcs

#  finding the longest common subsequence length of string A and string B
A = 'We are shannonai'
B = 'We like shannonai'
pylcs.lcs(A, B)
"""
>>> pylcs.lcs(A, B)
14
"""

#  finding the longest common subsequence length of string A and a list of string B
A = 'We are shannonai'
B = ['We like shannonai', 'We work in shannonai', 'We are not shannonai']
pylcs.lcs_of_list(A, B)
"""
>>> pylcs.lcs_of_list(A, B)
[14, 14, 16]
"""

# finding the longest common substring length of string A and string B
A = 'We are shannonai'
B = 'We like shannonai'
pylcs.lcs2(A, B)
"""
>>> pylcs.lcs2(A, B)
11
"""

#  finding the longest common substring length of string A and a list of string B
A = 'We are shannonai'
B = ['We like shannonai', 'We work in shannonai', 'We are not shannonai']
pylcs.lcs2_of_list(A, B)
"""
>>> pylcs.lcs2_of_list(A, B)
[11, 10, 10]
"""

