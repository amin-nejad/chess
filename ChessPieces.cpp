#include <iostream>
#include <string>
#include "ChessPieces.h"
#include "ChessBoard.h"

using namespace std;

BasePiece::BasePiece(){
  move_counter = 0;
}

BasePiece::~BasePiece(){
}

int BasePiece::getMoveCount() {
  return move_counter;
}

void BasePiece::incrementMoveCount() {
  move_counter++;
}

int BasePiece::getHorizontalDistance(string &source, string &destination){

  char source_file = source[0];
  char destination_file = destination[0];
  int file_distance = destination_file - source_file;
  return file_distance;
}

int BasePiece::getVerticalDistance(string &source, string &destination){

  int source_rank = source[1];
  int destination_rank = destination[1];
  int rank_distance = destination_rank - source_rank;
  return rank_distance;

}

////////////////////////////////////////////////////////////////////////////

King::King(ChessBoard* cb): cb(cb){
}

King::~King(){
}

bool King::isValidMove(string &source,
		       string &destination,
		       map<string, BasePiece*> &white_pieces,
		       map<string, BasePiece*> &black_pieces,
		       const bool test) {

  int file_distance = getHorizontalDistance(source, destination);
  int rank_distance = getVerticalDistance(source, destination);

  if (file_distance > -2 && file_distance < 2 &&
      rank_distance > -2 && rank_distance < 2) {

    if (test == false){
      incrementMoveCount();
    }
    return true;
  }
  
  // CASTLING IMPLEMENTATION
  
  if (getMoveCount() == 0 &&
      rank_distance == 0 &&
      (file_distance ==  2 || file_distance == -2)){

    string answer;
    int source_rank = stoi(string(1, source[1]));
    string intermediary_square;
    string opponent_piece = "";
    
    if (test == false) {
      while (1) {
	
	cout << "Are you trying to castle? (y or n)" << endl;
	cin >> answer;
	
	if (answer == "y" || answer == "n"){
	  break;
	}
      
	cout << "Please answer the question appropriately." << endl;
      }
    
      if (answer == "n") {
	return false;
      }
    }

    // Ensuring king is not already in check
    if (test == false) {
      cb->white_turn = !(cb->white_turn);
      if (cb->isCheck() == true){
	cb->white_turn = !(cb->white_turn);
	return false;
      }
      cb->white_turn = !(cb->white_turn);
    } else {
      if (cb->isCheck() == true){
	return false;
      }
    }

    // Go through the different possibilities of castling (Black/White & Long/Short)
    if (source_rank == 1 && file_distance == 2){

      if ((white_pieces.find("F1") != white_pieces.end()) ||
	  (white_pieces.find("G1") != white_pieces.end()) ||
	  (black_pieces.find("F1") != black_pieces.end()) ||
	  (black_pieces.find("G1") != black_pieces.end())){

	return false;
      }
      
      intermediary_square = "F1";

      if (test != false) {
	
	cb->white_turn = !(cb->white_turn);
	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  cb->white_turn = !(cb->white_turn);
	  return false;
	}
	cb->white_turn = !(cb->white_turn);

      } else {

	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  return false;
	}
      }

      if (white_pieces.find("H1") != white_pieces.end()){

	if ((white_pieces["H1"])->returnName() == "Rook" &&
	    (white_pieces["H1"])->getMoveCount() == 0) {
	  
	  if (test == false){
	    incrementMoveCount();
	    (white_pieces["H1"])->incrementMoveCount();

	    auto node_handler = white_pieces.extract("H1");
	    node_handler.key() = "F1";
	    white_pieces.insert(move(node_handler));

	    cb->capture_string = " and White's Rook moves from H1 to F1";	
	  }

	  return true;
	}
      }
      
    } else if (source_rank == 1 && file_distance == -2){

      if ((white_pieces.find("B1") != white_pieces.end()) ||
	  (white_pieces.find("C1") != white_pieces.end()) ||
	  (white_pieces.find("D1") != white_pieces.end()) ||
	  (black_pieces.find("B1") != black_pieces.end()) ||
	  (black_pieces.find("C1") != black_pieces.end()) ||
	  (black_pieces.find("D1") != black_pieces.end())){
	
	return false;
      }
      
      intermediary_square = "D1";
  
      if (test != false) {
	
	cb->white_turn = !(cb->white_turn);
	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  cb->white_turn = !(cb->white_turn);
	  return false;
	}
	cb->white_turn = !(cb->white_turn);

      } else {

	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  return false;
	}
      }
      if (white_pieces.find("A1") != white_pieces.end()){

	if ((white_pieces["A1"])->returnName() == "Rook" &&
	    (white_pieces["A1"])->getMoveCount() == 0){
	  
	  if (test == false){
	    incrementMoveCount();
	    white_pieces["A1"]->incrementMoveCount();
	    
	    auto node_handler = white_pieces.extract("A1");
	    node_handler.key() = "D1";
	    white_pieces.insert(move(node_handler));
	    
	    cb->capture_string = " and White's Rook moves from A1 to D1";
	  }
	  
	  return true;
	}
      }

    } else if (source_rank == 8 && file_distance == 2){

      if ((white_pieces.find("F8") != white_pieces.end()) ||
	  (white_pieces.find("G8") != white_pieces.end()) ||
	  (black_pieces.find("F8") != black_pieces.end()) ||
	  (black_pieces.find("G8") != black_pieces.end())){
	
	return false;
      }

      intermediary_square = "F8";

      if (test != false) {
	
	cb->white_turn = !(cb->white_turn);
	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  cb->white_turn = !(cb->white_turn);
	  return false;
	}
	cb->white_turn = !(cb->white_turn);

      } else {

	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  return false;
	}
      }

      if (black_pieces.find("H8") != black_pieces.end()){
      
	if ((black_pieces["H8"])->returnName() == "Rook" &&
	    (black_pieces["H8"])->getMoveCount() == 0){
	  
	  if (test == false){
	    incrementMoveCount();
	    (black_pieces["H8"])->incrementMoveCount();
	    
	    auto node_handler = black_pieces.extract("H8");
	    node_handler.key() = "F8";
	    black_pieces.insert(move(node_handler));

	    cb->capture_string = " and Black's Rook moves from H8 to F8";
	    
	  }
	  return true;
	}
      }

    } else if (source_rank == 8 && file_distance == -2){

      if ((white_pieces.find("B8") != white_pieces.end()) ||
	  (white_pieces.find("C8") != white_pieces.end()) ||
	  (white_pieces.find("D8") != white_pieces.end()) ||
	  (black_pieces.find("B8") != black_pieces.end()) ||
	  (black_pieces.find("C8") != black_pieces.end()) ||
	  (black_pieces.find("D8") != black_pieces.end())){
	
	return false;
      }
      
      intermediary_square = "D8";
      
      if (test != false) {
	
	cb->white_turn = !(cb->white_turn);
	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  cb->white_turn = !(cb->white_turn);
	  return false;
	}
	cb->white_turn = !(cb->white_turn);

      } else {

	if (cb->isSelfCheck(source, intermediary_square, opponent_piece) == true){
	  
	  return false;
	}
      }

      if (black_pieces.find("A8") != black_pieces.end()){
      
	if ((black_pieces["A8"])->returnName() == "Rook" &&
	    (black_pieces["A8"])->getMoveCount() == 0){

	  if (test == false){
	    incrementMoveCount();
	    (black_pieces["A8"])->incrementMoveCount();
	    
	    auto node_handler = black_pieces.extract("A8");
	    node_handler.key() = "D8";
	    black_pieces.insert(move(node_handler));
	    
	    cb->capture_string = " and Black's Rook moves from A8 to D8";
	    
	  }
	  return true;
	}
      }
    }
  }

  return false;
}

string King::returnName(){
  return "King";
}

////////////////////////////////////////////////////////////////////////////

Queen::Queen(){
}

Queen::~Queen(){
}

bool Queen::isValidMove(string &source,
			string &destination,
			map<string, BasePiece*> &white_pieces,
			map<string, BasePiece*> &black_pieces,
			const bool test) {

  int file_distance = getHorizontalDistance(source, destination);
  int rank_distance = getVerticalDistance(source, destination);

  if (file_distance == 0 || rank_distance == 0) {

    char source_file = source[0];
    int source_rank = source[1];
    string intermediary_square;

    if (file_distance == 0 && rank_distance > 0) {
      
      for (int i = 1; i < abs(rank_distance); i++){
	
	intermediary_square = string(1, source_file) +
	  string(1, source_rank + i);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    } else if (file_distance == 0 && rank_distance < 0) {

      for (int i = 1; i < abs(rank_distance); i++){
	
	intermediary_square = string(1, source_file) +
	  string(1, source_rank - i);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    } else if (rank_distance == 0 && file_distance > 0) {
      
      for (int i = 1; i < abs(file_distance); i++){
	
	intermediary_square = string(1, source_file + i) +
	  string(1, source_rank);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    } else if (rank_distance == 0 && file_distance < 0) {

      for (int i = 1; i < abs(file_distance); i++){
	
	intermediary_square = string(1, source_file - i) +
	  string(1, source_rank);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    }    
    
    if (test == false){
      incrementMoveCount();
    }
    return true;

  } else if (abs(file_distance) == abs(rank_distance)){

    char source_file = source[0];
    int source_rank = source[1];
    string intermediary_square;
    
    if (file_distance == rank_distance) {
      
      if (file_distance > 0){

	for (int i = 1; i < abs(file_distance); i++){
	  
	  intermediary_square = string(1, source_file + i) +
	    string(1, source_rank + i);
	  
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      } else {
	
	for (int i = 1; i < abs(file_distance); i++) {
	  
	  intermediary_square = string(1, source_file - i) +
	    string(1,source_rank - i);
	  
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      }
    } else {

      if (file_distance > 0 && rank_distance < 0){

	for (int i = 1; i < abs(file_distance); i++){
	  
	  intermediary_square = string(1, source_file + i) +
	    string(1, source_rank - i);
	
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      } else {

	for (int i = 1; i < abs(file_distance); i++){
	  
	  intermediary_square = string(1, source_file - i) +
	    string(1, source_rank + i);
	
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      }
    }
    
    if (test == false){
      incrementMoveCount();
    }
    
    return true;
  }

  return false;
}

string Queen::returnName(){
  return "Queen";
}


////////////////////////////////////////////////////////////////////////////

Rook::Rook(){
}

Rook::~Rook(){
}

bool Rook::isValidMove(string &source,
		       string &destination,
		       map<string, BasePiece*> &white_pieces,
		       map<string, BasePiece*> &black_pieces,
		       const bool test) {

  int file_distance = getHorizontalDistance(source, destination);
  int rank_distance = getVerticalDistance(source, destination);

  if (file_distance == 0 || rank_distance == 0) {

    char source_file = source[0];
    int source_rank = source[1];
    string intermediary_square;

    if (file_distance == 0 && rank_distance > 0) {

      for (int i = 1; i < abs(rank_distance); i++){
	  
	intermediary_square = string(1, source_file) +
	  string(1, source_rank + i);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    } else if (file_distance == 0 && rank_distance < 0) {

      for (int i = 1; i < abs(rank_distance); i++){
	
	intermediary_square = string(1, source_file) +
	  string(1, source_rank - i);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    } else if (rank_distance == 0 && file_distance > 0) {
      
      for (int i = 1; i < abs(file_distance); i++){
	
	intermediary_square = string(1, source_file + i) +
	  string(1, source_rank);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    } else if (rank_distance == 0 && file_distance < 0) {

      for (int i = 1; i < abs(file_distance); i++){
	
	intermediary_square = string(1, source_file - i) +
	  string(1, source_rank);
	
	if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	   black_pieces.find(intermediary_square) != black_pieces.end()){
	  
	  return false;
	}
      }
    }
    
    if (test == false){
      incrementMoveCount();
    }
    
    return true;
  }
      
  return false;
}

string Rook::returnName(){
  return "Rook";
}


////////////////////////////////////////////////////////////////////////////

Knight::Knight(){
}

Knight::~Knight(){
}

bool Knight::isValidMove(string &source,
			 string &destination,
			 map<string, BasePiece*> &white_pieces,
			 map<string, BasePiece*> &black_pieces,
			 const bool test) {

  int file_distance = abs(getHorizontalDistance(source, destination));
  int rank_distance = abs(getVerticalDistance(source, destination));

  if (file_distance > 0 && rank_distance > 0 &&
      (file_distance + rank_distance == 3)) {

    if (test == false){
      incrementMoveCount();
    }

    return true;
  }
  
  return false;
}

string Knight::returnName(){
  return "Knight";
}


////////////////////////////////////////////////////////////////////////////

Bishop::Bishop(){
}

Bishop::~Bishop(){
}

bool Bishop::isValidMove(string &source,
			 string &destination,
			 map<string, BasePiece*> &white_pieces,
			 map<string, BasePiece*> &black_pieces,
			 const bool test) {

  int file_distance = getHorizontalDistance(source, destination);
  int rank_distance = getVerticalDistance(source, destination);

  if (abs(file_distance) == abs(rank_distance)){

    char source_file = source[0];
    int source_rank = source[1];
    string intermediary_square;
    
    if (file_distance == rank_distance) {

      if (file_distance > 0){

	for (int i = 1; i < abs(file_distance); i++){
	  
	  intermediary_square = string(1, source_file + i) +
	    string(1, source_rank + i);
	  
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      } else {
	
	for (int i = 1; i < abs(file_distance); i++) {
	  
	  intermediary_square = string(1,source_file - i) +
	    string(1, source_rank - i);

	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      }
    } else {

      if (file_distance > 0 && rank_distance < 0){

	for (int i = 1; i < abs(file_distance); i++){
	  
	  intermediary_square = string(1, source_file + i) +
	    string(1, source_rank - i);
	
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      } else {

	for (int i = 1; i < abs(file_distance); i++){
	  
	  intermediary_square = string(1, source_file - i) +
	    string(1, source_rank + i);
	
	  if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	     black_pieces.find(intermediary_square) != black_pieces.end()){
	    
	    return false;
	  }
	}
      }
    }
    
    if (test == false){
      incrementMoveCount();
    }
    
    return true;
  }
  
  return false;
}

string Bishop::returnName(){
  return "Bishop";
}


////////////////////////////////////////////////////////////////////////////

Pawn::Pawn(ChessBoard* cb): cb(cb){
}

Pawn::~Pawn(){
}

bool Pawn::isValidMove(string &source,
		       string &destination,
		       map<string, BasePiece*> &white_pieces,
		       map<string, BasePiece*> &black_pieces,
		       const bool test) {
  
  int file_distance = getHorizontalDistance(source, destination);
  int rank_distance = getVerticalDistance(source, destination);
  bool capture = false;
  bool white_turn = false;

  char source_file = source[0];
  int source_rank = source[1];
  string intermediary_square;
  
  string last_move = cb->getLastMove();
  string last_move_source = last_move.substr(0,2);
  string last_move_destination = last_move.substr(3,2);
  
  if(white_pieces.find(destination) != white_pieces.end() ||
     black_pieces.find(destination) != black_pieces.end()){
    
    capture = true;
  }

  if(white_pieces.find(source) != white_pieces.end()){
    
    white_turn = true;
  }

  if (white_turn == true){

    if (file_distance == 0 && capture == false &&
	rank_distance > 0 && rank_distance < 3 &&
	getMoveCount() == 0) {
      
      intermediary_square = string(1, source_file) +
	string(1, source_rank + 1);
      
      if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	 black_pieces.find(intermediary_square) != black_pieces.end()){

	return false;
      }
      
      if (test == false){
	incrementMoveCount();
      }
      return true;
      
    } else if (file_distance == 0 && capture == false &&
	       rank_distance == 1 && getMoveCount() > 0) {
      
      if (test == false){
	incrementMoveCount();
      }
      return true;
      
    } else if ((file_distance == -1 || file_distance == 1) &&
	       rank_distance == 1 && capture == true) {
      
      if (test == false){
	incrementMoveCount();
      }
      return true;

      // EN PASSANT IMPLEMENTATION
    } else if ((file_distance == -1 || file_distance == 1) &&
	       rank_distance == 1 && capture == false){

      string source_rank = string(1, source[1]);
      string destination_file = string(1, destination[0]);
      string theo_source = destination_file + "7";
      string theo_destination = destination_file + source_rank;

      if (last_move_destination != theo_destination){
	return false;
      }

      if (source_rank != "5"){
	return false;
      }

      if (last_move_source != theo_source){
	return false;
      }

      if ((black_pieces[last_move_destination])->getMoveCount() == 1){

	if (test == false){
	  incrementMoveCount();
	
	  delete black_pieces[last_move_destination];
	  black_pieces[last_move_destination] = NULL;
	  black_pieces.erase(last_move_destination);
	  cb->capture_string = " taking Black's Pawn";
	}
	
	return true;
      }
    }
    
  } else {

    if (file_distance == 0 && capture == false &&
	rank_distance < 0 && rank_distance > -3 &&
	getMoveCount() == 0) {

      intermediary_square = string(1, source_file) +
	string(1, source_rank - 1);
      
      if(white_pieces.find(intermediary_square) != white_pieces.end() ||
	 black_pieces.find(intermediary_square) != black_pieces.end()){

	return false;
      }
      
      if (test == false){
	incrementMoveCount();
      }
      return true;
      
    } else if (file_distance == 0 && capture == false &&
	       rank_distance == -1 && getMoveCount() > 0) {
      
      if (test == false){
	incrementMoveCount();
      }
      return true;
      
    } else if ((file_distance == -1 || file_distance == 1) &&
	       rank_distance == -1 && capture == true) {
      
      if (test == false){
	incrementMoveCount();
      }
      return true;

      // EN PASSANT IMPLEMENTATION
    } else if ((file_distance == -1 || file_distance == 1) &&
	       rank_distance == -1 && capture == false){

      string source_rank = string(1, source[1]);
      string destination_file = string(1, destination[0]);
      string theo_source = destination_file + "2";
      string theo_destination = destination_file + source_rank;

      if (last_move_destination != theo_destination){
	return false;
      }

      if (source_rank != "4"){
	return false;
      }

      if (last_move_source != theo_source){
	return false;
      }

      if ((white_pieces[last_move_destination])->getMoveCount() == 1){

	if (test == false){
	  incrementMoveCount();

	  delete white_pieces[last_move_destination];
	  white_pieces[last_move_destination] = NULL;
	  white_pieces.erase(last_move_destination);
	  cb->capture_string = " taking White's Pawn";
	}
	
	return true;
      }
    }
  }

  return false;
}

string Pawn::returnName(){
  return "Pawn";
}
