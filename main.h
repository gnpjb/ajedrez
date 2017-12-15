#include<iostream>
#include<string>
#include<cmath>
#include<SDL2/SDL.h>

#ifndef _AJEDREZ_MAIN_H_
#define _AJEDREZ_MAIN_H_
const int G_Screen_Width=626;
const int G_Screen_Height=626;

enum G_ChessPiecesColors{White,Black};
enum G_ChessPiecesTypes{King,Queen,Rook,Bishop,Knight,Pawn,Blank};


void G_BlackToWhite(SDL_Surface* surface){
	
	uint32_t *pixels = (uint32_t*)surface->pixels;
	int pixelnum=surface->w*surface->h;
	for(int i=0;i<pixelnum;i++){
		
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		
		uint32_t pixel = *((uint32_t *)surface->pixels + i);
		SDL_GetRGBA(pixel, surface->format, &r, &g, &b,&a);
		if(a!=0)
		{
			pixels[i] = SDL_MapRGB(surface->format, 255, 255, 255);
		}
	}
}


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
		SDL_Surface* S_Screen;
		SDL_Window* Window;
		bool Initialized=false;
	public:
		ChessBoard();
		~ChessBoard();
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
		void UpdateScreen();//MISSING:implemetation
};
ChessBoard::ChessBoard(){//initializes a board with the whites on top and the blacks on the bottom
	for(int i=1;i<9;i++){
		if(i==1||i==2||i==7||i==8){
			for(int j=1;j<9;j++){
				if(i==1||i==8){
					switch(j){//check for each column and set the piece type accordingly accordingly
						case 1:
							Board[i-1][j-1].SetPieceType(Rook);
							break;
						case 2:
							Board[i-1][j-1].SetPieceType(Knight);
							break;
						case 3:
							Board[i-1][j-1].SetPieceType(Bishop);
							break;
						case 4:
							Board[i-1][j-1].SetPieceType(Queen);
							break;
						case 5:
							Board[i-1][j-1].SetPieceType(King);
							break;
						case 6:
							Board[i-1][j-1].SetPieceType(Bishop);
							break;
						case 7:
							Board[i-1][j-1].SetPieceType(Knight);
							break;
						case 8:
							Board[i-1][j-1].SetPieceType(Rook);
							break;
					}
					switch(i){//set first column to white and last column to Black
						case 1:
							Board[i-1][j-1].SetPieceColor(White);
							break;
						case 8:
							Board[i-1][j-1].SetPieceColor(Black);
							break;
					}
				}
				if(i==2||i==7){//set second a seventh row to white pawns and black pawns respectively
					Board[i-1][j-1].SetPieceType(Pawn);
					switch(i){
						case 2:
							Board[i-1][j-1].SetPieceColor(White);
							break;
						case 7:
							Board[i-1][j-1].SetPieceColor(Black);
							break;
					}
					
				}
			}
		}
	}
	//SDL
	SDL_Surface *S_Background;
	S_Background=NULL;
	S_Screen=NULL;
	Window=NULL;
	if(SDL_WasInit(SDL_INIT_EVERYTHING)==0){//if sdl is not Initialized then initialize it
		if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
			std::cout<<"Failed to initialize game"<<std::endl<<SDL_GetError()<<std::endl;
			Initialized=false;
		}
		else
			Initialized=true;
	}
	Window=SDL_CreateWindow(
		"Chess",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		G_Screen_Width,
		G_Screen_Height,
		SDL_WINDOW_RESIZABLE
	);
	if(Window==NULL)
		Initialized=false;
	if(Window!=NULL){
		S_Screen=SDL_GetWindowSurface(Window);
		S_Background=SDL_LoadBMP("images/ChessBoard.bmp");
		SDL_BlitSurface(S_Background,NULL,S_Screen,NULL);
		SDL_UpdateWindowSurface(Window);
	}
	SDL_FreeSurface(S_Background);
}
ChessBoard::~ChessBoard(){
	SDL_FreeSurface(S_Screen);
	SDL_DestroyWindow(Window);
}



bool ChessBoard::PawnValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a pawn in that place
	if(!(Board[R1-1][C1-1].GetPieceType()==Pawn))
		return false;
	if(std::abs(R1-R2)>2)//check that the move is less than two blocks
		return false;
	if(C1-C2!=0){//check for column changes
		if(std::abs(R1-R2)!=1)
			return false;
		if(Board[R1-1][C1-1].GetPieceColor()==White)
		{	//check to see if the move is to a blank spot or a a piece of the same color
			if((Board[R2-1][C2-1].GetPieceType()==Blank)||(Board[R2-1][C2-1].GetPieceColor()==White))
				return false;
		}
		else
		{	//check to see if the move is to a blank spot or a a piece of the same color
			if((Board[R2-1][C2-1].GetPieceType()==Blank)||(Board[R2-1][C2-1].GetPieceColor()==Black))
				return false;
		}
	}
	if(std::abs(R1-R2)==2){//check for the special case of the first time they move
		if(!((R1==2&&Board[R1-1][C1-1].GetPieceColor()==White)||(R1==7&&Board[R1-1][C1-1].GetPieceColor()==Black)))
			return false;
	}
	//check that they are moving in the right direction
	if((R2-R1)>0)
	{
		if(Board[R1-1][C1-1].GetPieceColor()==Black)
			return false;
	}
	if((R2-R1)<0)
	{
		if(Board[R1-1][C1-1].GetPieceColor()==White)
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
			if(!(Board[tmp_R-1][C1-1].GetPieceType()==Blank))
				return false;
		}
		
	}
	return true;
}



bool ChessBoard::KingValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a king in that place
	if(Board[R1-1][C1-1].GetPieceType()!=King)
		return false;
	
	//check that the move is in the king range of movement
	if((std::abs(R1-R2))>1||(std::abs(C1-C2))>1)
		return false;
	if(!((Board[R2-1][C2-1].GetPieceType()==Blank)||(Board[R2-1][C2-1].GetPieceColor()!=Board[R1-1][C1-1].GetPieceColor())))
		return false;
	//check that the king doesnt get into a check
/*	for(int i=1;i<=8;i++){
		for(int j;j<=8;j++){
			if((!(Board[i-1][j-1].GetPieceType()==Blank||(i==R1&&j==C1)))&&(Board[i-1][j-1].GetPieceColor()!=Board[R1-1][C1-1].GetPieceColor()))
			{
				
				if(//check if Board[i-1][j-1] can move to where the king will be
					PawnValidMove(i,j,R2,C2)
					||RookValidMove(i,j,R2,C2)
					||KnightValidMove(i,j,R2,C2)
					||BishopValidMove(i,j,R2,C2)
					||QueenValidMove(i,j,R2,C2)
				)
					return false;
				if(Board[i-1][j-1].GetPieceType()==King)
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
		ChessPiece Tmp_R1_C1=Board[R1-1][C1-1];
		ChessPiece Tmp_R2_C2=Board[R2-1][C2-1];
		Board[R2-1][C2-1]=Board[R1-1][C1-1];
		Board[R2-1][C2-1].SetPieceType(Blank);
		if(Tmp_R1_C1.GetPieceColor()==White&&WhiteInCheck())
			GetsInCheck=true;
		if(Tmp_R1_C1.GetPieceColor()==Black&&BlackInCheck())
			GetsInCheck=true;
		Board[R1-1][C1-1]=Tmp_R1_C1;
		Board[R2-1][C2-1]=Tmp_R2_C2;
	}
	return true;
}



bool ChessBoard::QueenValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a queen in that place
	if(Board[R1-1][C1-1].GetPieceType()!=Queen)
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
			if((Board[R1+(Dir_R*i)-1][C1+(Dir_C*i)-1].GetPieceType()!=Blank))
				return false;
		}
	}
	if(Board[R2-1][C2-1].GetPieceColor()==Board[R1-1][C1-1].GetPieceColor()&&Board[R2-1][C2-1].GetPieceType()!=Blank)
		return false;
	return true;
}



bool ChessBoard::RookValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a rook in that place
	if(Board[R1-1][C1-1].GetPieceType()!=Rook)
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
			if((Board[R1+(Dir_R*i)-1][C1+(Dir_C*i)-1].GetPieceType()!=Blank))
				return false;
		}
	}
	
	if(Board[R2-1][C2-1].GetPieceColor()==Board[R1-1][C1-1].GetPieceColor()&&Board[R2-1][C2-1].GetPieceType()!=Blank)//check that the space is blank or eatable
		return false;	
	
	return true;
}




bool ChessBoard::BishopValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a bishop in that place
	if(Board[R1-1][C1-1].GetPieceType()!=Bishop)
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
				if((Board[R1+(Dir_R*i)-1][C1+(Dir_C*i)-1].GetPieceType()!=Blank))
					return false;
			}
	}
	
	if(Board[R2-1][C2-1].GetPieceColor()==Board[R1-1][C1-1].GetPieceColor()&&Board[R2-1][C2-1].GetPieceType()!=Blank)//check that the space is blank or eatable
		return false;
	return true;
}
	
bool ChessBoard::KnightValidMove(int R1,int C1,int R2,int C2){
	//check that its in fact a knight in that place
	if(Board[R1-1][C1-1].GetPieceType()!=Knight)
		return false;
	
	//check that the move is in the Knight range of movement
	if(!(  
		(((std::abs(R1-R2)>=1)||std::abs(C1-C2)>=1)
		&&((std::abs(R1-R2)<=2)||std::abs(C1-C2)<=2))
		&&!((std::abs(R1-R2)==2)&&(std::abs(C1-C2)==2))
		&&((std::abs(R1-R2)+std::abs(C1-C2))==3)
	))
		return false;
	if(Board[R2-1][C2-1].GetPieceColor()==Board[R1-1][C1-1].GetPieceColor()&&Board[R2-1][C2-1].GetPieceType()!=Blank)//check that the space is blank or eatable
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
	if(Board[R1-1][C1-1].GetPieceColor()!=WhoseTurn)
		return false;
	if(Board[R1-1][C1-1].GetPieceType()==Blank)
		return false;
	if(IsValidMove(R1,C1,R2,C2)){//check if it is a valid move
		ChessPiece Tmp_P1=Board[R1-1][C1-1];
		ChessPiece Tmp_P2=Board[R2-1][C2-1];
		Board[R2-1][C2-1]=Board[R1-1][C1-1];
		Board[R1-1][C1-1].SetPieceType(Blank);
		if(WhoseTurn==White&&WhiteInCheck()){
			Board[R1-1][C1-1]=Tmp_P1;
			Board[R2-1][C2-1]=Tmp_P2;
			return false;
		}
		if(WhoseTurn==Black&&BlackInCheck()){
			Board[R1-1][C1-1]=Tmp_P1;
			Board[R2-1][C2-1]=Tmp_P2;
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
			if(Board[i-1][j-1].GetPieceType()==King&&Board[i-1][j-1].GetPieceColor()==White){
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
			if(Board[i-1][j-1].GetPieceType()==King&&Board[i-1][j-1].GetPieceColor()==Black){
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
			if(Board[i-1][j-1].GetPieceType()==King&&Board[i-1][j-1].GetPieceColor()==Black){
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
			if(Board[i-1][j-1].GetPieceType()==King&&Board[i-1][j-1].GetPieceColor()==White){
				if(std::abs(i-R)<=1&&std::abs(j-R)<=1)
					return true;
			}
		}
	}
	return false;
}

bool ChessBoard::IsValidMove(int R1,int C1,int R2, int C2){
	if(Board[R1-1][C1-1].GetPieceColor()==White){
		
		
		if(KnightValidMove(R1,C1,R2,C2)||BishopValidMove(R1,C1,R2,C2)||RookValidMove(R1,C1,R2,C2)||QueenValidMove(R1,C1,R2,C2)||KingValidMove(R1,C1,R2,C2)||PawnValidMove(R1,C1,R2,C2)){
			ChessPiece R1_C1_Piece=Board[R1-1][C1-1];
			ChessPiece R2_C2_Piece=Board[R2-1][C2-1];
			Board[R2-1][C2-1]=Board[R1-1][C1-1];
			Board[R1-1][C1-1].SetPieceType(Blank);
			if(WhiteInCheck()){
				Board[R1-1][C1-1]= R1_C1_Piece;
				Board[R2-1][C2-1]=R2_C2_Piece;
				return false;
			}
			Board[R1-1][C1-1]= R1_C1_Piece;
			Board[R2-1][C2-1]=R2_C2_Piece;
			return true;
		}
			
	}
	else if(Board[R1-1][C1-1].GetPieceColor()==Black){
		if(KnightValidMove(R1,C1,R2,C2)||BishopValidMove(R1,C1,R2,C2)||RookValidMove(R1,C1,R2,C2)||QueenValidMove(R1,C1,R2,C2)||KingValidMove(R1,C1,R2,C2)||PawnValidMove(R1,C1,R2,C2)){
			ChessPiece R1_C1_Piece=Board[R1-1][C1-1];
			ChessPiece R2_C2_Piece=Board[R2-1][C2-1];
			Board[R2-1][C2-1]=Board[R1-1][C1-1];
			if(BlackInCheck()){
				Board[R1-1][C1-1]= R1_C1_Piece;
				Board[R2-1][C2-1]=R2_C2_Piece;
				return false;
			}
			Board[R1-1][C1-1]= R1_C1_Piece;
			Board[R2-1][C2-1]=R2_C2_Piece;
			return true;
		}
	}
	
}
bool ChessBoard::BlackInCheckMate(){//checks if black is in checkmate
	if(!BlackInCheck())//if its not in check already it can never be in checkmate
		return false;
	for(int i=1;i<=8;i++){//go throught all the pieces,check if they are black, then move them temporarily and see if it is still in check, if not, return false
		for(int j=1;j<=8;j++){
			if(Board[i-1][j-1].GetPieceType()==Blank)
				continue;
			if(Board[i-1][j-1].GetPieceColor()==Black){
				for(int k=1;k<=8;k++){
					for(int l=1;l<=1;l++){
						if(IsValidMove(i,j,k,l))
						{
							ChessPiece i_j_Piece=Board[i-1][j-1];
							ChessPiece k_l_Piece=Board[k-1][l-1];
							Board[k-1][l-1]=Board[i-1][j-1];
							Board[i-1][j-1].SetPieceType(Blank);
							if(!BlackInCheck()){
								Board[i-1][j-1]=i_j_Piece;
								Board[k-1][l-1]=k_l_Piece;
								return false;
							}
							Board[i-1][j-1]=i_j_Piece;
							Board[k-1][l-1]=k_l_Piece;
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
			if(Board[i-1][j-1].GetPieceType()==Blank)
				continue;
			if(Board[i-1][j-1].GetPieceColor()==White){
				for(int k=1;k<=8;k++){
					for(int l=1;l<=1;l++){
						if(IsValidMove(i,j,k,l))
						{
							ChessPiece i_j_Piece=Board[i-1][j-1];
							ChessPiece k_l_Piece=Board[k-1][l-1];
							Board[k-1][l-1]=Board[i-1][j-1];
							Board[i-1][j-1].SetPieceType(Blank);
							if(!BlackInCheck()){
								Board[i-1][j-1]=i_j_Piece;
								Board[k-1][l-1]=k_l_Piece;
								return false;
							}
							Board[i-1][j-1]=i_j_Piece;
							Board[k-1][l-1]=k_l_Piece;
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
			if(Board[i-1][j-1].GetPieceType()==Blank){
				std::cout<<"bla ";
				continue;
			}
			if(Board[i-1][j-1].GetPieceColor()==White)
				std::cout<<"W";
			if(Board[i-1][j-1].GetPieceColor()==Black)
				std::cout<<"B";
			switch(Board[i-1][j-1].GetPieceType()){
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







//sdl part:

void ChessBoard::UpdateScreen(){
	SDL_Surface* S_Background=NULL;
	S_Background=SDL_LoadBMP("images/chessboard.bmp");
	SDL_BlitSurface(S_Background,NULL,S_Screen,NULL);
	SDL_UpdateWindowSurface(Window);
	SDL_FreeSurface(S_Background);
	SDL_Surface* S_Piece=NULL;
	SDL_Rect Rect;
	for(int i=0;i<8;i++){//put the correct image in each surface
		for(int j=0;j<8;j++){
			G_ChessPiecesTypes type = Board[i][j].GetPieceType();
			G_ChessPiecesColors color = Board[i][j].GetPieceColor();
			switch(type){
				case Rook:
					if(color==White) {
						S_Piece=SDL_LoadBMP("images/WhiteRook.bmp");
					} else {
						S_Piece=SDL_LoadBMP("images/BlackRook.bmp");
					}
					break;
				case King:
					if(color==White){
						S_Piece=SDL_LoadBMP("images/WhiteKing.bmp");
					}else{
						S_Piece=SDL_LoadBMP("images/BlackKing.bmp");
					}break;
				case Bishop:
					if(color==White)
						S_Piece=SDL_LoadBMP("images/WhiteBishop.bmp");
					else
						S_Piece=SDL_LoadBMP("images/BlackBishop.bmp");
					break;
				case Queen:
					if(color==White)
						S_Piece=SDL_LoadBMP("images/WhiteQueen.bmp");
					else
						S_Piece=SDL_LoadBMP("images/BlackQueen.bmp");
					break;
				case Knight:
					if(color==White)
						S_Piece=SDL_LoadBMP("images/WhiteKnight.bmp");
					else
						S_Piece=SDL_LoadBMP("images/BlackKnight.bmp");
					break;
				case Pawn:
					if(color==White)
						S_Piece=SDL_LoadBMP("images/WhitePawn.bmp");
					else
						S_Piece=SDL_LoadBMP("images/BlackPawn.bmp");
					break;
				default:
					continue;
			}
			if((i==0||i==2||i==4||i==6)&&(j==1||j==3||j==5||j==7)){
				G_BlackToWhite(S_Piece);
			}
			if((i==1||i==3||i==5||i==7)&&(j==0||j==2||j==4||j==6)){
				G_BlackToWhite(S_Piece);
			}
			int x = 79 * j;
			int y = 79 * i;
			Rect.x=x;
			Rect.y=y;
			SDL_BlitSurface(S_Piece,NULL,S_Screen,&Rect);
		}
	}
	SDL_FreeSurface(S_Piece);
	SDL_UpdateWindowSurface(Window);
}









#endif

