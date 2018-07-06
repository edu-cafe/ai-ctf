/* 개미무리 최적화법(aco) 프로그램 : aco를 이용하여 최적값을 학습 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NOA 10 		/*개미의 개체 수*/
#define ILIMIT 50 	/*반복 횟수*/
#define Q 3 		/*페로몬 갱신 정의*/
#define RHO 0.8 	/*증발 상수*/
#define STEP 10 	/*길 선택 단계 수*/
#define EPSILON 0.15 /*행동 선택의 무작위성을 결정*/
#define SEED 32768 	/*난수 시드*/

/*   함수 프로토타입 선언      */
void printp(double phero[2][STEP]) ;	/*표시*/
void printmstep(int mstep[NOA][STEP]) ;		/*개미의 행동 표시*/
void walk(int cost[2][STEP],double phero[2][STEP]
          ,int mstep[NOA][STEP] ) ;
/*페로몬 갱신*/
void update(int cost[2][STEP],double phero[2][STEP]
        ,int mstep[NOA][STEP] ) ;
double rand1() ;	/*0～1사이의 실수를 반환하는 난수 함수*/
int rand01() ;		/*0 또는 1을 반환하는 난수 함수*/

int main()
{
 int cost[2][STEP]={			/*각 단계의 비용(거리)*/
	 {1,1,1,1,1,1,1,1,1,1},
	 {5,5,5,5,5,5,5,5,5,5}};
 double phero[2][STEP]={0} ;/*각 단계의 페로몬 양*/
 int mstep[NOA][STEP] ;			/*개미가 걸은 과정*/
 int i;							/*반복 횟수 제어*/
 
 /*난수 초기화*/
 srand(SEED);

 /*최적화*/
 for(i=0;i<ILIMIT;++i){
  /*페로몬 상태 출력*/
  printf("%d:\n",i) ;
  printp(phero) ;
  /*개미를 걷게 함*/
  walk(cost,phero,mstep) ;
  /*페로몬 갱신*/
  update(cost,phero,mstep) ;
 }
 
 return 0 ;
}

/* update() 함수 : 페로몬 갱신 */
void update(int cost[2][STEP]
 ,double phero[2][STEP],int mstep[NOA][STEP] )
{
 int m ;			/*개미의 개체 변호*/
 int lm ;			/*개미가 걸은 거리*/
 int i,j ;
 double sum_lm=0 ;	/*개미가 걸은 합계 거리*/
 
 /*페로몬 증발*/
 for(i=0;i<2;++i)
  for(j=0;j<STEP;++j) phero[i][j]*=RHO ;

 /*개미에 의한 덧칠*/
 for(m=0;m<NOA;++m){
  /*개체 m의 이동 거리 lm을 계산*/
  lm=0 ;
  for(i=0;i<STEP;++i) lm+=cost[mstep[m][i]][i] ;

  /*페로몬 덧칠*/
  for(i=0;i<STEP;++i) phero[mstep[m][i]][i]+=Q*(1.0/lm) ;
  sum_lm+=lm ;
 }
 /*개미가 걸은 평균 거리를 출력*/
 printf("%lf\n",sum_lm/NOA) ;
}

/*    walk() 함수 : 개미를 걷게 함      */
void walk(int cost[2][STEP]
 ,double phero[2][STEP],int mstep[NOA][STEP])
{
 int m ;	/*개미의 개체 번호*/
 int s ;	/*개미의 현재 단계 위치*/

 for(m=0;m<NOA;++m){
  for(s=0;s<STEP;++s){
   /*ε-greedy법을 이용한 행동 선택*/
   if((rand1()<EPSILON) ||(abs(phero[0][s]-phero[1][s])<1e-9))
   {/*무작위 행동*/
    mstep[m][s]=rand01() ;
   } else{/*페로몬 농도에 따른 선택*/
    if(phero[0][s]>phero[1][s]) mstep[m][s]=0 ;
    else mstep[m][s]=1 ;
   }
  }
 }
 /*개미의 행동 출력*/
 printmstep(mstep) ;
}

/*  printmstep() 함수 : 개미의 행동 표시       */
void printmstep(int mstep[NOA][STEP])
{
 int i,j ;

 printf("*mstep\n") ;
 for(i=0;i<NOA;++i){
  for(j=0;j<STEP;++j) printf("%d ",mstep[i][j]) ;
  printf("\n") ;
 }
}

/*    printp() 함수 : 페로몬 표시          */
void printp(double phero[2][STEP]) 
{
 int i,j ;

 for(i=0;i<2;++i){
  for(j=0;j<STEP;++j) printf("%4.2lf ",phero[i][j]) ;
  printf("\n") ;
 }
}

/*    rand1() 함수 : 0～1사이의 실수를 반환하는 난수 함수  */
double rand1()
{
 /*난수의 계산*/
 return (double)rand()/RAND_MAX ;
}

/*     rand01() 함수 : 0 또는 1을 반환하는 난수 함수 */
int rand01()
{
 int rnd ;
 
 /*난수의 최댓값 제외*/
 while((rnd=rand())==RAND_MAX) ;
 /*난수의 계산*/ 
 return (int)((double)rnd/RAND_MAX*2) ;
}
