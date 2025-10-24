// 포인터 Pointer p.89
// 데이터 타입 중의 하나,
// int, char : 값을 담는 데이터 타입
// Pointer type : 주소를 담는 데이터 타입 (하드웨어와 친구)

#include <stdio.h>
#include <stdlib.h> // standard libracy < === malloc, free
#if 1
int main(void) {

  int a = 10; // 모든 것은 주소지만 사람이 편하게 보기 위한 것이 변수

  // 변수가 저장된 위치 (주소)를 접근하기 위한 수단
  // 수단 ==> pointer

  // 주소를 저장하기 위한 데이터형, pointer type
  /*
          int* // * : 주소를 저장하는 타입 의미,
                   // int : 포인터를 이용해서 그 위치에서 1번에 일고 쓸 수 있는
     데이터량, int == 4byte

          short* // 2byte
          char*  // 1byte
  */
  // pa와 pc가 차지하는 메모리 공간의 크기는 다를까?
  // == 똑같다! 항상 4byte pointer (하지만 처리할 수 있는 byte양이 다르다!)
  int *pa;
  char *pc;
  float *pf;

  // p.90 null pointer
  // 아무것도 가리키지 않는 포인터.
  // NULL, 0 ==> 포인터 변수 안에 저장된 주소가 올바른 것인지, 아니지 구분해
  // 주는 역할

  int *pa = 0;
  int *pb = NULL;

  // p. 90 포인터 연산자
  // 1. 주소 연산자
  int a = 10;
  // &a // 변수 a가 저장되어 있는 메모리 상의 주소.

  // int* pa = 0;
  // &pa // 주소의 주소// 포인터 변수도 메모리를 할당 받는다.

  // 2. 간접참조 연산자, *
  // 주의!!! pointer변수에 대해서만 적용가능!!!
  int a = 20;
  int *pa = &a;
  scanf("%d", &a); //==> 주소 연산자의 사용

  printf("%d  %d\n", a, *pa); // 포인터 변수 주소를 간접적으로 찾아서 변수를
                              // 찾아오는 역할 20, 20 똑같이 출력됨!! // *pa는
                              // 그 주소가 가지고 있는 값을 나타내는 것.
  printf(
      "%d  %d   %d\n", &a, pa,
      &pa); // a의 주소, a의 주소(pa가 들고 있는 값), 포인터 변수pa자체의 주소

  return 0;
}
#endif

// p.91 함수 매개변수로 포인터 사용하기
#if 0
// call by reference <--- 포인터를 이용하여 가능
void real_change(int* x, int* y) { // 실제 값의 주소를 가져옴
	int temp;
	
	temp = *x; // read
	*x = *y; // write
	*y = temp;

}


// call by value , 복사본이 넘어감.
void change_two_num(int a, int b) { 
	int temp;
	temp = b;
	b = a;
	a = temp;
	return;
}


int main(void) {

	int a = 10;
	int b = 20;

	printf("%d %d\n", a, b); // 10, 20
	change_two_num(a, b);
	printf("%d %d\n", a, b); // 10, 20 , 복사본을 바꾼 상황 <---- call by value
	real_change(&a, &b);
	printf("%d %d\n", a, b); // 20, 10 <--- call by reference



	return 0;
}
#endif

// p. 92 배열과 포인터
// 친밀한 관계
// 배열 : 같은 데이터형의 값들이 메모리의 "연속된 공간"에 저장되어 있는 것.
// int a[10]; 10개의 공간이 쭈루룩........
#if 0
int main(void) {

	int a[10];

	printf("%d %d\n", a[10], a[9]);
	
	// 배열과 포인터
	// 배열 이름은 포인터 그 자체
	printf("%d\n", a); // 배열이 저장된 곳의 시작 위치, 주소, 배열이름은 포인터 그 자체

	// a === &a[0]

	// a+1 == &a[1] // 인덱스 1의 위치와 a+1은 서로 같은 의미



	return 0;
}
#endif

// P.94, 동적 메모리 할당 <====> 정적 메모리 할당
// 정적메모리 : 컴파일할 때 사용하는 메모리양이 모두 결정,
// 동적메모리 : 수행하면서 메모리 할당, 속도가 느려....., 운영체제가 대빵,
// 그러나 원하는 만큼 딱,
//			   단, free을 안하면 메모리 낭비
//			   프로그램이 계속 수행되면, malloc만 계속하고, free를
// 안 하면, memory leak
// malloc (memory allocation)
// free (메모리 해제)
#if 1
int main(void) {

  // unreferenced space problem.
  char *p =
      (char *)malloc(100); // 100 바이트 공간을 할당해서, 시작주소를 반환한다.
                           // casting을 통해서 주소 타입을 맞춰줘야함.
  if (p == 0) {
    printf("메모리 없음!\n");
    return -100;
  }
  p = (char *)malloc(200); // ----> 이전에 할당받은 공간이 미아가 되어버림. //
                           // 만약 반복문 안에 있으면 프로그램이 천천히 죽음.
  free(p); // 할당받은 공간을 운영체제에게 반환, 까먹지 마시유

  // dangling pointer problem
  char *p = (char *)malloc(100);
  char *q = p;
  free(q); // q를 반납을 해버림

  *p = 20; // 이미 반납된 공간에 저장을 하려함. (같은 공간에 2개 이상의
           // 프로그램이 같이 돌아감.)

  return 0;
}
#endif

// p. 96 구조체와 포인터
#if 1
typedef struct {
  int a;
  char b;
} AAA;

int main(void) {
  AAA a;
  a.a = 10;
  a.b = 'a';

  AAA *pa; // 구조체를 포인터에 있는 걸로 가져올려면, ->를 이용한다.
  pa = &a;
  pa->a = 40;
  pa->b = 'c';

  pa = (AAA *)malloc(sizeof(AAA));
  pa->a = 50;
  pa->b = 'd';
  free(pa);

  return 0;
}
#endif

// Chapter 4
// Stack LIFO(Last In First Out)

// 구현?
// 입력되는 정수를 저장하는 stack을 구현해 보자!!
//
// 입력 : push <--- stack에 값을 저장하는 operation
// 출력 : pop  <--- stack에서 값을 꺼내는 operation
// 구현 될때는 1차월 배열로 구현이 된다.

#if 0
#define STACK_SZ 10 // 10개 까지만 push되는 stack

int stack[STACK_SZ];
int top = -1; // 현재 스택의 맨 꼭대기 위치 index // 처음에는 아무것도 없기에 -1

// stack이 full인지 검사
// full ----> 1을 반환
// 아니면 ----> 0을 반환
int isFull(void) {
	return	(top == (STACK_SZ - 1)); //관계 연산자이기 떄문에 참 ->1, 거짓->0
}

// stack이 비어있는지 확인
// 1 : 비어있으면,
// 0 : 아니면
int isEmpty(void) {
	return (top == -1);
}
// push, pop
void push(int _v) {
	
	if (isFull()) { // 더 이상 push가 불가능
		printf("에러, stack is full!!\n");
		return;
	}
	top++;
	stack[top] = _v;

	return;
}

int pop(void) {
	
	// 1% 아주 가끔 일어나는 에러 상황
	if (isEmpty()) {
		printf("스택 empty\n");
		return -999; // -999는 에러상황을 나타내는 특수숫자라고 가정
	}
	// 99% 확률로 일어나는 일
	int result = stack[top]; // 순서가 중요함.
	top--;
	return result;

}

int main(void) {

	push(4);
	push(5);
	push(6);
	push(7);

	pop();
	printf("%d\n", pop()); // ==> 올바르게 스택이 구현되었다면, 6
	return 0;
}
#endif
