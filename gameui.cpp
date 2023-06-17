#include "gameui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

GameUi::GameUi(QWidget* parent) : QWidget(parent) {

    setFocusPolicy(Qt::StrongFocus); //strong focus policy

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    gridLayout = new QGridLayout(); //그리드 레이아웃 생성
    gridLayout->setSpacing(10);
    for (int i = 0; i < 4; ++i) {
        gridLayout->setRowStretch(i, 1);
        gridLayout->setColumnStretch(i, 1);
    }

    QVBoxLayout* vertLayout = new QVBoxLayout(); //버티컬 레이아웃 생성
    vertLayout->setSpacing(10);

    scoreLabel = new QLabel(this);  // 점수 라벨
    exitButton = new QPushButton("Exit", this);  // Exit 버튼 생성
    restoreButton = new QPushButton("Restore", this);  // Restore 버튼 생성

    initializeGrid();
    initializeScoreLabel();
    initializeButtons();

    //각각의 widget 생성
    vertLayout->addWidget(scoreLabel);
    vertLayout->addWidget(exitButton);
    vertLayout->addWidget(restoreButton);

    // 그리드 레이아웃 그려넣기
    mainLayout->addLayout(gridLayout, 4);
    mainLayout->addLayout(vertLayout, 1);

    updateGrid();
    updateScoreLabel();
    // 버튼과 연결, 동기화
    connect(exitButton, SIGNAL(clicked()), this, SLOT(handleExitButton()));
    connect(restoreButton, SIGNAL(clicked()), this, SLOT(handleRestoreButton()));
}

void GameUi::initializeGrid() { //블록 생성하는 함수
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            blockUI[i][j] = new BlockUi(this);
            blockUI[i][j]->setFixedSize(250, 250);
            blockUI[i][j]->setAutoFillBackground(true);
            blockUI[i][j]->setStyleSheet("QWidget { background-color: lightGray; border: 5px solid darkGray; }");

            gridLayout->addWidget(blockUI[i][j], i, j, 1, 1);
        }
    }
}

void GameUi::initializeScoreLabel() { //점수 라벨 생성하는 함수
    scoreLabel->setText("Score: 0");
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel { font-size: 30px; }");
}

void GameUi::initializeButtons() { //버튼 만드는 함수
    exitButton->setFixedSize(300, 200);
    exitButton->setFont(QFont("Arial", 20));
    restoreButton->setFixedSize(300, 200);
    restoreButton->setFont(QFont("Arial", 20));
}

void GameUi::updateGrid() { //보드를 매번 업데이트 하는 함수
    const auto& grid = game.getBoard().getGrid();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            blockUI[i][j]->setBlock(grid[i][j].getValue());
        }
    }
}

void GameUi::updateScoreLabel() { //숫자를 업데이트하는 함수
    int score = game.getBoard().getScore();
    scoreLabel->setText("Score: " + QString::number(score));
}

void GameUi::handleExitButton() { //나가기 버튼 조작
    QApplication::quit();
}

void GameUi::handleRestoreButton() { //초기화 버튼 조작
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Restore",
                                  QString("Restore the game board to its previous state? Remaining chances: %1")
                                      .arg(game.getRemainingRestoreChances()),
                                  QMessageBox::Yes | QMessageBox::No); //복원 여부 물어보는 문장
    if (reply == QMessageBox::Yes) {
        if (game.restoreState()) {
            updateGrid();
            updateScoreLabel();
            QMessageBox::information(this, "Restore", "The board has been restored to its previous state!"); //복원 성공했을 경우 메시지 박스
            if (game.isGameOver()) {
                showGameOverDialog();
            } else if (game.isGameWon()) {
                showGameWonDialog();
            }
        } else {
            switch (game.getLastRestoreFailure()) { //복원이 불가능한 경우
            case Game::RestoreFailure::NoPreviousState:
                QMessageBox::information(this, "Restore", "There is no previously saved board in the buffer.");
                break;
            case Game::RestoreFailure::NoMoreChances:
                QMessageBox::information(this, "Restore", "No more chance to restore the board to its previous state.");
                break;
            default:
                break;
            }
        }
    }
}

void GameUi::keyPressEvent(QKeyEvent* event) { //방향키 누르는 거 처리하는 함수
    bool moved = false;
    game.saveState();

    switch (event->key()) {
    case Qt::Key_Up:
        moved = game.move(Game::Direction::Up);
        break;
    case Qt::Key_Down:
        moved = game.move(Game::Direction::Down);
        break;
    case Qt::Key_Left:
        moved = game.move(Game::Direction::Left);
        break;
    case Qt::Key_Right:
        moved = game.move(Game::Direction::Right);
        break;
    default:
        QWidget::keyPressEvent(event);
    }

    if(moved) {
        updateGrid();
        updateScoreLabel();
        if (game.isGameWon()) { //게임 성공했을 때, 1초 뒤 나오게 하는 함수
            QTimer::singleShot(1000, this, &GameUi::showGameWonDialog);  // Show the dialog 1 second later
        }
    }

    if(game.isGameOver()) { //게임 실패했을 때
        GameUi::showGameOverDialog();
    }
}

void GameUi::showGameWonDialog() { //이겼음을 알려주는 함수
    QMessageBox::information(this, "Congratulations!", "You have reached 2048!\n\nYour score: " + QString::number(game.getBoard().getScore()));
}

void GameUi::showGameOverDialog() { //게임 패배를 알려주는 함수
    QMessageBox::information(this, "Game Over", "You have no more valid moves. Your score: " + QString::number(game.getBoard().getScore()));
}


