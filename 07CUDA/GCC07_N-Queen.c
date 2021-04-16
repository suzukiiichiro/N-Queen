/**
  Cで学ぶアルゴリズムとデータ構造
  ステップバイステップでＮ−クイーン問題を最適化
  一般社団法人  共同通信社  情報技術局  鈴木  維一郎(suzuki.iichiro@kyodonews.jp)

 実行
 $ gcc -Wall -W -O3 -g -ftrapv -std=c99 GCC07.c && ./a.out [-c|-r]


７．CPU 非再帰 バックトラック＋ビットマップ＋対称解除法

 *     一つの解には、盤面を９０度、１８０度、２７０度回転、及びそれらの鏡像の合計
 *     ８個の対称解が存在する。対照的な解を除去し、ユニーク解から解を求める手法。
 *
 * ■ユニーク解の判定方法
 *   全探索によって得られたある１つの解が、回転・反転などによる本質的に変わること
 * のない変換によって他の解と同型となるものが存在する場合、それを別の解とはしない
 * とする解の数え方で得られる解を「ユニーク解」といいます。つまり、ユニーク解とは、
 * 全解の中から回転・反転などによる変換によって同型になるもの同士をグループ化する
 * ことを意味しています。
 *
 *   従って、ユニーク解はその「個数のみ」に着目され、この解はユニーク解であり、こ
 * の解はユニーク解ではないという定まった判定方法はありません。ユニーク解であるか
 * どうかの判断はユニーク解の個数を数える目的の為だけに各個人が自由に定義すること
 * になります。もちろん、どのような定義をしたとしてもユニーク解の個数それ自体は変
 * わりません。
 *
 *   さて、Ｎクイーン問題は正方形のボードで形成されるので回転・反転による変換パター
 * ンはぜんぶで８通りあります。だからといって「全解数＝ユニーク解数×８」と単純には
 * いきません。ひとつのグループの要素数が必ず８個あるとは限らないのです。Ｎ＝５の
 * 下の例では要素数が２個のものと８個のものがあります。
 *
 *
 * Ｎ＝５の全解は１０、ユニーク解は２なのです。
 *
 * グループ１: ユニーク解１つ目
 * - - - Q -   - Q - - -
 * Q - - - -   - - - - Q
 * - - Q - -   - - Q - -
 * - - - - Q   Q - - - -
 * - Q - - -   - - - Q -
 *
 * グループ２: ユニーク解２つ目
 * - - - - Q   Q - - - -   - - Q - -   - - Q - -   - - - Q -   - Q - - -   Q - - - -   - - - - Q
 * - - Q - -   - - Q - -   Q - - - -   - - - - Q   - Q - - -   - - - Q -   - - - Q -   - Q - - -
 * Q - - - -   - - - - Q   - - - Q -   - Q - - -   - - - - Q   Q - - - -   - Q - - -   - - - Q -
 * - - - Q -   - Q - - -   - Q - - -   - - - Q -   - - Q - -   - - Q - -   - - - - Q   Q - - - -
 * - Q - - -   - - - Q -   - - - - Q   Q - - - -   Q - - - -   - - - - Q   - - Q - -   - - Q - -
 *
 *
 *   それでは、ユニーク解を判定するための定義付けを行いますが、次のように定義する
 * ことにします。各行のクイーンが右から何番目にあるかを調べて、最上段の行から下
 * の行へ順番に列挙します。そしてそれをＮ桁の数値として見た場合に最小値になるもの
 * をユニーク解として数えることにします。尚、このＮ桁の数を以後は「ユニーク判定値」
 * と呼ぶことにします。
 *
 * - - - - Q   0
 * - - Q - -   2
 * Q - - - -   4   --->  0 2 4 1 3  (ユニーク判定値)
 * - - - Q -   1
 * - Q - - -   3
 *
 *
 *   探索によって得られたある１つの解(オリジナル)がユニーク解であるかどうかを判定
 * するには「８通りの変換を試み、その中でオリジナルのユニーク判定値が最小であるか
 * を調べる」ことになります。しかし結論から先にいえば、ユニーク解とは成り得ないこ
 * とが明確なパターンを探索中に切り捨てるある枝刈りを組み込むことにより、３通りの
 * 変換を試みるだけでユニーク解の判定が可能になります。
 *

bash-3.2$ gcc -Wall -W -O3 -g -ftrapv -std=c99 GCC07.c && ./a.out -r
７．CPUR 再帰 バックトラック＋ビットマップ＋対称解除法
 N:        Total       Unique        hh:mm:ss.ms
 4:            2               1            0.00
 5:           10               2            0.00
 6:            4               1            0.00
 7:           40               6            0.00
 8:           92              12            0.00
 9:          352              46            0.00
10:          724              92            0.00
11:         2680             341            0.00
12:        14200            1787            0.01
13:        73712            9233            0.08
14:       365596           45752            0.48
15:      2279184          285053            3.20
16:     14772512         1846955           22.49
17:     95815104        11977939         2:41.93


bash-3.2$ gcc -Wall -W -O3 -g -ftrapv -std=c99 GCC07.c && ./a.out -c
７．CPU 非再帰 バックトラック＋ビットマップ＋対称解除法
 N:        Total       Unique        hh:mm:ss.ms
 4:            2               1            0.00
 5:           10               2            0.00
 6:            4               1            0.00
 7:           40               6            0.00
 8:           92              12            0.00
 9:          352              46            0.00
10:          724              92            0.00
11:         2680             341            0.00
12:        14200            1787            0.01
13:        73712            9233            0.09
14:       365596           45752            0.49
15:      2279184          285053            3.25
16:     14772512         1846955           22.96
17:     95815104        11977939         2:43.94
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#define THREAD_NUM		96
#define MAX 27
//変数宣言
long Total=0 ;        //合計解
long Unique=0;
int down[2*MAX-1]; //down:flagA 縦 配置フラグ
int left[2*MAX-1];  //left:flagB 斜め配置フラグ
int right[2*MAX-1];  //right:flagC 斜め配置フラグ
int aBoard[MAX];
int aT[MAX];
int aS[MAX];
int COUNT2,COUNT4,COUNT8;
//関数宣言 CPU/GPU
void rotate_bitmap(int bf[],int af[],int si);
void vMirror_bitmap(int bf[],int af[],int si);
int intncmp(int lt[],int rt[],int n);
int rh(int a,int size);
//関数宣言 CPU
void TimeFormat(clock_t utime,char *form);
long getUnique();
long getTotal();
void symmetryOps_bitmap(int si);
//関数宣言 非再帰版
void solve_nqueen(int size,int mask, int row,int left,int down,int right);
void NQueen(int size,int mask);
//関数宣言 再起版
void solve_nqueenr(int size,int mask, int row,int left,int down,int right);
void NQueenR(int size,int mask);
//関数宣言 通常版
//  再帰
void NQueenDR(int size,int mask,int row,int left,int down,int right);
//  非再帰
void NQueenD(int size,int mask,int row);
//
//
int *paBoard;
void pd2b(int aB[],int si)
{
	printf("########\n");
	for(int i=0;i<si;i++){
		int decimal=aB[i];
		int n=dec2bin(decimal,paBoard,si);
		/* 求めた２進数を表示 */
		/* 第i桁を表示 */
		for(int i=0;i<n;i++){
			printf("%u",paBoard[n-1-i]);
		}
		printf("\n");
	}

}
//2進数を10進数に変換
int bin2dec(int binary)
{
	int decimal=0;
	int base=1;
  while(binary>0){
    decimal = decimal + ( binary % 10 ) * base;
    binary = binary / 10;
    base = base * 2;
  }
	return decimal;
}
//10進数を2進数に変換
int dec2bin(int decimal,int*pab,int size)
{
	int n=0;
	int a;
	while(n<size){
		/* 第n桁のみ1の値を算出 */
		a=(unsigned int)1<<n;
		/* &演算で第n桁の値取得 */
		if((decimal&a)==0){
			pab[n]=0;
		}else{
			pab[n]=1;
		}
		/* 次の桁へ */
		n++;
	}
  return n;
}

//hh:mm:ss.ms形式に処理時間を出力
void TimeFormat(clock_t utime,char *form){
  int dd,hh,mm;
  float ftime,ss;
  ftime=(float)utime/CLOCKS_PER_SEC;
  mm=(int)ftime/60;
  ss=ftime-(int)(mm*60);
  dd=mm/(24*60);
  mm=mm%(24*60);
  hh=mm/60;
  mm=mm%60;
  if(dd)
    sprintf(form,"%4d %02d:%02d:%05.2f",dd,hh,mm,ss);
  else if(hh)
    sprintf(form,"     %2d:%02d:%05.2f",hh,mm,ss);
  else if(mm)
    sprintf(form,"        %2d:%05.2f",mm,ss);
  else
    sprintf(form,"           %5.2f",ss);
}
//
int rh(int a,int sz){
  int tmp=0;
  for(int i=0;i<=sz;i++){
    if(a&(1<<i)){ return tmp|=(1<<(sz-i)); }
  }
  return tmp;
}
//
void vMirror_bitmap(int bf[],int af[],int si){
  int score ;
  for(int i=0;i<si;i++) {
    score=bf[i];
    af[i]=rh(score,si-1);
  }
}
//
void rotate_bitmap(int bf[],int af[],int si){
  for(int i=0;i<si;i++){
    int t=0;
    for(int j=0;j<si;j++){
      t|=((bf[j]>>i)&1)<<(si-j-1); // x[j] の i ビット目を
    }
    af[i]=t;                        // y[i] の j ビット目にする
  }
}
//
int intncmp(int lt[],int rt[],int n){
  int rtn=0;
  for(int k=0;k<n;k++){
    rtn=lt[k]-rt[k];
    if(rtn!=0){
      break;
    }
  }
  return rtn;
}
//
long getUnique(){
  return COUNT2+COUNT4+COUNT8;
}
//
long getTotal(){
  return COUNT2*2+COUNT4*4+COUNT8*8;
}
//CPU
/**
(1) 90度回転させてオリジナルと同型になる場合、
さらに90度回転(オリジナルから180度回転)させても、
さらに90度回転(オリジナルから270度回転)させてもオリジナルと同型になる。
(2) 90度回転させてオリジナルと異なる場合は、
270度回転させても必ずオリジナルとは異なる。
ただし、180度回転させた場合はオリジナルと同型になることも有り得る。
(1)に該当するユニーク解が属するグループの要素数は、
左右反転させたパターンを加えて２個しかない。
(2)に該当するユニーク解が属するグループの要素数は、
180度回転させて同型になる場合は４個(左右反転×縦横回転)、
そして180度回転させてもオリジナルと異なる場合は８個(左右反転×縦横回転×上下反転)になる。
以上のことから、ひとつひとつのユニーク解が上のどの種類に該当するのかを
調べることにより全解数を計算で導き出すことができます。
 */
void symmetryOps_bitmap(int si){
  int nEquiv;
  // 回転・反転・対称チェックのためにboard配列をコピー
  for(int i=0;i<si;i++){ aT[i]=aBoard[i];}
  printf("aBoard\n");
  pd2b(aBoard,si);
  rotate_bitmap(aT,aS,si);    //時計回りに90度回転
  printf("aBoardを左に90度回転\n");
  pd2b(aS,si);
  printf("intncmpはaBoardと90度回転させたものが同型か比較する\n");
  int k=intncmp(aBoard,aS,si);
  if(k>0){
	  printf("90度回転して違う場合。kが0より大きければユニーク解ではないので抜ける\n");
	  return;
  }
  if(k==0){
	  nEquiv=2;
	  printf("90度回転して同じ場合は180度,270度回転してもオリジナルと同型になる。この場合左右反転させたパターンを加えて２個");
  }else{
    rotate_bitmap(aS,aT,si);  //時計回りに180度回転
    printf("aBoard\n");
    pd2b(aBoard,si);
    printf("aBoardを左に180度回転\n");
    pd2b(aT,si);
    printf("intncmpはaBoardと180度回転させたものが同型か比較する\n");
    k=intncmp(aBoard,aT,si);
    if(k>0){
	  printf("180度回転して違う場合。kが0より大きければユニーク解ではないので抜ける\n");
      return;
    }
    if(k==0){
	    printf("180度回転させて同型になる場合は４個(左右反転×縦横回転)");
    	nEquiv=4;
    }else{
      rotate_bitmap(aT,aS,si);//時計回りに270度回転
      printf("aBoard\n");
      pd2b(aBoard,si);
      printf("aBoardを左に270度回転\n");
      pd2b(aS,si);
      printf("intncmpはaBoardと270度回転させたものが同型か比較する\n");
      k=intncmp(aBoard,aS,si);
      if(k>0){
	    printf("270度回転して違う場合。kが0より大きければユニーク解ではないので抜ける\n");
    	return;
      }
	  printf("180度回転させてもオリジナルと異なる場合は８個(左右反転×縦横回転×上下反転)になる。");
      nEquiv=8;
    }
  }
  printf("以下ではミラーがユニーク解かどうかチェックしていく\n");
  // 回転・反転・対称チェックのためにboard配列をコピー
  for(int i=0;i<si;i++){ aS[i]=aBoard[i];}
  printf("aBoard\n");
  pd2b(aS,si);
  vMirror_bitmap(aS,aT,si);   //垂直反転
  printf("aBoardを垂直反転\n");
  pd2b(aT,si);
  printf("intncmpはaBoardと垂直反転させたものが同型か比較する\n");
  k=intncmp(aBoard,aT,si);
  if(k>0){
	  printf("垂直反転させて違う場合。kが0より大きければユニーク解ではないので抜ける\n");
	  return;
  }
  if(nEquiv>2){             //-90度回転 対角鏡と同等
    rotate_bitmap(aT,aS,si);
    printf("aBoard\n");
    pd2b(aBoard,si);
    printf("aBoardを垂直反転させたものを90度回転\n");
    pd2b(aS,si);
    printf("intncmpはaBoardと垂直反転させて90度回転させてものが同型か比較する\n");
    k=intncmp(aBoard,aS,si);
    if(k>0){
	    printf("垂直反転させ90度回転させて違う場合。kが0より大きければユニーク解ではないので抜ける\n");
    	return;
    }
    if(nEquiv>4){           //-180度回転 水平鏡像と同等
      rotate_bitmap(aS,aT,si);
      printf("aBoard\n");
      pd2b(aBoard,si);
      printf("aBoardを垂直反転させたものを180度回転\n");
      pd2b(aT,si);
      printf("intncmpはaBoardと垂直反転させて180度回転させてものが同型か比較する\n");
      k=intncmp(aBoard,aT,si);
      if(k>0){
	      printf("垂直反転させ180度回転させて違う場合。kが0より大きければユニーク解ではないので抜ける\n");
    	  return;
      }       //-270度回転 反対角鏡と同等
      rotate_bitmap(aT,aS,si);
      printf("aBoard\n");
      pd2b(aBoard,si);
      printf("aBoardを垂直反転させたものを270度回転\n");
      pd2b(aS,si);
      printf("intncmpはaBoardと垂直反転させて270度回転させてものが同型か比較する\n");
      k=intncmp(aBoard,aS,si);
      if(k>0){
	      printf("垂直反転させ270度回転させて違う場合。kが0より大きければユニーク解ではないので抜ける\n");
    	  return;
      }
    }
  }
  printf("ここまでたどり着けたらユニーク解\n");
  if(nEquiv==2){COUNT2++;}
  if(nEquiv==4){COUNT4++;}
  if(nEquiv==8){COUNT8++;}
}
//
//CPU 非再帰版 ロジックメソッド
void solve_nqueen(int size,int mask, int row,int h_left,int h_down,int h_right){
	unsigned int left[size];
    unsigned int down[size];
	unsigned int right[size];
    unsigned int bitmap[size];
	left[row]=h_left;
	down[row]=h_down;
	right[row]=h_right;
	bitmap[row]=mask&~(left[row]|down[row]|right[row]);
    unsigned int bit;
    unsigned int sizeE=size-1;
    int mark=row;
    //固定していれた行より上はいかない
    while(row>=mark){//row=1 row>=1, row=2 row>=2
      if(bitmap[row]==0){
        --row;
      }else{
        bitmap[row]^=aBoard[row]=bit=(-bitmap[row]&bitmap[row]);
        if((bit&mask)!=0){
          if(row==sizeE){
            symmetryOps_bitmap(size);
            --row;
          }else{
            int n=row++;
            left[row]=(left[n]|bit)<<1;
            down[row]=down[n]|bit;
            right[row]=(right[n]|bit)>>1;
            bitmap[row]=mask&~(left[row]|down[row]|right[row]);
          }
        }else{
           --row;
        }
      }
    }
}
//
void NQueen(int size,int mask){
  int bit=0;
  //偶数、奇数共通
  for(int col=0;col<size;col++){
    aBoard[0]=bit=(1<<col);
    solve_nqueen(size,mask,1,bit<<1,bit,bit>>1);
  }
}
//
//CPUR 再帰版 ロジックメソッド
void solve_nqueenr(int size,int mask, int row,int left,int down,int right){
 int bitmap=0;
 int bit=0;
 int sizeE=size-1;
 bitmap=(mask&~(left|down|right));
 if(row==sizeE){
    if(bitmap){
      aBoard[row]=(-bitmap&bitmap);
      symmetryOps_bitmap(size);
    }
  }else{
    while(bitmap){
      bitmap^=aBoard[row]=bit=(-bitmap&bitmap);
      solve_nqueenr(size,mask,row+1,(left|bit)<<1, down|bit,(right|bit)>>1);
    }
  }
}
//CPUR 再帰版 ロジックメソッド
void NQueenR(int size,int mask){
  int bit=0;
  //1行目全てにクイーンを置く
  for(int col=0;col<size;col++){
    aBoard[0]=bit=(1<<col);
    solve_nqueenr(size,mask,1,bit<<1,bit,bit>>1);
  }
}
//
//通常版 CPU 非再帰版 ロジックメソッド
void NQueenD(int size,int mask,int row){
  int aStack[size];
  int* pnStack;
  int bit;
  int bitmap;
  int sizeE=size-1;
  int down[size],right[size],left[size];
  aStack[0]=-1;
  pnStack=aStack+1;
  bit=0;
  bitmap=mask;
  down[0]=left[0]=right[0]=0;
  while(true){
    if(bitmap){
      bitmap^=aBoard[row]=bit=(-bitmap&bitmap);
      if(row==sizeE){
        /* 対称解除法の追加 */
        //TOTAL++;

        symmetryOps_bitmap(size);
        bitmap=*--pnStack;
        --row;
        continue;
      }else{
        int n=row++;
        left[row]=(left[n]|bit)<<1;
        down[row]=down[n]|bit;
        right[row]=(right[n]|bit)>>1;
        *pnStack++=bitmap;
        bitmap=mask&~(left[row]|down[row]|right[row]);
        continue;
      }
    }else{
      bitmap=*--pnStack;
      if(pnStack==aStack){ break ; }
      --row;
      continue;
    }
  }
}
//
//通常版 CPUR 再帰版　ロジックメソッド
void NQueenDR(int size,int mask,int row,int left,int down,int right){
  int bit;
  int bitmap=mask&~(left|down|right);
  if(row==size){
    /* 対称解除法の追加 */
    //TOTAL++;
    symmetryOps_bitmap(size);
  }else{
    while(bitmap){
      //bitmap^=bit=(-bitmap&bitmap);
      bitmap^=aBoard[row]=bit=(-bitmap&bitmap);
      NQueenDR(size,mask,row+1,(left|bit)<<1,down|bit,(right|bit)>>1);
    }
  }
}
//
//メインメソッド
int main(int argc,char** argv) {
  printf("test\n");
  bool cpu=false,cpur=false,gpu=false,sgpu=false;
  cpu=true;
  int argstart=1;
  //steps=24576;
  /** パラメータの処理 */
  if(argc>=2&&argv[1][0]=='-'){
    if(argv[1][1]=='c'||argv[1][1]=='C'){cpu=true;}
    else if(argv[1][1]=='r'||argv[1][1]=='R'){cpur=true;}
    else if(argv[1][1]=='g'||argv[1][1]=='G'){gpu=true;}
    else if(argv[1][1]=='s'||argv[1][1]=='S'){sgpu=true;}
    else
      cpur=true;
    argstart=2;
  }
  if(argc<argstart){
    printf("Usage: %s [-c|-g|-r|-s]\n",argv[0]);
    printf("  -c: CPU only\n");
    printf("  -r: CPUR only\n");
    printf("  -g: GPU only\n");
    printf("  -s: SGPU only\n");
    printf("Default to 8 queen\n");
  }
  /** 出力と実行 */
  if(cpu){
    printf("\n\n７．CPU 非再帰 バックトラック＋ビットマップ＋対称解除法\n");
  }else if(cpur){
    printf("\n\n７．CPUR 再帰 バックトラック＋ビットマップ＋対称解除法\n");
  }else if(gpu){
    printf("\n\n７．GPU 非再帰 バックトラック＋ビットマップ＋対称解除法\n");
  }else if(sgpu){
    printf("\n\n７．SGPU 非再帰 バックトラック＋ビットマップ＋対称解除法\n");
  }
  if(cpu||cpur){
    printf("%s\n"," N:        Total       Unique        hh:mm:ss.ms");
    clock_t st;           //速度計測用
    char t[20];           //hh:mm:ss.msを格納
   // int min=4; int targetN=17;
    int min=7; int targetN=7;
    int mask;
    for(int i=min;i<=targetN;i++){
      //TOTAL=0; UNIQUE=0;
      COUNT2=COUNT4=COUNT8=0;
      paBoard = (int *)malloc(i * sizeof(int));//２進数表示用
      mask=(1<<i)-1;
      st=clock();
      //
      //再帰
      if(cpur){ NQueenR(i,mask); }
        //printf("通常版\n");
        //NQueenDR(i,mask,0,0,0,0); //通常版
      //非再帰
      if(cpu){
        NQueen(i,mask);
        //printf("通常版\n");
        //NQueenD(i,mask,0); //通常版
      }
      //
      TimeFormat(clock()-st,t);
      printf("%2d:%13ld%16ld%s\n",i,getTotal(),getUnique(),t);
    }
  }
  return 0;
}
