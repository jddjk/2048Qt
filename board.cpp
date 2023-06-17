#include "board.h"

void Board::reset() {
    for (auto& row : grid) {
        for (auto& block : row) {
            block.setValue(0);  //모든 블록 값 0으로 초기화
        }
    }
    score = 0; //점수 초기화
    addRandomBlock(); //랜덤한 위치에 블록 추가
    addRandomBlock(); //처음 두개라서 한 번 더
}

void Board::addRandomBlock() {
    std::vector<std::pair<int, int>> emptyPositions;
    std::vector<std::pair<int, int>> initialPositions;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j].getValue() == 0) {
                emptyPositions.push_back(std::make_pair(i, j));
            }
        }
    }

    if (emptyPositions.empty()) { //빈 위치 없는 경우 반환
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, emptyPositions.size() - 1);
    std::uniform_int_distribution<int> valueDist(0, 9);
    int randomIndex = dist(gen);
    int value = (valueDist(gen) < 8) ? 2 : 4; //80% 확률 2, 20%확률로 4
    int row = emptyPositions[randomIndex].first;
    int col = emptyPositions[randomIndex].second;
    grid[row][col].setValue(value);

    if(count >= 2) {//초기 상태가 아닌 경우
        gameLogger->logGenerate(row + 1, col + 1, value);
        gameLogger->logScore(score);
    } else if (count == 1) { //초기 상태인 경우
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (grid[i][j].getValue() != 0) {
                    initialPositions.push_back(std::make_pair(i, j));
                }
            }
        }
        gameLogger->logInitial(initialPositions[0].first + 1, initialPositions[0].second + 1, initialPositions[1].first + 1, initialPositions[1].second + 1);
    }
    count++;//턴 증가
}

bool Board::movePossible() const { //이동가능한지 여부를 판단하는 함수
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i][j].getValue() == grid[i][j + 1].getValue() ||
                grid[j][i].getValue() == grid[j + 1][i].getValue()) {
                return true;
            }
        }
    }

    return !isFull();
}


bool Board::isFull() const {  //꽉 찼는지 여부를 판단
    for (const auto& row : grid) {
        for (const auto& block : row) {
            if (block.getValue() == 0) {
                return false;
            }
        }
    }
    return true;
}

int Board::getScore() const { //점수 반환하는 함수
    return score;
}

bool Board::moveLeft() { //왼쪽으로 움직이는 함수. 나머지 방향은 상하좌우를 반전시킨 뒤 이를 활용
    std::array<std::array<Block, 4>, 4> prevState = grid;
    gameLogger->logMove("LEFT"); //파일에 LEFT 출력
    bool moved = false;
    for (int row = 0; row < 4; ++row) {
        moved = shiftBlocks(grid[row]) || moved; //한쪽으로 이동
        moved = mergeBlocks(grid[row], row, true) || moved; //병합 과정
        moved = shiftBlocks(grid[row]) || moved; //한쪽으로 이동
    }
    if (isSameState(prevState)) return false; //이전과 같은 상태라면 false 반환
    if (moved) addRandomBlock(); //움직임이 가능했다면, 새로운 블록 추가
    return moved; //움직임이 일어났는지 여부를 반환
}

bool Board::moveRight() {
    std::array<std::array<Block, 4>, 4> prevState = grid;
    gameLogger->logMove("RIGHT"); //파일에 RIGHT 출력
    bool moved = false;
    for (int row = 0; row < 4; ++row) {
        std::reverse(grid[row].begin(), grid[row].end());
        moved = shiftBlocks(grid[row]) || moved;
        moved = mergeBlocks(grid[row], row, true, true) || moved;
        moved = shiftBlocks(grid[row]) || moved;
        std::reverse(grid[row].begin(), grid[row].end());
    }
    if (isSameState(prevState)) return false;
    if (moved) addRandomBlock(); //움직임이 가능했다면, 새로운 블록 추가
    return moved; //움직임이 일어났는지 여부를 반환
}

bool Board::moveUp() {
    std::array<std::array<Block, 4>, 4> prevState = grid;
    gameLogger->logMove("UP"); //파일에 UP 출력
    bool moved = false;
    for (int col = 0; col < 4; ++col) {
        std::array<Block, 4> column;
        for (int row = 0; row < 4; ++row) {
            column[row] = grid[row][col];
        }
        moved = shiftBlocks(column) || moved;
        moved = mergeBlocks(column, col, false, false) || moved;
        moved = shiftBlocks(column) || moved;
        for (int row = 0; row < 4; ++row) {
            grid[row][col] = column[row];
        }
    }
    if (isSameState(prevState)) return false;
    if (moved) addRandomBlock(); //움직임이 가능했다면, 새로운 블록 추가
    return moved; //움직임이 일어났는지 여부를 반환
}


bool Board::moveDown() {
    std::array<std::array<Block, 4>, 4> prevState = grid;
    gameLogger->logMove("DOWN"); //파일에 DOWN 출력
    bool moved = false;
    for (int col = 0; col < 4; ++col) {
        std::array<Block, 4> column;
        for (int row = 0; row < 4; ++row) {
            column[row] = grid[3 - row][col];
        }
        moved = shiftBlocks(column) || moved;
        moved = mergeBlocks(column, col, false, true) || moved;
        moved = shiftBlocks(column) || moved;
        for (int row = 0; row < 4; ++row) {
            grid[3 - row][col] = column[row];
        }
    }
    if (isSameState(prevState)) return false;
    if (moved) addRandomBlock(); //움직임이 가능했다면, 새로운 블록 추가
    return moved; //움직임이 일어났는지 여부를 반환
}


const std::array<std::array<Block, 4>, 4>& Board::getGrid() const { //grid(보드) 반환
    return grid;
}

bool Board::mergeBlocks(std::array<Block, 4>& line, int rowOrColumn, bool isRow, bool isReversed) {//블록을 실제로 병합하는 함수, 마지막 두 파라미터는 상하좌우 반전 여부를 판단하기 위한 매개 변수
    bool merged = false;
    for (int i = 0; i < 3; ++i) {
        if (line[i].getValue() == line[i + 1].getValue() && line[i].getValue() != 0) {
            int newValue = line[i].getValue() * 2;
            line[i].setValue(newValue);
            line[i + 1].setValue(0);
            score += newValue;
            merged = true;
            int pos = isReversed ? 3 - i : i; //반전된 경우 이를 뒤집음
            if (isRow) {
                gameLogger->logMerge(rowOrColumn + 1, pos + 1, newValue); //병합이 이루어진 곳과 숫자를 출력
            } else {
                gameLogger->logMerge(pos + 1, rowOrColumn + 1, newValue); //병합이 이루어진 곳과 숫자를 출력
            }
        }
    }
    return merged;
}

bool Board::shiftBlocks(std::array<Block, 4>& line) {//블록 이동 함수
    int emptySlot = 0;
    for (int i = 0; i < 4; ++i) {
        if (line[i].getValue() != 0) {
            std::swap(line[emptySlot++], line[i]);
        }
    }
    return emptySlot != 4;
}

void Board::setScore(int newScore) { //점수 설정 함수
    score = newScore;
}

bool Board::hasAchieved2048() const { //2048 달성 여부를 알려주는 함수
    for (const auto& row : grid) {
        for (const auto& block : row) {
            if (block.getValue() == 2048) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isSameState(const std::array<std::array<Block, 4>, 4>& other) const {//이전과 같은 보드인지를 판단하는 함수
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j].getValue() != other[i][j].getValue()) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<int, int>> Board::getInitialPosition() { //초기 상태를 반환하는 함수
    std::vector<std::pair<int, int>> positions;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j].getValue() != 0) {
                positions.push_back({i, j});
            }
        }
    }
    return positions;
}

void Board::printRestore(int Restore) { //restore 남은 횟수를 출력하는 함수
    gameLogger->logRestore(Restore);
}
