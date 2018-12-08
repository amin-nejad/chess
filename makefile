chess: ChessMain.o ChessBoard.o ChessPieces.o
	g++ -Wall -g ChessMain.o ChessBoard.o ChessPieces.o -o chess -std=c++17

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -c ChessMain.cpp -std=c++17

ChessBoard.o: ChessBoard.cpp ChessBoard.h ChessPieces.h
	g++ -Wall -c ChessBoard.cpp -std=c++17

ChessPieces.o: ChessPieces.cpp ChessBoard.h ChessPieces.h
	g++ -Wall -c ChessPieces.cpp -std=c++17

.PHONY: clean
clean:
	rm -rf *.o
