import re
from _pylcs import *


def color_to_ansi_escape_code(color, is_front=True):
    if color is None:
        return ""
    color_mode = 38 if is_front else 48
    if isinstance(color, int):
        return f"\033[{color_mode};5;{color}m"
    if isinstance(color, str):
        color = color.strip("#")
        return f"\033[{color_mode};2;{int(color[0:2], 16)};{int(color[2:4], 16)};{int(color[4:6], 16)}m"
    return color


def coloring_match_sequence(match_list, s1, s2, c1=None, c2=None, b1=None, b2=None, t=5):
    """
    Coloring the s1 and s2 by match results in match_list. Returned the colored s1 and s2 using ANSI escape codes.
    Referring to https://en.wikipedia.org/wiki/ANSI_escape_code.
    The ANSI codes may not work in win32. In this time you can try colorama.init first(maybe useless):
    >>> import colorama
    >>> colorama.init(autoreset=True)
    :param match_list: An array of match results with the same length as s1. Each element indicates the match index in
                       s2. Not match for -1.
    :param s1: string1
    :param s2: string2
    :param c1: Option[int, str], Default None. Forefront color for s1.
               Int color index in https://en.wikipedia.org/wiki/ANSI_escape_code#Colors.
               Hex color string like "#FFFFFF" is also supported.
    :param c2: Option[int, str], Default None. Forefront color for s2.
    :param b1: Option[int, str], Default None. Background color for s1.
    :param b2: Option[int, str], Default None. Background color for s2.
    :param t: A continuous length threshold for coloring.
    :return: (colored_s1, colored_s2)
    """
    def _coloring(s, color, back_color):
        color = color_to_ansi_escape_code(color, is_front=True)
        back_color = color_to_ansi_escape_code(back_color, is_front=False)

        def _color_repl(re_obj):
            _slice = s[re_obj.start(): re_obj.end()]
            if re.match("1+", re_obj.group(0)):
                return color + back_color + _slice + "\033[0m"
            return _slice

        return _color_repl

    mask = ''.join(['1' if i != -1 else '0' for i in match_list])
    mask = re.sub("1+", lambda s: s.group(0).replace("1", "0" if len(s.group(0)) < t else "1"), mask)

    cs1 = re.sub("0+|1+", _coloring(s1, c1, b1), mask)

    mask = set(match_list)
    mask = ''.join(['1' if i in mask else '0' for i in range(len(s2))])
    mask = re.sub("1+", lambda s: s.group(0).replace("1", "0" if len(s.group(0)) < t else "1"), mask)

    cs2 = re.sub("0+|1+", _coloring(s2, c2, b2), mask)

    return cs1, cs2

