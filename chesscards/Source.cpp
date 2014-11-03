#include "Chessboard.h"
#include "Player.h"
#include <iostream>
	using std::cout;
#include <cstdlib>
	using std::system;

/* Chess Cards
	Description:
		Game of chess, but you can only takes moves that are in your deck of cards.
		Basically a card game where the objective is to win a game of chess
	End Goals:
		Support for Player vs Player or Player vs Computer modes
*/

void PlayGame( Player & p1, Player & p2 );

int main()
{
	cout << "   _____ _                   " << '\n';
	cout << "  / ____| |                  " << '\n';
	cout << " | |    | |__   ___  ___ ___ " << '\n';
	cout << " | |    | '_ \\ / _ \\/ __/ __|" << '\n';
	cout << " | |____| | | |  __/\\__ \\__ \\" << '\n';
	cout << "  \\_____|_| |_|\\___||___/___/" << '\n';
	cout << "\t**The card game**\n\n\n";

	cout << "Welcome Player 1! Please enter your name.\n";
	pstring name1, deck1;
	char in;
	do
	{
		cin >> name1;
		cout << "You have selected " << name1 << " as your name, are you sure?(y/n)\n";
		cin >> in;
		if( tolower( in ) != 'y' )
			cout << "No worries, simply type in your name again!\n";
	} while( tolower( in ) != 'y' );

	cout << "Excellent! Nice to meet you " << name1 << ".\n"
		<< "Now you must choose your deck with which to do battle.\n";
	//cin >> deck1;
	deck1 = "allinvalid.txt";

	pstring name2, deck2;
	cout << "Perfect! Now time for Player 2. Tell us, what is your name?\n";
	do
	{
		cin >> name2;
		cout << "You have selected " << name2 << " as your name, are you sure?(y/n)\n";
		cin >> in;
		if( tolower( in ) != 'y' )
			cout << "No worries, simply type in your name again!\n";
	} while( tolower( in ) != 'y' );

	cout << "Good, now you must tell me what deck you are using!\n";
	//cin >> deck2;
	deck2 = "allinvalid.txt";

	Player p1( name1, WHITE, deck1 );
	Player p2( name2, BLACK, deck2 );


	PlayGame( p1, p2 );

	return 0;
}

void PlayGame( Player & p1, Player & p2 )
{

	Chessboard cb;
	pstring r; //just holds some random characters so they can switch turns
	while( !cb.GameOver() )
	{
		system( "CLS" ); //clear the screen
		cout << cb.ToString( p1.GetSide() ); //print chessboard for player 1 orientation
		cb.Move( p1 ); //Player 1 moves
		if( cb.GameOver() )
		{
			cout << "Player 1 wins!\n";
			break;
		}

		system( "CLS" );

		cout << p2.GetName() << "'s turn. Have them type something when they're ready to take their turn.\n";
		cin >> r;

		system( "CLS" ); //clear the screen
		cout << cb.ToString( p2.GetSide() ); //print chessboard for player 2 orientation
		cb.Move( p2 ); //Player 2 moves
		if( cb.GameOver() )
		{
			cout << "Player 2 wins!\n";
		}
		else
		{
			system( "CLS" );
			cout << p1.GetName() << "'s turn. Have them type something when they're ready to take their turn.\n";
			cin >> r;
			r = "";
		}
	}
}