// 배열, 구조체, 포인터 p.70
// 배열 : 같은 데이터 타입, 순차적으로, 0~n-1번
// 크기 조절 불가

// 구조체 struct p.73
// 새로운 데이터 타입을 만드는 기능
// 데이터 타입이 다른 것들을 모아서 만들 수 있다.

// P.76 ~ 88 컷 보지마잉

#include <stdio.h>

// 배열
int main(void) {
  int a[10];    // 일차원 배열
  int aa[3][3]; // ---> aa[0][0], a[0][1] ..... a[2][2] 이차원 배열
                // 실제로 저장되는 것은 일차원

  return 0;
}

// 구조체
//  사람에 한 데이터를 저장하고 싶다.
//  사람마다 고유 번호(정수)가 있고, 나이 정보를 저장하고 싶다.

// int
// char === struct Person
// float

// struct -----> class[겍체](할 수 있는 일을 함수로 담을 수 있음.)

typedef struct { // typedef 사이에 이름이 없다. 짧게 쓰고 싶을때..
  int id;
  int age;
  float height;
} PersonA; // 이름

struct Person {
  int id;
  int age;
  float height; // 키정보
};

int main(void) {

  // struct Person
  PersonA a = {2, 19,
               160.0}; // 변수 a를 하나 만들고, 이것의 데이터 형은 struct Person

  a.id = 1;
  a.age = 20;
  a.height = 170.0;

  return 0;
}
