#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    gameUi = new GameUi(this);  // GameUi 인스턴스를 생성, 부모를 MainWindow로 설정
    setCentralWidget(gameUi);
}
