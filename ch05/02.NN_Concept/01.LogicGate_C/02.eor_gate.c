/* 단순한 계층형 신경망 계산 :１ 출력 망을 계산(학습 없음) */
/*$nn < data24.txt */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*기호 상수 정의*/
#define INPUTNO 2  /*입력층의 셀 개수*/ 
#define HIDDENNO 2  /*중간층의 셀 개수*/ 
#define MAXINPUTNO 100    /*데이터 최대 개수*/ 

/*함수 프로토타입 선언*/
double f(double u) ; /*전환 함수*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;  /*중간층의 가중치 초기화*/
void initwo(double wo[HIDDENNO+1]) ;/*출력층의 가중치 초기화*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO]) ; /*순방향 계산*/
int getdata(double e[][INPUTNO]) ;/*데이터 읽어들이기*/ 

int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*중간층의 가중치*/
 double wo[HIDDENNO+1] ;/*출력층의 가중치*/
 double e[MAXINPUTNO][INPUTNO] ;/*데이터 세트*/
 double hi[HIDDENNO+1] ;/*중간층 출력*/
 double o ;/*출력*/
 int i,j ;/*반복 제어*/
 int n_of_e ;/*데이터 개수*/
 
 /*가중치 초기화*/
 initwh(wh) ;
 initwo(wo) ;

 /*입력 데이터 읽어들이기*/
 n_of_e=getdata(e) ;
 printf("데이터 개수:%d\n",n_of_e) ;
 
 /*계산 본체*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO;++j) printf("%lf ",e[i][j]) ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/************************/
/*  getdata() 함수      */
/*학습 데이터 읽어들이기*/
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
double forward(double wh[HIDDENNO][INPUTNO+1],
	double wo[HIDDENNO+1],double hi[],
	double e[INPUTNO])
{
 int i,j ;/*반복 제어*/
 double u ;/*가중치를 적용한 합을 구함*/
 double o ;/*출력 계산*/

 /*hi 계산*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*가중치를 적용한 합을 구함*/
  for(j=0;j<INPUTNO;++j) u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*bias 처리*/
  hi[i]=f(u) ;
 }
 /*출력 o 계산*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i) o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*역치 처리*/
 
 return f(o) ;
} 

//***********************/
/*    initwh() 함수     */
/*중간층의 가중치 초기화*/
/************************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 
 /*가중을 상수로서 부여*/
 wh[0][0]=-2 ;
 wh[0][1]=3 ;
 wh[0][2]=-1 ;		//bias
 wh[1][0]=-2 ;
 wh[1][1]=1 ;
 wh[1][2]=0.5 ;		//bias
} 

/************************/
/*    initwo() 함수     */
/*출력층의 가중치 초기화*/
/************************/
void initwo(double wo[HIDDENNO+1])
{
 /*가중을 상수로서 부여*/
 wo[0]=-60 ;
 wo[1]=94 ;
 wo[2]=-1 ;		//bias
} 

/*******************/
/* f() 함수         */
/* 전환 함수        */
/*******************/
double f(double u)
{
 /*계단 함수 계산*/
 if(u>=0) return 1.0 ;
 else return 0.0 ;
 
 /*시그모이드 함수 계산*/
// return 1.0/(1.0+exp(-u)) ;
}
