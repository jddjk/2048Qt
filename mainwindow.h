#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>  // QMainWindow 헤더 파일 포함
#include "gameui.h"  // gameui.h 헤더 파일 포함

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    GameUi* gameUi; // GameUi 포인터 멤버
};

#endif
