#include "GameLogic.hpp"




void Logic::GameLogic::initBoard(int endCase) {
	switch (endCase) {
		case 0 :
		{
			auto king1 = make_shared<King>(Position(0, 4), Piece::Color::WHITE);
			board_.addPiece(king1);
			auto queen1 = make_shared<Queen>(Position(0, 3), Piece::Color::WHITE);
			board_.addPiece(queen1);
			auto rook1 = make_shared<Rook>(Position(0, 0), Piece::Color::WHITE);
			board_.addPiece(rook1);
			auto rook2 = make_shared<Rook>(Position(0, 7), Piece::Color::WHITE);
			board_.addPiece(rook2);
			auto bishop1 = make_shared<Bishop>(Position(0, 2), Piece::Color::WHITE);
			board_.addPiece(bishop1);
			auto bishop2 = make_shared<Bishop>(Position(0, 5), Piece::Color::WHITE);
			board_.addPiece(bishop2);
			auto knight1 = make_shared<Knight>(Position(0, 1), Piece::Color::WHITE);
			board_.addPiece(knight1);
			auto knight2 = make_shared<Knight>(Position(0, 6), Piece::Color::WHITE);
			board_.addPiece(knight2);
			auto king2 = make_shared<King>(Position(7, 4), Piece::Color::BLACK);
			board_.addPiece(king2);
			auto queen2 = make_shared<Queen>(Position(7, 3), Piece::Color::BLACK);
			board_.addPiece(queen2);
			auto rook3 = make_shared<Rook>(Position(7, 0), Piece::Color::BLACK);
			board_.addPiece(rook3);
			auto rook4 = make_shared<Rook>(Position(7, 7), Piece::Color::BLACK);
			board_.addPiece(rook4);
			auto bishop3 = make_shared<Bishop>(Position(7, 2), Piece::Color::BLACK);
			board_.addPiece(bishop3);
			auto bishop4 = make_shared<Bishop>(Position(7, 5), Piece::Color::BLACK);
			board_.addPiece(bishop4);
			auto knight3 = make_shared<Knight>(Position(7, 1), Piece::Color::BLACK);
			board_.addPiece(knight3);
			auto knight4 = make_shared<Knight>(Position(7, 6), Piece::Color::BLACK);
			board_.addPiece(knight4);
			for (int i = 0; i < 8; i++) {
				auto pawn1 = make_shared<Pawn>(Position(1, i), Piece::Color::WHITE);
				board_.addPiece(pawn1);
				auto pawn2 = make_shared<Pawn>(Position(6, i), Piece::Color::BLACK);
				board_.addPiece(pawn2);
			}
			break;
		}
		case 1 :
		{ //Queen vs Rook, philidor position
			auto king1 = make_shared<King>(Position(2, 2), Piece::Color::WHITE);
			board_.addPiece(king1);
			auto queen = make_shared<Queen>(Position(3, 0), Piece::Color::WHITE);
			board_.addPiece(queen);
			auto king2 = make_shared<King>(Position(0, 1), Piece::Color::BLACK);
			board_.addPiece(king2);
			auto rook = make_shared<Rook>(Position(1, 1), Piece::Color::BLACK);
			board_.addPiece(rook);
			break;
		}
		case 2 : 
		{//Queen vs Bishop and knight
			auto king1 = make_shared<King>(Position(0, 0), Piece::Color::WHITE);
			board_.addPiece(king1);
			auto queen = make_shared<Queen>(Position(6, 5), Piece::Color::WHITE);
			board_.addPiece(queen);
			auto king2 = make_shared<King>(Position(3, 1), Piece::Color::BLACK);
			board_.addPiece(king2);
			auto bishop = make_shared<Bishop>(Position(2, 0), Piece::Color::BLACK);
			board_.addPiece(bishop);
			auto knight = make_shared<Knight>(Position(2, 2), Piece::Color::BLACK);
			board_.addPiece(knight);
			break;
		}
		case 3 : 
		{//rook vs knight
			auto king1 = make_shared<King>(Position(0, 0), Piece::Color::WHITE);
			board_.addPiece(king1);
			auto rook = make_shared<Rook>(Position(2, 1), Piece::Color::WHITE);
			board_.addPiece(rook);
			auto king2 = make_shared<King>(Position(7, 7), Piece::Color::BLACK);
			board_.addPiece(king2);
			auto knight = make_shared<Knight>(Position(3, 6), Piece::Color::BLACK);
			board_.addPiece(knight);
			break;
		}
		case 4 : 
		{	//rook and bishop vs rook
			auto king1 = make_shared<King>(Position(0, 0), Piece::Color::WHITE);
			board_.addPiece(king1);
			auto rook = make_shared<Rook>(Position(0, 1), Piece::Color::WHITE);
			board_.addPiece(rook);
			auto king2 = make_shared<King>(Position(7, 7), Piece::Color::BLACK);
			board_.addPiece(king2);
			auto bishop = make_shared<Bishop>(Position(5, 2), Piece::Color::BLACK);
			board_.addPiece(bishop);
			auto rook2 = make_shared<Rook>(Position(6, 7), Piece::Color::BLACK);
			board_.addPiece(rook2);
			break;
		}
		case 5 : 
		{//rook and knight vs rook
			auto king1 = make_shared<King>(Position(0, 0), Piece::Color::WHITE);
			board_.addPiece(king1);
			auto rook1 = make_shared<Rook>(Position(0, 1), Piece::Color::WHITE);
			board_.addPiece(rook1);
			auto king2 = make_shared<King>(Position(7, 7), Piece::Color::BLACK);
			board_.addPiece(king2);
			auto knight = make_shared<Knight>(Position(7, 6), Piece::Color::BLACK);
			board_.addPiece(knight);
			auto rook2 = make_shared<Rook>(Position(6, 7), Piece::Color::BLACK);
			board_.addPiece(rook2);
			break;
		}
	}
}

vector<Position> Logic::GameLogic::getPossibleMoves(const Position& position) {
	vector<Position> possibleMoves;
	auto piece = board_.getPieceAt(position);
	if (piece == nullptr) {
		return possibleMoves;
	}
	possibleMoves = piece->getPossibleMoves(board_);
	return possibleMoves;
}

void Logic::GameLogic::resetBoard() {
	board_.reset();
}

bool Logic::GameLogic::isCheck() const {
	vector<shared_ptr<Piece>> oppositePieces; 
	if (whiteTurn_)
		oppositePieces = board_.getPieceByColor(Piece::Color::BLACK);
	else
		oppositePieces = board_.getPieceByColor(Piece::Color::WHITE);

	if (oppositePieces.empty())
		return false;
	vector<Position> possibleMoves;
	vector<Position> pawnMoves;
	Position kingsPosition = board_.getKingPosition(whiteTurn_ ? Piece::Color::WHITE : Piece::Color::BLACK);
	for (auto&& piece : oppositePieces) {
		//if (piece->getType() == Piece::Type::PAWN) {
			/*possibleMoves = piece->getPossibleMoves(board_);
			for (auto&& move : possibleMoves) {
				if (move.y_ != piece->getPosition().y_) {
					pawnMoves.push_back(move);
					qDebug() << " King cant move to " << move.x_ << " " << move.y_;
					auto it = find(pawnMoves.begin(), pawnMoves.end(), kingsPosition);
					if (it != pawnMoves.end())
						return true;
				}
				else {
					qDebug() << " King can move to " << move.x_ << " " << move.y_;
					continue;
					
				}
			}*/
			/*continue;
		}
		else {*/
			possibleMoves = piece->getPossibleMoves(board_);
			auto it = find(possibleMoves.begin(), possibleMoves.end(), kingsPosition);
			if (it != possibleMoves.end())
				return true;

		//}
	}
	return false;
}

bool Logic::GameLogic::isValidMoveWhileCheck(shared_ptr<Piece> piece, const Position& move) {
	Position oldPosition = piece->getPosition();
	bool returnValue = piece.get()->isValidMove(move, board_);
	if (!returnValue)
		return false;
	shared_ptr<Piece> oldPiece = board_.getPieceAt(move);
	Position oldPositionOldPiece = oldPiece != nullptr ? oldPiece->getPosition() : Position(-1, -1);
	Piece::Color oldPieceColor = oldPiece != nullptr ? oldPiece->getColor() : Piece::Color::WHITE;
	Piece::Type oldPieceType = oldPiece != nullptr ? oldPiece->getType() : Piece::Type::PAWN;
	board_.movePieceTo(piece, move);
	returnValue &= !isCheck();
	board_.movePieceTo(piece, oldPosition);
	if (oldPiece != nullptr) {
		switch (oldPieceType) {
			case Piece::Type::BISHOP:
			{
				shared_ptr<Piece> newOldPiece = make_shared<Bishop>(oldPositionOldPiece, oldPieceColor);
				board_.addPiece(newOldPiece);
				break;
			}
			case Piece::Type::KING:
			{
				shared_ptr<Piece> newOldPiece = make_shared<King>(oldPositionOldPiece, oldPieceColor);
				board_.addPiece(newOldPiece);
				break;
			}
			case Piece::Type::KNIGHT:
			{
				shared_ptr<Piece> newOldPiece = make_shared<Knight>(oldPositionOldPiece, oldPieceColor);
				board_.addPiece(newOldPiece);
				break;
			}
			case Piece::Type::PAWN:
			{
				shared_ptr<Piece> newOldPiece = make_shared<Pawn>(oldPositionOldPiece, oldPieceColor);
				board_.addPiece(oldPiece);
				break;
			}
			case Piece::Type::QUEEN:
			{
				shared_ptr<Piece> newOldPiece = make_shared<Queen>(oldPositionOldPiece, oldPieceColor);
				board_.addPiece(newOldPiece);
				break;
			}
			case Piece::Type::ROOK:
			{
				shared_ptr<Piece> newOldPiece = make_shared<Rook>(oldPositionOldPiece, oldPieceColor);
				board_.addPiece(newOldPiece);
				break;
			}

		}
	}
	return returnValue;
}

void Logic::GameLogic::pawnPromotion(shared_ptr<Piece> piece, const Position& move) {
	shared_ptr<Piece> newPiece;
	if (move.x_ == 0 || move.x_ == 7) {
		if (piece->getType() == Piece::Type::PAWN) {
			if (piece->getColor() == Piece::Color::WHITE)
				newPiece = make_shared<Queen>(move, Piece::Color::WHITE);
		
			else if (piece->getColor() == Piece::Color::BLACK)
				newPiece = make_shared<Queen>(move, Piece::Color::BLACK);
			board_.removePiece(piece);
			board_.addPiece(newPiece);
		}
	}
}

bool Logic::GameLogic::isCheckMate() {
	vector<shared_ptr<Piece>> pieces;
	if (whiteTurn_)
		pieces = board_.getPieceByColor(Piece::Color::WHITE);
	else
		pieces = board_.getPieceByColor(Piece::Color::BLACK);
	for (auto&& piece : pieces) {
		vector<Position> possibleMoves = piece->getPossibleMoves(board_);
		for (auto&& move : possibleMoves) {
			if (isValidMoveWhileCheck(piece, move))
				return false;
		}
	}
	return true;
}