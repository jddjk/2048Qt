#ifndef BLOCKUI_H
#define BLOCKUI_H

#include <QWidget>  // QWidget 헤더 파일 포함
#include <QLabel>   // QLabel 헤더 파일 포함
#include "block.h"  // block.h 헤더 파일 포함

class BlockUi : public QLabel {
    Q_OBJECT
public:
    explicit BlockUi(QWidget* parent = nullptr);
    void setBlock(int value); // 블록 값 설정 멤버 함수
private:
    void setBlockColor(int value); // 블록의 색상 설정 멤버 함수

    Block block;  // Block 클래스의 인스턴스 멤버
};

#endif
