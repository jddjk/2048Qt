#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <optional>

class Game {
public:
    enum class Direction { Up, Down, Left, Right }; //방향을 나타냄
    enum class RestoreFailure { None, NoPreviousState, NoMoreChances }; //restore가 실패하는 경우

    Game(); //기본 생성자
    const Board& getBoard() const; //보드를 반환하는 함수
    bool move(Direction direction); //움직임을 입력받아 움직임을 실행하는 함수
    void saveState(); //되돌린 상태가 존재하는지 여부를 판단하는 함수
    bool restoreState(); //상태를 되돌릴 수 있는지 여부를 판단하는 함수
    void reset(); //초기화 함수
    bool canRestoreState() const; //restore 여부를 판단하는 함수
    bool isGameOver() const; //gameover 여부를 판단하는 함수
    bool isGameWon() const; //game win 여부를 판단하는 함수
    int getRemainingRestoreChances() const; //restore 남은 횟수를 저장하는 변수
    RestoreFailure getLastRestoreFailure() const; //restore 실패하는 경우
    static std::string directionToString(Direction direction); //방향을 바로 string형으로 바꿔주는 함수


private:
    Board board; //board 인스턴스
    std::optional<std::pair<Board, int>> previousState; //이전 보드 상태를 나타내는 pair
    int restoreChances; //restore 횟수를 저장하는 변수
    bool gameOver; //게임 오버 여부 판단
    RestoreFailure lastRestoreFailure; //restore 실패여부를 저장
};

#endif
