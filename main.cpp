#include"main.h"

using namespace std;

int main(int argc,char* argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	ChessBoard ChessGame;
	int R1,R2,C1,C2;
	string Input1;
	string Input2;
	while(!(ChessGame.BlackInCheckMate()||ChessGame.WhiteInCheckMate())){
		ChessGame.UpdateScreen();
		ChessGame.PrintChessBoard();
		cout<<"make a, make a, make a, move"<<ChessGame.GetWhoseTurn()<<endl;
		cout<<"enter row of the piece"<<endl;
		cin>>R1;
		cout<<"enter column of the piece"<<endl;
		cin>>C1;
		cout<<"enter row to move to"<<endl;
		cin>>R2;
		cout<<"enter column to move to"<<endl;
		cin>>C2;
		ChessGame.MakeMove(R1,C1,R2,C2);
		cout<<endl<<R1<<R2<<C1<<C2<<endl;
	}
	if(ChessGame.WhiteInCheckMate()){
		cout<<"white has lost"<<endl;
		return 0;
	}
	if(ChessGame.BlackInCheckMate()){
		cout<<"black has lost"<<endl;
		return 0;
	}
	else{
		cout<<"something went wrong"<<endl;
		return 1;
	}
	SDL_Quit();
}
