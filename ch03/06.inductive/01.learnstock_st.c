// 단순한 귀납학습 예제 프로그램 : 패턴 학습기
// 100개의 학습 데이터를 읽어들여 적합한 10자리의 2진수 패턴을 답함
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define OK 1 
#define NG 0
#define SETSIZE 100 	/* 학습 데이터 세트의 크기 */
#define CNO 10 		/* 학습 데이터의 자릿수(10회사 분) */
#define GENMAX  100000 	/* 해답 후보 생성 횟수 */

/* 학습 데이터 세트를 읽어들임 */
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE]) ;
int rand012() ;		/*0, 1 또는 2를 반환하는 난수 함수 */
/* 해답 후보 패턴의 점수(0~SETSIZE점)의 계산 */
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE], int answer[CNO]) ;

int main()
{
 int i, j;
 int score = 0;			/* 점수(0～SETSIZE점)*/
 int answer[CNO];		/* 해답 후보 */
 int data[SETSIZE][CNO];	/* 학습 데이터 세트 */
 int teacher[SETSIZE];		/* 교사 데이터 */
 int bestscore = 0;		/* 가장 좋은 점수 */
 int bestanswer[CNO];		/* 탐색 중 찾은 가장 좋은 점수 */

 srand(getpid());		/* 난수 초기화 */

 /*학습 데이터 세트를 읽어들임 */
 readdata(data,teacher) ;

 /* 해답 후보 생성과 검사 */
 for (i = 0; i<GENMAX; ++i) {

  for (j = 0; j<CNO; ++j) {	/* 생성 */
   answer[j] = rand012();
  }

  /* 검사 */
  score=calcscore(data,teacher,answer) ;

  /* 가장 좋은 점수로 갱신 */
  if (score>bestscore) {	/* 지금까지 가장 좋은 점수라면 갱신 */
   for (j = 0; j<CNO; ++j)
    bestanswer[j] = answer[j];
   bestscore = score;
   for (j = 0; j<CNO; ++j)
    printf("%1d ", bestanswer[j]);
   printf(":score=%d\n", bestscore);
  }

 }

 /* 가장 좋은 해답 출력 */
 printf("\n가장 좋은 해답\n");
 for (j = 0; j<CNO; ++j)
  printf("%1d ", bestanswer[j]);
 printf(":score=%d\n", bestscore);

 return 0;
}

// calcscore() 함수: 해답 후보 패턴의 점수(0～SETSIZE점) 계산
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE], int answer[CNO])
{
 int score = 0; 	/* 점수(0～SETSIZE점)*/
 int point  ; 		/* 일치한 자릿수(0～CNO)  */
 int i,j ;
 
 for (i = 0; i<SETSIZE; ++i) {
  /* 일치도 계산 */
  point = 0;
  for (j = 0; j<CNO; ++j) {
   if (answer[j] == 2) ++point;		/* 와일드카드 */
   else if (answer[j] == data[i][j]) ++point;	/* 일치 */
  }

  if ((point == CNO) && (teacher[i] == 1)) {
   ++score;
  }
  else if ((point != CNO) && (teacher[i] == 0)) {
   ++score;
  }
 }
 return score ;
}

// readdata() 함수: 학습 데이터 세트를 읽어들임
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE])
{
 int i,j ;
 FILE *fp;
 char t_data[10];

 fp = fopen("./ldata.txt", "r");
 if(fp == NULL) {
  perror("fopen() error");
  exit(1);
 }
 
 for (i = 0; i<SETSIZE; ++i) {
  for (j = 0; j<CNO; ++j) {
   fscanf(fp, "%s", t_data);
   data[i][j] = atoi(t_data);
  }
  fscanf(fp, "%s", t_data);
  teacher[i] = atoi(t_data);
 }
}

// rand012() 함수: 0, 1 또는 2를 반환하는 난수 함수
int rand012()
{
 int rnd ;
 
 /* 난수의 최댓값을 제외 */
 while((rnd=rand())==RAND_MAX) ;
 /* 난수 계산 */ 
 return (double)rnd/RAND_MAX*3 ;
}

