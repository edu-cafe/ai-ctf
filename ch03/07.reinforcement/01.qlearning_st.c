// 강화학습(Q 학습) 예제 프로그램 : 미로 탐색 학습
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//#define GENMAX  1000	/*학습 반복 횟수*/
#define NODENO  15	/*Ｑ 값의 노드 */
#define ALPHA 0.1	/*학습 계수*/
#define GAMMA 0.9	/* 할인율*/
#define EPSILON 0.3	/*행동 선택의 무작위성 결정 */
#define SEED 32767	/*난수 시드*/

/* 함수 프로그램 선언  */
int rand100() ;		/*0～100을 반환하는 난수 함수*/
int rand01() ;		/*0 또는 1을 반환하는 난수 함수*/
double rand1() ;	/*0～1 사이의 실수를 반환하는 난수 함수*/
void printqvalue(int qvalue[NODENO]);	/*Q 값 출력*/
int selecta(int s,int qvalue[NODENO]);	/*행동 선택*/
int updateq(int s,int qvalue[NODENO]);	/*Q 값 갱신*/

int main(int argc, char *argv[])
{
 int i;
 int s;/*상태*/
 int t;/*시각*/
 int qvalue[NODENO] = {0,};/*Q 값*/
 int GENMAX = 1000;
 if(argc==2) GENMAX = atoi(argv[1]);

 srand(SEED);/*난수 초기화*/

 /*Ｑ 값 초기화*/
 for(i=1;i<NODENO;++i) qvalue[i]=rand100() ;
 printf("Init_Val ->");
 printqvalue(qvalue) ;

 /*실제 학습*/
 for(i=0;i<GENMAX;++i){
  s=0;/*행동 초기 상태*/
  for(t=0;t<3;++t){/*가장 아랫단까지 반복*/
   /*행동 선택*/
   s=selecta(s,qvalue) ;
   
   /*Q 값 갱신*/
   qvalue[s]=updateq(s,qvalue) ;
  }
  /*Q 값 출력*/
  printf("step_%04d->", i);
  printqvalue(qvalue) ;
 }
 return 0;
}

/****************************/
/*       updateq() 함수     */
/*       Q 값 갱신          */
/****************************/
int updateq(int s,int qvalue[NODENO])
{
 int qv ;/*갱신되는 Q 값*/
 int qmax ;/*Ｑ 값의 최댓값*/
 
 /*가장 아랫단일 때*/
 if(s>6){
  if(s==14)/*보상 부여*/ qv=qvalue[s]+ALPHA*(1000-qvalue[s]) ;
  else/*보상 없음*/ qv=qvalue[s] ;
 }
 /*가장 아랫단 이외*/
 else{
  if((qvalue[2*s+1])>(qvalue[2*s+2])) qmax=qvalue[2*s+1];
  else qmax=qvalue[2*s+2];
  qv=qvalue[s]+ALPHA*(GAMMA*qmax-qvalue[s]) ;
 }

 return qv ;
}

/****************************/
/*        selecta() 함수    */
/*        행동 선택         */
/****************************/
int selecta(int olds,int qvalue[NODENO])
{
 int s ;
 
 /*ε-greedy 법을 이용한 행동 선택*/
 if(rand1()<EPSILON){
  /*무작위로 행동*/
  if(rand01()==0) s=2*olds+1 ;
  else s=2*olds+2 ;
 }
 else{
  /*Ｑ 값 최댓값을 선택*/
  if((qvalue[2*olds+1])>(qvalue[2*olds+2])) 
   s=2*olds+1;
  else s=2*olds+2;
 }

 return s ;
}

/****************************/
/*    printqvalue()함수     */
/*    Q 값 출력             */
/****************************/
void printqvalue(int qvalue[NODENO])
{
 int i ;
 
 for (i=1;i<NODENO;++i) printf("%03d ",qvalue[i]);

 printf("\n");
}

/***********************************/
/*     rand1() 함수                */
/*0～1 사이의 실수 반환 난수 함수  */
/***********************************/
double rand1()
{
 /*난수 계산*/ 
 return (double)rand()/RAND_MAX ;
}

/***********************************/
/*     rand01() 함수               */
/*   0 또는 1을 반환하는 난수 함수 */
/***********************************/
int rand01()
{
 int rnd ;
 
 /*난수 최댓값을 제외*/
 while((rnd=rand())==RAND_MAX) ;
 /*난수 계산*/ 
 return (int)((double)rnd/RAND_MAX*2) ;
}

/**********************************/
/*     rand100() 함수             */
/*   0～100을 반환하는 난수 함수  */
/**********************************/
int rand100()
{
 int rnd ;
 
 /*난수 최댓값 제외*/
 while((rnd=rand())==RAND_MAX) ;
 /*난수 계산*/ 
 return (int)((double)rnd/RAND_MAX*101) ;
}
