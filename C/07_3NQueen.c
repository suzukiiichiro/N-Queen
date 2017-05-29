/**
  C$B$G3X$V%"%k%4%j%:%`$H%G!<%?9=B$(B  
  $B%9%F%C%W%P%$%9%F%C%W$G#N!]%/%$!<%sLdBj$r:GE,2=(B
  $B0lHL<RCDK!?M(B  $B6&F1DL?.<R(B  $B>pJs5;=Q6I(B  $BNkLZ(B  $B0]0lO:(B(suzuki.iichiro@kyodonews.jp)
  
  Java$BHG(B N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_N-Queen
  Bash$BHG(B N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_Bash
  Lua$BHG(B  N-Queen
  https://github.com/suzukiiichiro/AI_Algorithm_Lua
 
 
 
  N-Queens$BLdBj$H$O(B
  https://ja.wikipedia.org/wiki/$B%(%$%H!&%/%$!<%s(B
     N$B%/%$!<%sLdBj$H$O!"!V(B8$BNs!_(B8$B9T$N%A%'%9%\!<%I$K(B8$B8D$N%/%$!<%s$r!"8_$$$K8z$-$,(B
     $BEv$?$i$J$$$h$&$KJB$Y$h!W$H$$$&#8%/%$!<%sLdBj$N%/%$!<%s(B(N)$B$r!"$I$3$^$GBg$-(B
     $B$J(BN$B$^$G2r$r5a$a$k$3$H$,$G$-$k$+$H$$$&LdBj!#(B
     $B%/%$!<%s$H$O!"%A%'%9$G;H$o$l$F$$$k%/%$!<%s$r;X$7!"%A%'%9HW$NCf$G!"=D!"2#!"(B
     $B<P$a$K$I$3$^$G$b?J$`$3$H$,$G$-$k6p$G!"F|K\$N>-4}$G$$$&!VHt<V$H3Q!W$r9g$o(B
     $B$;$?F0$-$H$J$k!##8Ns!_#89T$G9=@.$5$l$k0lHLE*$J%A%'%9%\!<%I$K$*$1$k(B8-Queens
     $BLdBj$N2r$O!"2r$NAm?t$O(B92$B8D$G$"$k!#Hf3SE*C1=c$JLdBj$J$N$G!"3XIt%l%Y%k$N1i(B
     $B=,LdBj$H$7$F<h$j>e$2$i$l$k$3$H$,B?$$!#(B
     8-Queens$BLdBjDxEY$G$"$l$P!"?MNO$^$?$O%W%m%0%i%`$K$h$k!VNO$^$+$;C5:w!W$G$b(B
     $B2r$r5a$a$k$3$H$,$G$-$k$,!"(BN$B$,Bg$-$/$J$k$H2r$,0l5$$KGzH/$7!"<BMQE*$J;~4V$G(B
     $B$O2r$1$J$/$J$k!#(B
     $B8=:_$9$Y$F$N2r$,H=L@$7$F$$$k$b$N$O!"(B2004$BG/$KEE5$DL?.Bg3X$G(B264CPU$B!_(B20$BF|$r$+(B
     $B$1$F(Bn=24$B$r2r7h$7@$3&0l$K!"$=$N8e(B2005 $BG/$K%K%C%D%!Bg3X$G(Bn=25$B!"(B2016$BG/$K%I%l(B
     $B%9%G%s9)2JBg3X$G(Bn=27$B$N2r$r5a$a$k$3$H$K@.8y$7$F$$$k!#(B
 
 	$B%9%F%C%W%P%$%9%F%C%W$G#N!]%/%$!<%sLdBj$r:GE,2=(B
   $B#1!%%V%k!<%H%U%)!<%9!JNO$^$+$;C5:w!K(B NQueen1()
   $B#2!%%P%C%/%H%i%C%/(B                   NQueen2()
 <>$B#3!%G[CV%U%i%0!J@)Ls%F%9%H9bB.2=!K(B   NQueen3()
   $B#4!%BP>N2r=|K!(B($B2sE>$H<P<4!K(B          NQueen4()
   $B#5!%%S%C%H%^%C%W(B                     NQueen7()
   $B#6!%%^%k%A%9%l%C%I(B                   NQueen8()

  $B#3!%%P%C%/%H%i%C%/(B
   $B!!3FNs!"BP3Q@~>e$K%/%$!<%s$,$"$k$+$I$&$+$N%U%i%0$rMQ0U$7!"ESCf$G@)Ls$rK~$?(B
   $B$5$J$$;v$,L@$i$+$J>l9g$O!"$=$l0J9_$N%Q%?!<%s@8@.$r9T$o$J$$!#(B
   $B!!3FNs!"BP3Q@~>e$K%/%$!<%s$,$"$k$+$I$&$+$N%U%i%0$rMQ0U$9$k$3$H$G9bB.2=$r?^$k!#(B
   $B!!$3$l$^$G$O9TJ}8~$HNsJ}8~$K=EJ#$7$J$$AH$_9g$o$;$rNs5s$9$k$b$N$G$9$,!"2&H^(B
   $B$O<P$aJ}8~$N%3%^$r$H$k$3$H$,$G$-$k$N$G!"$I$N<P$a%i%$%s>e$K$b2&H^$r$R$H$D$@(B
   $B$1$7$+G[CV$G$-$J$$@)8B$r2C$($k;v$K$h$j!"?<$5M%@hC5:w$GA4$F$NMU$rK,Ld$;$:LZ(B
   $B$r9_$j$F$b2r$,$J$$$HH=L@$7$?;~E@$GLZ$r0z$-JV$9$H$$$&$3$H$,$G$-$^$9!#(B
 
 
	 $B<B9T7k2L(B
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
 *
 */
#include <stdio.h>
#include <time.h>

#define MAXSIZE 27

int iTotal=1 ;
int iUnique=0;
int iSize;
int colChk [2*MAXSIZE-1];
int diagChk[2*MAXSIZE-1];
int antiChk[2*MAXSIZE-1];
int aBoard[MAXSIZE];

void TimeFormat(clock_t utime, char *form) {
    int dd,hh,mm;
    float ftime,ss;
    ftime=(float)utime/CLOCKS_PER_SEC;
    mm=(int)ftime/60;
    ss=ftime-(float)(mm * 60);
    dd=mm/(24*60);
    mm=mm%(24*60);
    hh=mm/60;
    mm=mm%60;
    if (dd) sprintf(form,"%4d %02d:%02d:%05.2f",dd,hh,mm,ss);
    else if (hh) sprintf(form, "     %2d:%02d:%05.2f",hh,mm,ss);
    else if (mm) sprintf(form, "        %2d:%05.2f",mm,ss);
    else sprintf(form, "           %5.2f",ss);
}
void NQueen3(int row){
  if(row==iSize){
    iTotal++;
  }else{
    for(int col=0;col<iSize;col++){
      aBoard[row]=col ;
      if(colChk[col]==0 && diagChk[row-col+(iSize-1)]==0 && antiChk[row+col]==0){
        colChk[col]=diagChk[row-aBoard[row]+iSize-1]=antiChk[row+aBoard[row]]=1; 
        NQueen3(row+1); 
        colChk[col]=diagChk[row-aBoard[row]+iSize-1]=antiChk[row+aBoard[row]]=0; 
      }
    }  
  }
}
int main(void) {
  clock_t st; 
  char t[20];
  printf("%s\n"," N:        Total       Unique        hh:mm:ss.ms");
  for(int i=2;i<=MAXSIZE;i++){
    iSize=i;
    iTotal=0; 
    iUnique=0; 
    for(int j=0;j<iSize;j++){
      aBoard[j]=j;
    }
    st=clock();
    NQueen3(0);
    TimeFormat(clock()-st,t);
    printf("%2d:%13d%16d%s\n",iSize,iTotal,iUnique,t) ;
  } 
}

