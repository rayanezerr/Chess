//#ifndef RAIIMOVE_HPP
//#define RAIIMOVE_HPP
//
//#include "Piece.hpp"
//
//
//class RAIIMove {
//    Piece& piece;  
//    Position originalPos; 
//
//public:
//    RAIIMove(Piece& p, Position newPos)
//        : piece(p), originalPos(p.getPosition()) {
//        piece.moveTo(newPos);
//    }
//
//    ~RAIIMove() {
//        piece.resetTo(originalPos);
//    }
//};
//
//#endif 