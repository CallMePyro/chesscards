#include "Chessboard.h"
#include "Player.h"
#include <iostream>
	using std::cout;
#include <cstdlib>
	using std::system;
#include <fstream>
	using std::ifstream;

/* Chess Cards
	Description:
		Game of chess, but you can only takes moves that are in your deck of cards.
		Basically a card game where the objective is to win a game of chess
	End Goals:
		Support for Player vs Player or Player vs Computer modes
*/

void MainMenu();
	void PlayerSelect();
		pstring SelectName();
		pstring SelectDeck();
		void PlayGame( Player & p1, Player & p2 );
	void AddDeck();
	void ViewStats();


int main()
{
	srand( NULL ); //SEED THE RAND!

	cout << "   _____ _                   " << '\n'
		 << "  / ____| |                  " << '\n'
		 << " | |    | |__   ___  ___ ___ " << '\n'
		 << " | |    | '_ \\ / _ \\/ __/ __|" << '\n'
		 << " | |____| | | |  __/\\__ \\__ \\" << '\n'
		 << "  \\_____|_| |_|\\___||___/___/" << '\n'
			 << "\t**The card game**\n\n\n";

	MainMenu();

	return 0;
}

void MainMenu()
{
	pstring res;
	cout << "**Main Menu**\n"
		<< "1. Play Game\n"
		<< "2. Create a custom deck.\n"
		<< "3. See stats\n"
		<< "4. Exit\n";
	cin >> res;
	do
	{
		switch( res[0] )
		{
			case '1': PlayerSelect(); break;
			case '2': AddDeck(); break;
			case '3': ViewStats();
			case '4': cout << "Exiting...\n"; break;
			default: cout << "Invalid option.\n";
		}
	} while( res[0] != '4' );
}

void PlayerSelect()
{
	cout << "Welcome Player 1! Please enter your name.\n";

	pstring name1 = SelectName();

	cout << "Nice to meet you " << name1 << "!\n"
		<< "Now you must choose your deck with which to do battle.\n";

	pstring deck1 = SelectDeck();

	cout << "Excellent! Now on to Player 2. Please enter your name.\n";
	pstring name2 = SelectName();
	cout << "Good, now tell me what deck you are using " << name2 << "!\n";
	pstring deck2 = SelectDeck();

	Player p1( name1, WHITE, deck1 );
	Player p2( name2, BLACK, deck2 );

	PlayGame( p1, p2 );
}

pstring SelectName()
{
	pstring name;
	char in;
	do
	{
		cin >> name;
		cout << "You have selected " << name << " as your name, are you sure?(y/n)\n";
		cin >> in;
		if( tolower( in ) != 'y' )
			cout << "No worries, simply type in your name again!\n";
	} while( tolower( in ) != 'y' );
	return name;
}

pstring SelectDeck()
{
	pstring name;
	ifstream file( "decklist.txt" );
	ifstream t;
	bool invalid = true;

	while( file >> name ) //print out every file in the list
		cout << '\t' << name << '\n';
	do
	{
		invalid = false;

		cin >> name;
		t.open( ( name + ".txt" ).begin() );

		if( !t.is_open() || name == "decklist" )
		{
			invalid = true;
			cout << "Could not find deck named " << name << ".Please enter a valid deck name.\n";
		}

	} while( invalid );

	file.close();
	return name + ".txt";
}

void PlayGame( Player & p1, Player & p2 )
{

	Chessboard cb;
	while( !cb.GameOver() )
	{
		system( "CLS" ); //clear the screen
		cout << cb.ToString( p1.GetSide() ); //print chessboard for player 1 orientation
		cb.Move( p1 ); //Player 1 moves
		system( "CLS" );
		cout << cb.ToString( p1.GetSide() );
		if( cb.GameOver() )
		{
			cout << "Player 1 wins!\n";
			break;
		}

		cout << p2.GetName() << "'s turn. ";
		system( "PAUSE" );

		system( "CLS" ); //clear the screen
		cout << cb.ToString( p2.GetSide() ); //print chessboard for player 2 orientation
		cb.Move( p2 ); //Player 2 moves
		system( "CLS" );
		cout << cb.ToString( p2.GetSide() );
		if( cb.GameOver() )
		{
			cout << "Player 2 wins!\n";
		}
		else
		{
			cout << p1.GetName() << "'s turn. ";
			system( "PAUSE" );
		}
	}
}

void ViewStats()
{

}

void AddDeck()
{

}