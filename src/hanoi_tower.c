// 하노이 타워 p.56

// n : 몇개의 접시를 옮기는지, n개의 접시를 옮겨라!
// form 폴대에서
// team 폴대를 임시로 활용해서
// to 폴대로 옮기시오

#include <stdio.h>

void hanoi_tower(int n, int form, int temp, int to) {
  // 탈출

  if (n == 1) {
    printf("%d 에서 %d로 돌을 한개 움직입니다.\n", form, to);
    return;
  }

  hanoi_tower(n - 1, form, to, temp);
  // 마음가볍게 돌 하나만, form에서 to로 옮긴다.
  printf("%d 에서 %d로 돌을 한개 움직입니다.\n", form, to);
  hanoi_tower(n - 1, temp, form, to);
}

int main(void) {

  hanoi_tower(4, 1, 2, 3);

  return 0;
}
