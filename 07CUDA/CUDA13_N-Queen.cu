/**
 CUDAで学ぶアルゴリズムとデータ構造
 ステップバイステップでＮ−クイーン問題を最適化
 一般社団法人  共同通信社  情報技術局  鈴木  維一郎(suzuki.iichiro@kyodonews.jp)

 コンパイルと実行
 $ nvcc -O3 CUDA**_N-Queen.cu && ./a.out (-c|-r|-g|-s)
                    -c:cpu 
                    -r cpu再帰 
                    -g GPU 
                    -s SGPU(サマーズ版と思われる)

 １３．並列処理 pthread


 【注意】

 こちらのソースは参考版です

 理由：
 cudaのソースに参考のために 再帰・非再帰のpthread版を記載しましたが、
 cudaはpthreadをサポートしていないので、コンパイルは通りません。

 +590 行目のコメントアウトはそのためです。
 //iFbRet = pthread_create(&pth, NULL,&NQueenThread,NULL);

 pthreadの具体的なソースは、Cディレクトリの C13_N-Queen.cを見て下さい。
 こちらはきちんと動作します。
 【注意】



 実行結果

１３．CPUR 再帰 並列処理 pthread
 N:           Total           Unique          dd:hh:mm:ss.ms
 4:               2                1          00:00:00:00.00
 5:              10                2          00:00:00:00.00
 6:               4                1          00:00:00:00.00
 7:              40                6          00:00:00:00.00
 8:              92               12          00:00:00:00.00
 9:             352               46          00:00:00:00.00
10:             724               92          00:00:00:00.00
11:            2680              341          00:00:00:00.00
12:           14200             1787          00:00:00:00.00
13:           73712             9233          00:00:00:00.00
14:          365596            45752          00:00:00:00.02
15:         2279184           285053          00:00:00:00.10
16:        14772512          1846955          00:00:00:00.63
17:        95815104         11977939          00:00:00:04.33

１３．CPU 非再帰 並列処理 pthread
 N:           Total           Unique          dd:hh:mm:ss.ms
 4:               2                1          00:00:00:00.00
 5:              10                2          00:00:00:00.00
 6:               4                1          00:00:00:00.00
 7:              40                6          00:00:00:00.00
 8:              92               12          00:00:00:00.00
 9:             352               46          00:00:00:00.00
10:             724               92          00:00:00:00.00
11:            2680              341          00:00:00:00.00
12:           14200             1787          00:00:00:00.00
13:           73712             9233          00:00:00:00.00
14:          365596            45752          00:00:00:00.01
15:         2279184           285053          00:00:00:00.10
16:        14772512          1846955          00:00:00:00.65
17:        95815104         11977939          00:00:00:04.33


１３．GPU 非再帰 並列処理 CUDA
＜＜うごきません＞＞

ちなみに１２の処理結果

bash-3.2$ nvcc -O3 CUDA12_N-Queen.cu && ./a.out -g
１２．GPU 非再帰 枝刈り
 N:        Total      Unique      dd:hh:mm:ss.ms
 4:            2               1  00:00:00:00.02
 5:           10               2  00:00:00:00.00
 6:            4               1  00:00:00:00.00
 7:           40               6  00:00:00:00.01
 8:           92              12  00:00:00:00.00
 9:          352              46  00:00:00:00.01
10:          724              92  00:00:00:00.01
11:         2680             341  00:00:00:00.02
12:        14200            1787  00:00:00:00.04
13:        73712            9233  00:00:00:00.06
14:       365596           45752  00:00:00:00.11
15:      2279184          285053  00:00:00:00.37
16:     14772512         1846955  00:00:00:01.77
17:     95815104        11977939  00:00:00:11.91
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <pthread.h>
//
#define THREAD_NUM		96
#define MAX 27
//

int NR;
// GPUで使います
long Total=0 ;      //合計解
long Unique=0;

//
//変数宣言
// pthreadはパラメータを１つしか渡せないので構造体に格納
//グローバル構造体
typedef struct {
  int size;
  int sizeE;
  long lTOTAL,lUNIQUE;
}GCLASS, *GClass;
GCLASS G;
//ローカル構造体
typedef struct{
  int BOUND1,BOUND2,TOPBIT,ENDBIT,SIDEMASK,LASTMASK;
  int mask;
  int aBoard[MAX];
  long COUNT2[MAX],COUNT4[MAX],COUNT8[MAX];
}local ;
//関数宣言
void symmetryOps(local *l);
//非再帰
void backTrack2D_NR(int y,int left,int down,int right,local *l);
void backTrack1D_NR(int y,int left,int down,int right,local *l);
//非再帰 通常版
void backTrack2_NR(int y,int left,int down,int right,local *l);
void backTrack1_NR(int y,int left,int down,int right,local *l);
//再帰
void backTrack2D(int y,int left,int down,int right,local *l);
void backTrack1D(int y,int left,int down,int right,local *l);
//再帰 通常版
void backTrack2(int y,int left,int down,int right,local *l);
void backTrack1(int y,int left,int down,int right,local *l);
//pthread
void *run(void *args);
void *NQueenThread();
void NQueen();
//
__global__ void cuda_kernel(
    int size,int mark,
    unsigned int* totalDown,unsigned int* totalLeft,unsigned int* totalRight,
    unsigned int* results,int totalCond){
  const int tid=threadIdx.x;
  const int bid=blockIdx.x;
  const int idx=bid*blockDim.x+tid;
  __shared__ unsigned int down[THREAD_NUM][10];
  __shared__ unsigned int left[THREAD_NUM][10];
  __shared__ unsigned int right[THREAD_NUM][10];
  __shared__ unsigned int bitmap[THREAD_NUM][10];
  __shared__ unsigned int sum[THREAD_NUM];
  const unsigned int mask=(1<<size)-1;
  int total=0;
  int row=0;
  unsigned int bit;
  if(idx<totalCond){
    down[tid][row]=totalDown[idx];
    left[tid][row]=totalLeft[idx];
    right[tid][row]=totalRight[idx];
    bitmap[tid][row]=down[tid][row]|left[tid][row]|right[tid][row];
    while(row>=0){
      if((bitmap[tid][row]&mask)==mask){row--;}
      else{
        bit=(bitmap[tid][row]+1)&~bitmap[tid][row];
        bitmap[tid][row]|=bit;
        if((bit&mask)!=0){
          if(row+1==mark){total++;row--;}
          else{
            down[tid][row+1]=down[tid][row]|bit;
            left[tid][row+1]=(left[tid][row]|bit)<<1;
            right[tid][row+1]=(right[tid][row]|bit)>>1;
            bitmap[tid][row+1]=(down[tid][row+1]|left[tid][row+1]|right[tid][row+1]);
            row++;
          }
        }else{row--;}
      }
    }
    sum[tid]=total;
  }else{sum[tid]=0;} 
  __syncthreads();if(tid<64&&tid+64<THREAD_NUM){sum[tid]+=sum[tid+64];} 
  __syncthreads();if(tid<32){sum[tid]+=sum[tid+32];} 
  __syncthreads();if(tid<16){sum[tid]+=sum[tid+16];} 
  __syncthreads();if(tid<8){sum[tid]+=sum[tid+8];} 
  __syncthreads();if(tid<4){sum[tid]+=sum[tid+4];} 
  __syncthreads();if(tid<2){sum[tid]+=sum[tid+2];} 
  __syncthreads();if(tid<1){sum[tid]+=sum[tid+1];} 
  __syncthreads();if(tid==0){results[bid]=sum[0];}
}
//
long long solve_nqueen_cuda(int size,int steps) {
  unsigned int down[32];
  unsigned int left[32];
  unsigned int right[32];
  unsigned int bitmap[32];
  unsigned int bit;
  if(size<=0||size>32){return 0;}
  unsigned int* totalDown=new unsigned int[steps];
  unsigned int* totalLeft=new unsigned int[steps];
  unsigned int* totalRight=new unsigned int[steps];
  unsigned int* results=new unsigned int[steps];
  unsigned int* downCuda;
  unsigned int* leftCuda;
  unsigned int* rightCuda;
  unsigned int* resultsCuda;
  cudaMalloc((void**) &downCuda,sizeof(int)*steps);
  cudaMalloc((void**) &leftCuda,sizeof(int)*steps);
  cudaMalloc((void**) &rightCuda,sizeof(int)*steps);
  cudaMalloc((void**) &resultsCuda,sizeof(int)*steps/THREAD_NUM);
  const unsigned int mask=(1<<size)-1;
  const unsigned int mark=size>11?size-10:2;
  long long total=0;
  int totalCond=0;
  int row=0;
  down[0]=0;
  left[0]=0;
  right[0]=0;
  bitmap[0]=0;
  bool matched=false;
  for(int col=0;col<size/2;col++){
    bit=(1<<col);
    bitmap[0]|=bit;
    down[1]=bit;
    left[1]=bit<<1;
    right[1]=bit>>1;
    bitmap[1]=(down[1]|left[1]|right[1]);
    row=1;
    while(row>0){
      if((bitmap[row]&mask)==mask){row--;}
      else{
        bit=(bitmap[row]+1)&~bitmap[row];
        bitmap[row]|=bit;
        if((bit&mask)!=0){
          down[row+1]=down[row]|bit;
          left[row+1]=(left[row]|bit)<<1;
          right[row+1]=(right[row]|bit)>>1;
          bitmap[row+1]=(down[row+1]|left[row+1]|right[row+1]);
          row++;
          if(row==mark){
            totalDown[totalCond]=down[row];
            totalLeft[totalCond]=left[row];
            totalRight[totalCond]=right[row];
            totalCond++;
            if(totalCond==steps){
              if(matched){
                cudaMemcpy(results,resultsCuda,
                    sizeof(int)*steps/THREAD_NUM,cudaMemcpyDeviceToHost);
                for(int col=0;col<steps/THREAD_NUM;col++){total+=results[col];}
                matched=false;
              }
              cudaMemcpy(downCuda,totalDown,
                  sizeof(int)*totalCond,cudaMemcpyHostToDevice);
              cudaMemcpy(leftCuda,totalLeft,
                  sizeof(int)*totalCond,cudaMemcpyHostToDevice);
              cudaMemcpy(rightCuda,totalRight,
                  sizeof(int)*totalCond,cudaMemcpyHostToDevice);
              /** backTrack+bitmap*/
              cuda_kernel<<<steps/THREAD_NUM,THREAD_NUM
                >>>(size,size-mark,downCuda,leftCuda,rightCuda,resultsCuda,totalCond);
              matched=true;
              totalCond=0;
            }
            row--;
          }
        }else{row--;}
      }
    }
  }
  if(matched){
    cudaMemcpy(results,resultsCuda,
        sizeof(int)*steps/THREAD_NUM,cudaMemcpyDeviceToHost);
    for(int col=0;col<steps/THREAD_NUM;col++){total+=results[col];}
    matched=false;
  }
  cudaMemcpy(downCuda,totalDown,
      sizeof(int)*totalCond,cudaMemcpyHostToDevice);
  cudaMemcpy(leftCuda,totalLeft,
      sizeof(int)*totalCond,cudaMemcpyHostToDevice);
  cudaMemcpy(rightCuda,totalRight,
      sizeof(int)*totalCond,cudaMemcpyHostToDevice);
  /** backTrack+bitmap*/
  cuda_kernel<<<steps/THREAD_NUM,THREAD_NUM
    >>>(size,size-mark,downCuda,leftCuda,rightCuda,resultsCuda,totalCond);
  cudaMemcpy(results,resultsCuda,
      sizeof(int)*steps/THREAD_NUM,cudaMemcpyDeviceToHost);
  for(int col=0;col<steps/THREAD_NUM;col++){total+=results[col];}	
  total*=2;


  if(size%2==1){
    matched=false;
    totalCond=0;
    bit=(1<<(size-1)/2);
    bitmap[0]|=bit;
    down[1]=bit;
    left[1]=bit<<1;
    right[1]=bit>>1;
    bitmap[1]=(down[1]|left[1]|right[1]);
    row=1;
    while(row>0){
      if((bitmap[row]&mask)==mask){row--;}
      else{
        bit=(bitmap[row]+1)&~bitmap[row];
        bitmap[row]|=bit;
        if((bit&mask)!=0){
          down[row+1]=down[row]|bit;
          left[row+1]=(left[row]|bit)<<1;
          right[row+1]=(right[row]|bit)>>1;
          bitmap[row+1]=(down[row+1]|left[row+1]|right[row+1]);
          row++;
          if(row==mark){
            totalDown[totalCond]=down[row];
            totalLeft[totalCond]=left[row];
            totalRight[totalCond]=right[row];
            totalCond++;
            if(totalCond==steps){
              if(matched){
                cudaMemcpy(results,resultsCuda,
                    sizeof(int)*steps/THREAD_NUM,cudaMemcpyDeviceToHost);
                for(int col=0;col<steps/THREAD_NUM;col++){total+=results[col];}
                matched=false;
              }
              cudaMemcpy(downCuda,totalDown,
                  sizeof(int)*totalCond,cudaMemcpyHostToDevice);
              cudaMemcpy(leftCuda,totalLeft,
                  sizeof(int)*totalCond,cudaMemcpyHostToDevice);
              cudaMemcpy(rightCuda,totalRight,
                  sizeof(int)*totalCond,cudaMemcpyHostToDevice);
              /** backTrack+bitmap*/
              cuda_kernel<<<steps/THREAD_NUM,THREAD_NUM
                >>>(size,size-mark,downCuda,leftCuda,rightCuda,resultsCuda,totalCond);
              matched=true;
              totalCond=0;
            }
            row--;
          }
        }else{row--;}
      }
    }
    if(matched){
      cudaMemcpy(results,resultsCuda,
          sizeof(int)*steps/THREAD_NUM,cudaMemcpyDeviceToHost);
      for(int col=0;col<steps/THREAD_NUM;col++){total+=results[col];}
      matched=false;
    }
    cudaMemcpy(downCuda,totalDown,
        sizeof(int)*totalCond,cudaMemcpyHostToDevice);
    cudaMemcpy(leftCuda,totalLeft,
        sizeof(int)*totalCond,cudaMemcpyHostToDevice);
    cudaMemcpy(rightCuda,totalRight,
        sizeof(int)*totalCond,cudaMemcpyHostToDevice);
    /** backTrack+bitmap*/
    cuda_kernel<<<steps/THREAD_NUM,THREAD_NUM
      >>>(size,size-mark,downCuda,leftCuda,rightCuda,resultsCuda,totalCond);
    cudaMemcpy(results,resultsCuda,
        sizeof(int)*steps/THREAD_NUM,cudaMemcpyDeviceToHost);
    for(int col=0;col<steps/THREAD_NUM;col++){total+=results[col];}
  }
  cudaFree(downCuda);
  cudaFree(leftCuda);
  cudaFree(rightCuda);
  cudaFree(resultsCuda);
  delete[] totalDown;
  delete[] totalLeft;
  delete[] totalRight;
  delete[] results;
  return total;
}
/** CUDA 初期化 **/
bool InitCUDA(){
  int count;
  cudaGetDeviceCount(&count);
  if(count==0){fprintf(stderr,"There is no device.\n");return false;}
  int i;
  for(i=0;i<count;i++){
    cudaDeviceProp prop;
    if(cudaGetDeviceProperties(&prop,i)==cudaSuccess){if(prop.major>=1){break;} }
  }
  if(i==count){fprintf(stderr,"There is no device supporting CUDA 1.x.\n");return false;}
  cudaSetDevice(i);
  return true;
}
//
void symmetryOps(local *l){
  int own,ptn,you,bit;
  //90度回転
  if(l->aBoard[l->BOUND2]==1){ own=1; ptn=2;
    while(own<=G.sizeE){ bit=1; you=G.sizeE;
      while((l->aBoard[you]!=ptn)&&(l->aBoard[own]>=bit)){ bit<<=1; you--; }
      if(l->aBoard[own]>bit){ return; } if(l->aBoard[own]<bit){ break; }
      own++; ptn<<=1;
    }
    /** 90度回転して同型なら180度/270度回転も同型である */
    if(own>G.sizeE){ l->COUNT2[l->BOUND1]++; return; }
  }
  //180度回転
  if(l->aBoard[G.sizeE]==l->ENDBIT){ own=1; you=G.sizeE-1;
    while(own<=G.sizeE){ bit=1; ptn=l->TOPBIT;
      while((l->aBoard[you]!=ptn)&&(l->aBoard[own]>=bit)){ bit<<=1; ptn>>=1; }
      if(l->aBoard[own]>bit){ return; } if(l->aBoard[own]<bit){ break; }
      own++; you--;
    }
    /** 90度回転が同型でなくても180度回転が同型である事もある */
    if(own>G.sizeE){ l->COUNT4[l->BOUND1]++; return; }
  }
  //270度回転
  if(l->aBoard[l->BOUND1]==l->TOPBIT){ own=1; ptn=l->TOPBIT>>1;
    while(own<=G.sizeE){ bit=1; you=0;
      while((l->aBoard[you]!=ptn)&&(l->aBoard[own]>=bit)){ bit<<=1; you++; }
      if(l->aBoard[own]>bit){ return; } if(l->aBoard[own]<bit){ break; }
      own++; ptn>>=1;
    }
  }
  l->COUNT8[l->BOUND1]++;
}
//
//CPU 非再帰版 backTrack2//新しく記述
void backTrack2_NR(int row,int h_left,int h_down,int h_right,local *l){
    unsigned int left[G.size];
    unsigned int down[G.size];
    unsigned int right[G.size];
    unsigned int bitmap[G.size];
    left[row]=h_left;
    down[row]=h_down;
    right[row]=h_right;
    bitmap[row]=l->mask&~(left[row]|down[row]|right[row]);
    unsigned int bit;
    int mark=row;
    //固定していれた行より上はいかない
    while(row>=mark){//row=1 row>=1, row=2 row>=2
      if(bitmap[row]==0){
        --row;
      }else{
	//【枝刈り】上部サイド枝刈り
	if(row<l->BOUND1){             	
	  bitmap[row]&=~l->SIDEMASK;
        //【枝刈り】下部サイド枝刈り
        }else if(row==l->BOUND2) {     	
          if((down[row]&l->SIDEMASK)==0){ row--; }
          if((down[row]&l->SIDEMASK)!=l->SIDEMASK){ bitmap[row]&=l->SIDEMASK; }
        }
        int save_bitmap=bitmap[row];
        bitmap[row]^=l->aBoard[row]=bit=(-bitmap[row]&bitmap[row]); 
        if((bit&l->mask)!=0){
          if(row==G.sizeE){
            if((save_bitmap&l->LASTMASK)==0){ 	
              symmetryOps(l);
              --row;
		    }
          }else{
            int n=row++;
            left[row]=(left[n]|bit)<<1;
            down[row]=down[n]|bit;
            right[row]=(right[n]|bit)>>1;
            bitmap[row]=l->mask&~(left[row]|down[row]|right[row]);
          }
        }else{
           --row;
        }
      }  
    }
}
//
//通常版 CPU 非再帰版 backTrack2
void backTrack2D_NR(int row,int left,int down,int right,local *l){
  int bitmap,bit;
  int b[100], *p=b;
  int odd=G.size&1; //奇数:1 偶数:0
  for(int i=0;i<(1+odd);++i){
    bitmap=0;
    if(0==i){
      int half=G.size>>1; // size/2
      bitmap=(1<<half)-1;
    }else{
      bitmap=1<<(G.size>>1);
      // down[1]=bitmap;
      // right[1]=(bitmap>>1);
      // left[1]=(bitmap<<1);
      // pnStack=aStack+1;
      // *pnStack++=0;
    }
mais1:bitmap=l->mask&~(left|down|right);
      // 【枝刈り】
      if(row==G.sizeE){
        if(bitmap){
          //【枝刈り】 最下段枝刈り
          if((bitmap&l->LASTMASK)==0){
            l->aBoard[row]=bitmap;
            symmetryOps(l);
          }
        }
      }else{
        //【枝刈り】上部サイド枝刈り
        if(row<l->BOUND1){
          bitmap&=~l->SIDEMASK;
          //【枝刈り】下部サイド枝刈り
        }else if(row==l->BOUND2){
          if(!(down&l->SIDEMASK))
            goto volta;
          if((down&l->SIDEMASK)!=l->SIDEMASK)
            bitmap&=l->SIDEMASK;
        }
        if(bitmap){
outro:bitmap^=l->aBoard[row]=bit=-bitmap&bitmap;
      if(bitmap){
        *p++=left;
        *p++=down;
        *p++=right;
      }
      *p++=bitmap;
      row++;
      left=(left|bit)<<1;
      down=down|bit;
      right=(right|bit)>>1;
      goto mais1;
      //Backtrack2(y+1, (left | bit)<<1, down | bit, (right | bit)>>1);
volta:if(p<=b)
        return;
      row--;
      bitmap=*--p;
      if(bitmap){
        right=*--p;
        down=*--p;
        left=*--p;
        goto outro;
      }else{
        goto volta;
      }
        }
      }
      goto volta;
  }
}
//CPU 非再帰版 backTrack
void backTrack1_NR(int row,int h_left,int h_down,int h_right,local *l){

    unsigned int left[G.size];
    unsigned int down[G.size];
    unsigned int right[G.size];
    unsigned int bitmap[G.size];
    left[row]=h_left;
    down[row]=h_down;
    right[row]=h_right;
    bitmap[row]=l->mask&~(left[row]|down[row]|right[row]);
    unsigned int bit;
    int mark=row;
    //固定していれた行より上はいかない
    while(row>=mark){//row=1 row>=1, row=2 row>=2
      if(bitmap[row]==0){
        --row;
      }else{
        if(row<l->BOUND1) {
          bitmap[row]&=~2; // bm|=2; bm^=2; (bm&=~2と同等)
        }
        bitmap[row]^=l->aBoard[row]=bit=(-bitmap[row]&bitmap[row]); 
        if((bit&l->mask)!=0){
          if(row==G.sizeE){
            l->COUNT8[l->BOUND1]++;
            --row;
          }else{
            int n=row++;
            left[row]=(left[n]|bit)<<1;
            down[row]=down[n]|bit;
            right[row]=(right[n]|bit)>>1;
            bitmap[row]=l->mask&~(left[row]|down[row]|right[row]);
          }
        }else{
           --row;
        }
      }  
    }

}
//通常版 CPU 非再帰版 backTrack
void backTrack1D_NR(int row,int left,int down,int right,local *l){
  int bitmap,bit;
  int b[100], *p=b;
  int odd=G.size&1; //奇数:1 偶数:0
  for(int i=0;i<(1+odd);++i){
    bitmap=0;
    if(0==i){
      int half=G.size>>1; // size/2
      bitmap=(1<<half)-1;
    }else{
      bitmap=1<<(G.size>>1);
      // down[1]=bitmap;
      // right[1]=(bitmap>>1);
      // left[1]=(bitmap<<1);
      // pnStack=aStack+1;
      // *pnStack++=0;
    }
b1mais1:bitmap=l->mask&~(left|down|right);
        //【枝刈り】１行目角にクイーンがある場合回転対称チェックを省略
        if(row==G.sizeE){
          if(bitmap){
            // l->aBoard[row]=bitmap;
            l->COUNT8[l->BOUND1]++;
          }
        }else{
          //【枝刈り】鏡像についても主対角線鏡像のみを判定すればよい
          // ２行目、２列目を数値とみなし、２行目＜２列目という条件を課せばよい
          if(row<l->BOUND1) {
            bitmap&=~2; // bm|=2; bm^=2; (bm&=~2と同等)
          }
          if(bitmap){
b1outro:bitmap^=l->aBoard[row]=bit=-bitmap&bitmap;
        if(bitmap){
          *p++=left;
          *p++=down;
          *p++=right;
        }
        *p++=bitmap;
        row++;
        left=(left|bit)<<1;
        down=down|bit;
        right=(right|bit)>>1;
        goto b1mais1;
        //Backtrack1(y+1, (left | bit)<<1, down | bit, (right | bit)>>1);
b1volta:if(p<=b)
          return;
        row--;
        bitmap=*--p;
        if(bitmap){
          right=*--p;
          down=*--p;
          left=*--p;
          goto b1outro;
        }else{
          goto b1volta;
        }
          }
        }
        goto b1volta;
  }
}
//
//CPU 再帰版 backTrack
//ここに追記
void backTrack2(int row,int left,int down,int right,local *l){
 int bitmap=0;
 int bit=0;
 bitmap=(l->mask&~(left|down|right));
 if(row==G.sizeE){
   if(bitmap){
     //【枝刈り】 最下段枝刈り
     if((bitmap&l->LASTMASK)==0){ 	
       l->aBoard[row]=(-bitmap&bitmap);
       symmetryOps(l);
     }
   }
  }else{
    //【枝刈り】上部サイド枝刈り
    if(row<l->BOUND1){             	
      bitmap&=~l->SIDEMASK;
      //【枝刈り】下部サイド枝刈り
    }else if(row==l->BOUND2) {     	
      if((down&l->SIDEMASK)==0){ return; }
      if((down&l->SIDEMASK)!=l->SIDEMASK){ bitmap&=l->SIDEMASK; }
    }
    while(bitmap){
      bitmap^=l->aBoard[row]=bit=(-bitmap&bitmap);
      backTrack2(row+1,(left|bit)<<1, down|bit,(right|bit)>>1,l);
    }
  }

}
//通常版 CPU 再帰版 backTrack
void backTrack2D(int row,int left,int down,int right,local *l){
  int bit;
  int bitmap=l->mask&~(left|down|right);
  if(row==G.sizeE){ 								// 【枝刈り】
    if(bitmap){
      if((bitmap&l->LASTMASK)==0){ 	//【枝刈り】 最下段枝刈り
        l->aBoard[row]=bitmap;
        symmetryOps(l);
      }
    }
  }else{
    if(row<l->BOUND1){             	//【枝刈り】上部サイド枝刈り
      bitmap&=~l->SIDEMASK;
    }else if(row==l->BOUND2) {     	//【枝刈り】下部サイド枝刈り
      if((down&l->SIDEMASK)==0){ return; }
      if((down&l->SIDEMASK)!=l->SIDEMASK){ bitmap&=l->SIDEMASK; }
    }
    while(bitmap){
      bitmap^=l->aBoard[row]=bit=(-bitmap&bitmap);
      backTrack2D(row+1,(left|bit)<<1,down|bit,(right|bit)>>1,l);
    }
  }
}
//
//CPU 再帰版 backTrack
//ここに追記
void backTrack1(int row,int left,int down,int right,local *l){
 int bitmap=0;
 int bit=0;
 bitmap=(l->mask&~(left|down|right));
 if(row==G.sizeE){
   if(bitmap){
     l->COUNT8[l->BOUND1]++;
   }
  }else{
    if(row<l->BOUND1) {
      bitmap&=~2; // bm|=2; bm^=2; (bm&=~2と同等)
    }
    while(bitmap){
      bitmap^=l->aBoard[row]=bit=(-bitmap&bitmap);
      backTrack1(row+1,(left|bit)<<1, down|bit,(right|bit)>>1,l);
    }
  }
}
//通常版 CPU 再帰版 backTrack
void backTrack1D(int row,int left,int down,int right,local *l){
  int bit;
  int bitmap=l->mask&~(left|down|right);
  //【枝刈り】１行目角にクイーンがある場合回転対称チェックを省略
  if(row==G.sizeE) {
    if(bitmap){
      /* l->aBoard[row]=bitmap; */
      l->COUNT8[l->BOUND1]++;
    }
  }else{
    //【枝刈り】鏡像についても主対角線鏡像のみを判定すればよい
    // ２行目、２列目を数値とみなし、２行目＜２列目という条件を課せばよい
    if(row<l->BOUND1) {
      bitmap&=~2; // bm|=2; bm^=2; (bm&=~2と同等)
    }
    while(bitmap){
      bitmap^=l->aBoard[row]=bit=(-bitmap&bitmap);
      backTrack1D(row+1,(left|bit)<<1,down|bit,(right|bit)>>1,l);
    }
  }
}
//
void *run(void *args){
  local *l=(local *)args;
  int bit=0;
  l->TOPBIT=1<<(G.size-1);
  // 最上段のクイーンが角にある場合の探索
  if(l->BOUND1>1 && l->BOUND1<G.sizeE) {
    int col=0;
    l->aBoard[0]=bit=(1<<0);
    int left=bit<<1;
    int down=bit;
    int right=bit>>1;
    if(l->BOUND1<G.sizeE) {
      // 角にクイーンを配置
      int col_j=l->BOUND1;
      l->aBoard[1]=bit=(1<<col_j);
      //２行目から探索
      if(NR==1){
        //非再帰
        backTrack1_NR(2,(left|bit)<<1,(down|bit),(right|bit)>>1,l);//GPU適用版
        //backTrack1D_NR(2,(left|bit)<<1,(down|bit),(right|bit)>>1,l);
      }else{
        //再帰
        backTrack1(2,(left|bit)<<1,(down|bit),(right|bit)>>1,l);//GPU適用版
        //backTrack1D(2,(left|bit)<<1,(down|bit),(right|bit)>>1,l);//通常版
      }
    }
  }
  l->ENDBIT=(l->TOPBIT>>l->BOUND1);
  l->SIDEMASK=l->LASTMASK=(l->TOPBIT|1);
  /* 最上段行のクイーンが角以外にある場合の探索
     ユニーク解に対する左右対称解を予め削除するには、
     左半分だけにクイーンを配置するようにすればよい */
  if(l->BOUND1>0&&l->BOUND2<G.sizeE&&l->BOUND1<l->BOUND2){
    for(int i=1; i<l->BOUND1; i++){
      l->LASTMASK=l->LASTMASK|l->LASTMASK>>1|l->LASTMASK<<1;
    }
    if(l->BOUND1<l->BOUND2) {
      int col=l->BOUND1;
      l->aBoard[0]=bit=(1<<col);
      if(NR==1){
        //printf("非再帰\n");
        backTrack2_NR(1,bit<<1,bit,bit>>1,l); //GPU適用版
        //backTrack2D_NR(1,bit<<1,bit,bit>>1,l);//通常版
      }else{
        //printf("再帰\n");
        backTrack2(1,bit<<1,bit,bit>>1,l); //GPU適用版
        //backTrack2D(1,bit<<1,bit,bit>>1,l);//通常版
      }
    }
    l->ENDBIT>>=G.size;
  }
  return 0;   //*run()の場合はreturn 0;が必要
}
//
void *NQueenThread(){
  local l[MAX];                //構造体 local型
  pthread_t pt[G.size];                 //スレッド childThread
  for(int BOUND1=G.sizeE,BOUND2=0;BOUND2<G.sizeE;BOUND1--,BOUND2++){
    l[BOUND1].mask=(1<<G.size)-1;
    l[BOUND1].BOUND1=BOUND1; l[BOUND1].BOUND2=BOUND2;         //B1 と B2を初期化
    for(int j=0;j<G.size;j++){ l[l->BOUND1].aBoard[j]=j; } // aB[]の初期化
    l[BOUND1].COUNT2[BOUND1]=l[BOUND1].COUNT4[BOUND1]=l[BOUND1].COUNT8[BOUND1]=0;//カウンターの初期化
    // チルドスレッドの生成
    int iFbRet=pthread_create(&pt[BOUND1],NULL,&run,&l[BOUND1]);
    if(iFbRet>0){
      printf("[mainThread] pthread_create #%d: %d\n", l[BOUND1].BOUND1, iFbRet);
    }
  }
  for(int BOUND1=G.sizeE,BOUND2=0;BOUND2<G.sizeE;BOUND1--,BOUND2++){
    pthread_join(pt[BOUND1],NULL);
  }
  //スレッド毎のカウンターを合計
  for(int BOUND1=G.sizeE,BOUND2=0;BOUND2<G.sizeE;BOUND1--,BOUND2++){
    G.lTOTAL+=l[BOUND1].COUNT2[BOUND1]*2+l[BOUND1].COUNT4[BOUND1]*4+l[BOUND1].COUNT8[BOUND1]*8;
    G.lUNIQUE+=l[BOUND1].COUNT2[BOUND1]+l[BOUND1].COUNT4[BOUND1]+l[BOUND1].COUNT8[BOUND1];
  }
  return 0;
}
//
void NQueen(){
  pthread_t pth;  //スレッド変数
  int iFbRet;
  // メインスレッドの生成
  // 拡張子 CUDA はpthreadをサポートしていませんので実行できません
  // コンパイルが通らないので 以下をコメントアウトします
  // Cディレクトリの 並列処理はC13_N-Queen.c を参考にして下さい。
  //iFbRet = pthread_create(&pth, NULL,&NQueenThread,NULL);
  if(iFbRet>0){
    printf("[main] pthread_create: %d\n", iFbRet); //エラー出力デバッグ用
  }
  pthread_join(pth,NULL); /* いちいちjoinをする */
}
//メインメソッド
int main(int argc,char** argv) {
  bool cpu=false,cpur=false,gpu=false;
  int argstart=1,steps=24576;
  /** パラメータの処理 */
  if(argc>=2&&argv[1][0]=='-'){
    if(argv[1][1]=='c'||argv[1][1]=='C'){cpu=true;}
    else if(argv[1][1]=='r'||argv[1][1]=='R'){cpur=true;}
    else if(argv[1][1]=='g'||argv[1][1]=='G'){gpu=true;}
    else
      cpur=true;
    argstart=2;
  }
  if(argc<argstart){
    printf("Usage: %s [-c|-g|-r] n steps\n",argv[0]);
    printf("  -c: CPU only\n");
    printf("  -r: CPUR only\n");
    printf("  -g: GPU only\n");
    printf("Default to 8 queen\n");
  }
  /** 出力と実行 */
  if(cpu){
    printf("\n\n１３．CPU 非再帰 並列処理 pthread\n※nvccではpthreadは動きません！\n");
  }else if(cpur){
    printf("\n\n１３．CPUR 再帰 並列処理 pthread\n※nvccではpthreadは動きません！\n");
  }else if(gpu){
    printf("\n\n１３．GPU 非再帰 並列処理 CUDA\n");
  }
  if(cpu||cpur){
    printf("%s\n"," N:           Total           Unique          dd:hh:mm:ss.ms");
    struct timeval t0;
    struct timeval t1;
    int min=4; int targetN=18;
    for(int i=min;i<=targetN;i++){
      //TOTAL=0; UNIQUE=0;
      G.size=i; G.sizeE=i-1; //初期化
      G.lTOTAL=G.lUNIQUE=0;
      gettimeofday(&t0, NULL);
      //再帰
      if(cpur){
        //NR=0;NQueenD();
        NR=0;NQueen();
      }
      //非再帰
      if(cpu){ 
        //NR=1;NQueenD();
        NR=1;NQueen();
      }
      gettimeofday(&t1, NULL);
      int ss;int ms;int dd;
      if(t1.tv_usec<t0.tv_usec) {
        dd=(t1.tv_sec-t0.tv_sec-1)/86400;
        ss=(t1.tv_sec-t0.tv_sec-1)%86400;
        ms=(1000000+t1.tv_usec-t0.tv_usec+500)/10000;
      }else {
        dd=(t1.tv_sec-t0.tv_sec)/86400;
        ss=(t1.tv_sec-t0.tv_sec)%86400;
        ms=(t1.tv_usec-t0.tv_usec+500)/10000;
      }
      int hh=ss/3600;
      int mm=(ss-hh*3600)/60;
      ss%=60;
      printf("%2d:%16ld%17ld%12.2d:%02d:%02d:%02d.%02d\n", i,G.lTOTAL,G.lUNIQUE,dd,hh,mm,ss,ms);
    }
  }
  if(gpu){
    if(!InitCUDA()){return 0;}
    int min=4;int targetN=18;
    struct timeval t0;struct timeval t1;int ss;int ms;int dd;
    printf("%s\n"," N:          Total        Unique                 dd:hh:mm:ss.ms");
    for(int i=min;i<=targetN;i++){
      gettimeofday(&t0,NULL);   // 計測開始
      Total=solve_nqueen_cuda(i,steps);
      gettimeofday(&t1,NULL);   // 計測終了
      if (t1.tv_usec<t0.tv_usec) {
        dd=(int)(t1.tv_sec-t0.tv_sec-1)/86400;
        ss=(t1.tv_sec-t0.tv_sec-1)%86400;
        ms=(1000000+t1.tv_usec-t0.tv_usec+500)/10000;
      } else {
        dd=(int)(t1.tv_sec-t0.tv_sec)/86400;
        ss=(t1.tv_sec-t0.tv_sec)%86400;
        ms=(t1.tv_usec-t0.tv_usec+500)/10000;
      }
      int hh=ss/3600;
      int mm=(ss-hh*3600)/60;
      ss%=60;
      printf("%2d:%18ld%18ld%12.2d:%02d:%02d:%02d.%02d\n", i,Total,Unique,dd,hh,mm,ss,ms);
    }
  }
  return 0;
}
