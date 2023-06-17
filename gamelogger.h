#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <fstream>  // fstream 헤더 파일 포함
#include <string>  // string 헤더 파일 포함
#include <vector>  // vector 헤더 파일 포함
#include <utility>  // utility 헤더 파일 포함

class GameLogger {
public:
    GameLogger(); //기본 생성자
    ~GameLogger(); //기본 소멸자

    GameLogger(const GameLogger&) = delete; //복사 생성자 삭제
    GameLogger& operator=(const GameLogger&) = delete; // 대입 연산자 삭제

    void logInitial(int x1, int y1, int x2, int y2); //초기 블록 로그 함수
    void logMove(const std::string& direction); //이동 로그 함수
    void logGenerate(int x, int y, int n); //새로운 블록 위치 및 숫자 로그 함수
    void logMerge(int x, int y, int n); //병합 위치 및 숫자 로그 함수
    void logRestore(int n); //restore 횟수 로그 함수
    void logScore(int n); //점수 로그 함수

private:
    std::ofstream log_file_; //로그 파일 ofstream 객체
};

#endif
