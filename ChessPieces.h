#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <map>
#include "ChessBoard.h"

// BasePiece created as an abstract class from which all other chess pieces
// derive. Each derived class is responsible for determining which rules
// are valid for itself through 'isValidMove'. Each piece also returns the
// name of the piece through 'returnName'
class BasePiece {
 private:

  // keeps count of executed moves
  int move_counter;
  
 public:

  // constructor
  BasePiece();

  // destructor
  virtual ~BasePiece();

  // determines whether supplied move is valid or not and returns boolean
  virtual bool isValidMove(std::string &source,
			   std::string &destination,
			   std::map<std::string, BasePiece*> &white_pieces,
			   std::map<std::string, BasePiece*> &black_pieces,
			   const bool test = true)
    = 0;

  // returns move count
  int getMoveCount();

  // increments move count after a move has been executed
  void incrementMoveCount();

  // returns the name of the piece
  virtual std::string returnName() = 0;

  // returns the horizontal distance in number of squares between the source
  // and the destination
  int getHorizontalDistance(std::string &source, std::string &destination);

  // returns the vertical distance in number of squares between the source
  // and the destination
  int getVerticalDistance(std::string &source, std::string &destination);
};

/////////////////////////////////////////////////////////////////////////

// King piece takes a ChessBoard object as an argument to the constructor
// purely for castling implementation

class King: public BasePiece {
 private:

  ChessBoard* cb;

 public:

  King(ChessBoard* cb);

  ~King();
  
  bool isValidMove(std::string &source,
		   std::string &destination,
		   std::map<std::string, BasePiece*> &white_pieces,
		   std::map<std::string, BasePiece*> &black_pieces,
		   const bool test = true) override;

  std::string returnName();
};

////////////////////////////////////////////////////////////////////////

class Queen: public BasePiece {
 public:

  Queen();

  ~Queen();
  
  bool isValidMove(std::string &source,
		   std::string &destination,
		   std::map<std::string, BasePiece*> &white_pieces,
		   std::map<std::string, BasePiece*> &black_pieces,
		   const bool test = true) override;

  std::string returnName();
};

///////////////////////////////////////////////////////////////////////

class Rook: public BasePiece {  
 public:
  
  Rook();

  ~Rook();

  bool isValidMove(std::string &source,
		   std::string &destination,
		   std::map<std::string, BasePiece*> &white_pieces,
		   std::map<std::string, BasePiece*> &black_pieces,
		   const bool test = true) override;

  std::string returnName();
};

//////////////////////////////////////////////////////////////////////

class Knight: public BasePiece {
 public:

  Knight();

  ~Knight();
  
  bool isValidMove(std::string &source,
		   std::string &destination,
		   std::map<std::string, BasePiece*> &white_pieces,
		   std::map<std::string, BasePiece*> &black_pieces,
		   const bool test = true) override;

  std::string returnName();
};

//////////////////////////////////////////////////////////////////////

class Bishop: public BasePiece {
 public:

  Bishop();

  ~Bishop();
  
  bool isValidMove(std::string &source,
		   std::string &destination,
		   std::map<std::string, BasePiece*> &white_pieces,
		   std::map<std::string, BasePiece*> &black_pieces,
		   const bool test = true) override;

  std::string returnName();
};

//////////////////////////////////////////////////////////////////////

// Pawn piece takes a ChessBoard object as an argument to the constructor
// purely for en passant implementation

class Pawn: public BasePiece {
 private:

  ChessBoard* cb;
      
 public:

  Pawn(ChessBoard* cb);

  ~Pawn();
  
  bool isValidMove(std::string &source,
		   std::string &destination,
		   std::map<std::string, BasePiece*> &white_pieces,
		   std::map<std::string, BasePiece*> &black_pieces,
		   const bool test = true) override;

  std::string returnName();
};

#endif
