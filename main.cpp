#include"main.h"

using namespace std;

int main(int argc,char* argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	ChessBoard ChessGame;
	int R1,R2,C1,C2;
	bool Quit=false;
	SDL_Event Action;
	uint32_t FPS_Ticker;
	while(true){
		FPS_Ticker=SDL_GetTicks();
		ChessGame.UpdateScreen();
		if((ChessGame.BlackInCheckMate()||ChessGame.WhiteInCheckMate())){
			break;
		}
		SDL_WaitEvent(&Action);
		if(Action.type==SDL_QUIT){
			Quit=true;
		}
		if(Action.type==SDL_MOUSEBUTTONDOWN){
			R1=SquareDeduction(Action.button.y);
			C1=SquareDeduction(Action.button.x);
			cout<<"R1,C1="<<R1<<","<<C1<<endl;
			while(true){
				SDL_WaitEvent(&Action);
				if(Action.type==SDL_QUIT){
					Quit=true;
					break;
				}
				if(Action.type==SDL_MOUSEBUTTONDOWN){
					R2=SquareDeduction(Action.button.y);
					C2=SquareDeduction(Action.button.x);
					cout<<"R2,C2="<<R2<<","<<C2<<endl;
					break;
				}
			}
			
			
		}
		if(Quit==true){
			cout<<"Quitting"<<endl;
			break;
		}
		ChessGame.MakeMove(R1,C1,R2,C2);
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
