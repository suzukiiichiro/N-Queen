
//$ gcc -Wall -W -O3 -g -ftrapv -std=c99 GCC06NR.c && ./a.out [-c|-r]

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
//
#define MAX 27
//
int down[2*MAX-1]; 	//down:flagA 縦 配置フラグ
int right[2*MAX-1]; //right:flagB 斜め配置フラグ
int left[2*MAX-1]; 	//left:flagC 斜め配置フラグ
long TOTAL=0;
long UNIQUE=0;
// int aBoard[MAX];
int aT[MAX];       	//aT:aTrial[]
int aS[MAX];       	//aS:aScrath[]
//関数宣言
void TimeFormat(clock_t utime,char *form);
void NQueenR(int size,int mask,int row,int left,int down,int right);
void NQueen(int size,int mask);
//hh:mm:ss.ms形式に処理時間を出力
void TimeFormat(clock_t utime,char* form){
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
//CPU 非再帰版 ロジックメソッド
void NQueen(int size,int mask){
  int aStack[MAX+2];
  register int* pnStack;
  register int row=0;
  register int bit;
  register int bitmap;
  int odd=size&1;
  int sizeE=size-1;
  /* センチネルを設定-スタックの終わりを示します*/
  aStack[0]=-1; 
  /**
    注：サイズが奇数の場合、（サイズ＆1）は真。
    サイズが奇数の場合は2xをループする必要があります
    */
  for(int i=0;i<(1+odd);++i){
    /**
      クリティカルループ
      この部分を最適化する必要はありません。
      */
    bitmap=0;
    if(0==i){
      /*中央を除くボードの半分を処理します
        カラム。ボードが5 x 5の場合、最初の行は00011になります。
        クイーンを中央の列に配置することについてはまだです。
        */
      /* ２で割る */
      int half=size>>1;
      /*サイズの半分のビットマップで右端の1を埋めます
        サイズが7の場合、その半分は3です（残りは破棄します）
        ビットマップはバイナリで111に設定されます。 
        */
      bitmap=(1<<half)-1;
      pnStack=aStack+1;/* スタックポインタ */
      // aBoard[0]=0;
      down[0]=left[0]=right[0]=0;
    }else{
      /*（奇数サイズのボードの）中央の列を処理します。
        中央の列ビットを1に設定してから設定します 
        したがって、最初の行（1つの要素）と次の半分を処理しています。
        ボードが5 x 5の場合、最初の行は00100になり、次の行は00011です。
        */
      bitmap=1<<(size>>1);
      row=1; /*すでに 0 */
      /* 最初の行にはクイーンが1つだけあります（中央の列）*/
      // aBoard[0]=bitmap;
      down[0]=left[0]=right[0]=0;
      down[1]=bitmap;
      /* 次の行を実行します。半分だけビットを設定します
         「Y軸」で結果を反転します
         */
      right[1]=(bitmap>>1);
      left[1]=(bitmap<<1);
      pnStack=aStack+1; // スタックポインタ
      /* この行は-1つの要素のみで完了 */
      *pnStack++=0;
      /* ビットマップ-1は、単一の1の左側すべて1です */
      bitmap=(bitmap-1)>>1; 
    }
    // クリティカルループ
    while(true){
      /* 
         bit = bitmap ^（bitmap＆（bitmap -1））;
         最初の（最小のsig） "1"ビットを取得しますが、それは遅くなります。 
         */
      /* これは、2の補数アーキテクチャを想定しています */
      bit=-((signed)bitmap) & bitmap; 
      if(0==bitmap){
        /* 前を取得スタックからのビットマップ */
        bitmap=*--pnStack;
        /* センチネルがヒットした場合... */
        if(pnStack==aStack){ 
          break ;
        }
        --row;
        continue;
      }
      /* このビットをオフにして、再試行しないようにします */
      bitmap&=~bit; 
      /* 結果を保存 */
      // aBoard[row]=bit;
      /* 処理する行がまだあるか？ */
      if(row<sizeE){
        int n=row++;
        down[row]=down[n]|bit;
        right[row]=(right[n]|bit)>>1;
        left[row]=(left[n]|bit)<<1;
        *pnStack++=bitmap;
        /* 同じ女王の位置を考慮することはできません
           列、同じ正の対角線、または同じ負の対角線
           すでにボード上のクイーン。 
           */
        bitmap=mask&~(down[row]|right[row]|left[row]);
        continue;
      }else{
        /* 処理する行はもうありません。解決策が見つかりました。*/
        ++TOTAL;
        bitmap=*--pnStack;
        --row;
        continue;
      }
    }
  }
  /* 鏡像をカウントするために、ソリューションを2倍します */
  TOTAL*=2;
}
//CPUR 再帰版　ロジックメソッド
void NQueenR(int size,int mask,int row,int left,int down,int right){
  int bitmap=0;
  int bit=0;
  if(row==size){
    TOTAL++;
  }else{
    bitmap=(mask&~(left|down|right));
    while(bitmap){
      bitmap^=bit=(-bitmap&bitmap);
      NQueenR(size,mask,row+1,(left|bit)<<1, down|bit,(right|bit)>>1);
    }
  }
}
//メインメソッド
int main(int argc,char** argv){
  bool cpu=false,cpur=false;
  int argstart=2;
  /** 起動パラメータの処理 */
  if(argc>=2&&argv[1][0]=='-'){
    if(argv[1][1]=='c'||argv[1][1]=='C'){cpu=true;}
    else if(argv[1][1]=='r'||argv[1][1]=='R'){cpur=true;}
    else{ cpur=true;}
  }
  if(argc<argstart){
    printf("Usage: %s [-c|-g]\n",argv[0]);
    printf("  -c: CPU Without recursion\n");
    printf("  -r: CPUR Recursion\n");
  }
  if(cpu){
    printf("\n\n６．CPU 非再帰 バックトラック＋ビットマップ\n");
  }else if(cpur){
    printf("\n\n６．CPUR 再帰 バックトラック＋ビットマップ\n");
  }
  printf("%s\n"," N:        Total       Unique        hh:mm:ss.ms");
  clock_t st;           //速度計測用
  char t[20];           //hh:mm:ss.msを格納
  int min=4;
  int targetN=17;
  int mask=0;

  for(int i=min;i<=targetN;i++){
    TOTAL=0;
    mask=((1<<i)-1);
    UNIQUE=0;
    st=clock();
    if(cpu){
      // aBaordを使用しないので
      // 初期化の必要はありません
      // for(int j=0;j<=targetN;j++){
      // 	aBoard[j]=-1;
      // }
      NQueen(i,mask);
    }
    if(cpur){
      // aBaordを使用しないので
      // 初期化の必要はありません
      // for(int j=0;j<=targetN;j++){
      // 	aBoard[j]=j;
      // }
      NQueenR(i,mask,0,0,0,0);
    }
    TimeFormat(clock()-st,t);
    printf("%2d:%13ld%16ld%s\n",i,TOTAL,UNIQUE,t);
  }
  return 0;
}
