#!/bin/bash
#
#
# Bash（シェルスクリプト）で学ぶ「アルゴリズムとデータ構造」
# 一般社団法人  共同通信社  情報技術局  鈴木  維一郎(suzuki.iichiro@kyodonews.jp)
#
#
# ---------------------------------------------------------------------------------
# ４．バックトラック＋対象解除法
# 
# 　一つの解には、盤面を９０度、１８０度、２７０度回転、及びそれらの鏡像の合計
# 　８個の対称解が存在する。対照的な解を除去し、ユニーク解から解を求める手法。
# 
# ■ユニーク解の判定方法
#   全探索によって得られたある１つの解が、回転・反転などによる本質的に変わること
# のない変換によって他の解と同型となるものが存在する場合、それを別の解とはしない
# とする解の数え方で得られる解を「ユニーク解」といいます。つまり、ユニーク解とは、
# 全解の中から回転・反転などによる変換によって同型になるもの同士をグループ化する
# ことを意味しています。
# 
#   従って、ユニーク解はその「個数のみ」に着目され、この解はユニーク解であり、こ
# の解はユニーク解ではないという定まった判定方法はありません。ユニーク解であるか
# どうかの判断はユニーク解の個数を数える目的の為だけに各個人が自由に定義すること
# になります。もちろん、どのような定義をしたとしてもユニーク解の個数それ自体は変
# わりません。
# 
#   さて、Ｎクイーン問題は正方形のボードで形成されるので回転・反転による変換パター
# ンはぜんぶで８通りあります。だからといって「全解数＝ユニーク解数×８」と単純には
# いきません。ひとつのグループの要素数が必ず８個あるとは限らないのです。Ｎ＝５の
# 下の例では要素数が２個のものと８個のものがあります。
#
#
# Ｎ＝５の全解は１０、ユニーク解は２なのです。
# 
# グループ１: ユニーク解１つ目
# - - - Q -   - Q - - -
# Q - - - -   - - - - Q
# - - Q - -   - - Q - -
# - - - - Q   Q - - - -
# - Q - - -   - - - Q -
# 
# グループ２: ユニーク解２つ目
# - - - - Q   Q - - - -   - - Q - -   - - Q - -   - - - Q -   - Q - - -   Q - - - -   - - - - Q
# - - Q - -   - - Q - -   Q - - - -   - - - - Q   - Q - - -   - - - Q -   - - - Q -   - Q - - -
# Q - - - -   - - - - Q   - - - Q -   - Q - - -   - - - - Q   Q - - - -   - Q - - -   - - - Q -
# - - - Q -   - Q - - -   - Q - - -   - - - Q -   - - Q - -   - - Q - -   - - - - Q   Q - - - -
# - Q - - -   - - - Q -   - - - - Q   Q - - - -   Q - - - -   - - - - Q   - - Q - -   - - Q - -
#
# 
#   それでは、ユニーク解を判定するための定義付けを行いますが、次のように定義する
# ことにします。各行のクイーンが右から何番目にあるかを調べて、最上段の行から下
# の行へ順番に列挙します。そしてそれをＮ桁の数値として見た場合に最小値になるもの
# をユニーク解として数えることにします。尚、このＮ桁の数を以後は「ユニーク判定値」
# と呼ぶことにします。
# 
# - - - - Q   0
# - - Q - -   2
# Q - - - -   4   --->  0 2 4 1 3  (ユニーク判定値)
# - - - Q -   1
# - Q - - -   3
# 
# 
#   探索によって得られたある１つの解(オリジナル)がユニーク解であるかどうかを判定
# するには「８通りの変換を試み、その中でオリジナルのユニーク判定値が最小であるか
# を調べる」ことになります。しかし結論から先にいえば、ユニーク解とは成り得ないこ
# とが明確なパターンを探索中に切り捨てるある枝刈りを組み込むことにより、３通りの
# 変換を試みるだけでユニーク解の判定が可能になります。
#  
# 
# ■ユニーク解の個数を求める
#   先ず最上段の行のクイーンの位置に着目します。その位置が左半分の領域にあればユ
# ニーク解には成り得ません。何故なら左右反転によって得られるパターンのユニーク判
# 定値の方が確実に小さくなるからです。また、Ｎが奇数の場合に中央にあった場合はど
# うでしょう。これもユニーク解には成り得ません。何故なら仮に中央にあった場合、そ
# れがユニーク解であるためには少なくとも他の外側の３辺におけるクイーンの位置も中
# 央になければならず、それは互いの効き筋にあたるので有り得ません。
#
#  ***********************************************************************
#  最上段の行のクイーンの位置は中央を除く右側の領域に限定されます。(ただし、N ≧ 2)
#  ***********************************************************************
#  
#    次にその中でも一番右端(右上の角)にクイーンがある場合を考えてみます。他の３つ
#  の角にクイーンを置くことはできないので(効き筋だから）、ユニーク解であるかどうか
#  を判定するには、右上角から左下角を通る斜軸で反転させたパターンとの比較だけになり
#  ます。突き詰めれば、
#  
#  [上から２行目のクイーンの位置が右から何番目にあるか]
#  [右から２列目のクイーンの位置が上から何番目にあるか]
#  
# 
#  を比較するだけで判定することができます。この２つの値が同じになることはないからです。
#  
#        3 0
#        ↓↓
#  - - - - Q ←0
#  - Q - - - ←3
#  - - - - -         上から２行目のクイーンの位置が右から４番目にある。
#  - - - Q -         右から２列目のクイーンの位置が上から４番目にある。
#  - - - - -         しかし、互いの効き筋にあたるのでこれは有り得ない。
#  
#    結局、再帰探索中において下図の X への配置を禁止する枝刈りを入れておけば、得
#  られる解は総てユニーク解であることが保証されます。
#  
#  - - - - X Q
#  - Q - - X -
#  - - - - X -
#  - - - - X -
#  - - - - - -
#  - - - - - -
#  
#    次に右端以外にクイーンがある場合を考えてみます。オリジナルがユニーク解である
#  ためには先ず下図の X への配置は禁止されます。よって、その枝刈りを先ず入れておき
#  ます。
#  
#  X X - - - Q X X
#  X - - - - - - X
#  - - - - - - - -
#  - - - - - - - -
#  - - - - - - - -
#  - - - - - - - -
#  X - - - - - - X
#  X X - - - - X X
#  
#    次にクイーンの利き筋を辿っていくと、結局、オリジナルがユニーク解ではない可能
#  性があるのは、下図の A,B,C の位置のどこかにクイーンがある場合に限られます。従っ
#  て、90度回転、180度回転、270度回転の３通りの変換パターンだけを調べれはよいこと
#  になります。
#  
#  X X x x x Q X X
#  X - - - x x x X
#  C - - x - x - x
#  - - x - - x - -
#  - x - - - x - -
#  x - - - - x - A
#  X - - - - x - X
#  X X B - - x X X
# 
# 
#  ■ユニーク解から全解への展開
#    これまでの考察はユニーク解の個数を求めるためのものでした。全解数を求めるには
#  ユニーク解を求めるための枝刈りを取り除いて全探索する必要があります。したがって
#  探索時間を犠牲にしてしまうことになります。そこで「ユニーク解の個数から全解数を
#  導いてしまおう」という試みが考えられます。これは、左右反転によるパターンの探索
#  を省略して最後に結果を２倍するというアイデアの拡張版といえるものです。そしてそ
#  れを実現させるには「あるユニーク解が属するグループの要素数はいくつあるのか」と
#  いう考察が必要になってきます。
#  
#    最初に、クイーンが右上角にあるユニーク解を考えます。斜軸で反転したパターンが
#  オリジナルと同型になることは有り得ないことと(×２)、右上角のクイーンを他の３つの
#  角に写像させることができるので(×４)、このユニーク解が属するグループの要素数は必
#  ず８個(＝２×４)になります。
#  
#    次に、クイーンが右上角以外にある場合は少し複雑になりますが、考察を簡潔にする
#  ために次の事柄を確認します。
# 
#  TOTAL = (COUNT8 * 8) + (COUNT4 * 4) + (COUNT2 * 2);
#    (1) 90度回転させてオリジナルと同型になる場合、さらに90度回転(オリジナルか
#     ら180度回転)させても、さらに90度回転(オリジナルから270度回転)させてもオリ
#     ジナルと同型になる。  
# 
#     COUNT2 * 2
#  
#    (2) 90度回転させてオリジナルと異なる場合は、270度回転させても必ずオリジナ
#     ルとは異なる。ただし、180度回転させた場合はオリジナルと同型になることも有
#     り得る。 
# 
#     COUNT4 * 4
#  
#    (3) (1) に該当するユニーク解が属するグループの要素数は、左右反転させたパターンを
#        加えて２個しかありません。(2)に該当するユニーク解が属するグループの要素数は、
#        180度回転させて同型になる場合は４個(左右反転×縦横回転)、そして180度回転させても
#        オリジナルと異なる場合は８個になります。(左右反転×縦横回転×上下反転)
#  
#     COUNT8 * 8 
# 
#    以上のことから、ひとつひとつのユニーク解が上のどの種類に該当するのかを調べる
#  ことにより全解数を計算で導き出すことができます。探索時間を短縮させてくれる枝刈
#  りを外す必要がなくなったというわけです。 
#  
#    UNIQUE  COUNT2      +  COUNT4      +  COUNT8
#    TOTAL  (COUNT2 * 2) + (COUNT4 * 4) + (COUNT8 * 8)
# 
#  　これらを実現すると、前回のNQueen3()よりも実行速度が遅くなります。
#  　なぜなら、対称・反転・斜軸を反転するための処理が加わっているからです。
#  ですが、今回の処理を行うことによって、さらにNQueen5()では、処理スピードが飛
#  躍的に高速化されます。そのためにも今回のアルゴリズム実装は必要なのです。
#
# 実行結果
# N-Queen4 : バックトラック＋対称解除法
#  N:        Total       Unique        hh:mm:ss
#  2:            0            0         0:00:00
#  3:            0            0         0:00:00
#  4:            2            1         0:00:00
#  5:           10            2         0:00:01
#  6:            4            1         0:00:00
#  7:           40            6         0:00:00
#  8:           92           12         0:00:01
#  9:          352           46         0:00:05
# 10:          724           92         0:00:16
# 11:         2680          341         0:01:14
# 12:        14200         1787         0:06:48
#
#
# グローバル変数は大文字
typeset -i TOTAL=0;
typeset -i UNIQUE=0;
typeset -a flag_a="";     # -a は配列の型を宣言します
typeset -a flag_b="";
typeset -a flag_c="";
typeset -a trial="";
typeset -a board="";
typeset -a scratch="";
#
function intncmp(){
  local -i k; 
  local -i rtn=0;
  local -i n=$1;
  for((k=0;k<n;k++)){
    rtn=$((board[k]-trial[k]));
    ((rtn!=0))&&{ break; }
  }
  echo "$rtn";
}
#
function rotate() {
  local -i j;
  local -i k;
  local -i n=$1;
  local -i incr;
  local neg=$2;
  if [ "$neg" = "true" ];then
    k=0;
  else
    k=$((n-1)); 
  fi 
  if [ "$neg" = "true" ];then
    incr=$((incr+1));
  else
    incr=$((incr-1));
  fi 
  for((j=0;j<n;k+=incr)){ 
    j=$((j+1))
    scratch[$j]=${trial[$k]};
  }
  if [ "$neg" = "true" ];then
    k=$((n-1));
  else
    k=0;
  fi 
  for((j=0;j<n;k-=incr)){ 
    j=$((j+1))
    trial[${scratch[$j]}]=$k;
  }
}
#
function vMirror(){
  local -i j;
  local -i n=$1;
  for((j=0;j<n;j++)){
    local -i n1=$((n-1));
    trial[$j]=$((n1-trial[j]));
  }
}
#
function symmetryOps() {
  local -i k;
  local -i nEquiv;
  local -i size=$1;
  
  #// 回転・反転・対称チェックのためにboard配列をコピー
  for((k=0;k<size;k++)){
    trial[$k]=${board[$k]};
  }
  #//時計回りに90度回転
  rotate "$size" "false";
  k=$(intncmp "$size");
  ((k>0))&&{
    echo 0; 
    return;
  }  
  ((k==0))&&{
     nEquiv=1;
  }||{
   #//時計回りに180度回転
     rotate "$size" "false";
     k=$(intncmp "$size");
     ((k>0))&&{
       echo 0; 
       return;
     }
     ((k==0))&&{
        nEquiv=2;
   }||{
      #//時計回りに270度回転
      rotate "$size" "false";
      k=$(intncmp "$size");
      ((k>0))&&{
        echo 0; 
        return;
      }  
      nEquiv=4;
     }
  }
  #// 回転・反転・対称チェックのためにboard配列をコピー
  for((k=0;k<size;k++)){ 
    trial[$k]=${board[$k]};
  }
  #//垂直反転
  vMirror "$size";
  k=$(intncmp "$size");
  ((k>0))&&{ 
    echo 0; 
    return;
  }
  #// 4回転とは異なる場合
  ((nEquiv>1))&&{
   #// -90度回転 対角鏡と同等
     rotate "$size" "true";
     k=$(intncmp "$size");
     ((k>0))&&{
       echo 0;
       return;
     }
     ((nEquiv>2))&&{     #// 2回転とは異なる場合
      #// -180度回転 水平鏡像と同等
        rotate "$size" "true";
        k=$(intncmp "$size");
        ((k>0))&&{ 
          echo 0;
          return;
        }
        #// -270度回転 反対角鏡と同等
        rotate "$size" "true";
        k=$(intncmp "$size");
        ((k>0))&&{
          echo 0;
          return;
        }
     }
  }
  rtn=$((nEquiv * 2));
  echo "$rtn";
  return;
 }
N-Queen4_rec(){
  # ローカル変数は明示的に local をつけ、代入する場合は ""ダブルクォートが必要です。
  # -i は 変数の型が整数であることを示しています
  local -i min="$1";                # ひとつ目のパラメータ $1をminに代入
  local -i size=$2;                 # ふたつ目のパラメータ $2をsizeに代入
  local -i i=0;                     # 再帰するために forで使う変数も宣言が必要
  # forはこういうＣ的な書き方のほうが見やすい
  for((i=0;i<size;i++)){        # (()) の中の変数に $ は不要です 
    #わかりづらいですが、この文はif文 文字列比較の場合は [ ] を使います
    # 長い文章は \ （スペースバックスラッシュ）で改行することができます
    [ "${flag_a[$i]}" != "true"  ]&& \
    [ "${flag_b[$min+$i]}" != "true" ]&& \
    [ "${flag_c[$min-$i+$size-1]}" != "true" ]&&{   #この文はif文 文字列比較の場合は [ ] を使います
      board[$min]=$i ;              # 代入する場合、boardの前には$ は不要ですが、添え字には$が必要
      ((min==(size-1)))&&{          # (()) の中の変数に $ は不要です
        tst=$(symmetryOps "$size");
        ((tst!=0))&&{
          ((UNIQUE++));             # ((TOTAL++))はTOTALのインクリメント (()) の中の変数に $ は不要です
          TOTAL=$((TOTAL+tst));     # ((TOTAL++))はTOTALのインクリメント (()) の中の変数に $ は不要です
        }
      }||{                          # elseのはじまり                     
        flag_a[$i]="true";          # 配列の中の添え字には $ をつけます 
        flag_b[$min+$i]="true"; 
        flag_c[$min-$i+$size-1]="true"; 
        N-Queen4_rec "$((min+1))" "$size"; # 再帰する場合は $((min++))ではなく $((min+1))
        flag_a[$i]="";           
        flag_b[$min+$i]="";   
        flag_c[$min-$i+$size-1]=""; 
      }          
    }
  }  
}
#
N-Queen4(){
  local -i max=15;
  local -i min=2;
  local -i N="$min";
  local startTime=0;
	local endTime=0;
	local hh=mm=ss=0; 		# いっぺんにに初期化することもできます
  echo " N:        Total       Unique        hh:mm:ss";
  for((N=min;N<=max;N++)){
    TOTAL=0;      # Nが更新される度に TOTALとUNIQUEを初期化
    UNIQUE=0;
    startTime=`date +%s`;      # 計測開始時間
    for((k=0;k<N;k++)){ board[k]=k;}
    N-Queen4_rec 0 "$N";
		endTime=`date +%s`;					# 計測終了時間
		ss=`expr ${endTime} - ${startTime}`; # hh:mm:ss 形式に変換
		hh=`expr ${ss} / 3600`;
		ss=`expr ${ss} % 3600`;
		mm=`expr ${ss} / 60`;
		ss=`expr ${ss} % 60`;
    printf "%2d:%13d%13d%10d:%.2d:%.2d\n" $N $TOTAL $UNIQUE $hh $mm $ss ;
  } 
}
#
# 実行はコメントアウトを外して、 $ ./BASH_N-Queen.sh 
  echo "<>４．BT＋対称解除法 N-Queen4()";
  N-Queen4;
#
#
