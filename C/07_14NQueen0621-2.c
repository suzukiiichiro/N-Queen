/**
  Cで学ぶアルゴリズムとデータ構造  
  ステップバイステップでＮ−クイーン問題を最適化
  一般社団法人  共同通信社  情報技術局  鈴木  維一郎(suzuki.iichiro@kyodonews.jp)
  
*************************
はじめに
*************************

幸運にもこのページを参照することができたN-Queen(Nクイーン）エンジニアは少数だろう。
Google検索またはGit検索でたどり着いたのだとは思うが、確率は奇跡に近い。
エンジニアにしてこのページを参照できた奇跡ついでにもう少しだけ読み進めて欲しい。
具体的には以下のリンクにわかりやすく書いてある。

  エイト・クイーン問題
  https://ja.wikipedia.org/wiki/エイト・クイーン
 
エイト・クイーンは、名前の通り８つのクイーンの解を求めるというパズルである。
Nクイーンは、エイトクイーンの拡張版で、Nの値は８、９、１０，１１，１２･･･と言った風
に増え続け、そのNの値であるボードの解を求めるものである。

GooleなどWebを探索すると無数のページがあることがわかる。その中でも充実したサイトを
紹介したい。おおよそ以下のサイトをかみしめて読み解けば情報は９０％網羅されている。

N-Queens 問題(Nobuhide Tsudaさん)
*************************
  はじめに
  力まかせ探索（Brute-force search）
  バックトラッキング
  制約テスト高速化（配置フラグ）
  ビット演算（ビットマップ）による高速化
  対称解除去
  枝刈りによる高速化
  http://vivi.dyndns.org/tech/puzzle/NQueen.html

Puzzle DE Programming(M.Hiroiさん）
*************************
  バックトラックとビット演算による高速化
  http://www.geocities.jp/m_hiroi/puzzle/nqueens.html

takakenさん（高橋謙一郎さん）のページ
*************************
  Ｎクイーン問題（解の個数を求める）
    ビット処理を用いた基本形
    ビット処理を用いたプログラムの仕組み
    ユニーク解の判定方法
    ユニーク解の個数を求める
    ユニーク解から全解への展開
    ソースプログラムと実行結果
  http://www.ic-net.or.jp/home/takaken/nt/queen/index.html

の、みなさんが掲示板で議論している模様(貴重ですね）
http://www2.ic-net.or.jp/~takaken/auto/guest/bbs62.html

ptimal Queens
*************************
英語だが、上記の全てがJavaで書かれていて群を抜いている
http://penguin.ewu.edu/~trolfe/Queens/OptQueen.html

その他のリンク
https://rosettacode.org/wiki/N-queens_problem
http://www.cc.kyoto-su.ac.jp/~yamada/ap/backtrack.html
http://yucchi.jp/java/java_tip/n_queens_problem/n_queens_problem.html
http://www.shido.info/py/queen_py3.html
http://toraneko75.sakura.ne.jp/wp/?p=223
http://yoshiiz.blog129.fc2.com/blog-entry-380.html
http://nw.tsuda.ac.jp/class/algoB/c6.html
http://www.kawa.net/works/js/8queens/nqueens.html
http://www.yasugi.ai.kyutech.ac.jp/2012/4/nq.html
http://www.neuro.sfc.keio.ac.jp/~masato/jv/nqueen/MPneuron.java
http://fujimura2.fiw-web.net/java/lang/page-20-3.html
https://github.com/pankajmore/DPP/blob/master/EPI/src/puzzles/NQueens.java
http://www.kanadas.com/ccm/queens-sort/index-j.html
http://chiiji.s10.xrea.com/nn/nqueen/nqueenn.shtml
http://www.neuro.sfc.keio.ac.jp/~masato/jv/nqueen/nqueenDemo.htm


ここからは参考情報のメモとして

ビットマップを N-Queens に最初に応用したのは Jeff Somers 氏のようだ。 
参照：The N Queens Problem
http://www.jsomers.com/nqueen_demo/nqueens.html(リンク切れのようだ）

電気通信大学　N-queensとは
2004年、電気通信大学の研究グループが、処理を並列化し、N=24 の解の個数を世界で初めて発見。 
http://www.arch.cs.titech.ac.jp/~kise/nq/
プレスリリース
http://www.arch.cs.titech.ac.jp/~kise/nq/press-2004-10-05.txt

NQueens問題
ＱＪＨの基本構想は、”部分解から全体解を構成するというアプローチ”（部分解合成法：Ｐａｒts Assembly Approach)です。
http://deepgreen.game.coocan.jp/NQueens/nqueen_index.htm

N Queens World records
http://www.nqueens.de/sub/WorldRecord.en.html


*****************************
このぺーじにはなにがあるのか
*****************************

具体的にこのページにはNクイーンのプログラムがある。
少なくともこの（今見ているこのページだ）１枚を実行すればまたたくまに処理は実行され問題は解決される。
ためしにこのページを  NQueen.c という名前で保存して自分のターミナル（それがわかる人に限定される）で、

コンパイル
$ gcc -pthread -O3 -Wall NQueen.c -o NQueen 

実行
$ ./NQueen 


を試して欲しい。実はこのページは 07の14ステップ目のソースである。ではそのステップを以下に示す。

  ステップバイステップでＮ−クイーン問題を最適化
   １．ブルートフォース（力まかせ探索） NQueen01()
   ２．配置フラグ（制約テスト高速化）   NQueen02()
   ３．バックトラック                   NQueen03() N16: 1:07
   ４．対称解除法(回転と斜軸）          NQueen04() N16: 1:09
   ５．枝刈りと最適化                   NQueen05() N16: 0:18
   ６．ビットマップ                     NQueen06() N16: 0:13
   ７．ビットマップ+対称解除法          NQueen07() N16: 0:21
   ８．ビットマップ+クイーンの場所で分岐NQueen08() N16: 0:13
   ９．ビットマップ+枝刈りと最適化      NQueen09() N16: 0:02
   10．もっとビットマップ               NQueen10()
   11．マルチスレッド(構造体)           NQueen11() N16: 0:02
   12．マルチスレッド(pthread)          NQueen12() N16: 0:02
   13．マルチスレッド(join)             NQueen13() N16: 0:02
   14．マルチスレッド(mutex)            NQueen14() N16: 0:00

Nクイーンの解決には処理を分解して一つ一つ丁寧に理解すべくステップが必要だ。
最初はステップ１のソースを何度も見て書いて理解するしかない。
もちろん、簡単なだけに解決時間も相当かかる。処理が終わるまでにコーヒーが飲み終わってしまうかもしれない。
ステップ14までくると、およそ１秒もかからずに処理が終了する。１分かかっていたことが１秒で終わることに
興味がわかないかもしれない。がしかし、１００年かかることが１年かからないとしたらどうだろう。
人工知能AI技術は、デバイスの進化、処理の高速化、解法の最適化（アルゴリズム）の三位一体だ。
順番に、とばすことなくじっくりと読み進めて欲しい。たぶん、日本中のNクイーンプログラムをここまで分解して
ステップにまとめているサイトはそう多くはないはずだ。

さらに、このサイトはNクイーンプログラムを複数のプログラム言語で習熟出来る準備がある。
例えば以下の通りだ。

  Java版 N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_N-Queen

  Bash版 N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_Bash

  Lua版  N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_Lua

  C版  N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_C
 

C版
　およそ全てのプログラム言語の中で最も高速に処理できると言われている。事実そうだ。
　まだ何もわからない初学の人はC言語から始めるべきだ。
　マルチスレッドなど、Javaに比べて複雑に記述する必要がある分、プログラムの端々までの
深い知識が必要だ。C言語マスターは間違いなく、Javaプログラマよりシステム技術を網羅的に深く理解している。

Java版
　C言語があまりにも難解と言われ、取っつきやすい部分を残し、Cでできることを取りこぼさずにできた言語がJavaだ。
マルチスレッドも、C言語よりもわかりやすい。システム技術の表層的な知識だけしかないのであればJavaがよい。
システムがわかった気になる危険な言語でもある。結論から言えばJavaができてもLinuxコマンドやBash、カーネルの
理解は１つも進まない。

Bash版
Linux/UNIXを学ぶのであればBash版をおすすめする。
https://github.com/suzukiiichiro/AI_Algorithm_Bash

  なぜBashなのかは以下に書いておいた。
  https://github.com/suzukiiichiro/AI_Algorithm_Bash/blob/master/002UNIXBasic

Bashは遅い。だが強力だ。Linuxの力を手に入れることができる。
どの言語で学ぶのかを迷っているのであれば迷わず「Bash」を選んで欲しい。
その次はLua->Java->Cだ。

Lua版
スマートフォンアプリが世の中のテクノロジーを牽引しているのは間違いない。
そのアプリ開発で幅を利かせているのがLua言語だ。コンパクトで高速、周りとの相性も良いときている。


上記、どの言語から始めても良いと思う。できる人はどの言語でもすらすら書ける。
では、以下から本題に入る。


*****************************
  N-Queens問題とは
*****************************
 
     Nクイーン問題とは、「8列×8行のチェスボードに8個のクイーンを、互いに効きが
     当たらないように並べよ」という８クイーン問題のクイーン(N)を、どこまで大き
     なNまで解を求めることができるかという問題。
     クイーンとは、チェスで使われているクイーンを指し、チェス盤の中で、縦、横、
     斜めにどこまでも進むことができる駒で、日本の将棋でいう「飛車と角」を合わ
     せた動きとなる。８列×８行で構成される一般的なチェスボードにおける8-Queens
     問題の解は、解の総数は92個である。比較的単純な問題なので、学部レベルの演
     習問題として取り上げられることが多い。
     8-Queens問題程度であれば、人力またはプログラムによる「力まかせ探索」でも
     解を求めることができるが、Nが大きくなると解が一気に爆発し、実用的な時間で
     は解けなくなる。
     現在すべての解が判明しているものは、2004年に電気通信大学でIntel Pentium 4
     Xeon 2.8GHzのプロセッサを68個搭載するPCクラスタ×20日をかけてn=24を解決し、
     世界一に、その後2005 年にニッツァ大学でn=25、2009年にドレスデン工科大学で
     N-26、さらに2016年に同工科大学でN=27の解を求めることに成功している。
     JeffSommers氏のビット演算を用いたエレガントなアルゴリズムに加え、対称解除
     法、並列処理、部分解合成法、圧縮や枝刈りなど、先端技術でワールドレコードが
     次々と更新されている。

             Total解        Unique解    鈴木維版   QJH(GPU)版   高橋謙一郎版  電通大版  JeffSomers版
15         2,279,184         285,053    00:00:00     00:00:00     00:00:00    00:00:01    00:00:04
16        14,772,512       1,846,955    00:00:00     00:00:00     00:00:04    00:00:08    00:00:23
17        95,815,104      11,977,939    00:00:04     00:00:07     00:00:31    00:01:01    00:02:38
18       666,090,624      83,263,591    00:00:33     00:00:25     00:03:48    00:07:00    00:19:26
19     4,968,057,848     621,012,754    00:04:19     00:03:17     00:29:22    00:57:16    02:31:24
20    39,029,188,884   4,878,666,808    00:34:49     00:24:07     03:54:10    07:19:24    20:35:06
21   314,666,222,712  39,333,324,973    04:41:36     03:05:28  01:09:17:19
22 2,691,008,701,644 336,376,244,042 01:15:14:59  01:03:08:20



************************************************
  ステップバイステップでＮ−クイーン問題を最適化
************************************************

   １．ブルートフォース（力まかせ探索） NQueen01()
   ２．配置フラグ（制約テスト高速化）   NQueen02()
   ３．バックトラック                   NQueen03() N16: 1:07
   ４．対称解除法(回転と斜軸）          NQueen04() N16: 1:09
   ５．枝刈りと最適化                   NQueen05() N16: 0:18
   ６．ビットマップ                     NQueen06() N16: 0:13
   ７．ビットマップ+対称解除法          NQueen07() N16: 0:21
   ８．ビットマップ+クイーンの場所で分岐NQueen08() N16: 0:13
   ９．ビットマップ+枝刈りと最適化      NQueen09() N16: 0:02
   10．もっとビットマップ               NQueen10()
   11．マルチスレッド(構造体)           NQueen11() N16: 0:02
   12．マルチスレッド(pthread)          NQueen12() N16: 0:02
   13．マルチスレッド(排他処理)         NQueen13() N16: 0:02
   14．マルチスレッド(join)             NQueen14() N16: 0:00



 1. ブルートフォース　力任せ探索

 　全ての可能性のある解の候補を体系的に数え上げ、それぞれの解候補が問題の解と
   なるかをチェックする方法
   (※)各行に１個の王妃を配置する組み合わせを再帰的に列挙組み合わせを生成するだ
   けであって8王妃問題を解いているわけではありません

  実行結果
  :
  :
  16777207: 7 7 7 7 7 7 6 6
  16777208: 7 7 7 7 7 7 6 7
  16777209: 7 7 7 7 7 7 7 0
  16777210: 7 7 7 7 7 7 7 1
  16777211: 7 7 7 7 7 7 7 2
  16777212: 7 7 7 7 7 7 7 3
  16777213: 7 7 7 7 7 7 7 4
  16777214: 7 7 7 7 7 7 7 5
  16777215: 7 7 7 7 7 7 7 6
  16777216: 7 7 7 7 7 7 7 7


  ２．配置フラグ（制約テスト高速化）
   パターンを生成し終わってからチェックを行うのではなく、途中で制約を満たさな
   い事が明らかな場合は、それ以降のパターン生成を行わない。
  「手を進められるだけ進めて、それ以上は無理（それ以上進めても解はない）という
  事がわかると一手だけ戻ってやり直す」という考え方で全ての手を調べる方法。
  (※)各行列に一個の王妃配置する組み合わせを再帰的に列挙分枝走査を行っても、組
  み合わせを列挙するだけであって、8王妃問題を解いているわけではありません。
 
  実行結果
  :
  :
  40312: 7 6 5 4 2 1 3 0
  40313: 7 6 5 4 2 3 0 1
  40314: 7 6 5 4 2 3 1 0
  40315: 7 6 5 4 3 0 1 2
  40316: 7 6 5 4 3 0 2 1
  40317: 7 6 5 4 3 1 0 2
  40318: 7 6 5 4 3 1 2 0
  40319: 7 6 5 4 3 2 0 1
  40320: 7 6 5 4 3 2 1 0


  ３．バックトラック
   　各列、対角線上にクイーンがあるかどうかのフラグを用意し、途中で制約を満た
   さない事が明らかな場合は、それ以降のパターン生成を行わない。
   　各列、対角線上にクイーンがあるかどうかのフラグを用意することで高速化を図る。
   　これまでは行方向と列方向に重複しない組み合わせを列挙するものですが、王妃
   は斜め方向のコマをとることができるので、どの斜めライン上にも王妃をひとつだ
   けしか配置できない制限を加える事により、深さ優先探索で全ての葉を訪問せず木
   を降りても解がないと判明した時点で木を引き返すということができます。
 
 
  実行結果
  N:        Total       Unique        hh:mm:ss.ms
  2:            0               0            0.00
  3:            0               0            0.00
  4:            2               0            0.00
  5:           10               0            0.00
  6:            4               0            0.00
  7:           40               0            0.00
  8:           92               0            0.00
  9:          352               0            0.00
 10:          724               0            0.00
 11:         2680               0            0.01
 12:        14200               0            0.05
 13:        73712               0            0.26
 14:       365596               0            1.54
 15:      2279184               0            9.85
 16:     14772512               0         1:07.42


 ４．対称解除法
     一つの解には、盤面を９０度、１８０度、２７０度回転、及びそれらの鏡像の合計
     ８個の対称解が存在する。対照的な解を除去し、ユニーク解から解を求める手法。
 
 ■ユニーク解の判定方法
   全探索によって得られたある１つの解が、回転・反転などによる本質的に変わること
 のない変換によって他の解と同型となるものが存在する場合、それを別の解とはしない
 とする解の数え方で得られる解を「ユニーク解」といいます。つまり、ユニーク解とは、
 全解の中から回転・反転などによる変換によって同型になるもの同士をグループ化する
 ことを意味しています。
 
   従って、ユニーク解はその「個数のみ」に着目され、この解はユニーク解であり、こ
 の解はユニーク解ではないという定まった判定方法はありません。ユニーク解であるか
 どうかの判断はユニーク解の個数を数える目的の為だけに各個人が自由に定義すること
 になります。もちろん、どのような定義をしたとしてもユニーク解の個数それ自体は変
 わりません。
 
   さて、Ｎクイーン問題は正方形のボードで形成されるので回転・反転による変換パター
 ンはぜんぶで８通りあります。だからといって「全解数＝ユニーク解数×８」と単純には
 いきません。ひとつのグループの要素数が必ず８個あるとは限らないのです。Ｎ＝５の
 下の例では要素数が２個のものと８個のものがあります。


 Ｎ＝５の全解は１０、ユニーク解は２なのです。
 
 グループ１: ユニーク解１つ目
--- Q-  - Q---
 Q----  ---- Q
-- Q--  -- Q--
---- Q   Q----
- Q---  --- Q-
 
 グループ２: ユニーク解２つ目
---- Q   Q----  -- Q--  -- Q--  --- Q-  - Q---   Q----  ---- Q
-- Q--  -- Q--   Q----  ---- Q  - Q---  --- Q-  --- Q-  - Q---
 Q----  ---- Q  --- Q-  - Q---  ---- Q   Q----  - Q---  --- Q-
--- Q-  - Q---  - Q---  --- Q-  -- Q--  -- Q--  ---- Q   Q----
- Q---  --- Q-  ---- Q   Q----   Q----  ---- Q  -- Q--  -- Q--

 
   それでは、ユニーク解を判定するための定義付けを行いますが、次のように定義する
 ことにします。各行のクイーンが右から何番目にあるかを調べて、最上段の行から下
 の行へ順番に列挙します。そしてそれをＮ桁の数値として見た場合に最小値になるもの
 をユニーク解として数えることにします。尚、このＮ桁の数を以後は「ユニーク判定値」
 と呼ぶことにします。
 
---- Q   0
-- Q--   2
 Q----   4  --->  0 2 4 1 3 (ユニーク判定値)
--- Q-   1
- Q---   3
 
 
   探索によって得られたある１つの解(オリジナル)がユニーク解であるかどうかを判定
 するには「８通りの変換を試み、その中でオリジナルのユニーク判定値が最小であるか
 を調べる」ことになります。しかし結論から先にいえば、ユニーク解とは成り得ないこ
 とが明確なパターンを探索中に切り捨てるある枝刈りを組み込むことにより、３通りの
 変換を試みるだけでユニーク解の判定が可能になります。
  
 
 ■ユニーク解の個数を求める
   先ず最上段の行のクイーンの位置に着目します。その位置が左半分の領域にあればユ
 ニーク解には成り得ません。何故なら左右反転によって得られるパターンのユニーク判
 定値の方が確実に小さくなるからです。また、Ｎが奇数の場合に中央にあった場合はど
 うでしょう。これもユニーク解には成り得ません。何故なら仮に中央にあった場合、そ
 れがユニーク解であるためには少なくとも他の外側の３辺におけるクイーンの位置も中
 央になければならず、それは互いの効き筋にあたるので有り得ません。


 ***********************************************************************
 最上段の行のクイーンの位置は中央を除く右側の領域に限定されます。(ただし、N ≧ 2)
 ***********************************************************************
 
   次にその中でも一番右端(右上の角)にクイーンがある場合を考えてみます。他の３つ
 の角にクイーンを置くことはできないので(効き筋だから）、ユニーク解であるかどうか
 を判定するには、右上角から左下角を通る斜軸で反転させたパターンとの比較だけになり
 ます。突き詰めれば、
 
 [上から２行目のクイーンの位置が右から何番目にあるか]
 [右から２列目のクイーンの位置が上から何番目にあるか]
 

 を比較するだけで判定することができます。この２つの値が同じになることはないからです。
 
       3 0
       ↓↓
---- Q ←0
- Q--- ←3
-----         上から２行目のクイーンの位置が右から４番目にある。
--- Q-         右から２列目のクイーンの位置が上から４番目にある。
-----         しかし、互いの効き筋にあたるのでこれは有り得ない。
 
   結局、再帰探索中において下図の X への配置を禁止する枝刈りを入れておけば、得
 られる解は総てユニーク解であることが保証されます。
 
---- X Q
- Q-- X-
---- X-
---- X-
------
------
 
   次に右端以外にクイーンがある場合を考えてみます。オリジナルがユニーク解である
 ためには先ず下図の X への配置は禁止されます。よって、その枝刈りを先ず入れておき
 ます。
 
 X X--- Q X X
 X------ X
--------
--------
--------
--------
 X------ X
 X X---- X X
 
   次にクイーンの利き筋を辿っていくと、結局、オリジナルがユニーク解ではない可能
 性があるのは、下図の A,B,C の位置のどこかにクイーンがある場合に限られます。従っ
 て、90度回転、180度回転、270度回転の３通りの変換パターンだけを調べれはよいこと
 になります。
 
 X X x x x Q X X
 X--- x x x X
 C-- x- x- x
-- x-- x--
- x--- x--
 x---- x- A
 X---- x- X
 X X B-- x X X


 ■ユニーク解から全解への展開
   これまでの考察はユニーク解の個数を求めるためのものでした。全解数を求めるには
 ユニーク解を求めるための枝刈りを取り除いて全探索する必要があります。したがって
 探索時間を犠牲にしてしまうことになります。そこで「ユニーク解の個数から全解数を
 導いてしまおう」という試みが考えられます。これは、左右反転によるパターンの探索
 を省略して最後に結果を２倍するというアイデアの拡張版といえるものです。そしてそ
 れを実現させるには「あるユニーク解が属するグループの要素数はいくつあるのか」と
 いう考察が必要になってきます。
 
   最初に、クイーンが右上角にあるユニーク解を考えます。斜軸で反転したパターンが
 オリジナルと同型になることは有り得ないことと(×２)、右上角のクイーンを他の３つの
 角に写像させることができるので(×４)、このユニーク解が属するグループの要素数は必
 ず８個(＝２×４)になります。
 
   次に、クイーンが右上角以外にある場合は少し複雑になりますが、考察を簡潔にする
 ために次の事柄を確認します。

 TOTAL=(COUNT8 * 8)+(COUNT4 * 4)+(COUNT2 * 2);
  (1)90度回転させてオリジナルと同型になる場合、さらに90度回転(オリジナルか
    ら180度回転)させても、さらに90度回転(オリジナルから270度回転)させてもオリ
    ジナルと同型になる。  

    COUNT2 * 2
 
  (2)90度回転させてオリジナルと異なる場合は、270度回転させても必ずオリジナ
    ルとは異なる。ただし、180度回転させた場合はオリジナルと同型になることも有
    り得る。 

    COUNT4 * 4
 
  (3)(1)に該当するユニーク解が属するグループの要素数は、左右反転させたパターンを
       加えて２個しかありません。(2)に該当するユニーク解が属するグループの要素数は、
       180度回転させて同型になる場合は４個(左右反転×縦横回転)、そして180度回転させても
       オリジナルと異なる場合は８個になります。(左右反転×縦横回転×上下反転)
 
    COUNT8 * 8 

   以上のことから、ひとつひとつのユニーク解が上のどの種類に該当するのかを調べる
 ことにより全解数を計算で導き出すことができます。探索時間を短縮させてくれる枝刈
 りを外す必要がなくなったというわけです。 
 
   UNIQUE  COUNT2     +  COUNT4     +  COUNT8
   TOTAL (COUNT2 * 2)+(COUNT4 * 4)+(COUNT8 * 8)

 　これらを実現すると、前回のNQueen3()よりも実行速度が遅くなります。
 　なぜなら、対称・反転・斜軸を反転するための処理が加わっているからです。
 ですが、今回の処理を行うことによって、さらにNQueen5()では、処理スピードが飛躍的に高速化されます。そのためにも今回のアルゴリズム実装は必要なのです。

実行結果
  N:        Total       Unique        dd:hh:mm:ss
   N:        Total       Unique        dd:hh:mm:ss
   2:            0               0      0 00:00:00
   3:            0               0      0 00:00:00
   4:            2               1      0 00:00:00
   5:           10               2      0 00:00:00
   6:            4               1      0 00:00:00
   7:           40               6      0 00:00:00
   8:           92              12      0 00:00:00
   9:          352              46      0 00:00:00
  10:          724              92      0 00:00:00
  11:         2680             341      0 00:00:00
  12:        14200            1787      0 00:00:00
  13:        73712            9233      0 00:00:00
  14:       365596           45752      0 00:00:02
  15:      2279184          285053      0 00:00:10
  16:     14772512         1846955      0 00:01:09


 * ５．枝刈りと最適化
 * 　単純ですのでソースのコメントを見比べて下さい。
 *   単純ではありますが、枝刈りの効果は絶大です。

   実行結果
   N:        Total       Unique        dd:hh:mm:ss
   2:            0               0      0 00:00:00
   3:            0               0      0 00:00:00
   4:            2               1      0 00:00:00
   5:           10               2      0 00:00:00
   6:            4               1      0 00:00:00
   7:           40               6      0 00:00:00
   8:           92              12      0 00:00:00
   9:          352              46      0 00:00:00
  10:          724              92      0 00:00:00
  11:         2680             341      0 00:00:00
  12:        14200            1787      0 00:00:00
  13:        73712            9233      0 00:00:00
  14:       365596           45752      0 00:00:00
  15:      2279184          285053      0 00:00:03
  16:     14772512         1846955      0 00:00:18
  17:     95815104        11977939      0 00:02:20


 ６．ビットマップ
   ビット演算を使って高速化 状態をビットマップにパックし、処理する
   単純なバックトラックよりも２０〜３０倍高速
 
 　ビットマップであれば、シフトにより高速にデータを移動できる。
  フラグ配列ではデータの移動にO(N)の時間がかかるが、ビットマップであればO(1)
  フラグ配列のように、斜め方向に 2*N-1の要素を用意するのではなく、Nビットで充
  分。

 　配置可能なビット列を flags に入れ、-flags & flags で順にビットを取り出し処理。
 　バックトラックよりも２０−３０倍高速。
 
 ===================
 考え方 1
 ===================

 　Ｎ×ＮのチェスボードをＮ個のビットフィールドで表し、ひとつの横列の状態をひと
 つのビットフィールドに対応させます。(クイーンが置いてある位置のビットをONに
 する)
 　そしてバックトラッキングは0番目のビットフィールドから「下に向かって」順にい
 ずれかのビット位置をひとつだけONにして進めていきます。

 
  - - - - - Q - -    00000100 0番目のビットフィールド
  - - - Q - - - -    00010000 1番目のビットフィールド
  - - - - - - Q -    00000010 2番目のビットフィールド
  Q - - - - - - -    10000000 3番目のビットフィールド
  - - - - - - - Q    00000001 4番目のビットフィールド
  - Q - - - - - -    01000000 5番目のビットフィールド
  - - - - Q - - -    00001000 6番目のビットフィールド
  - - Q - - - - -    00100000 7番目のビットフィールド


 ===================
 考え方 2
 ===================

 次に、効き筋をチェックするためにさらに３つのビットフィールドを用意します。

 1. 左下に効き筋が進むもの: left 
 2. 真下に効き筋が進むもの: down
 3. 右下に効き筋が進むもの: right

次に、斜めの利き筋を考えます。
 上図の場合、
 1列目の右斜め上の利き筋は 3 番目 (0x08)
 2列目の右斜め上の利き筋は 2 番目 (0x04) になります。
 この値は 0 列目のクイーンの位置 0x10 を 1 ビットずつ「右シフト」すれば求める
 ことができます。
 また、左斜め上の利き筋の場合、1 列目では 5 番目 (0x20) で 2 列目では 6 番目 (0x40)
になるので、今度は 1 ビットずつ「左シフト」すれば求めることができます。

つまり、右シフトの利き筋を right、左シフトの利き筋を left で表すことで、クイー
ンの効き筋はrightとleftを1 ビットシフトするだけで求めることができるわけです。

  *-------------
  | . . . . . .
  | . . . -3. .  0x02 -|
  | . . -2. . .  0x04  |(1 bit 右シフト right)
  | . -1. . . .  0x08 -|
  | Q . . . . .  0x10 ←(Q の位置は 4   down)
  | . +1. . . .  0x20 -| 
  | . . +2. . .  0x40  |(1 bit 左シフト left)  
  | . . . +3. .  0x80 -|
  *-------------
  図：斜めの利き筋のチェック

 n番目のビットフィールドからn+1番目のビットフィールドに探索を進めるときに、そ
 の３つのビットフィールドとn番目のビットフィールド(bit)とのOR演算をそれぞれ行
 います。leftは左にひとつシフトし、downはそのまま、rightは右にひとつシフトして
 n+1番目のビットフィールド探索に渡してやります。

 left : (left |bit)<<1
 right: (right|bit)>>1
 down :   down|bit


 ===================
 考え方 3
 ===================

   n+1番目のビットフィールドの探索では、この３つのビットフィールドをOR演算した
 ビットフィールドを作り、それがONになっている位置は効き筋に当たるので置くことが
 できない位置ということになります。次にその３つのビットフィールドをORしたビッ
 トフィールドをビット反転させます。つまり「配置可能なビットがONになったビットフィー
 ルド」に変換します。そしてこの配置可能なビットフィールドを bitmap と呼ぶとして、
 次の演算を行なってみます。
 
 bit = -bitmap & bitmap; //一番右のビットを取り出す
 
   この演算式の意味を理解するには負の値がコンピュータにおける２進法ではどのよう
 に表現されているのかを知る必要があります。負の値を２進法で具体的に表わしてみる
 と次のようになります。
 
  00000011   3
  00000010   2
  00000001   1
  00000000   0
  11111111  -1
  11111110  -2
  11111101  -3
 
   正の値nを負の値-nにするときは、nをビット反転してから+1されています。そして、
 例えばn=22としてnと-nをAND演算すると下のようになります。nを２進法で表したときの
 一番下位のONビットがひとつだけ抽出される結果が得られるのです。極めて簡単な演算
 によって1ビット抽出を実現させていることが重要です。
 
      00010110   22
  AND 11101010  -22
 ------------------
      00000010
 
   さて、そこで下のようなwhile文を書けば、このループは bitmap のONビットの数の
 回数だけループすることになります。配置可能なパターンをひとつずつ全く無駄がなく
 生成されることになります。
 
 while (bitmap) {
     bit = -bitmap & bitmap;
     bitmap ^= bit;
     //ここでは配置可能なパターンがひとつずつ生成される(bit) 
 }


  実行結果
   N:        Total       Unique        dd:hh:mm:ss
   2:            0               0      0 00:00:00
   3:            0               0      0 00:00:00
   4:            2               1      0 00:00:00
   5:           10               2      0 00:00:00
   6:            4               1      0 00:00:00
   7:           40               6      0 00:00:00
   8:           92              12      0 00:00:00
   9:          352              46      0 00:00:00
  10:          724              92      0 00:00:00
  11:         2680             341      0 00:00:00
  12:        14200            1787      0 00:00:00
  13:        73712            9233      0 00:00:00
  14:       365596           45752      0 00:00:01
  15:      2279184          285053      0 00:00:02
  16:     14772512         1846955      0 00:00:13


  ８．ビットマップ＋クイーンの場所で分岐

    実行結果
   N:        Total       Unique        dd:hh:mm:ss
   2:            0               0      0 00:00:00
   3:            0               0      0 00:00:00
   4:            2               1      0 00:00:00
   5:           10               2      0 00:00:00
   6:            4               1      0 00:00:00
   7:           40               6      0 00:00:00
   8:           92              12      0 00:00:00
   9:          352              46      0 00:00:00
  10:          724              92      0 00:00:00
  11:         2680             341      0 00:00:00
  12:        14200            1787      0 00:00:00
  13:        73712            9233      0 00:00:00
  14:       365596           45752      0 00:00:00
  15:      2279184          285053      0 00:00:02
  16:     14772512         1846955      0 00:00:13


  ９．ビットマップ＋枝刈りと最適化

  実行結果
   N:        Total       Unique        dd:hh:mm:ss
   2:            0               0      0 00:00:00
   3:            0               0      0 00:00:00
   4:            2               1      0 00:00:00
   5:           10               2      0 00:00:00
   6:            4               1      0 00:00:00
   7:           40               6      0 00:00:00
   8:           92              12      0 00:00:00
   9:          352              46      0 00:00:00
  10:          724              92      0 00:00:00
  11:         2680             341      0 00:00:00
  12:        14200            1787      0 00:00:00
  13:        73664            9227      0 00:00:00
  14:       365492           45739      0 00:00:00
  15:      2278664          284988      0 00:00:00
  16:     14768296         1846428      0 00:00:02
  17:     95795792        11975525      0 00:00:14


  １０．もっとビットマップ(takaken版) すごく速い！
  実行結果
   N:           Total          Uniquei  days hh:mm:ss.--
   5:          10               2             0.00
   6:           4               1             0.00
   7:          40               6             0.00
   8:          92              12             0.00
   9:         352              46             0.00
  10:         724              92             0.00
  11:        2680             341             0.00
  12:       14200            1787             0.00
  13:       73712            9233             0.01
  14:      365596           45752             0.04
  15:     2279184          285053             0.26
  16:    14772512         1846955             1.70
  17:    95815104        11977939            11.69
  18:   666090624        83263591          1:24.96


  11.マルチスレッド（構造体）
  実行結果 9と同じ。 N16:02 N17:14

  12.マルチスレッド（pthread)
  実行結果 9と同じ   N16:02 N17:14

  13.マルチスレッド（排他処理 mutex）
  実行結果 9と同じ   N16:02 N17:14

  14．C版マルチスレッド(join) 
  実行結果 
   N:           Total          Uniquei  days hh:mm:ss.--
  14:          365596            45752              0.01
  15:         2279184           285053              0.10
  16:        14772512          1846955              0.62
  17:        95815104         11977939              3.80
  18:       666090624         83263591             28.62
  19:      4968057848        621012754          03:44.91


  参考（Bash版 07_8NQueen.lua）
  10:             724               92                 0
  11:            2680              341                 3
  12:           14200             1787                18
  13:           73712             9233                99
  14:          365596            45752               573
  15:         2279184           285053              3511

  参考（Lua版 07_8NQueen.lua）
  14:          365596            45752          00:00:00
  15:         2279184           285053          00:00:03
  16:        14772512          1846955          00:00:20

  参考（Java版 NQueen8.java マルチスレット）
  16:        14772512          1846955          00:00:00
  17:        95815104         11977939          00:00:04
  18:       666090624         83263591          00:00:34
  19:      4968057848        621012754          00:04:18
  20:     39029188884       4878666808          00:35:07
  21:    314666222712      39333324973          04:41:36
  22:   2691008701644     336376244042          39:14:59


 *
*/

#include<stdio.h>
#include<time.h>
#include <math.h>
#include "pthread.h"
#define MAXSIZE 27

// pthreadはパラメータを１つしか渡せないので構造体に格納
/** スレッドローカル構造体 */
struct local{
  int BOUND1;
  int BOUND2;
  int TOPBIT;
  int ENDBIT;
  int MASK;
  int SIDEMASK;
  int LASTMASK;
  int aBoard[MAXSIZE];
  int SIZE;
  int SIZEE;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

pthread_mutex_t mutex;
pthread_cond_t cond;
//グローバル構造体
typedef struct {
  int SIZE; //SIZEはスレッドローカルにコピーします。
  int SIZEE;//SIZEEはスレッドローカルにコピーします。
  long COUNT2;
  long COUNT4;
  long COUNT8;
}GCLASS, *GClass;
GCLASS G; //グローバル構造体

/** 時刻のフォーマット変換 */
void TimeFormat(clock_t utime,char *form){
  int dd,hh,mm;
  float ftime,ss;
  //ftime=(float)utime/CLOCKS_PER_SEC;
  ftime=(float)utime/CLOCKS_PER_SEC;
  mm=(int)ftime/60;
  ss=ftime-(int)(mm*60);
  dd=mm/(24*60);
  mm=mm%(24*60);
  hh=mm/60;
  mm=mm%60;
  sprintf(form,"%7d %02d:%02d:%02.0f",dd,hh,mm,ss);
}

/** ユニーク解のset */
void setCount(long C2,long C4,long C8,pthread_mutex_t mutex){
  pthread_mutex_lock(&mutex);
  G.COUNT2+=C2;
  G.COUNT4+=C4;
  G.COUNT8+=C8;
  pthread_mutex_unlock(&mutex);
}

/** ユニーク解のget */
long getUnique(){ 
  long sum=G.COUNT2+G.COUNT4+G.COUNT8;
  return sum;
}

/** 総合計のget */
long getTotal(){ 
  long sum= G.COUNT2*2+G.COUNT4*4+G.COUNT8*8;
  return sum;
}
/**********************************************/
/** 対称解除法                               **/
/** ユニーク解から全解への展開               **/
/**********************************************/
/**
ひとつの解には、盤面を90度・180度・270度回転、及びそれらの鏡像の合計8個の対称解が存在する

    １２ ４１ ３４ ２３
    ４３ ３２ ２１ １４

    ２１ １４ ４３ ３２
    ３４ ２３ １２ ４１
    
上図左上がユニーク解。
1行目はユニーク解を90度、180度、270度回転したもの
2行目は1行目のそれぞれを左右反転したもの。
2行目はユニーク解を左右反転、対角反転、上下反転、逆対角反転したものとも解釈可 
ただし、 回転・線対称な解もある
**/
/**
クイーンが右上角にあるユニーク解を考えます。
斜軸で反転したパターンがオリジナルと同型になることは有り得ないことと(×２)、
右上角のクイーンを他の３つの角に写像させることができるので(×４)、
このユニーク解が属するグループの要素数は必ず８個(＝２×４)になります。

(1) 90度回転させてオリジナルと同型になる場合、さらに90度回転(オリジナルから180度回転)
　　させても、さらに90度回転(オリジナルから270度回転)させてもオリジナルと同型になる。 
(2) 90度回転させてオリジナルと異なる場合は、270度回転させても必ずオリジナルとは異なる。
　　ただし、180度回転させた場合はオリジナルと同型になることも有り得る。

　(1)に該当するユニーク解が属するグループの要素数は、左右反転させたパターンを加えて
２個しかありません。(2)に該当するユニーク解が属するグループの要素数は、180度回転させ
て同型になる場合は４個(左右反転×縦横回転)、そして180度回転させてもオリジナルと異なる
場合は８個になります。(左右反転×縦横回転×上下反転)
*/
void symmetryOps_bitmap(int bitmap,int BOUND1,int BOUND2,
    int TOPBIT,int ENDBIT,int aBoard[],int SIZEE,pthread_mutex_t mutex,pthread_cond_t cond){
  int own,ptn,you,bit;
  //90度回転
  if(aBoard[BOUND2]==1){ 
    pthread_mutex_lock(&mutex);
    own=1; ptn=2;
    pthread_mutex_unlock(&mutex);
    while(own<=SIZEE){ 
      pthread_mutex_lock(&mutex);
        bit=1; 
        you=SIZEE;
      pthread_mutex_unlock(&mutex);
      while((aBoard[you]!=ptn)&&(aBoard[own]>=bit)){ 
        pthread_mutex_lock(&mutex);
          bit<<=1; 
          you--; 
        pthread_mutex_unlock(&mutex);
      }
      if(aBoard[own]>bit){ return; } 
      if(aBoard[own]<bit){ break; }
      pthread_mutex_lock(&mutex);
        own++; 
        ptn<<=1;
      pthread_mutex_unlock(&mutex);
    }
    /** 90度回転して同型なら180度/270度回転も同型である */
    if(own>SIZEE){ 
      //COUNT2++; 
      setCount(1,0,0,mutex);
      return; }
  }
  //180度回転
  //if(aBoard[SIZEE]==ENDBIT){ own=1; you=SIZEE-1;
  if(bitmap==ENDBIT){ 
    pthread_mutex_lock(&mutex);
      own=1; 
      you=SIZEE-1;
    pthread_mutex_unlock(&mutex);
    while(own<=SIZEE){ 
      pthread_mutex_lock(&mutex);
        bit=1; ptn=TOPBIT;
      pthread_mutex_unlock(&mutex);
      while((aBoard[you]!=ptn)&&(aBoard[own]>=bit)){ 
        pthread_mutex_lock(&mutex);
          bit<<=1; 
          ptn>>=1; 
        pthread_mutex_unlock(&mutex);
      }
      if(aBoard[own]>bit){ return; } 
      if(aBoard[own]<bit){ break; }
      pthread_mutex_lock(&mutex);
        own++; 
        you--;
      pthread_mutex_unlock(&mutex);
    }
    /** 90度回転が同型でなくても180度回転が同型である事もある */
    if(own>SIZEE){ 
      //COUNT4++; 
      setCount(0,1,0,mutex);
      return; 
    }
  }
  //270度回転
  if(aBoard[BOUND1]==TOPBIT){ 
    pthread_mutex_lock(&mutex);
      own=1; 
      ptn=TOPBIT>>1;
    pthread_mutex_unlock(&mutex);
    while(own<=SIZEE){ 
      pthread_mutex_lock(&mutex);
        bit=1; 
        you=0;
      pthread_mutex_unlock(&mutex);
      while((aBoard[you]!=ptn)&&(aBoard[own]>=bit)){ 
        pthread_mutex_lock(&mutex);
          bit<<=1; 
          you++; 
        pthread_mutex_unlock(&mutex);
      }
      if(aBoard[own]>bit){ return; } 
      if(aBoard[own]<bit){ break; }
      pthread_mutex_lock(&mutex);
        own++; 
        ptn>>=1;
      pthread_mutex_unlock(&mutex);
    }
  }
  //COUNT8++;
  setCount(0,0,1,mutex);
}
/**********************************************/
/* 最上段行のクイーンが角以外にある場合の探索 */
/**********************************************/
/**
１行目角にクイーンが無い場合、クイーン位置より右位置の８対称位置にクイーンを
置くことはできない
１行目位置が確定した時点で、配置可能位置を計算しておく（☓の位置）
lt, dn, lt 位置は効きチェックで配置不可能となる
回転対称チェックが必要となるのは、クイーンがａ, ｂ, ｃにある場合だけなので、 
90度、180度、270度回転した状態のユニーク判定値との比較を行うだけで済む

【枝刈り図】
  x x - - - Q x x    
  x - - - / | ＼x    
  c - - / - | -rt    
  - - / - - | - -    
  - / - - - | - -    
  lt- - - - | - a    
  x - - - - | - x    
  x x b - - dnx x    
*/
//void backTrack2(int y,int left,int down,int right){
void backTrack2(int y,int left,int down,int right,
    int BOUND1,int BOUND2,int MASK,int SIDEMASK,int LASTMASK,
    int TOPBIT,int ENDBIT,int aBoard[],int SIZE,int SIZEE,pthread_mutex_t mutex,pthread_cond_t cond){
  //配置可能フィールド
  pthread_mutex_lock(&mutex);
    int bitmap=MASK&~(left|down|right); 
  pthread_mutex_unlock(&mutex);
  int bit=0;
  if(y==SIZEE){
    if(bitmap!=0){
      if( (bitmap&LASTMASK)==0){ //【枝刈り】最下段枝刈り
        pthread_mutex_lock(&mutex);
          aBoard[y]=bitmap;
        pthread_mutex_unlock(&mutex);
        //対称解除法
        symmetryOps_bitmap(bitmap,BOUND1,BOUND2,TOPBIT,ENDBIT,aBoard,SIZEE,mutex,cond); 
      }
    }
  }else{
    if(y<BOUND1){             //【枝刈り】上部サイド枝刈り
      pthread_mutex_lock(&mutex);
        bitmap&=~SIDEMASK; 
      pthread_mutex_unlock(&mutex);
      // bitmap|=SIDEMASK; 
      // bitmap^=SIDEMASK;(bitmap&=~SIDEMASKと同等)
    }else if(y==BOUND2) {     //【枝刈り】下部サイド枝刈り
      if((down&SIDEMASK)==0){ return; }
      if((down&SIDEMASK)!=SIDEMASK){ 
        pthread_mutex_lock(&mutex);
          bitmap&=SIDEMASK; 
        pthread_mutex_unlock(&mutex);
      }
    }
    while(bitmap!=0) {
      //最も下位の１ビットを抽出
      pthread_mutex_lock(&mutex);
        bitmap^=aBoard[y]=bit=-bitmap&bitmap;
      pthread_mutex_unlock(&mutex);
      //backTrack2(y+1,(left|bit)<<1,down|bit,(right|bit)>>1);
      backTrack2(y+1,(left|bit)<<1,down|bit,(right|bit)>>1,
          BOUND1,BOUND2,MASK,SIDEMASK,LASTMASK,
          TOPBIT,ENDBIT,aBoard,SIZE,SIZEE,mutex,cond);
    }
  }
}
/**********************************************/
/* 最上段行のクイーンが角にある場合の探索     */
/**********************************************/
/* 
１行目角にクイーンがある場合、回転対称形チェックを省略することが出来る
１行目角にクイーンがある場合、他の角にクイーンを配置することは不可
鏡像についても、主対角線鏡像のみを判定すればよい
２行目、２列目を数値とみなし、２行目＜２列目という条件を課せばよい 
*/
//void backTrack1(int y,int left,int down,int right,void *args){
void backTrack1(int y,int left,int down,int right,
    int BOUND1,int BOUND2,int MASK,int SIDEMASK,int LASTMASK,
    int TOPBIT,int ENDBIT,int aBoard[],int SIZE,int SIZEE,pthread_mutex_t mutex,pthread_cond_t cond){
  //配置可能フィールド
  int bit;
  pthread_mutex_lock(&mutex);
    int bitmap=MASK&~(left|down|right); 
  pthread_mutex_unlock(&mutex);
  if(y==SIZEE) {
    if(bitmap!=0){
      pthread_mutex_lock(&mutex);
        aBoard[y]=bitmap;
      pthread_mutex_unlock(&mutex);
      //【枝刈り】１行目角にクイーンがある場合回転対称チェックを省略
      setCount(0,0,1,mutex);
    }
  }else{
    if(y<BOUND1) {   
      //【枝刈り】鏡像についても主対角線鏡像のみを判定すればよい
      // ２行目、２列目を数値とみなし、２行目＜２列目という条件を課せばよい
      pthread_mutex_lock(&mutex);
        bitmap&=~2; 
      // bitmap|=2; 
      // bitmap^=2; //(bitmap&=~2と同等)
      pthread_mutex_unlock(&mutex);
    }
    while(bitmap!=0) {
      //最も下位の１ビットを抽出
      pthread_mutex_lock(&mutex);
        bitmap^=aBoard[y]=bit=(-bitmap&bitmap);
      pthread_mutex_unlock(&mutex);
      //backTrack1(y+1,(left|bit)<<1,down|bit,(right|bit)>>1,&l);
      backTrack1(y+1,(left|bit)<<1,down|bit,(right|bit)>>1,
          BOUND1,BOUND2,MASK,SIDEMASK,LASTMASK,
          TOPBIT,ENDBIT,aBoard,SIZE,SIZEE,mutex,cond);
    }
  } 
}
void *run(void *args){
  struct local *l=(struct local *)args;
   // pthread_mutex_t mutex=l->mutex;
   // pthread_cond_t cond=l->cond;

    int bit ;
    int SIZEE=l->SIZEE;
    int SIZE=l->SIZE;
    int aBoard[MAXSIZE]; aBoard[0]=1;
    int BOUND1=l->BOUND1;
    int BOUND2=l->BOUND2;
    int MASK=(1<<l->SIZE)-1;
    int SIDEMASK=l->SIDEMASK;
    int LASTMASK=l->LASTMASK;
    int TOPBIT=1<<l->SIZEE;
    int ENDBIT=l->ENDBIT;

  // 最上段のクイーンが角にある場合の探索
  if(BOUND1>1 && BOUND1<SIZEE) { 
    // 角にクイーンを配置 
    aBoard[1]=(1<<BOUND1);
    bit=(1<<BOUND1);
    //
    //２行目から探索
    backTrack1(2,(2|bit)<<1,(1|bit),(bit>>1),
        BOUND1,BOUND2,MASK,SIDEMASK,LASTMASK,
        TOPBIT,ENDBIT,aBoard,SIZE,SIZEE,mutex,cond);
  }
  ENDBIT=(TOPBIT>>BOUND1);
  SIDEMASK=(TOPBIT|1);
  LASTMASK=(TOPBIT|1);
  /* 最上段行のクイーンが角以外にある場合の探索 
     ユニーク解に対する左右対称解を予め削除するには、
     左半分だけにクイーンを配置するようにすればよい */
  if(BOUND1>0 && BOUND2<SIZE-1 && BOUND1<BOUND2){ 
    for(int i=1; i<BOUND1; i++){
      LASTMASK=LASTMASK|LASTMASK>>1|LASTMASK<<1;
    }
    if(BOUND1<BOUND2) {
      aBoard[0]=bit=(1<<BOUND1);
      backTrack2(1,bit<<1,bit,bit>>1,
          BOUND1,BOUND2,MASK,SIDEMASK,LASTMASK,
          TOPBIT,ENDBIT,aBoard,SIZE,SIZEE,mutex,cond);
    }
    //ENDBIT>>1;
    ENDBIT>>=SIZE;
  }
  return 0;
}
/**********************************************/
/* マルチスレッド　排他処理                   */
/**********************************************/
/**
 * マルチスレッド pthreadには排他処理をします。
   まずmutexの宣言は以下の通りです。

      pthread_mutex_t mutex;   // mutexの宣言

 * さらにmutexは以下の方法のいずれかで初期化します。
    pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;//mutexの初期化
    pthread_mutex_init(&mutex, NULL);     //pthread 排他処理
 
 * 実行部分は以下のようにロックとロック解除で処理を挟みます。
      pthread_mutex_lock(&mutex);     //ロックの開始
      setCount(0,0,1);                //保護されている処理
      pthread_mutex_unlock(&mutex);   //ロックの終了
 *
  使い終わったら破棄します。
    pthread_mutex_destroy(&mutex);        //nutexの破棄
 *
 */
void *NQueenThread( void *args){
  struct local l[MAXSIZE];              //構造体 local型 
  int SIZE=*(int *)args;
  int SIZEE=SIZE-1;
  pthread_t cth[SIZE];                //スレッド childThread
  /**
   *
   * N=8の場合は8つのスレッドがおのおののrowを担当し処理を行います。

        メインスレッド  N=8
            +--BOUND1=7----- run()
            +--BOUND1=6----- run()
            +--BOUND1=5----- run()
            +--BOUND1=4----- run()
            +--BOUND1=3----- run()
            +--BOUND1=2----- run()
            +--BOUND1=1----- run()
            +--BOUND1=0----- run()
    
   * そこで、それぞれのスレッド毎にスレッドローカルな構造体を持ちます。
   *
        // スレッドローカル構造体 
        struct local{
          int bit;
          int BOUND1;
          int BOUND2;
          int TOPBIT;
          int ENDBIT;
          int MASK;
          int SIDEMASK;
          int LASTMASK;
          int aBoard[MAXSIZE];
        };
   * 
   * スレッドローカルな構造体の宣言は以下の通りです。
   *
   *    //スレッドローカルな構造体
   *    struct local l[MAXSIZE];
   *
   * アクセスはグローバル構造体同様 . ドットでアクセスします。
        l[BOUND1].BOUND1=BOUND1;
        l[BOUND1].BOUND2=BOUND2;
   *
   */
  // スレッドローカルな構造体
  G.COUNT2=0;
  G.COUNT4=0;
  G.COUNT8=0;
  // BOUND1から順にスレッドを生成しながら処理を分担する 
  for(int BOUND1=SIZEE,BOUND2=0;BOUND2<SIZEE;BOUND1--,BOUND2++){
    //初期化
    // pthread_mutex_init(&l[BOUND1].mutex, NULL);
    pthread_mutex_init(&mutex, NULL);
    // pthread_cond_init(&l[BOUND1].cond,NULL);
    // pthread_mutex_lock(&l[BOUND1].mutex);
    pthread_mutex_lock(&mutex);
    l[BOUND1].BOUND1=BOUND1; 
    l[BOUND1].BOUND2=BOUND2;
    l[BOUND1].SIZE=SIZE;
    l[BOUND1].SIZEE=SIZEE;
    l[BOUND1].TOPBIT=0;
    l[BOUND1].ENDBIT=0;
    l[BOUND1].MASK=0;
    l[BOUND1].SIDEMASK=0;
    l[BOUND1].LASTMASK=0;
    for(int j=0;j<SIZE;j++){ l[BOUND1].aBoard[j]=j; } 
    pthread_mutex_unlock(&mutex);
    // pthread_mutex_unlock(&l[BOUND1].mutex);
    //ここまで初期化
    
    // チルドスレッドの生成
    int iFbRet=pthread_create(&cth[BOUND1],NULL,run, (void *) &l[BOUND1]);
    if(iFbRet>0){
      printf("[mainThread] pthread_create #%d: %d\n", l[BOUND1].BOUND1, iFbRet);
    }
    //処理を待って次の処理へ
    //以下をコメントアウトすることによってBOUND1の順次処理の度にjoinせずに並行処理する
    //コメントを外すとシングルスレッドになります。
    //pthread_join(cth[BOUND1],NULL);  
  }
  for(int i=SIZEE;i>0;i--){
    pthread_join(cth[i],NULL);//処理が終わったら 全ての処理をjoinする
    pthread_mutex_destroy(&l[i].mutex); //nutexの破棄       
  }
  return 0;
}
/**********************************************/
/*  マルチスレッド pthread                    */
/**********************************************/
/**
 *  マルチスレッドには pthreadを使います。
 *  pthread を宣言するには pthread_t 型の変数を宣言します。
 *
      pthread_t tId;  //スレッド変数
    
    スレッドを生成するには pthread_create()を呼び出します。
    戻り値iFbRetにはスレッドの状態が格納されます。正常作成は0になります。
    pthread_join()はスレッドの終了を待ちます。
 */
void NQueen(int SIZE){
  pthread_t pth;  //スレッド変数
  // メインスレッドの生成
  int iFbRet = pthread_create(&pth, NULL, NQueenThread,(void *) &SIZE);
  if(iFbRet>0){
    printf("[main] pthread_create: %d\n", iFbRet); //エラー出力デバッグ用
  }
  pthread_join(pth, NULL); //スレッドの終了を待つ
}
/**********************************************/
/*  メイン関数                                */
/**********************************************/
/**
 * N=2 から順を追って 実行関数 NQueen()を呼び出します。
 * 最大値は 先頭行でMAXSIZEをdefineしています。
 * G は グローバル構造体で宣言しています。

    //グローバル構造体
    typedef struct {
      int nThread;
      int SIZE;
      int SIZEE;
      long COUNT2;
      long COUNT4;
      long COUNT8;
    }GCLASS, *GClass;
    GCLASS G; //グローバル構造体

グローバル構造体を使う場合は
  G.SIZE=i ; 
  のようにドットを使ってアクセスします。
 
  NQueen()実行関数は forの中の値iがインクリメントする度に
  Nのサイズが大きくなりクイーンの数を解法します。 
 */
#include <time.h>
#include <sys/time.h>
int main(void){
  clock_t st;  // 計測開始時刻
  char t[20];  // 計測結果出力
  printf("%s\n"," N:        Total       Unique           hh:mm:ss.ms");
  struct timeval t0;
  struct timeval t1;
  for(int i=2;i<=MAXSIZE;i++){
  //for(int i=12;i<=12;i++){
    st=clock();   // 計測開始

    //マルチスレッドの場合、これまでの計測方法ではマルチコアで処理される
    //全てのスレッドの処理時間の合計となるため、gettimeofday()で計測する
    gettimeofday(&t0, NULL);
    NQueen(i);     // 実行関数
    gettimeofday(&t1, NULL);
    int ss,ms;
    if (t1.tv_usec < t0.tv_usec) {
      ss=(t1.tv_sec-t0.tv_sec-1)%86400;
      ms=(1000000+t1.tv_usec-t0.tv_usec+500)/10000;
    }
    else {
      ss=(t1.tv_sec-t0.tv_sec)%86400;
      ms=(t1.tv_usec - t0.tv_usec+500)/10000;
    }
    int hh=ss/3600;
    int mm=(ss-hh*3600)/60;
    ss%=60;
    printf("%2d:%13ld%16ld%10.4d:%02d:%02d.%02d\n", i,getTotal(),getUnique(),hh,mm,ss,ms); 
  } 
}

