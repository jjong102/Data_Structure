//--------------------------------------------
// p. 146 Queue (큐)
//
// 사자성어 : FIFO (frist in, frist out), 통로와 같은 형태 front(출구),
// vear(입구)
//
// stack : push, pop
// queue : enqueue (enter queue)
//		 : dequeue (depart from queue)
//			departure <---> arrival
//
// 구현
// queue의 구현에도 배열을 사용한다.
// front, rear <----- 큐에서 위치를 나타내는 변수
// front : dequeue할 것이 있는 위치 (값을 빼는 것)
// rear  : enqueue할 위치 (값을 넣는 것)
//
// front와 rear가 같은 곳을 가리키고 있으면 queue가 비어 있다! (꽉차도 같은 곳을
// 가리킴) ---> 그냥 한칸을 비우자 하나를 빼면 front가 옆으로 이동한다.
//		- 비어 있는 공간을 찾아 이동!
// 하나를 저장하면 rear가 이동한다. (2 가지)
//		1. 앞에 있는 것을 다 떙기고 그 뒤에 저장 (땡기는데 시간이
// 많이걸려!!, 비효율적)
//		2. rear가 비어있는 공간을 찾아 이동 (효율적) [circular queue]
//
//		1. 앞으로 당기는 방식... 이것은 비효율적
//		2. 일반적인 큐 규형방식은, dequeue되고 나서, 데이터를 한칸씩
//
//
// queue도 isEmpty와 isFull이 존재
//
// circular queue는 1칸을 비움으로써, empty와 full을 구분
//		최대 저장 용량은 N - 1
//--------------------------------------------

#include <stdio.h>
#define Q_SZ 10 // 최대 9개,circular queue일 경우
int que[Q_SZ];  // 중요한 위치 변수,

int front = 0;
int rear = 0;

int isEmpty() { return (front == rear); }

int isFull() { // rear 앞에(뒤에) front가 있으면, full
  return (((rear + 1) % Q_SZ) ==
          front); // 뒤로 돌아가는 경우가 있기 때문에 나머지 활용
}

void enqueue(int _v) {
  if (isFull()) {
    printf("error, full\n");
    return;
  }

  // rear가 가리키고 있는 현재 위치에 넣는다.
  que[rear] = _v;
  // rear를 1개 증가 시킨다. ,, 항상 뒤로 돌아가는 경우를 생각
  rear = (rear + 1) % Q_SZ;
  return;
}

int dequeue() {
  // empty 체크
  if (isEmpty()) {
    return -999; // error표시 -999
  }

  // front 위치에 있는 것 뽑기
  int result = que[front];

  // front 조정
  front = (front + 1) % Q_SZ;

  // 뽑아 놓은 것 반환
  return result;
}

int main(void) {

  enqueue(4);
  enqueue(5);
  enqueue(7);

  while (!isEmpty()) {
    printf("%d\n", dequeue());
  }

  return 0;
}
