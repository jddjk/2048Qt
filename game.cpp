#include "game.h"

Game::Game() : restoreChances(3), gameOver(false) {} //초기 생성자, 복원 횟수 3번으로 설정

const Board& Game::getBoard() const { //보드 반환하는 함수
    return board;
}

bool Game::move(Direction direction) { //움직임 담당 함수
    bool moved = false;

    switch (direction) {
    case Direction::Up:
        moved = board.moveUp();
        break;
    case Direction::Down:
        moved = board.moveDown();
        break;
    case Direction::Left:
        moved = board.moveLeft();
        break;
    case Direction::Right:
        moved = board.moveRight();
        break;
    }

    if (!moved && !board.movePossible()) {
        gameOver = true;
    }

    return moved;
}

void Game::saveState() { //이전 상태를 저장하는 함수(복원 역할)
    previousState = std::make_pair(board, board.getScore());
}

bool Game::restoreState() { //보드 복원하는 함수, 복원이 이뤄졌는지 여부를 반환
    if (!previousState.has_value()) { //버퍼에 이전 상태가 없을 때
        lastRestoreFailure = RestoreFailure::NoPreviousState;
        return false;
    }
    if (restoreChances <= 0) { //복원 횟수가 없을 때
        lastRestoreFailure = RestoreFailure::NoMoreChances;
        return false;
    }
    --restoreChances;
    board.printRestore(restoreChances);
    board = previousState->first;
    board.setScore(previousState->second);
    previousState.reset();
    lastRestoreFailure = RestoreFailure::None;
    return true;
}

Game::RestoreFailure Game::getLastRestoreFailure() const { //복원 실패 여부를 확인하는 함수
    return lastRestoreFailure;
}

void Game::reset() { //처음 게임판 초기화하는 함수
    gameOver = false;
    board.reset();
}

bool Game::canRestoreState() const { //상태 복원 가능 여부 반환
    return previousState.has_value() && restoreChances > 0;
}

bool Game::isGameOver() const { //게임 패배 여부 반환
    return gameOver;
}

bool Game::isGameWon() const {//게임 성공 여부 반환
    return board.hasAchieved2048();
}

int Game::getRemainingRestoreChances() const { //복원 횟수 반환
    return restoreChances;
}
