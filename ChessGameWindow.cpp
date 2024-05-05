#include "ChessGameWindow.h"
#include <qbrush.h>
#include <qtablewidget.h>
#include <cppitertools/range.hpp>
#include <qobject.h>
#include <qdebug.h>
#include <qtablewidget.h>
#include <qpixmap.h>
#include <qpalette.h>
#include <iostream>
using namespace iter;

Interface::ChessGameWindow::ChessGameWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initUI();
    gameLogic.initBoard(gameCase);
    updatePiecesUI(gameLogic.board_);
    Position previousPos = Position(0, 0);
    QObject::connect(ui.restartBtn, &QPushButton::clicked, [&]() {
        resetUI();
        ui.restartBtn->setVisible(false);
        });
    QObject::connect(ui.resetBtn, &QPushButton::clicked, [&]() {
        resetUI();
        ui.resetBtn->setVisible(false);
        });
    QObject::connect(ui.startBtn, &QPushButton::clicked, [&]() { setGameStarted(); });
    QObject::connect(ui.caseCBox, &QComboBox::currentIndexChanged, [&](const int& endCase) {
        gameLogic.resetBoard();
        gameLogic.initBoard(endCase);
        updatePiecesUI(gameLogic.board_);
        isPieceSelected = false;
        gameCase = endCase;
        });
    QObject::connect(ui.chessTable, &QTableWidget::cellClicked, [&](int row, int col) {
        Position pos = Position(row, col);
        if (isPieceSelected) {
            shared_ptr<Piece> piece = gameLogic.board_.getPieceAt(previousPos);
            verif = gameLogic.isValidMoveWhileCheck(piece, pos);
            if (verif) {
                if (gameLogic.board_.getPieceAt(pos) != nullptr) {
                    shared_ptr<Piece> oldPiece = gameLogic.board_.getPieceAt(pos);
                    gameLogic.kills_.push_back(oldPiece);
                    addPieceToKills();
                }

                gameLogic.board_.movePieceTo(piece, pos);
                gameLogic.pawnPromotion(piece, pos);
                updatePiecesUI(gameLogic.board_);
                isPieceSelected = false;
                updateBoardColor();
                gameLogic.changeTurn();
            }
            else {
                isPieceSelected = false;
                updateBoardColor();
            }
            if (gameLogic.isCheck()) {
                updateCheckUI();
                if (gameLogic.isCheckMate()) {
                    updateCheckMateUI();
                    return;
				}
            }
            updateTurnLabel();
        }
        else {
            if (gameLogic.getTurn() && gameLogic.board_.getPieceAt(pos) != nullptr && gameLogic.board_.getPieceAt(pos).get()->getColor() == Piece::Color::WHITE)
            {
                vector<Position> moves = gameLogic.getPossibleMoves(pos);
                shared_ptr<Piece> piece2 = gameLogic.board_.getPieceAt(pos);
                vector<Position> validMoves;
                copy_if(moves.begin(), moves.end(), back_inserter(validMoves), [&](Position pos) {
                    if (piece2 != nullptr)
                        return gameLogic.isValidMoveWhileCheck(piece2, pos);
                    return false;
                    });
                isPieceSelected = updateMovesUI(validMoves);
                previousPos = pos;
            }
            else if (!gameLogic.getTurn() && gameLogic.board_.getPieceAt(pos) != nullptr && gameLogic.board_.getPieceAt(pos).get()->getColor() == Piece::Color::BLACK)
            {
                vector<Position> moves = gameLogic.getPossibleMoves(pos);
                shared_ptr<Piece> piece2 = gameLogic.board_.getPieceAt(pos);
                vector<Position> validMoves;
                copy_if(moves.begin(), moves.end(), back_inserter(validMoves), [&](Position pos) {
                    if (piece2 != nullptr)
                        return gameLogic.isValidMoveWhileCheck(piece2, pos);
                    return false;
                    });
                isPieceSelected = updateMovesUI(validMoves);
                previousPos = pos;
            }
        }
        });
}
void Interface::ChessGameWindow::updatePiecesUI(const Board& board) {
    vector<shared_ptr<Piece>> whitePieces = board.getPieceByColor(Piece::Color::WHITE);
    vector<shared_ptr<Piece>> blackPieces = board.getPieceByColor(Piece::Color::BLACK);
    for (int i : range(8))
    {
        for (int j : range(8))
        {
            QTableWidgetItem* item = ui.chessTable->item(i, j);
            item->setData(Qt::DecorationRole, QVariant());
        }
    }
    for (int i = 0; i < whitePieces.size(); i++) {
		Position pos = whitePieces[i].get()->getPosition();
        QPixmap pixmap = QPixmap(QString::fromStdString("assets\\White\\" + whitePieces[i].get()->getName() + ".png"));
		QTableWidgetItem* item = ui.chessTable->item(pos.getPosition().first, pos.getPosition().second);
        item->setData(Qt::DecorationRole, pixmap.scaled(75, 75));
	}

    for (int i = 0; i < blackPieces.size(); i++) {
		Position pos = blackPieces[i].get()->getPosition();
        QPixmap pixmap = QPixmap(QString::fromStdString("assets\\Black\\" + blackPieces[i].get()->getName() + ".png"));
        QTableWidgetItem* item = ui.chessTable->item(pos.getPosition().first, pos.getPosition().second);
        item->setData(Qt::DecorationRole, pixmap.scaled(75, 75));
    }

}

bool Interface::ChessGameWindow::updateMovesUI(const vector<Position>& moves) {
    if (moves.empty()) 
        return false;
    for (auto&& move : moves) {
		Position pos = move;
        
		QTableWidgetItem* item = ui.chessTable->item(pos.getPosition().first, pos.getPosition().second);
		item->setBackground(QBrush(QColor(176, 167, 253, 255)));
	}
	return true;
}

void Interface::ChessGameWindow::updateBoardColor() {
    for (int i : range(8))
    {
        for (int j : range(8))
        {
            QBrush brush = ((i + j)) % 2 == 0 ? QBrush(QColor(183, 192, 216, 255)) : QBrush(QColor(232, 237, 249, 255));
            QTableWidgetItem* item = ui.chessTable->item(i,j);
            item->setBackground(brush);
        }
    }
}

void Interface::ChessGameWindow::setGameStarted() {
	ui.chessTable->setEnabled(true);
    ui.startBtn->setVisible(false);
    ui.resetBtn->setVisible(true);
    ui.resetBtn->setEnabled(true);
    ui.startBtn->setEnabled(false);
    ui.caseCBox->setEnabled(false);
    ui.caseCBox->setVisible(false);
    ui.turnLabel->setVisible(true);
    ui.blackDeath->setVisible(true);
    ui.whiteDeath->setVisible(true);
}

void Interface::ChessGameWindow::addPieceToKills() {
  
    for (auto& kill : gameLogic.kills_) {
        if (kill == nullptr || kill.get()->getName() == "King")
			continue;
        else if (kill.get()->getColor() == Piece::Color::WHITE) {
			QPixmap pixmap = QPixmap(QString::fromStdString("assets\\White\\" + kill.get()->getName() + ".png"));
			QTableWidgetItem* item = ui.whiteDeath->item(killsPosition_[kill.get()->getName()], 0);
            item->setData(Qt::DecorationRole, pixmap.scaled(75, 75));
		}
        else {
			QPixmap pixmap = QPixmap(QString::fromStdString("assets\\Black\\" + kill.get()->getName() + ".png"));
            QTableWidgetItem* item2 = ui.blackDeath->item(killsPosition_[kill.get()->getName()], 0); 
            item2->setData(Qt::DecorationRole, pixmap.scaled(75, 75));
		}
        
	}
	
}

void Interface::ChessGameWindow::updateTurnLabel() {
	if (gameLogic.getTurn())
		ui.turnLabel->setText("White's turn");
	else
		ui.turnLabel->setText("Black's turn");
}

void Interface::ChessGameWindow::updateCheckUI() {
    Position kingPos = gameLogic.board_.getKingPosition(gameLogic.getTurn() ? Piece::Color::WHITE : Piece::Color::BLACK);
    QTableWidgetItem* item = ui.chessTable->item(kingPos.getPosition().first, kingPos.getPosition().second);
    item->setBackground(QBrush(QColor(244, 253, 167, 255)));
}

void Interface::ChessGameWindow::updateCheckMateUI() {
    Position kingPos = gameLogic.board_.getKingPosition(gameLogic.getTurn() ? Piece::Color::WHITE : Piece::Color::BLACK);
    QTableWidgetItem* item = ui.chessTable->item(kingPos.getPosition().first, kingPos.getPosition().second);
    item->setBackground(QBrush(QColor(255, 77, 102, 255)));
    if (gameLogic.getTurn())
        ui.winLabel->setText("Black wins");
    else
        ui.winLabel->setText("White wins");
    ui.winLabel->setVisible(true);
    ui.chessTable->setEnabled(false);
    updatePiecesUI(gameLogic.board_);
    ui.restartBtn->setVisible(true);
    ui.resetBtn->setVisible(false);
    ui.resetBtn->setEnabled(false);

}

void Interface::ChessGameWindow::resetUI() {
    ui.chessTable->setEnabled(false);
	ui.startBtn->setVisible(true);
	ui.startBtn->setEnabled(true);
	ui.caseCBox->setEnabled(true);
	ui.caseCBox->setVisible(true);
	ui.turnLabel->setVisible(false);
	ui.blackDeath->setVisible(false);
	ui.whiteDeath->setVisible(false);
	ui.winLabel->setVisible(false);
	gameLogic.kills_.clear();
	gameLogic.board_.reset();
	gameLogic.initBoard(gameCase);
    ui.chessTable->clearSelection();
    if (gameLogic.getTurn())
        gameLogic.changeTurn();
	updateBoardColor();
	updatePiecesUI(gameLogic.board_);
    for (int i : range(5)) {
        QTableWidgetItem* item = ui.whiteDeath->item(i, 0);
        item->setData(Qt::DecorationRole, QVariant());
        QTableWidgetItem* item2 = ui.blackDeath->item(i, 0);
        item2->setData(Qt::DecorationRole, QVariant());
    }
}
void Interface::ChessGameWindow::initUI() {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(183, 192, 216));
    this->setPalette(pal);
    for (int i : range(8))
    {
        for (int j : range(8))
        {
            QBrush brush = ((i + j)) % 2 == 0 ? QBrush(QColor(183, 192, 216, 255)) : QBrush(QColor(232, 237, 249, 255));
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setBackground(brush);
            ui.chessTable->setItem(i, j, item);
            if (j == 0) {
                QTableWidgetItem* item2 = new QTableWidgetItem();
                item2->setBackground(QBrush(QColor(183, 192, 216, 255)));
                ui.whiteDeath->setItem(i, j, item2);
                QTableWidgetItem* item3 = new QTableWidgetItem();
                item3->setBackground(QBrush(QColor(183, 192, 216, 255)));
                ui.blackDeath->setItem(i, j, item3);
            }
        }
    }
    ui.chessTable->setStyleSheet("QTableView::item:selected { background-color: rgb(176, 167, 253); }");
    QString startButtonStyle = "QPushButton#startBtn {"
        "    background-color: #a9b4d1;"
        "    border: 2px solid #8897BF;"
        "    color: #ffffff;"
        "    font-size: 28px;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "}"
        "QPushButton#startBtn:hover {"
        "    background-color: #8c9ac1;"
        "}"
        "QPushButton#startBtn:pressed {"
        "    background-color: #7384b3;"
        "    border-color: #55699D;"
        "}";
    QString restartButtonStyle = "QPushButton#restartBtn {"
        "    background-color: #a9b4d1;"
        "    border: 2px solid #8897BF;"
        "    color: #ffffff;"
        "    font-size: 28px;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "}"
        "QPushButton#restartBtn:hover {"
        "    background-color: #8c9ac1;"
        "}"
        "QPushButton#restartBtn:pressed {"
        "    background-color: #7384b3;"
        "    border-color: #55699D;"
        "}";
    QString resetButtonStyle = "QPushButton#resetBtn {"
        "    background-color: #a9b4d1;"
        "    border: 2px solid #8897BF;"
        "    color: #ffffff;"
        "    font-size: 28px;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "}"
        "QPushButton#resetBtn:hover {"
        "    background-color: #8c9ac1;"
        "}"
        "QPushButton#resetBtn:pressed {"
        "    background-color: #7384b3;"
        "    border-color: #55699D;"
        "}";
    QString comboBoxStyle =
        "QComboBox#caseCBox {"
        "    background-color: #a9b4d1;"
        "    border: 2px solid #8897BF;"
        "    color: #ffffff;"
        "    font-size: 20px;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "}"
        "QComboBox#caseCBox QAbstractItemView {"
        "    background-color: #a9b4d1;"
        "    color: #ffffff;"
        "    selection-background-color: #7384b3;"
        "}"
        "QComboBox#caseCBox QAbstractItemView::item {"
        "    min-height: 40px;"
        "}"
        "QComboBox#caseCBox QAbstractItemView::item:selected {"
        "    font-size: 28px;"
        "}";
    ui.caseCBox->setStyleSheet(comboBoxStyle);
    ui.caseCBox->update();
    ui.resetBtn->setStyleSheet(resetButtonStyle);
    ui.resetBtn->update();
    ui.startBtn->setStyleSheet(startButtonStyle);
    ui.startBtn->update();
    ui.restartBtn->setStyleSheet(restartButtonStyle);
    ui.restartBtn->update();
    ui.restartBtn->setVisible(false);
    ui.resetBtn->setVisible(false);
    ui.resetBtn->setEnabled(false);
    ui.winLabel->setVisible(false);
    ui.turnLabel->setVisible(false);
    ui.blackDeath->setVisible(false);
    ui.whiteDeath->setVisible(false);
    
}

Interface::ChessGameWindow::~ChessGameWindow()
{
    for (int i : iter::range(8)) {
        for (int j : iter::range(8)) {
            QTableWidgetItem* item = ui.chessTable->item(i, j);
            delete item; 
        }
    }


    for (int i : iter::range(5)) { 
        QTableWidgetItem* item = ui.whiteDeath->item(i, 0);
        delete item; 
    }


    for (int i : iter::range(5)) { 
        QTableWidgetItem* item = ui.blackDeath->item(i, 0);
        delete item; 
    }
}
