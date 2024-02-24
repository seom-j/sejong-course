## :books: 프로젝트 주제
simple-banking-system-project : 은행 ATM 시스템 구현

> 세종대학교 2022-2 문제 해결 및 실습 : JAVA 
>
> 2022.11 ~ 2023.11

<br/><br/>

## 🌟 프로젝트 목적

📌 JAVA를 사용한 은행 ATM UI 및 기능 구현

> JAVA Swing을 활용한 GUI프로그램 구축
> 
> JAVA 클래스 및 Thread의 이해

<br/><br/>

## :star2: 프로젝트 기능

📌 Login
> 계좌번호와 비밀번호를 입력받아 txt파일의 정보와 일치할 경우 아래의 3가지 기능의 선택 화면으로 이동
> 
> 일치하지 않을 경우 경고메세지와 함께 초기 화면으로 이동

1. Balance
> 현재 계좌의 잔액 출력

2. Withdraw
> 비밀번호 재확인
>
> 비밀번호가 일치한 후, 출금이 가능할 경우 - 해당 내용을 거래 내역 파일에 삽입
>
> 비밀번호가 일치하지 않을 경우 or 잔액이 모자란 경우  - 오류 메시지 출력 & 로그인 직후 화면으로

3. Deposit
> 사용자에게 현금/수표 등을 넣으라는 안내메시지 출력 & 금액 입력받음
> 3초가 지난 후 입금액 확인, 해당 입금액을 계좌 잔액에 합산하여 해당 내용 거래 내역 파일에 삽입

📌 Simulation
> simulation 파일을 읽어들여 실행 내역을 하나씩 구동
> 
> 이의 출력 내용은 별도의 영역을 통해 알아보기 쉽도록 출력
> 
> Simulation 결과 또한 transactions 파일에 반영
> 
> 반드시 별도의 Thread를 구성하여 동작

<br/>

![Java](https://img.shields.io/badge/java-%23ED8B00.svg?style=for-the-badge&logo=openjdk&logoColor=white)

<br/><br/>

## :star2: 프로젝트 결론

JAVA의 Swing을 활용하여 ATM의 기능을 하는 GUI 프로그램을 구축해볼 수 있었음

해당 과정에서 버튼, 마우스/키보드 입력, 파일 입출력 등을 활용해볼 수 있었으며 객체지향언어인 JAVA의 클래스, Thread의 개념을 이해할 수 있었음
