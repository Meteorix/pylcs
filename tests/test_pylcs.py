# encoding=utf-8
import pylcs
import colorama


def test_lcs_sequence():
    assert pylcs.lcs("aaa", "") == 0
    assert pylcs.lcs("", "bbb") == 0
    assert pylcs.lcs("aaa", "bbb") == 0
    assert pylcs.lcs("你好", "中国") == 0
    assert pylcs.lcs_sequence_length("aaa", "aabbbaa") == 3
    assert pylcs.lcs_sequence_length("aaa你好", "你好呀") == 2


def test_lcs_sequence_of_list():
    assert pylcs.lcs_of_list("aaa", ["aabbbaa"] * 10) == [3] * 10
    assert pylcs.lcs_of_list("aaa你好", ["你好呀"] * 10) == [2] * 10
    assert pylcs.lcs_sequence_of_list("aaa", ["aabbbaa"] * 10) == [3] * 10
    assert pylcs.lcs_sequence_of_list("aaa你好", ["你好呀"] * 10) == [2] * 10


def test_lcs_sequence_idx():
    assert pylcs.lcs_sequence_idx("", "bbb") == []
    assert pylcs.lcs_sequence_idx("aaa", "") == [-1, -1, -1]
    assert pylcs.lcs_sequence_idx("aaa", "bbb") == [-1, -1, -1]
    assert pylcs.lcs_sequence_idx("你好", "中国") == [-1, -1]
    res = pylcs.lcs_sequence_idx("aaa", "aabbbaa")
    assert all([x in [0, 1, 5, 6] for x in res]) and res == sorted(res)
    assert pylcs.lcs_sequence_idx("aaa你好", "你好呀") == [-1, -1, -1, 0, 1]


def test_lcs_string():
    assert pylcs.lcs2("aaa", "") == 0
    assert pylcs.lcs2("", "bbb") == 0
    assert pylcs.lcs2("aaa", "bbb") == 0
    assert pylcs.lcs2("你好", "中国") == 0
    assert pylcs.lcs_string_length("aaa", "aabbbaa") == 2
    assert pylcs.lcs_string_length("aaa你好", "好呀你") == 1


def test_lcs_string_of_list():
    assert pylcs.lcs2_of_list("aaa", ["aabbbaa"] * 10) == [2] * 10
    assert pylcs.lcs2_of_list("aaa你好", ["好呀你"] * 10) == [1] * 10
    assert pylcs.lcs_string_of_list("aaa", ["aabbbaa"] * 10) == [2] * 10
    assert pylcs.lcs_string_of_list("aaa你好", ["好呀你"] * 10) == [1] * 10


def test_lcs_string_idx():
    assert pylcs.lcs_string_idx("", "bbb") == []
    assert pylcs.lcs_string_idx("aaa", "") == [-1, -1, -1]
    assert pylcs.lcs_string_idx("aaa", "bbb") == [-1, -1, -1]
    assert pylcs.lcs_string_idx("你好", "中国") == [-1, -1]
    assert pylcs.lcs_string_idx("aaa", "aabbbaa") in ([0, 1, -1], [-1, 0, 1], [5, 6, -1], [-1, 5, 6])
    assert pylcs.lcs_string_idx("aaa", "aabbbaaa") == [5, 6, 7]
    assert pylcs.lcs_string_idx("aaa你好", "你好呀") == [-1, -1, -1, 0, 1]


def test_edit_distance():
    assert pylcs.edit_distance("", "") == 0
    assert pylcs.edit_distance("", "bbb") == 3
    assert pylcs.edit_distance("aaa", "") == 3
    assert pylcs.edit_distance("aaa", "aaa") == 0
    assert pylcs.edit_distance("aaa", "bbb") == 3
    assert pylcs.edit_distance("aaa", "aabbbaa") == 4
    assert pylcs.edit_distance("你好", "中国") == 2
    assert pylcs.edit_distance("aaa你好", "你好呀") == 4


def test_edit_distance_weighted():
    assert pylcs.edit_distance("", "bbb", {}) == 3
    assert pylcs.edit_distance("", "bbb", {'': {'b': 2}}) == 6
    assert pylcs.edit_distance("", "bbb", {'b': {'': 2}}) == 3
    assert pylcs.edit_distance("aaa", "", {}) == 3
    assert pylcs.edit_distance("aaa", "", {'': {'a': 2}}) == 3
    assert pylcs.edit_distance("aaa", "", {'a': {'': 2}}) == 6
    assert pylcs.edit_distance("aaa", "aba", {'a': {'b': 2}}) == 2
    assert pylcs.edit_distance("aaa", "aba", {'a': {'b': 3}}) == 2
    assert pylcs.edit_distance("aaa", "aaa", {'a': {'a': 1}}) == 3
    assert pylcs.edit_distance("aa", "aababb", {'a': {'a': 0.5, 'b': 2}}) == 5
    assert pylcs.edit_distance("x你好", "你好呀", {'你': {'你': -1}}) == 1
    assert pylcs.edit_distance("x你好", "你好呀", {'你好': {'你好': -1}}) == 2
    weight = {'A': {'A': -2, 'C': 7, 'G': 5, 'T': 7, '': 5},
              'C': {'A': 7, 'C': -2, 'G': 7, 'T': 5, '': 5},
              'G': {'A': 5, 'C': 7, 'G': -2, 'T': 7, '': 5},
              'T': {'A': 7, 'C': 5, 'G': 7, 'T': -2, '': 5},
              '': {'A': 5, 'C': 5, 'G': 5, 'T': 5, '': 0}}
    assert pylcs.edit_distance("GCT", "CTT", weight) == 6


def test_edit_distance_idx():
    assert pylcs.edit_distance_idx("aaa", "") == [-1, -1, -1]
    assert pylcs.edit_distance_idx("", "bbb") == []
    assert pylcs.edit_distance_idx("aaa", "aba", {'a': {'b': 1}}) == [0, 1, 2]
    assert pylcs.edit_distance_idx("aaa", "aba", {'a': {'b': 3}}) == [0, -1, 2]
    assert pylcs.edit_distance_idx("aa", "aabb", {'a': {'a': 2, 'b': 0}}) == [2, 3]


def test_edit_distance_of_list():
    assert pylcs.edit_distance_of_list("aaa", ["bbb"] * 10) == [3] * 10
    assert pylcs.edit_distance_of_list("aaa你好", ["你好呀"] * 10) == [4] * 10
    assert pylcs.edit_distance_of_list("aaa你好", ["bbb", "你好呀"] * 10) == [5, 4] * 10


def test_coloring_match_sequence():
    s1, s2 = "abcdefghijklmnopq", "-c-fgh-kl-nop-q"
    match_list = pylcs.lcs_sequence_idx(s1, s2)
    colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 11, 11, "#2266ff", "#2266ff", t=1)
    print(colored_s1, colored_s2)
    colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 11, 11, "#2266ff", "#2266ff", t=2)
    print(colored_s1, colored_s2)
    colored_s1, colored_s2 = pylcs.coloring_match_sequence(match_list, s1, s2, 11, 11, "#2266ff", "#2266ff", t=3)
    print(colored_s1, colored_s2)


test_lcs_sequence()
test_lcs_sequence_of_list()
test_lcs_sequence_idx()
test_lcs_string()
test_lcs_string_of_list()
test_lcs_string_idx()
test_edit_distance()
test_edit_distance_weighted()
test_edit_distance_idx()
test_edit_distance_of_list()

colorama.init(autoreset=True)
test_coloring_match_sequence()
