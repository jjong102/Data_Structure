// 허프만 코드
// 빈도수를 센다음
// 가장 작은 두개 더하고, 그런다음 비교, 또 더하고,, 허프만 트리 완성,,
// 무손실 압축

// 허프만 코드 프로그램
// 우선순위큐 MINheap사용

#include <stdio.h>
#include <stdlib.h>

#define Q_SZ 100

struct node {
  char c; // 허프만 코드를 할당받을 문자.
  int freq;
  struct node *left;
  struct node *right;
};

// min heap == 우선순위큐, 빈도수가 적을수록 우선순위가 높다.
struct node *PQUE[Q_SZ + 1];
int idx = 0;

// huffman code를 만드는 전역변수 배열
char code[30] = {
    0,
};                 // 초기에는 null character로 초기화
int code_idx = -1; // 코드를 추가해야 하는 위치, 011

struct node *createNode(char _c, int _freq) {
  struct node *_new_node = (struct node *)malloc(sizeof(struct node));
  _new_node->c = _c;
  _new_node->freq = _freq;
  _new_node->left = 0;
  _new_node->right = 0;
  return _new_node;
}

void enqueue(struct node *_new_node) {
  // queue full
  if (idx == Q_SZ) {
    return;
  }

  idx += 1;
  PQUE[idx] = _new_node; // 노드의 주소를 넣는다.

  // 부모가 자기보다 크면, 내가 위로 올라간다. 왜냐면 min heap
  int _cur_idx = idx;
  int _p_idx = _cur_idx / 2;

  while (_cur_idx > 1) {
    if (PQUE[_cur_idx]->freq < PQUE[_p_idx]->freq) {
      struct node *temp = PQUE[_cur_idx];
      PQUE[_cur_idx] = PQUE[_p_idx];
      PQUE[_p_idx] = temp;
      _cur_idx = _p_idx;
      _p_idx = _cur_idx / 2;
    } else {
      break;
    }
  }
}

struct node *dequeue(void) {

  // queue empty
  if (idx == 0) {
    return 0;
  }

  struct node *_res = PQUE[1]; //  나갈애
  // 나갈애를 대신해서, 마지막 애가 올라온다.
  // minheap 조건 (complete binary tree 조건 충족을 위해서)
  PQUE[1] = PQUE[idx];
  idx--;

  int _cur_idx = 1;
  int _child_idx = _cur_idx * 2; // 일단 왼쪽자식

  while (1) {
    if (_child_idx > idx) { // 무자식
      break;
    }

    // 1. 일단 오른쪽 자식이 있어야 하고,
    // 2. 왼, 오: 둘 중 더 작은애와만 비교하면 된다.
    if ((_child_idx + 1 <= idx) &&
        (PQUE[_child_idx]->freq > PQUE[_child_idx + 1]->freq)) {
      _child_idx += 1; // 진정으로 비교할 아이는 오른쪽 아이임.
    }
    // 드디어, 결전의 날, 부모와 자식간의 혈투
    if (PQUE[_cur_idx]->freq > PQUE[_child_idx]->freq) {
      // 자식에게 자리를 내어주고 내려와야 함.
      struct node *temp = PQUE[_cur_idx];
      PQUE[_cur_idx] = PQUE[_child_idx];
      PQUE[_child_idx] = temp;
      _cur_idx = _child_idx;
      _child_idx = 2 * _cur_idx;
    } else {
      break;
    }
  }
  return _res;

  // minheap 조건 (부모는 자식보다 작아야 한다.)
}
// minheap네 담긴 노드 정보들을 이용해서
// huffman tree를 만들고,
// 마지막에 rootnode를 반환한다.
struct node *bulidHuffmanTree(void) {

  while (1) {
    // 1. 2개를 꺼낸다.
    // 단, 한개만 있으면, 반환하고 끝.
    struct node *_first = dequeue();
    struct node *_second = dequeue();

    if (_second == 0) {
      return _first;
    }
    // 2. 이진트리를 만들어서, 다시 engueue
    struct node *_combined = createNode(0, _first->freq + _second->freq);
    _combined->left = _first;
    _combined->right = _second;

    enqueue(_combined);
  }
}

void genHuffmanCode(struct node *_node) {

  if (_node == 0) {
    return;
  }
  code_idx++;
  code[code_idx] = '0';
  genHuffmanCode(_node->left);
  code[code_idx] = 0; // 내가 넣은 것을 지운다.
  code_idx--;

  if (_node->c != 0) { // 'a' , 'b' ,,, 이런 것들이 있다면,
    printf("%c ---> %s\n", _node->c, code);
  }

  code_idx++;
  code[code_idx] = '1';
  genHuffmanCode(_node->right);
  code[code_idx] = 0; // 내가 넣은 것을 지운다.
  code_idx--;
}
int main(void) {
  enqueue(createNode('c', 6));
  enqueue(createNode('a', 3));
  enqueue(createNode('z', 100));
  enqueue(createNode('b', 4));

  /*for (int i = 1; i <= idx; i++) {
          printf("%c   %d \n", PQUE[i]->c, PQUE[i]->freq);
  }*/
  /*while (1) {
          struct node* temp = dequeue();
          printf("%c ---> %d \n", temp->c, temp->freq);
  }*/

  struct node *temp = bulidHuffmanTree();
  // printf("%d\n", temp->freq); // 113 a, 3, b, 4, c,6 z100 ===> 113
  genHuffmanCode(temp);
  return 0;
}