# encoding=utf-8
import pylcs


def test_lcs():
    assert pylcs.lcs("aaa", "bbb") == 0
    assert pylcs.lcs("aaa", "aabbbaa") == 3
    assert pylcs.lcs("你好", "中国") == 0
    assert pylcs.lcs("aaa你好", "你好呀") == 2


def test_lcs_of_list():
    assert pylcs.lcs_of_list("aaa", ["aabbbaa"] * 10) == [3] * 10
    assert pylcs.lcs_of_list("aaa你好", ["你好呀"] * 10) == [2] * 10


def test_lcs2():
    assert pylcs.lcs2("aaa", "bbb") == 0
    assert pylcs.lcs2("aaa", "aabbbaa") == 2
    assert pylcs.lcs2("你好", "中国") == 0
    assert pylcs.lcs2("aaa你好", "好呀你") == 1


def test_lcs2_of_list():
    assert pylcs.lcs2_of_list("aaa", ["aabbbaa"] * 10) == [2] * 10
    assert pylcs.lcs2_of_list("aaa你好", ["好呀你"] * 10) == [1] * 10


def test_edit_distance():
    assert pylcs.edit_distance("aaa", "bbb") == 3
    assert pylcs.edit_distance("aaa", "aabbbaa") == 4
    assert pylcs.edit_distance("你好", "中国") == 2
    assert pylcs.edit_distance("aaa你好", "你好呀") == 4

