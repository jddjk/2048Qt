#include "blockui.h"

BlockUi::BlockUi(QWidget* parent) : QLabel(parent) {
    setFixedSize(250, 250);  // 고정된 크기 250x250
    setAlignment(Qt::AlignCenter);  // 중앙 정렬
}

void BlockUi::setBlock(int value) { //블록 색깔 설정
    QString text;
    QString styleSheet = "QLabel { background: ";

    switch (value) {
    case 0:
        text = "";
        styleSheet += "rgb(255, 255, 255)";
        break;
    case 2:
        text = "2";
        styleSheet += "rgb(187, 173, 160)";
        break;
    case 4:
        text = "4";
        styleSheet += "rgb(237, 224, 200)";
        break;
    case 8:
        text = "8";
        styleSheet += "rgb(242, 177, 121)";
        break;
    case 16:
        text = "16";
        styleSheet += "rgb(245, 149, 99)";
        break;
    case 32:
        text = "32";
        styleSheet += "rgb(246, 126, 95)";
        break;
    case 64:
        text = "64";
        styleSheet += "rgb(246, 94, 59)";
        break;
    case 128:
        text = "128";
        styleSheet += "rgb(237, 207, 114)";
        break;
    case 256:
        text = "256";
        styleSheet += "rgb(237, 204, 97)";
        break;
    case 512:
        text = "512";
        styleSheet += "rgb(237, 200, 80)";
        break;
    case 1024:
        text = "1024";
        styleSheet += "rgb(237, 197, 63)";
        break;
    case 2048:
        text = "2048";
        styleSheet += "rgb(237, 194, 46)";
        break;
    default:
        text = QString::number(value);
        styleSheet += "rgb(0, 0, 0)";
        break;
    }
    //블록 내부 스타일 설정
    styleSheet += "; color: black; border-style: solid; font: 70pt; font-weight: bold; }";
    setStyleSheet(styleSheet);
    setText(text);
}
