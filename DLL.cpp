//-------------------------------------------------
// Doubly Linked List
// 팔이 두개, nextm prev
// head
//-------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
  struct node *prev; // DLL에서 추가된 부분
};
struct node *head = 0;

// node를 만드는 함수
struct node *createNode(int _v) {
  struct node *_new = (struct node *)malloc(sizeof(struct node));
  _new->data = _v;
  _new->next = _new->prev = 0;
  return _new;
}

void addToDLL(int _v) {
  struct node *_new = createNode(_v);

  // 비어 있는 경우
  if (head == 0) {
    head = _new;
    return;
  }

  // 끝을 찾아서 추가
  struct node *spear = head;
  while (spear->next != 0) {
    spear = spear->next;
  }

  // 이순간, spear는 마지막 노드를 찌르고 있음.
  // 팔연결
  spear->next = _new;
  _new->prev = spear;
  return;
}

void displayDLL(void) {

  struct node *temp = head;

  while (1) { // (temp != 0)

    if (temp == 0) {
      break;
    }

    printf("%d\n", temp->data);
    temp = temp->next;
  }
}

void displayReverseDLL(void) {

  // epty list 확인
  if (head == 0) {
    return;
  }

  struct node *spear = head;
  while (spear->next != 0) { // spear은 맨 끝에 노드를 가리키고 있음.
    spear = spear->next;
  }

  // 거꾸로 오면서 하나씩 출력
  while (spear != 0) {
    printf("%d\n", spear->data);
    spear = spear->prev;
  }

  return;
}

// _t를 가진 node를 찾아서
// 주소 반환
struct node *findNode(int _t) {

  struct node *spear = head;

  while (spear) {
    if (spear->data == _t) {
      break;
    }
    spear = spear->next;
  }
  return spear;
}
// _t : 찾아야 할 노드
// _v :추가해야 할 노드
void insertIntoDLL(int _t, int _v) {

  // _t를 가진 노드 찾기
  struct node *spear = findNode(_t);

  if (spear == 0) {
    return; // _t를 가진 노드가 없음.
  }

  // 이제, 추가 하자...spear뒤에
  struct node *_new = createNode(_v);

  // 아쉬운 애가 손을 연결한다.
  _new->prev = spear;
  _new->next = spear->next; // null인 경우도 상관없음.
  spear->next = _new;

  // 여기가 중요!!
  // 내 뒤에 누가 있는 경우에만,
  if (_new->next != 0) {
    _new->next->prev = _new;
  }
  return;
}

// _t를 가진 노드를 삭제
//
void delFromDLL(int _t) {

  // _t를 가진 node를 찾는다.
  struct node *spear = findNode(_t);
  if (spear == 0) { // thank you!
    return;
  }
  // 인생 꼬이는 경우

  // 1. 하필 spear == head, head 주의
  if (spear == head) {
    // head 대피
    head = head->next;
    // 폭파
    free(spear);
    if (head != 0) {
      head->prev = 0; // 단독 node가 아닐 경우.
    }
    return;
  }

  // 2. 중간 혹은 끝에 있는 노드
  spear->prev->next = spear->next;
  if (spear->next != 0) { // 내 뒤에 누가 있을 때만
    spear->next->prev = spear->prev;
  }
  free(spear); // 폭파
  return;
}

int main(void) {

  addToDLL(10);
  addToDLL(20);
  addToDLL(30);

  // displayReverseDLL();
  displayDLL(); // SLL과 같음

  // 20을 가진 노드를 찾아서 그 뒤에 90을 추가
  insertIntoDLL(20, 90);

  // delFromDLL(90); // 90을 가진 노드를 찾아서 지운다.
  displayDLL();
  // displayReverseDLL();

  return 0;
}
