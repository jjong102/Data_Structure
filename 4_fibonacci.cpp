// P.53 피보나치수열의 계산
// 0,1,1,2,3,5,8,13 .....
// 앞선 두개 항의 항이 나의 값
// recursion을 이용

// n번째 피보나치 값을 반환하는 함수
// 0번째 : 0
// 1번째 : 1
// 2번째 : 1
#include <stdio.h>

int a[] = {
    0,
    1,
}; // 전역변수 일차원 배열 설정
//
//
// 3. 테이블 이용, 배열을 이용한 시간 단축이 가능함.(전역변수) o(n)
int fibo_r(int n) {

  if (a[n - 1] == -1) {
    if (a[n - 2] != -1 && a[n - 3] != -1) {
      a[n - 1] = a[n - 3] + a[n - 2];
    } else {
    }
    return fibo_r(n - 2) + fibo_r(n - 1);
  } else {
    return a[n - 1];
  }
}

// 1. recursion을 이용한 fibonacci 계산 O(2^n)
// int fibo_r(int n) {
//
//	//탈출조건
//	if (n == 0) {
//		return 0;
//	}
//	if (n == 1) {
//		return 1;
//	}
//
//	return fibo_r(n - 2) + fibo_r(n - 1);
//}

// 2. 반복을 이용한 계산
int fibo(int n) {

  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }

  int pp = 0;     // previous-previous
  int p = 1;      // previous
  int result = 0; // 결과값

  for (int i = 2; i <= n; i++) {
    result = pp + p;
    pp = p;
    p = result;
  }

  return result;
}

int main(void) {
  int n = 0;
  int i;

  scanf_s("%d", &n);
  /*for (i = 2; i <= n - 1; i++) {
          a[i] = -1;
  }*/

  printf("%d\n", fibo_r(n));

  return 0;
}
