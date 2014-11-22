#include "Chessboard.h"
#include "Player.h"
#include <iostream>
	using std::cout;
#include <cstdlib>
	using std::system;
#include <fstream>
	using std::ifstream;
	using std::ofstream;
	using std::ios;
#include "pvector.h"


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
	void RemoveDeck();
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
	do
	{
		cout << "**Main Menu**\n"
			<< "1. Play Game\n"
			<< "2. Add a custom deck.\n"
			<< "3. Exit\n";
		cin >> res;
		switch( res[0] )
		{
			case '1': 
				system( "CLS" );
				PlayerSelect(); 
				break;
			case '2':
				system( "CLS" );
				AddDeck();
				break;
			case '3':
				exit( 0 ); //oh baby
			default: 
				system( "CLS" );
				cout << "Invalid option.\n";
				break;
		}
	} while( true );
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
	cout << "Now tell me what deck you are using, " << name2 << ".\n";
	pstring deck2 = SelectDeck();

	Player p1( name1, WHITE, deck1, name1.tolower() == "ai" );
	Player p2( name2, BLACK, deck2, name2.tolower() == "ai" );

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
	pstring input;
	ifstream t;
	bool invalid = true;
	int idx = 0;
	pvector<pstring> opts;

	ifstream decklist( "decklist.txt" );
	while( decklist >> input ) //print out every file in the list
	{
		cout << '\t' << ++idx  << ". " << input << '\n';
		opts.push_back( input );
	}
	decklist.close();

	do
	{
		cin >> input;
		if( input.is_numeric() )
		{
			int res = input.to_int() - 1;
			if( res >= 0 && (unsigned)res < opts.size() )
			{
				system( "CLS" );
				return opts[res] + ".txt";
			}
			else
			{
				cout << "Please select a valid option.\n";
				continue;
			}
		}
		else
		{
			cout << input << " Please input a valid number.\n";
			continue;
		}
	} while( true );
	return input;
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
			cout << p1.GetName() << " wins!\n";
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
			cout << p2.GetName() << " wins!\n";
		}
		else
		{
			cout << p1.GetName() << "'s turn. ";
			system( "PAUSE" );
		}
	}
}

void AddDeck()
{
	cout << "Please enter a name for your deck.\n";

	pstring name;
	char in;
	do
	{
		cin >> name;
		cout << "You have selected " << name << " as the name for your deck, are you sure?(y/n)\n";
		cin >> in;
		if( tolower( in ) != 'y' )
			cout << "No worries, simply type in the deck name again!\n";
	} while( tolower( in ) != 'y' );

	ifstream ifile( ( name + ".txt" ).begin() );
	if( ifile.is_open() )
	{
		char c;
		cout << "The deck " << name << " already exists. Are you sure you want to overwrite it?(y/n)\n";
		cin >> c;
		if( tolower( c ) != 'y' )
		{
			ifile.close();
			system( "CLS" );
			cout << "Deck has been finalized!\n";
		}
	}
	else
	{
		ofstream decklist( "decklist.txt", ios::app );
		decklist << name + '\n';
		decklist.close();
	}

	cout << "Now start adding cards! Simply type a card type and then direction and the card will be added to your deck.\n"
		<< "Type 'done' when you're done adding cards to the deck.\n";

	ofstream file( ( name + ".txt" ).begin() );

	pstring ptype, pdir;
	while( cin >> ptype )
	{
		if( ptype.tolower() == "done" )
			break;
		cin >> pdir;

		PIECE type = Deck::GetPiece( ptype );
		Card::SPEC dir = Deck::GetSpec( pdir );

		if( type == NOPIECE )
			cout << "Invalid piece entered.\n";
		else if( dir == Card::NOSPEC )
			cout << "Invalid direction entered.\n";
		else
		{
			cout << Card( type, dir ).ToString() << " has been added to your deck.\n";
			file << ptype << ' ' << pdir << '\n';
		}
	}
	system( "CLS" );
	cout << "Deck has been finalized!\n";
	file.close();
}