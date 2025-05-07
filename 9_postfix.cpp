//--------------------------------------------------------------
// stack, LIFO (last in fast out)
//
// postfix 계산
// 우리가 사용하는 수식 : 2 + 3, infix
//	 operator 위치 기준
// 컴퓨터가 계산할 떄는 postfix 형태를 사용
//	 2 + 3 --> 2 3 +
//
// postfix의 장점
// - 괄호를 사용하지 않고도 우선순위 표기가 가능
//
// 2 + 3 * 5 ---> 2 3 5 * +
// (2 + 3) * 5 (infix에서는 괄호를 피할 방법이 없음)
// 그러나,
// postfix에서는
// (2 + 3) * 5 ---> 2 3 + 5 * (괄호 없이도 표현 가능)
//
// postfix의 계산
//		왼쪽에서 오른쪽으로 읽어 나가면서,
//		연산자 (+,- ...) 만나면 앞의 2개 숫자로 계산 --> 숫자로 치환
//		끝까지 읽을 때까지 반복
//
// 사람은 infix로 입력
// 컴퓨터는 1) infix --> postfix로 전환
//         2) posetfix를 계산	(둘다 stack를 사용하여 계산)
//
// postfix 수식 계산
//		구현을 간단히 하기 위해서 1자리 숫자
//		4칙연산, +,-,*,/, 정수형 계산
//		수삭에 공백없이 입력
//
// stack을 이용해서 구현하는 알고리즘
//		stack을 하나 마련하고,
//		수식은 왼쪽에서 오른쪽으로 읽어가면서
//		숫자면, stack에 push
//		연산자면, stack에서 2개를 pop하고, 계산해서 다시 push
//		수식 끝날 때까지 계속
//--------------------------------------------------------------

#include <stdio.h>
#define STACK_SZ 20

int stack[STACK_SZ]; // stack 구현, 정수를 저장하는 공간
int top = -1;        // 맨 위에 저장된 숫자 위치 (index) {

// push, pop, isFull, isEmpty
int isFull() { return (top == (STACK_SZ - 1)); }

int isEmpty() { return (top == -1); }

void push(int _v) {
  // 예외,full
  if (isFull()) {
    printf("미쳣슈 ?? \n");
    return;
  }
  top++;
  stack[top] = _v;
  return;
}

int pop(void) {
  if (isEmpty()) {
    printf("고마하이소\n");
    return -999; // -999는 비었다는 특별한 값,, 숫자 아님
  }
  int result = stack[top];
  top--;
  return result;
}

// v1과 v2를 받아서, op 연산을 한 결과를 반환
// op : +, -, *, /
int calc_expr(char op, int v1, int v2) {

  switch (op) {
  case '+':
    return (v1 + v2);
  case '-':
    return (v2 - v1); // 순서 조심
  case '*':
    return (v1 * v2);
  case '/':
    return (v2 / v1); // 순서 조심
  }
}

int main(void) {

  char postfix[] = "775*/"; // postfix expression
  int idx = 0;              // expression에서 현재 읽는 위치

  // 왼쪽에서 오른쪽으로 한글자씩 읽는 코드
  // expression끝에 도달할 때까지.... \0은 expression 끝인 null을 의미
  while (postfix[idx] != '\0') {

    // 숫자, 연산자, 둘 중 하나가 나온다.

    // 숫자인 경우 처리
    char _c = postfix[idx]; // 일단 복사, 이거 안해도 되지만...
    if ((_c >= '0') && (_c <= '9')) { // 숫자 확인
      push((int)(_c - '0')); // '0'을 빼버리면 상대적이기 때문에 숫자가 나온다.
                             // ex) 103('3') - 100('0') = 3
    } else { // 절대 안심, 숫자 아니면 연사자 4개중 하나 들어온다고 믿자!!
             // 그러나, 이렇게 짜면 안됨...!

      // _c는 연산자,
      int v1 = pop();
      int v2 = pop();
      int res = calc_expr(_c, v1, v2);
      push(res);
    }
    idx++;
  }

  // 여기에 왔다면, 스택에는 숫자 1개가 있어야 함!!
  printf("연산 결과는 %d \n", pop());

  return 0;
}
