#include "gamelogger.h"
#include <iostream>

GameLogger::GameLogger() : log_file_("progress.txt", std::ios::out) { //기본 생성자, 파일 이름은 "progress.txt"
    if (!log_file_) {
        throw std::runtime_error("Could not open progress.txt for writing"); //파일 작성이 안되는 경우
    }
}

GameLogger::~GameLogger() { //기본 소멸자
    if (log_file_.is_open())
        log_file_.close();
}

void GameLogger::logInitial(int x1, int y1, int x2, int y2) { //초기 상태 출력
    log_file_ << "INITIAL " << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl<< std::endl;
}


void GameLogger::logMove(const std::string& direction) { //움직임 방향 출력
    log_file_ << direction << std::endl<< std::endl;
}

void GameLogger::logGenerate(int x, int y, int n) { //새로운 블록 생성 출력
    log_file_ << "GENERATE " << x << " " << y << " " << n << std::endl<< std::endl;
}

void GameLogger::logMerge(int x, int y, int n) { //병합된 블록 출력
    log_file_ << "MERGE " << x << " " << y << " " << n << std::endl<< std::endl;
}

void GameLogger::logRestore(int n) { //남은 복원 횟수 출력
    log_file_ << "RESTORE " << n << std::endl<< std::endl;
}

void GameLogger::logScore(int n) { //점수 출력
    log_file_ << "SCORE " << n << std::endl<< std::endl;
}
