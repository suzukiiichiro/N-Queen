/**

 Javaで学ぶ「アルゴリズムとデータ構造」
 ステップバイステップでＮ−クイーン問題を最適化
 一般社団法人  共同通信社  情報技術局  鈴木 維一郎(suzuki.iichiro@kyodonews.jp)
 

 Java/C/Lua/Bash版
 https://github.com/suzukiiichiro/N-Queen 
 			

コンパイル
javac -cp .:commons-lang3-3.4.jar Java07_NQueen.java ;

実行
java  -cp .:commons-lang3-3.4.jar: -server -Xms4G -Xmx8G -XX:-HeapDumpOnOutOfMemoryError -XX:NewSize=256m -XX:MaxNewSize=256m -XX:-UseAdaptiveSizePolicy -XX:+UseConcMarkSweepGC Java07_NQueen  ;

 ７．バックトラック＋ビットマップ＋対称解除法

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

  実行結果
 N:            Total       Unique     hh:mm:ss.SSS
 4:                2            1     00:00:00.000
 5:               10            2     00:00:00.000
 6:                4            1     00:00:00.000
 7:               40            6     00:00:00.000
 8:               92           12     00:00:00.001
 9:              352           46     00:00:00.002
10:              724           92     00:00:00.002
11:             2680          341     00:00:00.005
12:            14200         1787     00:00:00.016
13:            73712         9233     00:00:00.086
14:           365596        45752     00:00:00.452
15:          2279184       285053     00:00:03.003
16:         14772512      1846955     00:00:20.812
17:         95815104     11977939     00:02:38.799  
  
 */
//
import org.apache.commons.lang3.time.DurationFormatUtils;
//
class Java07_NQueen{
  //グローバル変数
  private int size;
  private int board[];
  private int MASK;
  private int aT[];
  private int aS[];
  private int bit;
  private int COUNT2,COUNT4,COUNT8;
  //
  public int rh(int a,int sz){
    int tmp=0;
    for(int i=0;i<=sz;i++){
      if( (a&(1<<i))!=0){ return tmp|=(1<<(sz-i)); }
    }
    return tmp;
  }
  //
  public void vMirror_bitmap(int bf[],int af[],int si){
    int score ;
    for(int i=0;i<si;i++) {
      score=bf[i];
      af[i]=rh(score,si-1);
    }
  }
  //
  public void rotate_bitmap(int bf[],int af[],int si){
    for(int i=0;i<si;i++){
      int t=0;
      for(int j=0;j<si;j++){
        t|=((bf[j]>>i)&1)<<(si-j-1); // x[j] の i ビット目を
      }
      af[i]=t;                        // y[i] の j ビット目にする
    }
  }
  //
  public int intncmp(int lt[],int rt[],int n){
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
  public long getUnique(){
    return COUNT2+COUNT4+COUNT8;
  }
  //
  public long getTotal(){
    return COUNT2*2+COUNT4*4+COUNT8*8;
  }
  //
  public void symmetryOps_bitmap(){
    int nEquiv;
    // 回転・反転・対称チェックのためにboard配列をコピー
    for(int i=0;i<size;i++){ aT[i]=board[i];}
    rotate_bitmap(aT,aS,size);    //時計回りに90度回転
    int k=intncmp(board,aS,size);
    if(k>0)return;
    if(k==0){ nEquiv=2;}else{
      rotate_bitmap(aS,aT,size);  //時計回りに180度回転
      k=intncmp(board,aT,size);
      if(k>0)return;
      if(k==0){ nEquiv=4;}else{
        rotate_bitmap(aT,aS,size);//時計回りに270度回転
        k=intncmp(board,aS,size);
        if(k>0){ return;}
        nEquiv=8;
      }
    }
    // 回転・反転・対称チェックのためにboard配列をコピー
    for(int i=0;i<size;i++){ aS[i]=board[i];}
    vMirror_bitmap(aS,aT,size);   //垂直反転
    k=intncmp(board,aT,size);
    if(k>0){ return; }
    if(nEquiv>2){             //-90度回転 対角鏡と同等
      rotate_bitmap(aT,aS,size);
      k=intncmp(board,aS,size);
      if(k>0){return;}
      if(nEquiv>4){           //-180度回転 水平鏡像と同等
        rotate_bitmap(aS,aT,size);
        k=intncmp(board,aT,size);
        if(k>0){ return;}       //-270度回転 反対角鏡と同等
        rotate_bitmap(aT,aS,size);
        k=intncmp(board,aS,size);
        if(k>0){ return;}
      }
    }
    if(nEquiv==2){COUNT2++;}
    if(nEquiv==4){COUNT4++;}
    if(nEquiv==8){COUNT8++;}
  }
  //
  public void NQueen(int row,int left,int down,int right){
    int bitmap=(MASK&~(left|down|right));
    if(row==size){
       if(bitmap==0){
        board[row]=bitmap;
        symmetryOps_bitmap();
       }
    }else{
      while(bitmap>0){
         bit=(-bitmap&bitmap);
         bitmap=(bitmap^bit);
         board[row]=bit;
        NQueen(row+1,(left|bit)<<1,down|bit,(right|bit)>>1);
      }
    }
  }
  //
  public Java07_NQueen(){
    int min=4;
    int max=17;
		System.out.println(" N:            Total       Unique     hh:mm:ss.SSS");
    for(int i=min;i<=max;i++){
      COUNT2=COUNT4=COUNT8=0;
      MASK=(1<<i)-1;
      board=new int[i+1];
      aT=new int[i+1];
      aS=new int[i+1];
      for(int j=0;j<=i;j++){
        board[j]=j;
      }
      size=i;
			long start=System.currentTimeMillis();
			NQueen(0,0,0,0); // ０列目に王妃を配置してスタート
			long end=System.currentTimeMillis();
			String TIME=DurationFormatUtils.formatPeriod(start,end,"HH:mm:ss.SSS");
			System.out.printf("%2d:%17d%13d%17s%n",size,getTotal(),getUnique(),TIME);
    }
  }
  //
	public static void main(String[] args){
		new Java07_NQueen();
	}
}

