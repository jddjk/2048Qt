#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
    Block();  // Block 클래스 기본 생성자 선언
    Block(int value); // Block 클래스 매개변수 가진 생성자 선언
    int getValue() const; // value 멤버 변수의 값을 반환하는 멤버 함수
    void setValue(int value); // value 멤버 변수의 값 설정하는 멤버 함수

private:
    int value;
};

#endif // BLOCK_H
