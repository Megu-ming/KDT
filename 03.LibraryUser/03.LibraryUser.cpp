#include <iostream>
#include "../03-01.StaticLibrary/framework.h"
#include "../03-02.StaticLibrary/framework.h"
#include "../03-03.StaticLibrary/framework.h"
// [Windows 기준]
// lib, dll
// - Windows에서만 사용이 가능하다.
// - 리눅스(안드로이드)도 라이브러리가 있다. .a(lib), .so(dll)
// - 둘 다 코드 집합이다.
// -> 내가 만든 코드를 다른 사람이 사용 가능하게 하고싶다.
//      - cpp(구현) 코드는 공개하고 싶지 않은 경우 라이브러리를 만들어서 배포할 수 있다.
//          (h는 공개; h파일들과 .lib파일 또는 .dll파일을 배포)
//      - 관리의 단위로(모듈화를 위해) 라이브러리로 구분하고, 코드를 까는 경우도 있다.

// [lib, dll 차이]
// - lib는 빌드 타임에 exe에 통합된다.
// - dll은 실행 시간에 exe에 로드된다.

// 다른 사람이 만들어둔 코드를 사용하는 방법
// [소스코드가 있는 경우]
// - (Ex. ini parser) 프로젝트에 code를 그대로 가져온다. (ThirdParty 폴더 등으로 분류해서 구분)
// - [Static Library(.lib), DynamicLibrary(.dll)] 다른 사람이 만들어둔 프로젝트를 솔루션에 포함해서 참조
//    -> 라이브러리를 참조할 프로젝트에 우클릭 -> 추가 -> 참조 -> 원하는 라이브러리 프로젝트 선택

// [소스코드가 없는 경우]
// - [Static Library] 이미 만들어둔 lib를 빌드 시점에 링크해서 빌드 (lib파일과 Header파일만 공개된 상황, cpp(구현부))
// - 내 빌드 시스템이랑 호환이 안될 수 있다. (Ex. Visual stdio 구버전으로 빌드된 라이브러리의 경우 신버전에 사용할 수 없다.
//       아마 VS2015 이후로는 호환이 된다.)
// - 런타임 라이브러리 설정이 일치해야 한다.(프로젝트 속성 -> C++ -> 코드 형성 -> 런타임 라이브러리(MT, MD))
//      - 런타임 라이브러리 : 표준 함수들 (vector 등 포함)
//      - MT: 런타임 라이브러리를 lib로 취급해서 빌드타임에 링크하겠다,
//              - 단점 : exe 크기가 늘어난다.
//              - 장점 : 만들 때 있던 라이브러리를 가져다 쓰기 때문에 일관성 있는 동작을 보장
//      - MD: 런타임 라이브러리를 dll로 취급해서 런타임에 로드하겠다.
//      - 내 프로젝트(라이브러리를 가져다 쓰는 쪽) 설정과 라이브러리 배포자가 지정해둔 설정이 일치해야 한다.

// 참조가 아닌 방식으로 정적 라이브러리 포함하는 방법 (03-02.StaticLibrary)
// 1. 프로젝트 속성에 추가
//  - 프로젝트 속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉터리
//      - 라이브러리 경로를 추가한다
//  - 프로젝트 속성 -> 링커 -> 입력 -> 추가 종속성
//      - 라이브러리 이름을 추가한다
//      - 소스코드에 #pragma comment로 추가
#pragma comment(lib, "03-03.StaticLibrary.lib")
// static library(A)일 경우 해당 라이브러리에서 다른 라이브러리(B)를 참조하는 경우
// 해당 라이브러리를 사용하는 exe 또는 A,B라이브러리 모두 포함해야 빌드가 성공한다.
// dll이 동일한 상황이라면 exe에서 해당 dll만 포함하면 된다.

int main()
{
    std::cout << "Hello World!\n";
    fnMy0301StaticLibrary();
    fnMy0302StaticLibrary();
    fnMy0303StaticLibrary();
}