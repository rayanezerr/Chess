#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ChessGameWindow.h"
#include "Position.hpp"
#include "GameLogic.hpp"
#include <unordered_map>

namespace Interface {
    class ChessGameWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        ChessGameWindow(QWidget* parent = nullptr);
        void updatePiecesUI(const Board& board);
        bool updateMovesUI(const vector<Position>& moves);
        void updateBoardColor();
        void updateCheckMateUI();
        void resetUI();

        void setGameStarted();
        void addPieceToKills();
        void updateTurnLabel();
        void updateCheckUI();
        void initUI();

        ~ChessGameWindow();


    private:
        Position pos = Position(0, 0);
        Ui::ChessGameWindowClass ui;
        Logic::GameLogic gameLogic;
        bool isPieceSelected = false;
        bool verif = false;
        int gameCase = 0;
        unordered_map<string, int> killsPosition_ = {
            {"Rook", 0},{"Bishop", 1},{"Knight", 2},{"Queen", 3}, {"Pawn", 4}
        };

    };
}