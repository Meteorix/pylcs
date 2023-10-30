# pylcs

**The [original repository](https://github.com/Meteorix/pylcs) stop maintenance. This is a transfer version**

**pylcs** is a super fast c++ library which adopts dynamic programming(DP) algorithm to solve two classic LCS problems as below .  
  
[The longest common subsequence](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem) problem is the problem of finding the longest subsequence common to all sequences in a set of sequences (often just two sequences).  
  
[The longest common substring](https://en.wikipedia.org/wiki/Longest_common_substring_problem) problem is to find the longest string (or strings) that is a substring (or are substrings) of two or more strings.

[Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance), aka ``edit distance`` is also supported. Emm...forget the package name. Example usage is in [tests](./tests/test_pylcs.py).

We also support Chinese(or any UTF-8) string.

Colorful Visualization: After 0.1.0, you can visualize the lcs result with colorful output.


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
pylcs.lcs_sequence_length(A, B)
"""
>>> pylcs.lcs_sequence_length(A, B)
14
"""

#  finding alignment from string A to B
A = 'We are shannonai'
B = 'We like shannonai'
res = pylcs.lcs_sequence_idx(A, B)
''.join([B[i] for i in res if i != -1])
"""
>>> res
[0, 1, 2, -1, -1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
>>> ''.join([B[i] for i in res if i != -1])
'We e shannonai'
"""

#  finding the longest common subsequence length of string A and a list of string B
A = 'We are shannonai'
B = ['We like shannonai', 'We work in shannonai', 'We are not shannonai']
pylcs.lcs_sequence_of_list(A, B)
"""
>>> pylcs.lcs_sequence_of_list(A, B)
[14, 14, 16]
"""

# finding the longest common substring length of string A and string B
A = 'We are shannonai'
B = 'We like shannonai'
pylcs.lcs_string_length(A, B)
"""
>>> pylcs.lcs_string_length(A, B)
11
"""

#  finding alignment from string A to B
A = 'We are shannonai'
B = 'We like shannonai'
res = pylcs.lcs_string_idx(A, B)
''.join([B[i] for i in res if i != -1])
"""
>>> res
[-1, -1, -1, -1, -1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
>>> ''.join([B[i] for i in res if i != -1])
'e shannonai'
"""

#  finding the longest common substring length of string A and a list of string B
A = 'We are shannonai'
B = ['We like shannonai', 'We work in shannonai', 'We are not shannonai']
pylcs.lcs_string_of_list(A, B)
"""
>>> pylcs.lcs_string_of_list(A, B)
[11, 10, 10]
"""

#  finding the weighted edit distance from string A to B
pylcs.edit_distance("aaa", "aba")
pylcs.edit_distance("aaa", "aba", {'a': {'b': 2.0}})
pylcs.edit_distance("", "aa", {'': {'a': 0.5}})
#  weight['']['a'] means inserting a char 'a' costs 0.5
#  similarly, weight['a'][''] means the score of deleting a char 'a'
"""
>>> pylcs.edit_distance("aaa", "aba")
1
>>> pylcs.edit_distance("aaa", "aba", {'a': {'b': 2.0}})
2.0
>>> pylcs.edit_distance("", "aa", {'': {'a': 0.5}})
1.0
"""

#  finding edit distance alignment from string A to B
pylcs.edit_distance_idx("aaa", "aba")
pylcs.edit_distance_idx("aaa", "aba", {'a': {'b': 3}})
pylcs.edit_distance_idx("aa", "aabb", {'a': {'a': 2, 'b': 0}})
"""
>>> pylcs.edit_distance_idx("aaa", "aba")
[0, 1, 2]
>>> pylcs.edit_distance_idx("aaa", "aba", {'a': {'b': 3}})
[0, -1, 2]
>>> pylcs.edit_distance_idx("aa", "aabb", {'a': {'a': 2, 'b': 0}})
[2, 3]
"""
```

After 0.1.0, you can make a visualized comparison with colorful output. Using `coloring_match_sequence` to color the s1 and s2 by a match list like:
```python
s1, s2 = "abcdefghijklmnopq", "-c-fgh-kl-nop-q"
match_list = pylcs.lcs_sequence_idx(s1, s2)
colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 11, 11, "#2266ff", "#2266ff", t=1)
print(colored_s1, colored_s2)
colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 11, 11, "#2266ff", "#2266ff", t=2)
print(colored_s1, colored_s2)
colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 11, 11, "#2266ff", "#2266ff", t=3)
print(colored_s1, colored_s2)
```
![](https://github.com/kuangkzh/pylcs/blob/master/tests/coloring_match_sequence.jpg)
```python
s1, s2 = "How does this string edit to s2?", "How similar is this string to s1?"
match_list = pylcs.edit_distance_idx(s1, s2)
colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 4, 4, 230, 230, t=2)
print(colored_s1, colored_s2, sep='\n')
```
![](https://github.com/kuangkzh/pylcs/blob/master/tests/coloring_match_sequence_2.jpg)

Note that the colorful output uses ANSI escape codes. Referring to https://en.wikipedia.org/wiki/ANSI_escape_code.

The ANSI codes may not work in win32 command line.
