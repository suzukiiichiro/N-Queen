/**
  Cで学ぶアルゴリズムとデータ構造  
  ステップバイステップでＮ−クイーン問題を最適化
  一般社団法人  共同通信社  情報技術局  鈴木  維一郎(suzuki.iichiro@kyodonews.jp)
 
 1. ブルートフォース　力任せ探索
		コンパイルと実行
		$ make nq1 && ./07_01NQueen

 　全ての可能性のある解の候補を体系的に数え上げ、それぞれの解候補が問題の解と
   なるかをチェックする方法

   (※)各行に１個の王妃を配置する組み合わせを再帰的に列挙組み合わせを生成するだ
   けであって8王妃問題を解いているわけではありません

  実行結果
  :
  : ＜すごく時間がかかります＞
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
**/

#include <stdio.h>
#include <time.h>

int c=1 ;   // c:count
int aB[8];  // aB:aBoard[]

// mi:min ma:max
void NQueen(int mi,int ma) {
  for(int i=0;i<ma;i++){
    aB[mi]=i ;
    if (mi==ma-1){ 
      printf("%d: ",c++);
      for(int j=0;j<ma;j++){
        printf("%d ",aB[j]);
      }
      printf("\n");
    }else{
      NQueen(mi+1,ma);
    }
  }
}
int main(void) {
  NQueen(0,8);
  return 0;
}
