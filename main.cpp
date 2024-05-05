#include "ChessGameWindow.h"
#include <QtWidgets/QApplication>
#include "GameLogic.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include <qdebug.h>
#include <iostream>

using namespace Interface;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChessGameWindow window;
	window.setWindowTitle("Chess");
	QIcon icon("assets//Black//Knight.png");
	window.setWindowIcon(icon);
    window.show();
    return app.exec();
}
