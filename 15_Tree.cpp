// chap.8 , Tree, p. 254

// stack, queue, SLL, DLL
// --> 선형

// 계층적 구조
// Tree는 계층적 구조를 표현하는 대표적 데이터구조
// Root Node : Tree에서 처음 시작하는 Node
// sub_Tree : Tree 밑에 있는 또 다른 작은 Tree
// edge : node와 node를 이어주는 것
// ~ p.255

// Parent node : node의 상위 node
// Child node : node의 하위 node
// Sibling node : node의 같은 계층에 있는 node
// ~ p. 256 상단부

// terminal node (종말, 단말 노드) : child node가 없는 node
// non-terminal node (비단말 노드) : chile node가 있는 node
// child node 존재 유무에 따라서,
// p.256

// degree of a node(차수) p.256
// 노드의 자식노드 최대 개수
// degree of tree
// == max(degree of a node)
//   0        ex) degree of node == 3
// 0 0 0

// Height of a tree (트리의 높이), p.256
// == max(level)
// Level (레벨) : 같은 계층 = 같은 층(level)

// p.256 마지막 용어 == Forest (나무들의 집합)
//					== set of trees

// p.257, 트리의 종류
// ---> degree of a tree == 2 (자식의 수가 최대 2개)
//		=== binary tree
//		=== 이진 트리

// p.258
// left subtree, right subtree (binary tree이기 떄문에 이런 표현이 가능)

// p.259 이진트리의 성질

// 1. n개의 노드를 가진 이진트리에서
//		edge의 개수는 n-1개다.
//		트리에서 모든 노드는 부모로 가는 edge를 가진다.
//		단, root node는 제외

// 2. (p.260)
//	높이가 h인 이진 트리에는
//		노드가 최소 h개 있고,
//			최대 2^h - 1 만큼 있다.

// 3. (p. 260)
//	n개의 노드를 가지는 이진트리의 높이는
//	최대 n이거나,
//	최소 log_2(n+1)
//		n <= 2^h -1
//		n + 1 <= 2^h
//		log_2(n+1) <= h

// p.261
// 이진트리의 분류

// 1. full binary tree : node를 꽉꽉채운 tree
// 2. complete binary tree : 순서대로 꽉꽉 채우면 complete

// tree --> binary tree --> binary search tree (BST) : 검색에 최적화된 Tree
//							왼쪽에 있는 subTree의
// 값은 작고, 오른쪽에 있는 subTree의 값은 크다.  - 2 -
// 한 level씩 내려올때 마다, 검색량이 반땅이 난다.
// 1	  3

#include <stdio.h>
#include <stdlib.h>

// BST의 노드를 표현
struct node {
  int data;
  struct node *left;
  struct node *right;
};

// root node를 가리키는 포인터
struct node *root = 0;

void addToBST(int _v) {
  struct node *_new = (struct node *)malloc(sizeof(struct node));
  _new->left = 0;
  _new->right = 0;
  _new->data = _v;

  // BST에 노드를 추가
  // 1. BST가 텅텅 비어있는 경우
  if (root == 0) {
    root = _new;
    return;
  }

  // 2. BST에 뭔가 있는 경우,
  // 이때는 자기 위치를 찾아가야 한다. 어디가서 붙어야 하는지
  // root를 움직일 수 없으니, 별도의 포인터 필요
  struct node *spear = root;

  while (1) {

    if (spear->data < _new->data) { // 뭔가 오른쪽으로 가야하는데,,,
      // 1. 그 자리가 비었네,
      if (spear->right == 0) { // 빈자리 넣고 끝!
        spear->right = _new;
        return;
      }
      // 2. 아 누군가 그 자리를 차지하고 있어서, 더 내려가 봐야 하는 상황.
      else {
        spear = spear->right;
      }
    }

    else {                    // 왼쪽으로 가야하는데
      if (spear->left == 0) { // 빈자리에 넣고 끝!
        spear->left = _new;
        return;
      } else {
        spear = spear->left;
      }
    }
  }
}

// Traversal (방문) : 갈 수 있는 node를 한번씩 만 방문 (중복x)
// 3가지 방문 방법, p. 236, 이진 트리의 순회 (traversal)
// 1. pre-order traversal (전위 순회) 자기 - l - r         4      4,2,1,5
// 2. in-order traversal (중위 순회) l - 자기 - r        2  5     1,2,4,5
// (오름차순 정렬)
// 3. post-order traversl (후위 순회) l - r - 자기      1         1,2,5,4
//

void traversal_inorder(struct node *_cur) {
  if (_cur == 0) {
    return;
  }
  traversal_inorder(_cur->left);
  printf("%d\n", _cur->data);
  traversal_inorder(_cur->right);
}

void traversal_preorder(struct node *_cur) {
  if (_cur == 0) {
    return;
  }
  printf("%d\n", _cur->data);
  traversal_preorder(_cur->left);
  traversal_preorder(_cur->right);
}

void traversal_postorder(struct node *_cur) {
  if (_cur == 0) {
    return;
  }
  traversal_preorder(_cur->left);
  traversal_preorder(_cur->right);
  printf("%d\n", _cur->data);
}

// recursion는 위험해!  p.277
// 재귀함수 없이 inorder를 구현해보자!
// 어떻게?
//	 letf우선으로 내려가고 null이 아니면 push, null이면 pop
//	 right로 내려가면서 left 보고, right 보고 stack이 비어있으면 끝!
#define STACK_SZ 10
struct node *stack[STACK_SZ];
int top = -1;

// 여기서 무슨 문제가.....
void push(struct node *_cur) {
  if (top == STACK_SZ - 1) {
    return;
  }
  top++;
  stack[top] = _cur;
  return;
}

struct node *pop(void) {
  if (top == -1) {
    return 0;
  }
  struct node *temp = stack[top];
  top--;
  return temp;
}

// 비재귀적으로 inorder traversal을 수행
void nonrecurvise_inorder(struct node *_cur) {

  while (1) {
    while (1) { // 왼쪽으로 내려가면서 push
      if (_cur != 0) {
        push(_cur);
        _cur = _cur->left;
      } else {
        break;
      }
    }
    _cur = pop();
    if (_cur == 0) {
      break;
    }
    printf("%d\n", _cur->data);
    _cur = _cur->right;
  }

  return;
}

// 레벨 순회 p.279
#define Q_SZ 10
struct node *que[Q_SZ];
int front = 0;
int rear = 0;

void enqueue(struct node *_cur) {
  if ((rear + 1) & Q_SZ == front) {
    return;
  }

  que[rear] = _cur;
  rear = (rear + 1) % Q_SZ;
  return;
}

struct node *dequeue(void) {
  if (front == rear) {
    return 0;
  }
  struct node *result = que[front];
  front = (front + 1) % Q_SZ;
  return result;
}

void level_order(struct node *_cur) {
  if (_cur == 0) {
    return; // BST에 아무것도 없는 경우
  }
  enqueue(_cur);

  while (1) {
    if (front == rear) {
      break;
    }
    _cur = dequeue();
    printf("%d\n", _cur->data);
    if (_cur->left != 0) {
      enqueue(_cur->left);
    }
    if (_cur->right != 0) {
      enqueue(_cur->right);
    }
  }
}

// 높이 구하기, p.289
// 왼쪽이던 오른쪽이던 키큰애 +1하면 키나옴 (recursion)
int which_is_bigger(int a, int b) {

  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int get_height(struct node *_cur) {
  if (_cur == 0) { // NULL
    return 0;      // height
  }
  return (1 + which_is_bigger(get_height(_cur->left), get_height(_cur->right)));
}

// node 개수 구하기, p.288
int get_node_count(struct node *_cur) {
  if (_cur == 0) {
    return 0;
  }

  return 1 + get_node_count(_cur->left) + get_node_count(_cur->right);
}

// p. 289, 단말 노드 개수 구하기 (자식이 없는 node의 개수 구하기)
int get_terminalnode_count(struct node *_cur) {
  // 탈출 조건
  if (_cur == 0) {
    return 0;
  } else if (_cur->left == 0 && _cur->right == 0) {
    return 1;
  }

  return get_terminalnode_count(_cur->left) +
         get_terminalnode_count(_cur->right);
}

// p. 283
// 8.7 트리의 응용, 수식 트리 처리
// 그림 8-32
// post order를 이용하면 posefix바로 나옴
// -   === abc*-
// a *
//  b c

// p.289

int main(void) {

  //  20
  // 10 30
  // 5   40
  addToBST(20);
  addToBST(10);
  addToBST(30);
  addToBST(40);
  addToBST(5);

  // printf("%d\n", (root->data == 20));
  // printf("%d\n", (root->left->data == 10));
  // printf("%d\n", (root->right->data == 30));
  // printf("%d\n", (root->left->left->data == 5));
  // printf("%d\n", (root->right->right->data == 40));
  struct node *spear = root;

  // traversal_inorder(spear);
  // traversal_preorder(spear);

  nonrecurvise_inorder(root);

  // level_order(root); // 위에서 아래로, 왼쪽에서 오른쪽으로

  /*printf("height = %d입니다유~!\n", get_height(root));
  printf("terminal node count의 개수는 %d입니다유~!\n",
  get_terminalnode_count(root));*/
  return 0;
}

// skewed BST : SLL가 똑같음, 모든 장점을 잃어버린다잉
//
// 5
//  10
//   15
//    20
