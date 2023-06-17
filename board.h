#ifndef BOARD_H
#define BOARD_H

#include <array>  // array 헤더 파일 포함
#include <random>  // random 헤더 파일 포함
#include <algorithm>  // algorithm 헤더 파일 포함
#include <memory>  // memory 헤더 파일 포함
#include "block.h"  // block.h 헤더 파일 포함
#include "gamelogger.h"  // gamelogger.h 헤더 파일 포함

class Board {
public:
    Board() : gameLogger(std::make_shared<GameLogger>()) { //기본 생성자
        reset(); // reset 함수 호출
    }
    ~Board() { }// Board 클래스 소멸자

    Board(const Board& other) //복사 생성자
        : grid(other.grid), score(other.score), count(other.count), gameLogger(other.gameLogger) {
    }

    Board& operator=(const Board& other) { //대입 연산자
        if (this != &other) {
            grid = other.grid;
            score = other.score;
            count = other.count;
            gameLogger = other.gameLogger;
        }
        return *this;
    }

    void reset(); //보드 초기화 함수
    void addRandomBlock(); //랜덤하게 블록 생성하는 함수
    bool movePossible() const; //이동 가능한지 여부를 판단하는 함수
    bool isFull() const; //보드가 가득 찼는지 여부를 판단하는 함수
    int getScore() const; //현재 점수 반환 함수
    void setScore(int newScore); //현재 점수 설정 함수

    bool moveUp(); //위 방향 이동
    bool moveDown(); //아래 방향 이동
    bool moveLeft(); //왼 방향 이동
    bool moveRight(); //오른 방향 이동
    bool hasAchieved2048() const; //2048 달성 여부 판단 함수
    bool isSameState(const std::array<std::array<Block, 4>, 4>& other) const; //전과 같은 상태인지 여부를 판단하는 함수

    const std::array<std::array<Block, 4>, 4>& getGrid() const; //그리드를 반환하는 함수(보드)
    std::vector<std::pair<int, int>> getInitialPosition(); //초기 블록 상태 반환 함수
    std::pair<int, int> getInitialPosition() const; //초기 블록 상태 반환 함수
    void printRestore(int Restore); //restore 횟수를 출력하는 함수

private:
    std::array<std::array<Block, 4>, 4> grid; //보드를 나타내는 함수
    int score; //점수를 나타내는 변수
    int count; //총 턴이 진행된 횟수를 나타내는 변수
    std::shared_ptr<GameLogger> gameLogger; //게임을 출력하는 gamelogger클래스 포인터

    bool mergeBlocks(std::array<Block, 4>& line, int rowOrColumn, bool isRow, bool isReversed = false); //블록을 합치는 과정의 함수
    bool shiftBlocks(std::array<Block, 4>& line); //블록을 방향에 맞게 옮기는 함수
};

#endif
