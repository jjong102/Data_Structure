//-------------------------------------------------------------
// infix에서 postfix 만들어내기
//
// stack 이용
//
// 알고리즘
// 관찰점: 숫자 순서는 안바뀜
// 외쪽에서 오른쪽으로 1글자씩 읽어나가면서,
// 숫자면 출력
// 연산자면 ???
//	 - 기본적으로 push
//	 - 단, 나보다 연산순위가 낮은 것이 있으면
//	    	아니면, 연산순위 높은 것을 빼내고 push
//				ex) 1 + 2 - 3 * 5 ---> 1 2 + 3 5 * -
//	 - 괄호가 나왔다. 2가지 종류, 여는 괄호 (, 닫는 괄호 ) [ )는 stack에
// 집어 넣지 아니한다.]
//     .. 여는 괄호는 무조건 push
//	   .. 여는 괄호의 우선순위는 최하위로 취급
//	   .. 닫는 괄호가 나오면, 여는 괄호 최초나올 때까지 pop하면서 연산자
// 출력
//-------------------------------------------------------------

#include <stdio.h>
#define STACK_SZ 20

char stack[STACK_SZ]; // stack 구현, 기호가 들어가는 공간
int top = -1;         // 맨 위에 저장된 숫자 위치 (index) {

// push, pop, isFull, isEmpty
int isFull() { return (top == (STACK_SZ - 1)); }

int isEmpty() { return (top == -1); }

void push(char _v) {
  // 예외,full
  if (isFull()) {
    printf("미쳣슈 ?? \n");
    return;
  }
  top++;
  stack[top] = _v;
  return;
}

char pop(void) {
  if (isEmpty()) {
    printf("고마하이소\n");
    return '\0'; // '\0'는 비었다는 특별한 값,, 연산자 아님
  }
  char result = stack[top];
  top--;
  return result;
}

int amIHigher(char _c) {

  if (stack[top] == '(') { // 호구 케이스
    return 1;
  } else if (_c == '*' || _c == '/') {
    if (stack[top] == '+' || stack[top] == '-c') {
      return 1;
    }
  }
  // _c가 +, - 인 경우는 우선순위가 높을 수가 없다.
  return 0;
}

// 가정
// 숫자는 한자리
// 공백없음.
int main(void) {

  char infix_expr[] = "1*(2+3)"; // == > 1 2 3 + *
  int idx = 0;                   // 지금 어디를 일고 있는지 표시

  while (infix_expr[idx] != '\0') {
    char _c = infix_expr[idx];
    // 1. 숫자면 출력, happy case
    if ((_c >= '0') && (_c <= '9')) {
      printf("%c", _c);
    } else { // 연산자, (, ) -세 개 중에 하나
      if (_c == '(') {
        push(_c);
      } else if (_c == ')') { // 닫는 괄호면, 여는 괄호 나올 때까지 pop하면서
                              // 연산자 출력
        while (1) {
          char _d = pop();
          if (_d == '(') { // 탈출 조건
            break;         // 더 이상 pop을 하지 않고, 넘어간다.
          }
          printf("%c", _d);
        }
      } else { // +, -, *, /
        // 가. 스택이 비어있는 --> thank you case, push만 하면 되니까....
        // 나. 스택이 안 비어있는데, (가 내 밑이야, --> thank, push만 하면
        // 되니까... 다. 스택이 안 비어있는데, 연산자 우선순위를 따져야 하는
        // 경우, --> 인생케이스
        if (isEmpty()) { // 가. 경우
          push(_c);
        } else { // 나, 다 경우 처리 : 스택이 안 비어있는 경우
          // _c와 stack[top]의 우선순위를 따져서,
          // _c가 높으면 --> push : 그나마 thank you
          //		낮으면 --> 높은 애들 다 pop해서 출력하고, puxh --> 고생
          // 케이스
          // amIHigher(_c) 함수 : _c의 우선순위가 stack[top]보다 높으면 1,
          // 아니면 0
          while (1) {
            if (!amIHigher(_c)) {
              printf("%c", pop());
            } else {
              break;
            }
          }
          push(_c);
        }
      }
    }

    idx++;
  }

  // 다 일고 나면, 무엇을 해야 하나요?
  // 스택이 empty될 때따지, pop하면서 출력
  while (isEmpty() != 1) {
    printf("%c", pop());
  }

  printf("\n");
  return 0;
}
