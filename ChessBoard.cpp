#include <string>
#include <iostream>
#include <map>
#include "ChessBoard.h"
#include "ChessPieces.h"

using namespace std;

const int MAX_PIECES = 16;

ChessBoard::ChessBoard(){

  white_turn = true;
  checkmate = false;
  true_stalemate = false;
  last_move = "Z0:Z1";
  capture_string = "";
  initBoard();
}

ChessBoard::~ChessBoard(){

  freeMemory();
}

bool ChessBoard::isCheck(){

  map<string, BasePiece*>::iterator i = white_pieces.begin();
  map<string, BasePiece*>::iterator j = black_pieces.begin();

  string king_square;
  string source_square;
  
  if (white_turn != true){

    while (i != white_pieces.end()){

      if ((i->second)->returnName() == "King"){
	king_square = i->first;
      }
      i++;
    }
    
    while (j != black_pieces.end()) {

      source_square = j->first;
      if ((j->second)->isValidMove(source_square,
				  king_square,
				  white_pieces,
				  black_pieces) == true){
	return true;
      }
      j++;
    }
  } else {

    while (j != black_pieces.end()){

      if ((j->second)->returnName() == "King"){
	king_square = j->first;
      }
      j++;
    }

    while (i != white_pieces.end()) {

      source_square = i->first;
      if ((i->second)->isValidMove(source_square,
				  king_square,
				  white_pieces,
				  black_pieces) == true){
	return true;
      }
      i++;
    }
  }
  
  return false;
}

bool ChessBoard::isSelfCheck(string &source, string &destination, string &opponent_piece){

  string removed_square = "Z0";
  bool temp_check = false;

  white_turn = !white_turn;

  if (white_turn != true){
    
    auto node_handler = white_pieces.extract(source);
    node_handler.key() = destination;
    white_pieces.insert(move(node_handler));

    if (opponent_piece.length() > 0){
      auto node_handler_opp = black_pieces.extract(destination);
      node_handler_opp.key() = removed_square;
      black_pieces.insert(move(node_handler_opp));
    }

    temp_check = isCheck();

    auto node_handler2 = white_pieces.extract(destination);
    node_handler2.key() = source;
    white_pieces.insert(move(node_handler2));
    
    if (opponent_piece.length() > 0){
      auto node_handler_opp2 = black_pieces.extract(removed_square);
      node_handler_opp2.key() = destination;
      black_pieces.insert(move(node_handler_opp2));
    }

    white_turn = !white_turn;
    
    if (temp_check == true){
      return true;
    }

  } else {

    auto node_handler = black_pieces.extract(source);
    node_handler.key() = destination;
    black_pieces.insert(move(node_handler));

    if (opponent_piece.length() > 0){
      auto node_handler_opp = white_pieces.extract(destination);
      node_handler_opp.key() = removed_square;
      white_pieces.insert(move(node_handler_opp));
    }

    temp_check = isCheck();
    
    auto node_handler2 = black_pieces.extract(destination);
    node_handler2.key() = source;
    black_pieces.insert(move(node_handler2));

    if (opponent_piece.length() > 0){
      auto node_handler_opp2 = white_pieces.extract(removed_square);
      node_handler_opp2.key() = destination;
      white_pieces.insert(move(node_handler_opp2));
    }

    white_turn = !white_turn;

    if (temp_check == true){
      return true;
    }
  }

  return false;
}

bool ChessBoard::isStalemate(){

  map<string, BasePiece*>::iterator i = white_pieces.begin();
  map<string, BasePiece*>::iterator j = black_pieces.begin();

  string king_square;
  string source_square;
  string destination_square;
  bool invalid_move;
  string opponent_piece;  
  
  if (white_turn != true) {

    while (i != white_pieces.end()) {

      source_square = i->first;

      for (char file = 'A'; file < 'I'; file++){
	for (int rank = 1; rank < 9; rank++){

	  destination_square = string(1, file) + to_string(rank);

	  if (white_pieces.find(destination_square) == white_pieces.end()){
	  
	    if ((i->second)->isValidMove(source_square,
					 destination_square,
					 white_pieces,
					 black_pieces) == true){

	      white_turn = !white_turn;
	      opponent_piece = isOpponentPieceCaptured(destination_square);	
	      invalid_move = isSelfCheck(source_square, destination_square, opponent_piece);
	      white_turn = !white_turn;
	    
	      if (invalid_move == false){
		return false;
	      }
	    }
	  }
	}
      }
      
      i++;
    }
  } else {
    
    while (j != black_pieces.end()) {

      source_square = j->first;

      for (char file = 'A'; file < 'I'; file++){
	for (int rank = 1; rank < 9; rank++){

	  destination_square = string(1, file) + to_string(rank);

	  if (black_pieces.find(destination_square) == black_pieces.end()){
	  
	    if ((j->second)->isValidMove(source_square,
					 destination_square,
					 white_pieces,
					 black_pieces) == true){

	      white_turn = !white_turn;
	      opponent_piece = isOpponentPieceCaptured(destination_square);	
	      invalid_move = isSelfCheck(source_square, destination_square, opponent_piece);
	      white_turn = !white_turn;
	    
	      if (invalid_move == false){
		return false;
	      }
	    }
	  }
	}
      }
      
      j++;
    }
  }    
    
  return true;
}


void ChessBoard::submitMove(string source, string destination){

  string turn;
  string piece;
  string opponent_piece;
  string check_string;
  string checkmate_string;

  bool check;
  bool stalemate;

  capture_string = "";
  
  if (checkmate == true){
    
    cout << "The game has already ended in checkmate!\n" <<
      "Please reset the board" << endl;
    return;
    
  } else if (true_stalemate == true){

    cout << "The game has already ended in stalemate!\n" <<
      "Please reset the board" << endl;
    return;
  }
  
  if (isTurnAndPieceValid(source) == false){
    return;
  }

  if (isDestinationSquareValid(destination) == false){
    return;
  }

  opponent_piece = isOpponentPieceCaptured(destination);

  if (isSelfCheck(source, destination, opponent_piece) == true){
    cout << "Illegal move! You would place yourself in check. Try again" << endl;
    return;
  }
  
  if (white_turn == true){

    turn = "White's";
    piece = white_pieces[source]->returnName();

    if (white_pieces[source]->isValidMove(source,
					  destination,
					  white_pieces,
					  black_pieces,
					  false) == false){
      
      cout << turn << " " << piece << " cannot move to " << destination << "!" << endl;
      return;
    }
    
    auto node_handler_w = white_pieces.extract(source);
    node_handler_w.key() = destination;
    white_pieces.insert(move(node_handler_w));
    
    if (opponent_piece.length() > 0){

      delete black_pieces[destination];
      black_pieces[destination] = NULL;
      black_pieces.erase(destination);
      capture_string = " taking Black's " + opponent_piece;
    }
    
  } else {

    turn = "Black's";
    piece = black_pieces[source]->returnName();

    if (black_pieces[source]->isValidMove(source,
					  destination,
					  white_pieces,
					  black_pieces,
					  false) == false){
      
      cout << turn << " " << piece << " cannot move to " << destination << "!" << endl;
      return;
    }

    
    auto node_handler_b = black_pieces.extract(source);
    node_handler_b.key() = destination;
    black_pieces.insert(move(node_handler_b));

    if (opponent_piece.length() > 0){
      
      delete white_pieces[destination];
      white_pieces[destination] = NULL;
      white_pieces.erase(destination);
      capture_string = " taking White's " + opponent_piece;
    }
  }   

  
  cout << turn << " " << piece << " moves from " << source << " to " <<
    destination << capture_string << endl;

  check = isCheck();
  stalemate = isStalemate();

  if (check == false && stalemate == true){

    true_stalemate = true;

  } else if (check == true && stalemate == true){

    checkmate = true;
    
  }
    
  if (check == true && checkmate == false){

    if (white_turn == true){
      cout << "Black is in check" << endl;
    } else {
      cout << "White is in check" << endl;
    }
    
  } else if (checkmate == true){

    if (white_turn == true){
      cout << "Black is in checkmate" << endl;
    } else {
      cout << "White is in checkmate" << endl;
    }
        
  } else if (true_stalemate == true){

    cout << "Stalemate! It's a draw!" << endl;
  }
  
  last_move = source + ":" + destination;
  capture_string = "";
  white_turn = !white_turn;
}

void ChessBoard::resetBoard(){

  freeMemory();

  white_pieces.clear();
  black_pieces.clear();

  initBoard();

  white_turn = true;
  checkmate = false;
  true_stalemate = false;
}

void ChessBoard::initBoard(){

  for (int i = 0; i < MAX_PIECES; i++) {

    char file;
    string rank_white;
    string rank_black;
    string square_white;
    string square_black;

    BasePiece* K_w = new King(this);
    BasePiece* Q_w = new Queen;
    BasePiece* R_w = new Rook;
    BasePiece* N_w = new Knight;
    BasePiece* B_w = new Bishop;
    BasePiece* P_w = new Pawn(this);
    BasePiece* K_b = new King(this);
    BasePiece* Q_b = new Queen;
    BasePiece* R_b = new Rook;
    BasePiece* N_b = new Knight;
    BasePiece* B_b = new Bishop;
    BasePiece* P_b = new Pawn(this);
    
    if (i < 8){

      file = 'A' + i;
      rank_white = to_string(1);
      rank_black = to_string(8);
      square_white = string(1, file) + rank_white;
      square_black = string(1, file) + rank_black;

      if (i==0 || i==7) {

	white_pieces.insert(make_pair(square_white, R_w));
	black_pieces.insert(make_pair(square_black, R_b));	

      } else if (i==1 || i==6) {

	white_pieces.insert(make_pair(square_white, N_w));
	black_pieces.insert(make_pair(square_black, N_b));

      } else if (i==2 || i==5) {
	
	white_pieces.insert(make_pair(square_white, B_w));	
	black_pieces.insert(make_pair(square_black, B_b));

      } else if (i==3) {

	white_pieces.insert(make_pair(square_white, Q_w));
	black_pieces.insert(make_pair(square_black, Q_b));

      } else if (i==4) {

	white_pieces.insert(make_pair(square_white, K_w));
	black_pieces.insert(make_pair(square_black, K_b));
      }

    } else if (i > 7){

      file = 'A' + i - 8;
      rank_white = to_string(2);
      rank_black = to_string(7);
      square_white = string(1, file) + rank_white;
      square_black = string(1, file) + rank_black;

      white_pieces.insert(make_pair(square_white, P_w));
      black_pieces.insert(make_pair(square_black, P_b));

    }
  }

  cout << "A new chess game is started!" << endl;
}

bool ChessBoard::isTurnAndPieceValid(string &source){

  bool white_move_attempt = false;
  bool black_move_attempt = false;
  
  if(white_pieces.find(source) != white_pieces.end()){
    white_move_attempt = true;
  }

  if(black_pieces.find(source) != black_pieces.end()){
    black_move_attempt = true;
  }

  if (white_turn != white_move_attempt){
    if (white_turn == true && black_move_attempt == false){
      cout << "There is no piece at position " << source << "!" << endl;
      return false;
    } else if (white_turn == true && black_move_attempt == true){
      cout << "It is not Black's turn to move!" << endl;
      return false;
    } else if (white_move_attempt == true){
      cout << "It is not White's turn to move!" << endl;
      return false;
    }
  } else if (white_turn == false && white_move_attempt == false &&
	     black_move_attempt == false){
      cout << "There is no piece at position " << source << "!" << endl;
      return false;
  }

  return true;
}

bool ChessBoard::isDestinationSquareValid(string &destination){

  if (white_turn == true){
    if(white_pieces.find(destination) != white_pieces.end()){
      cout << "There is already one of your pieces at " << destination
	   << "!" << endl;
      return false;
    }
  } else {
    if(black_pieces.find(destination) != black_pieces.end()){
      cout << "There is already one of your pieces at " << destination
	   << "!" << endl;
      return false;
    }
  }

  return true;
}

string ChessBoard::isOpponentPieceCaptured(string &destination){

  if (white_turn == true){
    if(black_pieces.find(destination) != black_pieces.end()){
      return black_pieces[destination]->returnName();
    }
  } else {
    if(white_pieces.find(destination) != white_pieces.end()){
      return white_pieces[destination]->returnName();
    }
  }

  return "";
}

void ChessBoard::freeMemory(){

  map<string, BasePiece*>::iterator i = white_pieces.begin();

  while(i != white_pieces.end()){

    if (i->second != NULL){
      delete i->second;
      i->second = NULL;
    }
    
    i++;
  }

  map<string, BasePiece*>::iterator j = black_pieces.begin();

  while(j != black_pieces.end()){

    if (j->second != NULL){
      delete j->second;
      j->second = NULL;
    }
    
    j++;
  }
}

string ChessBoard::getLastMove(){
  return last_move;
}
