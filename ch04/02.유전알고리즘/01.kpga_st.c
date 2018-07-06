/* kpga.c : GA(Genetic Alogorithm, 유전알고리즘)를 이용한 배낭 문제 해결 프로그램 */
/* GA를 이용하여 배낭 문제의 가장 좋은 해답을 탐색   */
/* $kpga < data.txt            */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXVALUE 100 				/* 무게와 가치의 최댓값*/
#define N 30 						/*짐の개수*/
#define WEIGHTLIMIT (N*MAXVALUE/4) 	/*무게 제한*/
#define POOLSIZE 30 				/*풀 크기*/
#define LASTG 50    				/*끝 세대*/
#define MRATE 0.01  				/*돌연변이의 확률*/
#define YES 1   					/*yes에 해당하는 정수*/
#define NO 0    					/*no에 해당하는 정수 */
#define SEED 32767

void initparcel(void);			/*짐 초기화*/
int evalfit(int gene[]) ; 	/*적응도 계산*/
/*교차*/
void mating(int pool[POOLSIZE][N],int ngpool[POOLSIZE*2][N]) ; 
void mutation(int ngpool[POOLSIZE*2][N]) ; /*돌연변이*/
void printp(int pool[POOLSIZE][N]) ; /*결과 출력*/
void initpool(int pool[POOLSIZE][N]) ; /*초기 집단 생성*/
int rndn() ; /*n미만의 난수 생성  */
int notval(int v) ;/*진릿값 반전*/
int selectp(int roulette[POOLSIZE],int totalfitness) ;/*부모 선택*/
void crossing(int m[],int p[],int c1[],int c2[]) ; /* 특정 염색체 2개를 교차 */
/*다음 세대 선택*/
void selectng(int ngpool[POOLSIZE*2][N],int pool[POOLSIZE][N]) ;

/*전역 변수(짐 데이터)*/
 int parcel[N][2] ;/*짐*/

int main(int argc,char *argv[])
{
 int pool[POOLSIZE][N] ; 		/*염색체 풀*/
 int ngpool[POOLSIZE*2][N] ; 	/*다음 세대 염색체 풀*/
 int generation;				/* 현재 세대 수 */
 
 /*난수 초기화*/
 srand(SEED);

 /*짐 초기화*/
 initparcel() ;
 
 /*초기 집단 생성*/
 initpool(pool) ;
 
 /*끝 세대까지 반복*/
 for(generation=0;generation<LASTG;++generation){
  printf("-->%d세대\n",generation) ;
  mating(pool,ngpool) ;			/*교차*/
  mutation(ngpool) ;			/*돌연변이*/
  selectng(ngpool,pool) ;		/*다음 세대 선택*/
  printp(pool) ;				/*결과 출력*/
 }
 return 0 ;
}

/*      initparcel() 함수 : 짐 초기화          */
//$kpga < data.txt
void initparcel(void)
{
 int i=0 ;
 while((i<N) && 
  (scanf("%d %d",&parcel[i][0],&parcel[i][1])
                 !=EOF)){
  ++i ;
 }
}

/*   selectng() 함수 : 다음 세대 선택     */
void selectng(int ngpool[POOLSIZE*2][N]
              ,int pool[POOLSIZE][N]) 
{
 int i,j,c ;				/* 반복 제어 변수 */
 int totalfitness=0 ;		/*적응도 합계*/
 int roulette[POOLSIZE*2] ;	/*적응도 저장*/
 int ball ;					/* 공(선택 위치의 수치)*/
 int acc=0 ;				/*적응도 계산 값*/
 
 /*선택을 반복*/
 for(i=0;i<POOLSIZE;++i){
  /* 룰렛 작성 */
  totalfitness=0 ;
  for(c=0;c<POOLSIZE*2;++c){
   roulette[c]=evalfit(ngpool[c]) ;
   /* 적응도 합계 계산*/
   totalfitness+=roulette[c] ;
  }
  /*염색체 하나를 선택*/
  ball=rndn(totalfitness) ;
  acc=0 ;
  for(c=0;c<POOLSIZE*2;++c){
   acc+=roulette[c] ;	/*적응도 더하기*/
   if(acc>ball) break ;	/*해당하는 유전자*/
  }

  /*염색체 복사*/
  for(j=0;j<N;++j){
   pool[i][j]=ngpool[c][j] ;
  }
 }
}

/*   selectp() 함수 : 부모 선택          */
int selectp(int roulette[POOLSIZE],int totalfitness)
{
 int i ;/* 반복 제어 변수 */
 int ball ;/* 공(선택 위치의 수치)*/
 int acc=0 ;/*적응도 계산 값*/

 ball=rndn(totalfitness) ;
 for(i=0;i<POOLSIZE;++i){
  acc+=roulette[i] ;/*적응도 더하기*/
  if(acc>ball) break ;/*해당하는 유전자*/
 }
 return i ;
}

/*   mating() 함수 : 교차          */
void mating(int pool[POOLSIZE][N],int ngpool[POOLSIZE*2][N])
{
 int i ;/* 반복 제어 변수 */
 int totalfitness=0 ;/*적응도 합계*/
 int roulette[POOLSIZE] ;/*적응도 저장*/
 int mama,papa ;/*부모 유전자 번호*/

 /* 룰렛 작성*/
 for(i=0;i<POOLSIZE;++i){
  roulette[i]=evalfit(pool[i]) ;
  /* 적응도 합계계산*/
  totalfitness+=roulette[i] ;
 }

 /*선택과 교차를 반복*/
 for(i=0;i<POOLSIZE;++i){
  do{/*부모 선택*/
   mama=selectp(roulette,totalfitness) ;
   papa=selectp(roulette,totalfitness) ;
  }while(mama==papa) ;    //중복제거

  /*특정 유전자 2개를 교차*/
  crossing(pool[mama],pool[papa]
            ,ngpool[i*2],ngpool[i*2+1])  ;  
 }
}

/*  crossing() 함수 : 특정 염색체 2개를 교차 */
void crossing(int m[],int p[],int c1[],int c2[])
{
 int j ;/* 반복 제어 변수 */
 int cp ;/*교차하는 점*/

 /*교차점 결정*/
 cp =rndn(N) ;

 /*앞부분 복사*/
 for(j=0;j<cp;++j){
  c1[j]=m[j] ;
  c2[j]=p[j] ;
 }
 /*뒷부분 복사*/
 for(;j<N;++j){
  c2[j]=m[j] ;
  c1[j]=p[j] ;
 }
}

/*   evalfit() 함수 : 적응도 계산        */
int evalfit(int g[])
{
 int pos ;/*유전자 위치 지정*/
 int value=0 ;/*평갓값*/
 int weight=0 ;/*중량*/

 /*각 유전자 위치를 조사하여 중량과 평갓값을 계산*/
 for(pos=0;pos<N;++pos){
  weight+=parcel[pos][0]*g[pos] ;
  value+=parcel[pos][1]*g[pos] ;
 }
 /*죽은 유전자 처리*/
 if(weight>=WEIGHTLIMIT) value=0 ;
 return value;
}

/*   printp() 함수 : 결과 출력         */
void printp(int pool[POOLSIZE][N])
{
 int i,j ;/* 반복 제어 변수 */
 int fitness ;/* 적응도 */
 double totalfitness=0 ;/* 적응도 합계 */
 int elite,bestfit=0 ;/*엘리트 유전자 처리용 변수*/

 for(i=0;i<POOLSIZE;++i){
  for(j=0;j<N;++j) printf("%1d",pool[i][j]) ;
  fitness=evalfit(pool[i]) ;
  printf("\t%d\n",fitness) ;
  if(fitness>bestfit){/*엘리트 정답*/
   bestfit=fitness ;
   elite=i ;
  }
  totalfitness+=fitness ;
 }
 /*엘리트 정답의 적응도 출력*/
 printf("%d\t%d \t",elite,bestfit) ;
 /*평균 적응도 출력*/
 printf("%lf\n",totalfitness/POOLSIZE) ;
}

/*   initpool() 함수 : 초기 집단 생성    */
void initpool(int pool[POOLSIZE][N])
{
 int i,j ;/* 반복 제어 변수 */

 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<N;++j)
   pool[i][j]=rndn(2) ;
}

/*   rndn() 함수 : n 미만의 난수 생성 */
int rndn(int l)
{
 int rndno ;/*생성한 난수*/

 while((rndno=((double)rand()/RAND_MAX)*l)==l) ;

 return rndno;
}

/*   mutation() 함수 : 돌연변이          */
void mutation(int ngpool[POOLSIZE*2][N])
{
 int i,j ;/* 반복 제어 변수 */

 for(i=0;i<POOLSIZE*2;++i)
  for(j=0;j<N;++j)
   if((double)rndn(100)/100.0<=MRATE)
    /*반전 돌연변이*/
    ngpool[i][j]=notval(ngpool[i][j]) ;
}

/*   notval() 함수 : 진릿값 반전        */
int notval(int v)
{
 if(v==YES) return NO ;
 else return YES ;
}