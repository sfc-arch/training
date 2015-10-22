//
// Place to store constant paragraphs, such as --help or --version s.
// Thanks to generate_paragraph() or show_paragraph() in cat_body.c, these would be shown easily.
//

// The original one
const char *HelpSentencesOld[] = {
    "使用法: cat [オプション]... [ファイル]...",
    "ファイル、または標準入力を連結し、標準出力に出力します。",
    "",
    "  -A, --show-all           -vETと同じ",
    "  -b, --number-nonblank    空行を除いて行番号を付け加える。-n より優先される",
    "  -e                       -vEと同じ",
    "  -E, --show-ends          行の最後に $ を付け加える",
    "  -n, --number             全ての行に行番号を付け加える",
    "  -s, --squeeze-blank      連続した空行の出力を抑止する",
    "  -t                       -vTと同じ",
    "  -T, --show-tabs          TAB文字を`^I'で表示",
    "  -u                       (無視)",
    "  -v, --show-nonprinting   非表示文字と`^'や`^'を付けて表示 (LFDとTABは除く)",
    "      --help     この使い方を表示して終了する",
    "      --version  バージョン情報を表示して終了する",
    "",
    "ファイルの指定がなかったり, - であった場合, 標準入力から読み込みます.",
    "",
    "例:",
    "  cat f - g  最初に f の中身を出力し、次に標準入力を出力します。",
    "             そして g の中身を出力します。",
    "  cat        標準入力を標準出力に複製します。",
    "",
    "GNU coreutils online help: <http://www.gnu.org/software/coreutils/>",
    "cat の翻訳に関するバグは <http://translationproject.org/team/ja.html> に連絡してください。",
    "Full documentation at: <http://www.gnu.org/software/coreutils/cat>",
    "or available locally via: info '(coreutils) cat invocation'"
};

const char *HelpSentences[] = {
    "使用法: cat [オプション]... [ファイル]...",
    "ファイル、または標準入力を連結し、標準出力に出力します。",
    "",
    "      --help     この使い方を表示して終了する",
    "      --version  バージョン情報を表示して終了する",
    "",
    "ファイルの指定がなかったり, - であった場合, 標準入力から読み込みます.",
    "",
    "例:",
    "  cat f - g  最初に f の中身を出力し、次に標準入力を出力します。",
    "             そして g の中身を出力します。",
    "  cat        標準入力を標準出力に複製します。",
    "",
    "GNU coreutils online help: <http://www.gnu.org/software/coreutils/>",
    "cat の翻訳に関するバグは <http://translationproject.org/team/ja.html> に連絡してください。",
    "Full documentation at: <http://www.gnu.org/software/coreutils/cat>",
    "or available locally via: info '(coreutils) cat invocation'"
};

// The original one
const char *VersionSentencesOld[] = {
    "cat (GNU coreutils) 8.23",
    "Copyright (C) 2014 Free Software Foundation, Inc.",
    "ライセンス GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.",
    "This is free software: you are free to change and redistribute it.",
    "There is NO WARRANTY, to the extent permitted by law.",
    "",
    "作者 Torbjörn Granlund および Richard M. Stallman。"
};

const char *VersionSentences[] = {
    "cat (imitation) 0.0.1",
    "Copyright (C) 2015 U-dory/Todoroki",
    "ライセンス :Distribution prohibited.",
    "This is garbage software: you are free to dispose and recycle it.",
    "There is NO WARRANTY, to the extent permitted by law.",
    "",
    "作者 U-dory a.k.a. Todoroki (@ndac_todoroki)。"
};