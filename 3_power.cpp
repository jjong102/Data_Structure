// 거듭 제곱값의 계산
// 2 ^ 3 = 2*2*2
// recursion 이용
#include <stdio.h>

// recursion power, 좀 더 빠르게 2^10 ---> 4^5(값은 같다잉)[지수값을 빨리
// 떨어트리는 것이 포인트]
//  ---> 지수의 5는 2로 나눌 수가없음
//  ---> 4 * 4^4
//  ---> 4 * 16^2
//  ---> 4 * (16^2)^1	10 ---> 4단계로
// O(log_2 n)
int my_power_fast(int a, int b) {

  if (b == 1) {
    return a;
  }

  // b가 짝수
  if (b % 2 == 0) {
    return my_power_fast(a * a, b / 2);
  }

  // b가 홀수
  else {
    return a * my_power_fast(a * a, (b - 1) / 2);
  }
}

// O(n)  ---> O(log_2 n)
int my_power_recursion(int a, int b) { // a^b을 계선해서 반환
  // recursion을 이용한 해법

  // 탈출조건
  if (b == 1) {
    return a;
  }

  return a * my_power_recursion(a, b - 1);
}

// O(n)
int my_power(int a, int b) { // a^b을 계선해서 반환
  // 반복을 이용한 해법
  int res = 1;
  int i;

  for (i = 1; i <= b; i++) {

    res = res * a;
  }
  return res;
}

int main(void) {
  int res = my_power(2, 3);

  return 0;
}
