#pragma once
#include <qobject.h>
#include "Piece.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include <QDebug>

namespace Logic {
	class GameLogic : public QObject
	{
		Q_OBJECT
	public:
		GameLogic() = default;
		~GameLogic() = default;
		bool isCheck() const;
		bool isCheckMate();
		void pawnPromotion(shared_ptr<Piece> piece, const Position& move);

		vector<vector<unique_ptr<Piece>>> getBoard() const;
		static int kingCounter_;
		void initBoard(int endCase);
		void resetBoard();
		bool getTurn() const { return whiteTurn_; }
		void changeTurn() { whiteTurn_ = !whiteTurn_; }
		bool isValidMoveWhileCheck(shared_ptr<Piece> piece, const Position& move);

		vector<shared_ptr<Piece>> kills_;
		Board board_;
	public slots:
		vector<Position> getPossibleMoves(const Position& position);


	private:
		bool whiteTurn_ = false;
		
	};

}