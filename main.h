#include<iostream>
#include<string>
#include<cmath>

#ifndef _AJEDREZ_MAIN_H_
#define _AJEDREZ_MAIN_H_

enum G_ChessPiecesColors{White,Black};
enum G_ChessPiecesTypes{King,Queen,Rook,Bishop,Knight,Pawn,Blank};



class ChessPiece {
	protected:
		G_ChessPiecesColors PieceColor=White;
		G_ChessPiecesTypes PieceType=Blank;
	public:
		void SetPieceType(G_ChessPiecesTypes SettingType){
			PieceType=SettingType;
		} //set which type of piece it is
		void SetPieceColor(G_ChessPiecesColors SettingColor){
			PieceColor=SettingColor;					//set the piece color
		}
		G_ChessPiecesTypes GetPieceType(){return PieceType;}						//returns the piece type
		G_ChessPiecesColors GetPieceColor(){return PieceColor;}						//returns the piece color
		std::string String_GetPieceType();												//returns the type in a string
		std::string String_GetPieceColor();											//returns the color in a string
};

//ChessPiece Function declarations
std::string ChessPiece::String_GetPieceColor(){//returns a string with the color of the piece
	switch(PieceColor){
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

std::string ChessPiece::String_GetPieceType(){//returns a striing with the name of the piece type
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





class ChessBoard{
	protected:
		G_ChessPiecesColors WhoseTurn=White;
		int num_of_moves=0;
		ChessPiece Board[8][8];
	public:
		ChessBoard();
		bool MakeMove(int R1,int C1,int R2,int C2);
		bool PawnValidMove(int R1,int C1,int R2,int C2);
		bool KingValidMove(int R1,int C1,int R2,int C2);
		bool QueenValidMove(int R1,int C1,int R2,int C2);
		bool RookValidMove(int R1,int C1,int R2,int C2);
		bool BishopValidMove(int R1,int C1,int R2,int C2);
		bool KnightValidMove(int R1,int C1,int R2,int C2);
		bool WhiteInCheck();
		bool BlackInCheck();
		bool WhiteInCheckMate();
		bool BlackInCheckMate();
		bool IsValidMove(int R1,int C1,int R2, int C2);
		void PrintChessBoard();
		std::string GetWhoseTurn();
};
ChessBoard::ChessBoard(){//initializes a board with the whites on top and the blacks on the bottom
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
						case 8:
							Board[i][j].SetPieceColor(Black);
							break;
					}
				}
				if(i==2||i==7){//set second a seventh row to white pawns and black pawns respectively
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

bool ChessBoard::PawnValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a pawn in that place
	if(!(Board[R1][C1].GetPieceType()==Pawn))
		return false;
	if(std::abs(R1-R2)>2)//check that the move is less than two blocks
		return false;
	if(C1-C2!=0){//check for column changes
		if(std::abs(R1-R2)!=1)
			return false;
		if(Board[R1][C1].GetPieceColor()==White)
		{	//check to see if the move is to a blank spot or a a piece of the same color
			if((Board[R2][C2].GetPieceType()==Blank)||(Board[R2][C2].GetPieceColor()==White))
				return false;
		}
		else
		{	//check to see if the move is to a blank spot or a a piece of the same color
			if((Board[R2][C2].GetPieceType()==Blank)||(Board[R2][C2].GetPieceColor()==Black))
				return false;
		}
	}
	if(std::abs(R1-R2)==2){//check for the special case of the first time they move
		if(!((R1==2&&Board[R1][C1].GetPieceColor()==White)||(R1==7&&Board[R1][C1].GetPieceColor()==Black)))
			return false;
	}
	//check that they are moving in the right direction
	if((R2-R1)>0)
	{
		if(Board[R1][C1].GetPieceColor()==Black)
			return false;
	}
	if((R2-R1)<0)
	{
		if(Board[R1][C1].GetPieceColor()==White)
			return false;
	}
	{
		int Dir;//direction of move
		if((R1-R2)>0)
			Dir=(-1);
		else
			Dir=1;	
		int Undir_move=std::abs(R1-R2);//number of moves without direction
		int tmp_R=R1;
		for(int i=1;i<=Undir_move;i++)
		{//checks that the spaces to move are empty
			tmp_R=tmp_R+(Dir*i);
			if(!(Board[tmp_R][C1].GetPieceType()==Blank))
				return false;
		}
		
	}
	return true;
}



bool ChessBoard::KingValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a king in that place
	if(Board[R1][C1].GetPieceType()!=King)
		return false;
	
	//check that the move is in the king range of movement
	if((std::abs(R1-R2))>1||(std::abs(C1-C2))>1)
		return false;
	if(!((Board[R2][C2].GetPieceType()==Blank)||(Board[R2][C2].GetPieceColor()!=Board[R1][C1].GetPieceColor())))
		return false;
	//check that the king doesnt get into a check
/*	for(int i=1;i<=8;i++){
		for(int j;j<=8;j++){
			if((!(Board[i][j].GetPieceType()==Blank||(i==R1&&j==C1)))&&(Board[i][j].GetPieceColor()!=Board[R1][C1].GetPieceColor()))
			{
				
				if(//check if Board[i][j] can move to where the king will be
					PawnValidMove(i,j,R2,C2)
					||RookValidMove(i,j,R2,C2)
					||KnightValidMove(i,j,R2,C2)
					||BishopValidMove(i,j,R2,C2)
					||QueenValidMove(i,j,R2,C2)
				)
					return false;
				if(Board[i][j].GetPieceType()==King)
				{
					if((std::abs(i-R2)<=1)&&(std::abs(j-C2)<=1))
					return false;
				}
			}
		}
		
	}
	changed implemetation
	*/
	{
		bool GetsInCheck=false;
		ChessPiece Tmp_R1_C1=Board[R1][C1];
		ChessPiece Tmp_R2_C2=Board[R2][C2];
		Board[R2][C2]=Board[R1][C1];
		Board[R2][C2].SetPieceType(Blank);
		if(Tmp_R1_C1.GetPieceColor()==White&&WhiteInCheck())
			GetsInCheck=true;
		if(Tmp_R1_C1.GetPieceColor()==Black&&BlackInCheck())
			GetsInCheck=true;
		Board[R1][C1]=Tmp_R1_C1;
		Board[R2][C2]=Tmp_R2_C2
	}
	return true;
}



bool ChessBoard::QueenValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a queen in that place
	if(Board[R1][C1].GetPieceType()!=Queen)
		return false;
	
	//check that the move is in the Queen range of movement
	if(!(((R1-R2)==0)
		||((C1-C2)==0)
		||(std::abs(R1-R2)==std::abs(C1-C2))))
		return false;
	{
		int Dir_R=1;
		int Dir_C=1;
		if((R1-R2)==0)
			Dir_R=0;
		if((R1-R2)>0)
			Dir_R=-1;
		if((C1-C2)==0)
			Dir_C=0;
		if((C1-C2)>0)
			Dir_C=-1;
		int Mov=std::abs(R1-R2);//number of moves.(R1-R2) is put there so one less if is needed
		if(std::abs(R1-R2)<std::abs(C1-C2))
			Mov=std::abs(C1-C2);//in the case where r1-r2 is 0 is when c1-C2 is needed instead
		for(int i=1;i<=(Mov-1);i++){
			if((Board[R1+(Dir_R*i)][C1+(Dir_C*i)].GetPieceType()!=Blank))
				return false;
		}
	}
	if(Board[R2][C2].GetPieceColor()==Board[R1][C1].GetPieceColor()&&Board[R2][C2].GetPieceType()!=Blank)
		return false;
	return true;
}



bool ChessBoard::RookValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a rook in that place
	if(Board[R1][C1].GetPieceType()!=Rook)
		return false;
	
	//check that the move is in the rook range of movement
	if(!(((R1-R2)==0)
		||((C1-C2)==0)))
		return false;
	{
		int Dir_R=1;
		int Dir_C=1;
		if((R1-R2)==0)
			Dir_R=0;
		if((R1-R2)<0)
			Dir_R=-1;
		if((C1-C2)==0)
			Dir_C=0;
		if((C1-C2)<0)
			Dir_C=-1;
		int Mov=std::abs(R1-R2);//number of moves.(R1-R2) is put there so one less if is needed
		if(std::abs(R1-R2)<std::abs(C1-C2))
			Mov=std::abs(C1-C2);//in the case where r1-r2 is 0 is when c1-C2 is needed instead
		for(int i=1;i<=(Mov-1);i++){//loop throught every place it will pass
			if((Board[R1+(Dir_R*i)][C1+(Dir_C*i)].GetPieceType()!=Blank))
				return false;
		}
	}
	
	if(Board[R2][C2].GetPieceColor()==Board[R1][C1].GetPieceColor()&&Board[R2][C2].GetPieceType()!=Blank)//check that the space is blank or eatable
		return false;	
	
	return true;
}




bool ChessBoard::BishopValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a bishop in that place
	if(Board[R1][C1].GetPieceType()!=Bishop)
		return false;
	if(R1==R2||C1==2)//has to move in both R and C
		return false;
	
	//check that the move is in the Bishop range of movement
	if(!(std::abs(R1-R2)==std::abs(C1-C2)))
		return false;
	{
		int Dir_R=1;
		int Dir_C=1;
		if((R1-R2)==0)
			Dir_R=0;
		if((R1-R2)>0)
			Dir_R=-1;
		if((C1-C2)==0)
			Dir_C=0;
		if((C1-C2)>0)
			Dir_C=-1;
		int Mov=std::abs(R1-R2);//number of moves.(R1-R2) is put there so one less if is needed
		if(std::abs(R1-R2)<std::abs(C1-C2))
			Mov=std::abs(C1-C2);//in the case where r1-r2 is 0 is when c1-C2 is needed instead
			for(int i=1;i<=(Mov-1);i++){//loop throught every place it will pass
				if((Board[R1+(Dir_R*i)][C1+(Dir_C*i)].GetPieceType()!=Blank))
					return false;
			}
	}
	
	if(Board[R2][C2].GetPieceColor()==Board[R1][C1].GetPieceColor()&&Board[R2][C2].GetPieceType()!=Blank)//check that the space is blank or eatable
		return false;
	return true;
}
	
bool ChessBoard::KnightValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a knight in that place
	if(Board[R1][C1].GetPieceType()!=Knight)
		return false;
	
	//check that the move is in the Knight range of movement
	if(!(  
		(((std::abs(R1-R2)>=1)||std::abs(C1-C2)>=1)
		&&((std::abs(R1-R2)<=2)||std::abs(C1-C2)<=2))
		&&!((std::abs(R1-R2)==2)&&(std::abs(C1-C2)==2))
		&&((std::abs(R1-R2)+std::abs(C1-C2))==3)
	))
		return false;
	if(Board[R2][C2].GetPieceColor()==Board[R1][C1].GetPieceColor()&&Board[R2][C2].GetPieceType()!=Blank)//check that the space is blank or eatable
		return false;
	
	return true;
}



bool ChessBoard::MakeMove(int R1,int C1,int R2,int C2){
	if((R1-R2)==0&&(C1-C2)==0)
		return false;
	if(R1<1||R2<1||C1<1||C2<1||R1>8||R2>8||C1>8||C2>8)
		return false;
	if(WhoseTurn==Black){
		if(BlackInCheckMate()){
			return false;
		}
	}
	if(WhoseTurn==White){
		if(WhiteInCheckMate())
			return false;
	}
	if(Board[R1][C1].GetPieceColor()!=WhoseTurn)
		return false;
	if(Board[R1][C1].GetPieceType()==Blank)
		return false;
	if(IsValidMove(R1,C1,R2,C2)){//check if it is a valid move
		ChessPiece Tmp_P1=Board[R1][C1];
		ChessPiece Tmp_P2=Board[R2][C2];
		Board[R2][C2]=Board[R1][C1];
		Board[R1][C1].SetPieceType(Blank);
		if(WhoseTurn==White&&WhiteInCheck()){
			Board[R1][C1]=Tmp_P1;
			Board[R2][C2]=Tmp_P2;
			return false;
		}
		if(WhoseTurn==Black&&BlackInCheck()){
			Board[R1][C1]=Tmp_P1;
			Board[R2][C2]=Tmp_P2;
			return false;
		}
		num_of_moves++;
		if(WhoseTurn==White)
			WhoseTurn=Black;
		else
			WhoseTurn=White;
	}
	else
		return false;
	return true;
}

bool ChessBoard::WhiteInCheck(){
	//finding the coordinates of the white king
	int C,R;
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(Board[i][j].GetPieceType()==King&&Board[i][j].GetPieceColor()==White){
				R=i;
				C=j;
				break;
			}
		}
		
	}
	//check if anyone can move to where the king is(basically if the king is in check)
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(QueenValidMove(i,j,R,C)||PawnValidMove(i,j,R,C)||KnightValidMove(i,j,R,C)||BishopValidMove(i,j,R,C)||RookValidMove(i,j,R,C))
				return true;
			if(Board[i][j].GetPieceType()==King&&Board[i][j].GetPieceColor()==Black){
				if(std::abs(i-R)<=1&&std::abs(j-R)<=1)
					return true;
			}
		}
	}
	return false;
}

bool ChessBoard::BlackInCheck(){
	//finding the coordinates of the white king
	int C,R;
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(Board[i][j].GetPieceType()==King&&Board[i][j].GetPieceColor()==Black){
				R=i;
				C=j;
				break;
			}
		}
	}
	//check if anyone can move to where the king is(basically if the king is in check)
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(QueenValidMove(i,j,R,C)||PawnValidMove(i,j,R,C)||KnightValidMove(i,j,R,C)||BishopValidMove(i,j,R,C)||RookValidMove(i,j,R,C))
				return true;
			if(Board[i][j].GetPieceType()==King&&Board[i][j].GetPieceColor()==White){
				if(std::abs(i-R)<=1&&std::abs(j-R)<=1)
					return true;
			}
		}
	}
	return false;
}

bool ChessBoard::IsValidMove(int R1,int C1,int R2, int C2){
	if(Board[R1][C1].GetPieceColor()==White){
		
		
		if(KnightValidMove(R1,C1,R2,C2)||BishopValidMove(R1,C1,R2,C2)||RookValidMove(R1,C1,R2,C2)||QueenValidMove(R1,C1,R2,C2)||KingValidMove(R1,C1,R2,C2)||PawnValidMove(R1,C1,R2,C2)){
			ChessPiece R1_C1_Piece=Board[R1][C1];
			ChessPiece R2_C2_Piece=Board[R2][C2];
			Board[R2][C2]=Board[R1][C1];
			Board[R1][C1].SetPieceType(Blank);
			if(WhiteInCheck()){
				Board[R1][C1]= R1_C1_Piece;
				Board[R2][C2]=R2_C2_Piece;
				return false;
			}
			Board[R1][C1]= R1_C1_Piece;
			Board[R2][C2]=R2_C2_Piece;
			return true
		}
			
	}
	else if(Board[R1][C1].GetPieceColor()==Black){
		if(KnightValidMove(R1,C1,R2,C2)||BishopValidMove(R1,C1,R2,C2)||RookValidMove(R1,C1,R2,C2)||QueenValidMove(R1,C1,R2,C2)||KingValidMove(R1,C1,R2,C2)||PawnValidMove(R1,C1,R2,C2)){
			ChessPiece R1_C1_Piece=Board[R1][C1];
			ChessPiece R2_C2_Piece=Board[R2][C2];
			Board[R2][C2]=Board[R1][C1];
			if(BlackInCheck()){
				Board[R1][C1]= R1_C1_Piece;
				Board[R2][C2]=R2_C2_Piece;
				return false;
			}
			Board[R1][C1]= R1_C1_Piece;
			Board[R2][C2]=R2_C2_Piece;
			return true;
		}
	}
	
}
bool ChessBoard::BlackInCheckMate(){//checks if black is in checkmate
	if(!BlackInCheck())//if its not in check already it can never be in checkmate
		return false;
	for(int i=1;i<=8;i++){//go throught all the pieces,check if they are black, then move them temporarily and see if it is still in check, if not, return false
		for(int j=1;j<=8;j++){
			if(Board[i][j].GetPieceType()==Blank)
				continue;
			if(Board[i][j].GetPieceColor()==Black){
				for(int k=1;k<=8;k++){
					for(int l=1;l<=1;l++){
						if(IsValidMove(i,j,k,l))
						{
							ChessPiece i_j_Piece=Board[i][j];
							ChessPiece k_l_Piece=Board[k][l];
							Board[k][l]=Board[i][j];
							Board[i][j].SetPieceType(Blank);
							if(!BlackInCheck()){
								Board[i][j]=i_j_Piece;
								Board[k][l]=k_l_Piece;
								return false;
							}
							Board[i][j]=i_j_Piece;
							Board[k][l]=k_l_Piece;
							return true;
						}
					}
				}
			}
		}
	}
}
bool ChessBoard::WhiteInCheckMate(){//checks if white is in checkmate
	if(!WhiteInCheck())//if its not in check already it can never be in checkmate
		return false;
	for(int i=1;i<=8;i++){//go throught all the pieces,check if they are white, then move them temporarily and see if it is still in check, if not, return false
		for(int j=1;j<=8;j++){
			if(Board[i][j].GetPieceType()==Blank)
				continue;
			if(Board[i][j].GetPieceColor()==White){
				for(int k=1;k<=8;k++){
					for(int l=1;l<=1;l++){
						if(IsValidMove(i,j,k,l))
						{
							ChessPiece i_j_Piece=Board[i][j];
							ChessPiece k_l_Piece=Board[k][l];
							Board[k][l]=Board[i][j];
							Board[i][j].SetPieceType(Blank);
							if(!BlackInCheck()){
								Board[i][j]=i_j_Piece;
								Board[k][l]=k_l_Piece;
								return false;
							}
							Board[i][j]=i_j_Piece;
							Board[k][l]=k_l_Piece;
							return true;
						}
					}
				}
			}
		}
	}
}


void ChessBoard::PrintChessBoard(){
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(Board[i][j].GetPieceType()==Blank){
				std::cout<<"bla ";
				continue;
			}
			if(Board[i][j].GetPieceColor()==White)
				std::cout<<"W";
			if(Board[i][j].GetPieceColor()==Black)
				std::cout<<"B";
			switch(Board[i][j].GetPieceType()){
				case King:
					std::cout<<"Ki ";
					break;
				case Rook:
					std::cout<<"Ro ";
					break;
				case Knight:
					std::cout<<"Kn ";
					break;
				case Bishop:
					std::cout<<"Bi ";
					break;
				case Queen:
					std::cout<<"Qu ";
					break;
				case Pawn:
					std::cout<<"Pa ";
					break;
			}
		}
		std::cout<<std::endl;
	}
}

std::string ChessBoard::GetWhoseTurn(){
	if(WhoseTurn==White)
		return "white";
	else
		return "black";
}
#endif

