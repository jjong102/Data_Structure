#include <stdio.h>
#include <stdlib.h>

// BST의 노드를 표현
struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct combo {
  struct node *parent;
  struct node *me;
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

// BST의 노드 삭제

// 1. 무자식 노드 (terminal node) 삭제는 쉽다.
//		다만, 부모 노드만 영향을 받는다. 해당 link = null로 설정
//		!!! 무자식 노드 == root
//				===> root를 null로 변환

// 2. 홑 (1개)자식,
//		자식에게 자기 자리를 물려주고, 나의 부모에게 '그자식'을
// 연결시켜준다.
//		** 내가 부모의 '어떤 자식'인지 잘 기억했다가, 그렇게 '그 자식'
// 연결해준다.
//		!!! 홑자식 노드가 == root,
//				root로 하여금 남은 자식을 가리키게 한다.

// 3. 쌍(2개) 자식
//		왼쪽 집안에서 가장 큰 노드가 올라와서 대체,
//		오른쪽 집안에서 가장 작은 노드가 올라와서 대체,
//		!!! 쌍자식 노드 == root,
//				별거없네...

// 값 _v를 가진 노드와 parent 노드를 찾아서,
// 각각에 대한 포인터를 struct combo로 만들어서 반환한다.
//		parent: _v를 가진 노드의 부모 노드 (부모가 없으면 null로 반환)
//		me  : _v를 가진 노드              ( _v를 가진 노드가 없는 경우,
// null)
struct combo
findNodeCombo(int _v) { // 노드의 대한 pointer하고 부모에 대한 pointer 2개를
                        // 넘겨줘야함. --> struct 이용
  struct node *spear = root;
  struct node *parent = 0; // root(me)의 부모

  while (1) {

    if (spear == 0) {
      struct combo res = {0, 0};
      return res;
    }

    if (spear->data == _v) { // _v를 가진 노드를 찾은 경우,
      struct combo res = {parent, spear};
      return res;
    }

    else if (spear->data < _v) { // 오른쪽으로 타고 내려가야함.
      parent = spear;
      spear = spear->right;
    }

    else { // 왼쪽으로 타고 내려 가는 경우,
      parent = spear;
      spear = spear->left;
    }
  }
}

// 값 _v를 가진 노드를 삭제
void delFromBST(int _v) {

  struct combo res = findNodeCombo(_v); //_v를 가진 노드를 찾는다.

  if (res.me == 0) { // _v가 없으므로 종료, thank you
    return;
  }

  // 1. 무자식
  if (res.me->left == 0 && res.me->right == 0) {
    // 예외,root인지 판별
    if (res.parent == 0) { // 내가 root
      root = 0;
      free(res.me);
      return;
    } else {
      if (res.parent->left == res.me) { // 내가 부모의 왼자식
        res.parent->left = 0;
      } else { // 내가 부모의 오른자식
        res.parent->right = 0;
      }
      free(res.me);
      return;
    }
  }

  // 3. 쌍자식
  else if (res.me->left != 0 && res.me->right != 0) {
    // 일단 후계자를 찾는다.
    struct node *spear = res.me->right;
    while (1) {
      if (spear->left == 0) {
        break;
      }
      spear = spear->left;
    }
    // 이 상황에서 spear는 후계자를 가리키고 있다.
    // 후계가 값을 임시 저장해 놓는다.
    int temp = spear->data;
    // 후계자를 날려버린다.
    delFromBST(temp);
    // 임시저장 값을 me자리에 채운다.
    res.me->data = temp;
    return;
  }

  // 2. 홑자식
  else {
    // 일단, 내가 왼자식 가지고 있는지 확인
    if (res.me->left != 0) { // 왼쪽 자식 하나만 가지고 있음.
      // 내가 root인 경우
      if (res.parent == 0) { // root인 조건
        root = res.me->left;
        free(res.me);
        return;
      } else {                            // 내가 root가 아님.
        if (res.parent->left == res.me) { // me가 parent의 left
          res.parent->left = res.me->left;
        } else { // me가 parent의 right
          res.parent->right = res.me->left;
        }
        free(res.me);
        return;
      }
    } else { // 오른자식 하나만 가지고 있음.
      // 내가 root인 경우
      if (res.parent == 0) { // root인 조건
        root = res.me->right;
        free(res.me);
        return;
      } else {                            // 내가 root가 아님.
        if (res.parent->left == res.me) { // me가 parent의 left
          res.parent->left = res.me->right;
        } else { // me가 parent의 right
          res.parent->right = res.me->right;
        }
        free(res.me);
        return;
      }
    }
  }
}

void inorder_traversal(struct node *_cur) {
  if (_cur == 0) {
    return;
  }
  inorder_traversal(_cur->left);
  printf("%d\n", _cur->data);
  inorder_traversal(_cur->right);
}

int main(void) {

  //  20
  // 10 30
  // 5   40
  addToBST(20);
  addToBST(10);
  addToBST(30);
  addToBST(40);
  addToBST(5);

  // 무자식 지우기
  delFromBST(10);
  // delFromBST(40);

  // 홑자식 지우기
  // delFromBST(30);

  // 쌍자식 지우기
  // delFromBST(20);

  // 없는 자식 지우기
  delFromBST(100);

  inorder_traversal(root);

  // struct combo res = findNodeCombo(5);
  // printf("%d    %d\n", res.me->data, res.parent->data); // if) 5를 찾는다면
  // 5, 10 printf("%d    %d\n", res.me->data, (res.parent == 0)); // if 20 root
  // 20, 1 printf("%d    %d\n", (res.me == 0), (res.parent == 0)); // if 100 1,
  // 1
  return 0;
}
