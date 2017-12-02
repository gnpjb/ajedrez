#include"main.h"

int main(int argc,char* argv[]){
	ChessBoard ChessGame;
	int R1,R2,C1,C2;
	while(!(ChessGame.BlackInCheckMate()||ChessGame.WhiteInCheckMate())){
		ChessGame.PrintChessBoard();
		std::cout<<"make a, make a, make a, move"<<std::endl;
		std::cout<<"enter piece tu move(row then column in number)"<<std::endl;
		std::cin>>R1,C2;
		std::cout<<"move to(row the column in numbers)"<<std::endl;
		std::cin>>R2,C2;
		ChessGame.MakeMove(R1,C1,R2,C2);
	}
	if(ChessGame.WhiteInCheckMate()){
		std::cout<<"white has lost"<<std::endl;
		return 0;
	}
	if(ChessGame.BlackInCheckMate()){
		std::cout<<"black has lost"<<std::endl;
		return 0;
	}
	else{
		std::cout<<"something went wrong"<<std::endl;
		return 1;
	}
}
