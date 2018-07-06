/* 하나의 인공 신경 계산 : 적당한 가중치와 역치를 가진 인공 신경을 흉내냄 */
// $neuron < data24.txt

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUTNO 2  /*입력 수*/ 
#define MAXINPUTNO 100    /*데이터의 최대 개수*/ 

double f(double u) ; /*전환 함수*/
void initw(double w[INPUTNO+1]) ;  /*가중치와 역치의 초기화*/
double forward(double w[INPUTNO+1],double e[INPUTNO]) ; /*순방향 계산*/
int getdata(double e[][INPUTNO]) ;/*데이터 읽어들이기*/ 

int main()
{
 double w[INPUTNO+1] ;/*가중치와 역치*/
 double e[MAXINPUTNO][INPUTNO] ;/*데이터 세트*/
 double o ;/*출력*/
 int i,j ;/*반복 제어*/
 int n_of_e ;/*데이터 개수*/
 
 /*가중치 초기화*/
 initw(w) ;

 /*입력 데이터 읽어들이기*/
 n_of_e=getdata(e) ;
 printf("데이터 개수:%d\n",n_of_e) ;
 
 /*계산 본체*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(w,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/************************/
/*  getdata() 함수      */
/* 학습데이터 읽어들이기*/
/************************/
int getdata(double e[][INPUTNO])
{
 int n_of_e=0 ;/*데이터 세트 개수*/
 int j=0 ;/*반복 제어용*/

 /*데이터 입력*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>=INPUTNO){/*다음 데이터*/
   j=0 ;
   
#ifdef DEBUG
 printf("data(%d)--->%f,%f\n", n_of_e, e[n_of_e][0], e[n_of_e][1]);
#endif

   ++n_of_e ;
  }
 }
 return n_of_e ;
}

/**********************/
/*  forward() 함수    */
/*  순방향 계산       */
/**********************/
double forward(double w[INPUTNO+1],double e[INPUTNO])
{
 int i ;/*반복 제어*/
 double u,o ;/*중간 계산값 u와 출력 o*/

 /*계산 본체*/
 u=0 ;
 for(i=0;i<INPUTNO;++i)
  u+=e[i]*w[i] ;
 u-=w[i] ;/*역치 처리*/
 /*출력값 계산*/
 o=f(u) ;
 return o ;
} 

/**********************/
/*    initw() 함수    */
/*  가중치 초기화     */
/**********************/
void initw(double w[INPUTNO+1])
{
 /*상수를 가중치로 줌*/
 w[0]=1 ;
 w[1]=1 ;
 w[2]=1.5 ;		//bias
// w[2]=0.5 ;
} 

/*******************/
/* f() 함수        */
/* 전환 함수       */
/*******************/
double f(double u)
{
 /*계단 함수 계산*/
 if(u>=0) return 1.0 ;
 else return 0.0 ;
 
 /*시그모이드 함수 계산*/
// return 1.0/(1.0+exp(-u)) ;
}
