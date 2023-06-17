#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>  // QWidget 헤더 파일 포함
#include <QGridLayout>  // QGridLayout 헤더 파일 포함
#include <QLabel>  // QLabel 헤더 파일 포함
#include <QPushButton>  // QPushButton 헤더 파일 포함
#include <QApplication>  // QApplication 헤더 파일 포함
#include <QKeyEvent>  // QKeyEvent 헤더 파일 포함
#include <QMessageBox>  // QMessageBox 헤더 파일 포함
#include <QPalette>  // QPalette 헤더 파일 포함
#include <QTimer>  // QTimer 헤더 파일 포함
#include "blockui.h"  // blockui.h 헤더 파일 포함
#include "game.h"  // game.h 헤더 파일 포함

class GameUi : public QWidget {
    Q_OBJECT
public:
    explicit GameUi(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void showGameOverDialog();

private:
    QGridLayout* gridLayout;  // QGridLayout 포인터 멤버
    QLabel* scoreLabel;  // QLabel 포인터 멤버
    QPushButton* exitButton;  // QPushButton 포인터 멤버
    QPushButton* restoreButton;
    BlockUi* blockUI[4][4]; //블록ui 포인터 배열 멤버
    Game game; // game 클래스

    void initializeGrid(); //그리드 초기화
    void initializeScoreLabel(); //점수 초기화
    void initializeButtons(); //버튼 초기화
    void updateGrid(); //그리드 업데이트
    void updateScoreLabel(); //점수 업데이트
    void showGameWonDialog(); //game win 출력

private slots:
    void handleExitButton(); //종료 버튼
    void handleRestoreButton(); //restore 버튼

};

#endif
