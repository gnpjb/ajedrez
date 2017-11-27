#include<iostream>
#include<string>
#ifndef _AJEDREZ_MAIN_H_
#define _AJEDREZ_MAIN_H_
using namespace std;

class ChessPiece {
	protected:
		enum Colors{White,Black};
		Colors Color=White;
		enum PiecesTypes{King,Queen,Rook,Bishop,Knight,Pawn,Blank};
		PiecesTypes PieceType=Blank;
	public:
		void SetPieceType(PiecesTypes SettingType){
			PieceType=SettingType;
		} //set which type of piece it is
		void SetPieceColor(Colors SettingColor){
			PieceType=SettingColor;					//set the piece color
		}
		string GetPieceType();						//returns the piece type
		string GetSettingColor();						//returns the piece color
};
string ChessPiece::GetPieceType(){
	switch(PieceType){
		case King:
			return "King";
			break;
		case Queen:
			return "Queen";
			break;
		case Rook:
			return "Rook";
			break;
		case Bishop:
			return "Bishop";
			break;
		case Knight:
			return "Knight";
			break;
		case Pawn:
			return "Pawn";
			break;
		case Blank:
			return "Blank";
			break;
		default:
			return "Error";
	}
}
string ChessPiece::GetSettingColor(){
	switch(PieceType){
		case White:
			return "White";
			break;
		case Black:
			return "Black";
			break;
		default:
			return "Error";
	}
}









class ChessBoard {
	protected:
		int num_of_moves=0;
		ChessPiece Board[8][8];
	public:
		ChessBoard();
	
}
ChessBoard::ChessBoard(){
	for(int i=1;i<9;i++){
		if(i==1||i==2||i==7||i==8){
			for(int j=1;j<9;j++){
				if(i==1||i==8){
					switch(j){//check for each column and set the piece type accordingly accordingly
						case 1:
							Board[i][j].SetPieceType(Rook);
							break;
						case 2:
							Board[i][j].SetPieceType(Knight);
							break;
						case 3:
							Board[i][j].SetPieceType(Bishop);
							break;
						case 4:
							Board[i][j].SetPieceType(Queen);
							break;
						case 5:
							Board[i][j].SetPieceType(King);
							break;
						case 6:
							Board[i][j].SetPieceType(Bishop);
							break;
						case 7:
							Board[i][j].SetPieceType(Knight);
							break;
						case 8:
							Board[i][j].SetPieceType(Rook);
							break;
					}
					switch(i){//set first column to white and last column to Black
						case 1:
							Board[i][j].SetPieceColor(White);
							break;
						case 2:
							Board[i][j].SetPieceColor(Black);
							break;
					}
				}
				if(i==2||i==7){
					Board[i][j].SetPieceType(Pawn);
					switch(i){
						case 2:
							Board[i][j].SetPieceColor(White);
							break;
						case 7:
							Board[i][j].SetPieceColor(Black);
							break;
					}
					
				}
			}
		}
	}
		
	}
	
	
	
	
}


#endif
