# encoding=utf-8
import pylcs


def test_lcs():
    assert pylcs.lcs("aaa", "") == 0
    assert pylcs.lcs("", "bbb") == 0
    assert pylcs.lcs("aaa", "bbb") == 0
    assert pylcs.lcs("你好", "中国") == 0
    assert pylcs.lcs_sequence_length("aaa", "aabbbaa") == 3
    assert pylcs.lcs_sequence_length("aaa你好", "你好呀") == 2


def test_lcs_of_list():
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


def test_lcs2():
    assert pylcs.lcs2("aaa", "") == 0
    assert pylcs.lcs2("", "bbb") == 0
    assert pylcs.lcs2("aaa", "bbb") == 0
    assert pylcs.lcs2("你好", "中国") == 0
    assert pylcs.lcs_string_length("aaa", "aabbbaa") == 2
    assert pylcs.lcs_string_length("aaa你好", "好呀你") == 1


def test_lcs2_of_list():
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
    assert pylcs.edit_distance("aaa", "bbb") == 3
    assert pylcs.edit_distance("aaa", "aabbbaa") == 4
    assert pylcs.edit_distance("你好", "中国") == 2
    assert pylcs.edit_distance("aaa你好", "你好呀") == 4


def test_edit_distance_of_list():
    assert pylcs.edit_distance_of_list("aaa", ["bbb"] * 10) == [3] * 10
    assert pylcs.edit_distance_of_list("aaa你好", ["你好呀"] * 10) == [4] * 10
    assert pylcs.edit_distance_of_list("aaa你好", ["bbb", "你好呀"] * 10) == [5, 4] * 10


test_lcs()
test_lcs_of_list()
test_lcs_sequence_idx()
test_lcs_string_idx()
test_lcs2()
test_lcs2()
test_lcs2_of_list()
test_edit_distance()
test_edit_distance_of_list()
