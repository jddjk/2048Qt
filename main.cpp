#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;  // MainWindow 인스턴스 생성
    mainWindow.show();  // MainWindow 표시

    return app.exec();
}
