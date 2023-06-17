#include "block.h"

Block::Block() : value(0) {} //value 0으로 초기화하는 기본 생성자

Block::Block(int value) : value(value) {} //value값 받는 생성자

int Block::getValue() const { //value 반환 함수
    return value;
}

void Block::setValue(int value) { //value 설정 함수
    this->value = value;
}
