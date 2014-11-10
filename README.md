English version is below.

Arch C言語 課題No.1 catコマンドの実装
=====

### 目的

システムコールの基本について学ぶ

### 課題内容

Unix系OSに標準で同梱されている`cat`コマンドと同等の働きをするアプリケーションを以下の条件のもとでC言語によって実装してください。

* `stdio.h`および`stdlib.h`はインクルードしてはいけません
* `cat`コマンドに実装されているオプションは実装しなくても構いません

### 評価内容

* 上記の条件を確かに満たしているか
* OS同梱の`cat`コマンドの結果と`diff`して同じになっているか


--

Arch Subject#1 Implement cat command
=====

### Intent

To learn the basis of system calls

### Details

Implement an application same behave as the `cat` command using C.

- Do not include `stdio.h` or `stdlib.h`.
- Do not need to implement same behave as the `cat` command options.

### Evaluations

- Meet the above requirements.
- Have the same results of original `cat` and made `cat` using `diff`.
