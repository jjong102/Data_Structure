//--------------------------------------------
// p. 176, 연결리스트 == linked list
//
// 데이터 구조의 꽃!!!!
//
// array의 4대 단점
//		1. 크기가 고정,
//		2. 연속된 메모리 공간이 필요
//		3. 중간에 끼워넣기,, 매우 힘들어잉!
//		4. 중간에 빠져나가면, 공간 채우기가 힘들어.
//
// 시즌 2. 그래서 linked list라는 것이 나왔다.
//		array의 모든 단점을 극복!!!
//		array의 모든 장점을 잃었어...
//
//		장점1 : 필요한 만큼만 메모리 사용
//		장점2 : 연속되지 않은 메모리도, 기워서 쓴다.
//		장점3,4: 끼워넣고, 빠져나가기, ---> 티도 안나!! 매우 효율적으로
// 처리
//
//		단점1 : 매우 느림
//		단점2 : 구현이 복잡
//
//		내 뒤에는 이 친구 --> linked 되어 있따!! ㅁ--> ■--> ㅁ-> ■
//
// Linked list를 구현해 보자.
//	Node들의 집합 (■-->)
//  linked list의 개별요소들을 node라고 부른다.
//	각 node는 데이터를 저장하는 공간과,
//		그 다음 것을 가리키는 링크로 구성
//--------------------------------------------
#include <stdio.h>
#include <stdlib.h> // malloc 때문에 필요

// linked list의 기본 요소인 node
// linked list : LL
// Singly Linked list : SLL

struct node {
  int data;
  struct node *next;
};

struct node *head = 0; // head는 linked list의 처음을 알려준다잉!

// stack에는 top, queue에는 front/rear, linked list에는 head

// _v 정수값을 SLL의 끝에 추가한다.
// 점점 늘어나는 리스트의 역할

void addToSLL(int _v) {
  // _v 값을 저장할 node를 메모리에 마련한다.
  // data type을 casting하는 이유
  // malloc의 반환값은 void* (주소를 반환해 준다.)
  // type이 없으므로 (void), 적절한 type으로 casting
  // _new는 새로 할당받은 node 구조체의 주소를 가리키고 있다.

  // 주의!! _new를 잃어버리면, 할당받은 공간을 다시 찾아갈 방법이 없음.

  struct node *_new =
      (struct node *)malloc(sizeof(struct node)); // 새로운 노드를 만든다.
  // -> 화살표를 사용하는 이유 : _new가 포인터 이기 때문에
  _new->data = _v;

  _new->next = 0; // 신규 노드는 뒤에 오는 노드가 없으므로, 0(null)로 초기화

  //_new를 기존 SLL에 추가

  // 경우의 수 2가지
  // 1. 빈 SLL인 경우

  if (head == 0) {
    head = _new;
    return;
  }
  // 2. 아닌 경우

  // 2.1 기존 SLL에서 맨 끝의 노드의 주소를 알아낸다.
  struct node *temp = head; // head를 가지고 움직이면 다시는 뒤로 돌아갈 수
                            // 없어... 따라서 새로운 포인터 생성
  while (temp->next != 0) {
    temp = temp->next;
  }

  // 2.2 맨끝 노드의 next에 새로운 노드의 주소를 집어넣는다.
  temp->next = _new; // 새로운 노드의 주소를 저장해준다.
  return;
  // h -> ㅁ -> ㅁ -> ㅁ
}

void displaySLL(void) {
  struct node *temp = head;
  while (1) { // (temp != 0)

    if (temp == 0) {
      break;
    }

    printf("%d\n", temp->data);
    temp = temp->next;
  }
}

// SLL에 포함된 node개수를 반환
int countSLL(void) {
  struct node *temp = head;
  int cnt = 0; // 노드 개수

  while (temp != 0) {
    cnt++;
    temp = temp->next;
  }
  return cnt++;
}

// _v값을 가지는 노드를 찾아서,
// 그 노드의 주소를 반환
// 그래서, 반환값이 struct node*
// 반환값
//	- _v를 가진 노드의 주소
//	- 0 : 그런 노드가 없을 때
struct node *findSLL(int _v) {

  struct node *temp = head;

  while (temp != 0) {

    if (temp->data == _v) {
      return temp;
    }
    temp = temp->next;
  }
  return temp;
}

void destroySLL(void) {

  struct node *spear = head;

  while (head != 0) {
    head = head->next; // head를 스리슬쩍 옆으로 넘긴다.
    free(spear);
    spear = head;
  }
  return;
}

// _v를 가진 노드를 맨 앞에 추가
void addToFront(int _v) {
  // 새로운 node를 1개 할당 받아서, _v를 저장, 그 노드를 _new가 가리킨다.
  struct node *_new = (struct node *)malloc(sizeof(struct node));
  _new->data = _v;
  _new->next = 0;

  // 경우의 수. 1 SLL == empty
  if (head == 0) {
    head = _new;
    return;
  }

  // 경우의 수. 2, SLL에 뭔가 있을때. (순서가 상당히 중요하다!)
  _new->next =
      head; // SLL의 대원칙 = 새로온 사람이 아쉽다. 먼저손 (손서 중요!!!)
  head = _new;
  return;
}

int delFromFront(void) {

  if (head == 0) {
    return -999; // SLL이 텅비었다는 의미.
  }

  struct node *spear = head;
  // head 대피
  head = head->next;
  // 데이터 보관
  int res = spear->data;
  // 폭파
  free(spear);
  // 저장값 반환
  return res;
}

int delFromLast(void) {

  // thank you.1
  if (head == 0) {
    return -999;
  }

  if (head->next == 0) {
    int res = head->data;
    free(head);
    head = 0;
    return res;
  }

  // oh my god .3
  // 1. 맨 뒤에서 두 번째 노드에 창을 꼽는다.
  struct node *spear = head;

  while (spear->next->next != 0) {
    spear = spear->next;
  }
  int res = spear->next->data; // 데이터 대피
  // 폭파
  free(spear->next);
  // 끝단 처리
  spear->next = 0;
  return res;
}

// _findv값을 가진 노드를 찾아서,
// 그 위에 _addv를 가진 새로운 노드를 추가한다.
void insertInto(int _findv, int _addv) {

  // _findv를 가진 노드가 없다면,
  struct node *target = findSLL(_findv);
  if (target == 0) { // _findv를 가진 노드가 없다. thank youououoyuyuyu
    return;
  }
  struct node *_new = (struct node *)malloc(sizeof(struct node));
  _new->data = _addv;
  _new->next = 0;

  // 붙여넣기
  // 아쉽손.
  _new->next = target->next;
  target->next = _new;
  return;
}
// _v값을 가진 노드를 찾아서 삭제
void delFromSLL(int _v) {
  //_v값을 가진 노드를 찾는다.
  struct node *spear = findSLL(_v);

  if (spear == 0) { // 못찾으면, thank you
    return;
  }

  // 주의해야할 케이스
  // 지워야 하는 것이 head인 경우
  if (head == spear) {
    // head 대피
    head = head->next;
    // 폭파
    free(spear);
    return;
  }

  // 나머지 케이스
  // spear 꽂힌 노드가 중간에 있는 경우. 최소한 노드가 2개가 있는 경우

  struct node *prev = head;
  // prev가 창꽃힌 노드의 직전 노드가 될 때 까지 이동.
  while (prev->next != spear) {
    prev = prev->next;
  }

  prev->next = spear->next;
  free(spear);
  return;
}

int main(void) {

  addToSLL(10);
  addToSLL(20);
  addToSLL(30);
  addToSLL(40);

  addToFront(90);
  addToFront(80);

  delFromFront();
  delFromFront();

  delFromLast();

  // insertInto <--- 특정 노드를 찾아서, 그 뒤에 추가
  insertInto(20, 99);

  // delFromSLL <--- 특정 노드를 찾아서 제거
  delFromSLL(99);

  // SLL를 앞에서부터 뒤로 지나가면서
  // 각노드에 저장된 값들을 출력한다.
  displaySLL();

  // countSLL <--- SLL 안에 있는 노드 개수를 반환
  printf("SLL안의 노드개수는: %d개 입니다.\n", countSLL());

  // findSLL <--- SLL 안에 있는 특정 노드 위치를 검색
  printf("20을 가진 노드의 주소 %x 입니다유!\n", findSLL(20));
  struct node *temp = findSLL(20);
  printf("%d\n", temp->data); // ----> must be 20, 그 값을 반환

  // destroySLL <--- SLL 노드를 모두 제거
  destroySLL();
  if (head != 0) {
    printf("제대로 destroy하지 못했음.\n");
  }

  // addToFront <--- 맨 앞에 추가
  // displaySLL(); 앞에 있어용

  // delFromFont <--- 맨 앞 것을 제거, 그 값을 반환
  // displaySLL(); 앞에 있어용

  // displaySLL(); 앞에 있어용

  return 0;
}
