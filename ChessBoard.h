#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>

// forward definition of BasePiece
class BasePiece;

class ChessBoard {

 private:

  bool white_turn;
  bool checkmate;
  bool true_stalemate;
  std::string last_move;
  std::string capture_string;
  
  std::map<std::string, BasePiece*> white_pieces;
  std::map<std::string, BasePiece*> black_pieces;

  // initialises the board when the object is first created putting the correct
  // pieces on the board in the correct places
  void initBoard();

  // after a move has been made, check if said move has placed opponent into check
  bool isCheck();
  
  // before a move is made, check if proposed move would place the player
  // themselves into check. If so, the move is not allowed
  bool isSelfCheck(std::string &source,
		   std::string &destination,
		   std::string &opponent_piece);

  // after a move has been made, check if said move has created a stalemate situation
  // for the opponent, in which case the game finishes as a draw
  bool isStalemate();

  // check if the proposed move is coming from the right person whose turn it is
  // and that they are using one of their own pieces
  bool isTurnAndPieceValid(std::string &source);

  // check if the destination square is a valid square on the chess board either
  // unoccupied or occupied by an enemy piece
  bool isDestinationSquareValid(std::string &destination);

  // return the name of the opponent piece that the player is capturing (if any)
  std::string isOpponentPieceCaptured(std::string &destination);

  // free all the memory off the heap that is held within the 'map' data structures
  // i.e. any remaining chess pieces on the board
  void freeMemory();

  // stores the last move completed on the board purely for en passant implementation
  // this is because en passant capture is only valid on the very next turn otherwise
  // the right to do so is lost
  std::string getLastMove();

  // makes King class a friend for castling implementation
  friend class King;

  // makes Pawn class a friend for en passant implementation
  friend class Pawn;
  
 public:

  // constructor
  ChessBoard();

  // destructor
  ~ChessBoard();

  // allows anyone interacting with the chessboard class to make a move
  // by supplying a source square and a destination square
  void submitMove(std::string source, std::string destination);

  // resets the board in order to start a new game
  void resetBoard();

};

#endif
