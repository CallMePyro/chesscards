#include "Chessboard.h"


//	[0,0]			[0,8]


//	[8,0]			[8,8]

//initial construciton of board.
Chessboard::Chessboard()
{
	for( int i = 0; i < 8; ++i ) //pawns
	{
		m_array[1][i] = Piece( PAWN, BLACK );
		m_array[6][i] = Piece( PAWN, WHITE );
	}
	//rooks
	m_array[0][0] = Piece( ROOK, BLACK );
	m_array[0][7] = Piece( ROOK, BLACK );
	m_array[7][0] = Piece( ROOK, WHITE );
	m_array[7][7] = Piece( ROOK, WHITE );
	//knights
	m_array[0][1] = Piece( KNIGHT, BLACK );
	m_array[0][6] = Piece( KNIGHT, BLACK );
	m_array[7][1] = Piece( KNIGHT, WHITE );
	m_array[7][6] = Piece( KNIGHT, WHITE );
	//bishops
	m_array[0][2] = Piece( BISHOP, BLACK );
	m_array[0][5] = Piece( BISHOP, BLACK );
	m_array[7][2] = Piece( BISHOP, WHITE );
	m_array[7][5] = Piece( BISHOP, WHITE );
	// Queen and King
	m_array[0][3] = Piece( KING, BLACK );
	m_array[0][4] = Piece( QUEEN, BLACK );
	m_array[7][3] = Piece( KING, WHITE );
	m_array[7][4] = Piece( QUEEN, WHITE );

}

//Take a piece struct and convert it to a character
char type_tostring( Piece p )
{
	char center;
	switch( p.type )
	{
		case PAWN: center = 'p'; break;
		case ROOK: center = 'r'; break;
		case KNIGHT: center = 'n'; break;
		case BISHOP: center = 'b'; break;
		case KING: center = 'k'; break;
		case QUEEN: center = 'q'; break;
		default: center = ' '; break;
	}
	return p.side == WHITE ? toupper( center ) : center; //uppercase if white side
}

char idx_to_row( short idx ) //convert row index to character
{
	return ( 8 - idx ) + '0';
}

short row_to_idx( char row ) //character to row index
{
	return 8 - ( row - '0' );
}

char idx_to_column( short idx ) //convert column index to character
{
	if( idx != 7 )
		return ( ( 8 * idx ) / 7 ) + 'a';
	else return 'h'; //darn integer division
}

short column_to_idx( char column ) //convert user input to column index
{
	return ( ( 7 * column ) / 8 ) - 84;
}

//invert a SPEC enum to be the opposite direction. This is used for black side moves to preserve orientation.
Card::SPEC InvertDir( Card::SPEC & s )
{
	switch( s )
	{
		case Card::N: return Card::S;
		case Card::NE: return Card::SW;
		case Card::E: return Card::W;
		case Card::SE: return Card::NW;
		case Card::S: return Card::N;
		case Card::SW: return Card::NE;
		case Card::W: return Card::E;
		case Card::NW: return Card::SE;
		default: return Card::NOSPEC;
	}
}

//convert a board to a string, based on the SIDE enum passed. Black side views inverted and upside down
pstring Chessboard::ToString( SIDE side ) const
{
	if( side == WHITE )
	{
		pstring str;
		for( short row = 0; row < 8; ++row )
		{
			str += "    #################################################\n";
			str += "    #     #     #     #     #     #     #     #     #\n";
			str += idx_to_row( row );
			str += "|  #"; //wow this is silly. Can't do these additions together because it's treated as pointer math instead of string concatenation.
			//Holy hard to fix bug, batman. That one took me like 30 minutes.
			//The worst part is that it still gives a valid result, as it gives a pointer to somewhere in the symbol table.
			for( short column = 0; column < 8; ++column )
			{
				str += "  ";
				str += type_tostring( m_array[row][column] );
				str += "  #";
			}

			str += "\n    #     #     #     #     #     #     #     #     #\n";
		}
		str += "    #################################################\n     ";
		for( short column = 0; column < 8; ++column )
		{
			str += "  ";
			str += idx_to_column( column );
			str += "   ";
		}
		str += '\n';
		return str;
	}
	else //side == BLACK
	{ //print chessboard inverted for black side so they don't have to think upside down and backwards
		pstring str;
		for( short row = 7; row >= 0; --row )
		{
			str += "    #################################################\n";
			str += "    #     #     #     #     #     #     #     #     #\n";
			str += idx_to_row( row );
			str += "|  #";
			for( short column = 7; column >= 0; --column )
			{
				str += "  ";
				str += type_tostring( m_array[row][column] );
				str += "  #";
			}

			str += "\n    #     #     #     #     #     #     #     #     #\n";
		}
		str += "    #################################################\n     ";
		for( short column = 7; column >= 0; --column )
		{
			str += "  ";
			str += idx_to_column( column );
			str += "   ";
		}
		str += '\n';
		return str;
	}
}

//This function handles moving a human player. It queries which piece to move, how far to move that piece, and then moves it.
//It also handles all exceptions and edge cases.
void Chessboard::MoveHuman( Player & ply )
{
	int idx = 0;
	bool * invalid = new bool[ply.GetHand().GetCards().size()]; //keep track of which cards are invalid
	bool all_invalid = true; //set to false if any non-valid piece is found
	for each( Card card in ply.GetHand().GetCards() )
	{
		if( !IsValidMove( ply.GetSide(), card ) )
		{
			cout << "Invalid: ";
			invalid[idx] = true;
		}
		else
		{
			invalid[idx] = false;
			all_invalid = false; //if we don't hit a valid card, then we ask the user to discard a card
		}
		cout << ++idx << ". " << card.ToString() << '\n';
	}

	if( all_invalid )
	{
		pstring input;
		int result;
		cout << "Since you can't play any cards, select a card to discard and draw another.\n";
		do
		{
			cin >> input;
			if( input.is_numeric() )
			{
				result = input.to_int() - 1;
				if( result >= 0 && (unsigned)result < ply.GetHand().GetCards().size() )
				{
					break; //we've got valid input, break out of loop
				}
				else
				{
					cout << "Please enter a number between 1 and " << idx << ".\n";
					continue;
				}
			}
			else
			{
				cout << "Please enter a valid number.\n";
				continue;
			}

		} while( true );

		ply.GetHand().Play( result, ply.GetGraveyard() ); //put card in graveyard

		if( ply.GetDeck().IsEmpty() ) //if we're out of cards then return all graveyard to deck
		{
			ply.GetGraveyard().ReturnToDeck( ply.GetDeck() );
			ply.GetDeck().Shuffle();
		}
		ply.GetHand().Draw( ply.GetDeck() ); //get new card;

		system( "CLS" ); //redraw game
		cout << ToString( ply.GetSide() );
		Move( ply ); //move again
	}
	else
	{
		pstring input;
		int result;
		do
		{
			cin >> input;
			if( input.len() != 1 )
			{
				cout << "Input too long. Input only one number.\n";
				continue;
			}
			else if( !isdigit( input[0] ) )
			{
				cout << "Please input a number.\n";
				continue;
			}
			result = input[0] - '0';
			result--;

			if( result < 0 || result >= idx || invalid[result] )
			{
				cout << "Invalid choice. Please choose another.\n";
				continue;
			}
			else break;


		} while( true );

		Card to_play = ply.GetHand().Play( result, ply.GetGraveyard() ); //puts card in graveyard then returns it so it can be affected to board
		if( ply.GetDeck().IsEmpty() ) //if we're out of cards then return all graveyard to deck
		{
			ply.GetGraveyard().ReturnToDeck( ply.GetDeck() );
			ply.GetDeck().Shuffle();
		}

		ply.GetHand().Draw( ply.GetDeck() ); //draw a new card

		Card::SPEC dir = to_play.GetSpec(); //direction the piece will move in

		//pawn can move 2 spaces N if it's the first move
		if( to_play.GetPiece() == PAWN )
		{
			short * pos = GetPiece( to_play, ply.GetSide() );
			int dist = 1;
			//if the pawn is in its home row
			if( ( ply.GetSide() == BLACK && pos[0] == 1 ) || ( ply.GetSide() == WHITE && pos[0] == 6 ) )
			{
				if( dir == Card::N || dir == Card::S ) //not taking a piece diagonally
					dist = GetDistance( pos[0], pos[1], dir );
			}

			if( PieceMoveResult( pos[0], pos[1], dist, dir ) == KING )
				m_end = true;

			MovePiece( pos[0], pos[1], dist, dir );
			delete[] pos;
		}
		//these units don't have variable move distances, so we can ignore choosing move distance
		else if( to_play.GetPiece() == KNIGHT || to_play.GetPiece() == KING )
		{
			short * pos = GetPiece( to_play, ply.GetSide() );

			if( PieceMoveResult( pos[0], pos[1], 1, dir ) == KING )
				m_end = true;

			MovePiece( pos[0], pos[1], 1, dir );
			delete[] pos;
		}
		else //every other unit we need to get their move distance once we choose the unit
		{
			short * pos = GetPiece( to_play, ply.GetSide() );
			int dist = GetDistance( pos[0], pos[1], dir ); //get the number of units to move the piece

			if( PieceMoveResult( pos[0], pos[1], dist, dir ) == KING )
				m_end = true;

			MovePiece( pos[0], pos[1], dist, dir );
			delete[] pos;
		}
	}
	delete[] invalid;
}

//This code handles moving AI
//It kills the most powerful piece it can, otherwise it moves the best piece to move.
void Chessboard::MoveAI( Player & ply )
{
	bool all_invalid = true;
	PIECE best_kill = NOPIECE;
	short pos[2] = { 0 };
	Card::SPEC to_use;
	int kill_dist = 0;
	for each( Card card in ply.GetHand().GetCards() )
	{
		if( IsValidMove( ply.GetSide(), card ) ) //for each valid card
		{
			all_invalid = false;
			for( short row = 0; row < 8; ++row )
			{
				for( short column = 0; column < 8; ++column )
				{
					if( m_array[row][column].side == ply.GetSide() && m_array[row][column].type == card.GetPiece() ) //for each piece of ours of the same type
					{
						int dist = GetPieceMaxDist( row, column, card.GetSpec() );
						PIECE kill = PieceMoveResult( row, column, dist, card.GetSpec() );
						if( kill > best_kill )
						{
							best_kill = kill;
							to_use = card.GetSpec();
							pos[0] = row;
							pos[1] = column;
							kill_dist = dist;
							if( kill == KING )
								break;
						}
					}
				}
			}
		}
	}
	if( best_kill != NOPIECE ) //we can make a kill
		MovePiece( pos[0], pos[1], kill_dist, to_use );
	else if( all_invalid )
	{
		ply.GetHand().Play( rand() % ply.GetHand().GetCards().size(), ply.GetGraveyard() ); //put random card in graveyard

		if( ply.GetDeck().IsEmpty() ) //if we're out of cards then return all graveyard to deck
		{
			ply.GetGraveyard().ReturnToDeck( ply.GetDeck() );
			ply.GetDeck().Shuffle();
		}
		ply.GetHand().Draw( ply.GetDeck() ); //get new card;
		Move( ply ); //move again
	}
	else //no kill moves but there are cards we can play
	{
		for each( Card card in ply.GetHand().GetCards() )
		{
			for( short row = 0; row < 8; ++row )
			{
				for( short column = 0; column < 8; ++column )
				{
					if( m_array[row][column].side == ply.GetSide() && m_array[row][column].type == card.GetPiece() )
					{
						if( PieceMoveResult( row, column, 1, card.GetSpec() ) != OOB )
						{
							if( card.GetPiece() == KNIGHT )
								MovePiece( row, column, 1, card.GetSpec() );
							else
								MovePiece( row, column, GetPieceMaxDist( row, column, card.GetSpec() ), card.GetSpec() ); //move is as far as possible cuz lazy AI
							break;
						}
					}
				}
			}
		}
	}
}

//simply determines which type of move function to call
void Chessboard::Move( Player & ply )
{
	if( ply.IsAI() )
		MoveAI( ply );
	else
		MoveHuman( ply );
}

//determines if s1 is the opposite side of s2
bool IsOpSide( SIDE s1, SIDE s2 )
{
	if( s1 == WHITE && s2 == BLACK ) return true;
	else if( s1 == BLACK && s2 == WHITE ) return true;
	else return false;
}

//returns the type of piece that the passed piece will move onto given the direction and distance
PIECE Chessboard::PieceMoveResult ( short row, short column, short dist, Card::SPEC dir ) const
{
	switch( m_array[row][column].type )
	{
		case PAWN:
			return CanMovePawn( row, column, dist, dir );
		case ROOK:
			return CanMoveRook( row, column, dist, dir );
		case KNIGHT:
			return CanMoveKnight( row, column, dir );
		case BISHOP:
			return CanMoveBishop( row, column, dist, dir );
		case QUEEN:
			return CanMoveQueen( row, column, dist, dir );
		case KING:
			return CanMoveQueen( row, column, dist, dir ); //King has same movement pattern as Queen
		default: return OOB;
	}
}

//determines if a card of a certain side has any valid moves on the board
bool Chessboard::IsValidMove( SIDE side, const Card & c ) const
{
	for( short row = 0; row < 8; ++row )
	{
		for( short column = 0; column < 8; ++column )
		{
			const Piece & pce = m_array[row][column]; //make the code look a bit nicer
			if( side == pce.side && pce.type == c.GetPiece() )
			{
				if( PieceMoveResult( row, column, 1, c.GetSpec() ) != OOB )
					return true;
			}
		}
	}
	return false; //if we got here, we never returned true on any of the 'CanMoves', so they all returned false
}

//queries the user for which piece to move once they select a card
short * Chessboard::GetPiece( const Card & c, SIDE side ) const
{
	short * pos = new short[2]; //this gets deleted by the calling function.
	int count = 0;

	for( short row = 0; row < 8; ++row ) //loop through pieces and count em.
	{
		for( short column = 0; column < 8; ++column )
		{
			if( m_array[row][column].type == c.GetPiece() && m_array[row][column].side == side )
			{
				count++;
				pos[0] = row;
				pos[1] = column;

				if( c.GetPiece() == KING || c.GetPiece() == QUEEN ) //if we know that there's only one of these pieces we can stop iterating
					break;
			}
		}
	}

	if( count == 1 ) //only one piece of our type then that's the only position we could use
		return pos;

	pstring input;

	cout << "Enter the column and row of the piece you'd like to move.\n";

	do
	{
		cin >> input;
		input.tolower();

		if( input.len() > 2 )
		{
			cout << "Input is too long. Column must be between 'a' and 'h'. Row must be between '1' and '8'.\n";
			continue;
		}
		else if( input.len() < 2 )
		{
			cout << "Input is too short. Column must be between 'a' and 'h'. Row must be between '1' and '8'.\n";
			continue;
		}

		if( isdigit( input[0] ) && isalpha( input[1] ) ) //detect flipped input
		{
			char t = input[0];
			input[0] = input[1];
			input[1] = t;
		}

		if( input[0] >= 'a' && input[0] <= 'h' && input[1] >= '1' && input[1] <= '8' ) //have valid input up to this point
		{
			pos[0] = row_to_idx( input[1] ); //flip em because chess notation says so
			pos[1] = column_to_idx( input[0] );

			if( m_array[pos[0]][pos[1]].side == NOSIDE )
			{
				cout << "That's an empty square.\n";
				continue;
			}
			else if( m_array[pos[0]][pos[1]].side != side )
			{
				cout << "You dont't own that piece!\n";
				continue;
			}
			else if( m_array[pos[0]][pos[1]].type != c.GetPiece() )
			{
				cout << "Wrong piece type selected.\n";
				continue;
			}
			else if( PieceMoveResult( pos[0], pos[1], 1, c.GetSpec() ) == OOB )
			{
				cout << "You can't move that piece\n";
				continue;
			}
			else break;
		}
		else
		{
			cout << "Invalid location selected.\n";
			continue;
		}

	} while( true );

	return pos; //got a valid array location that holds a piece of the right type and side
}

//Moves a piece from one location to another based on location, distance, and direction
void Chessboard::MovePiece( short row, short column, short dist, Card::SPEC dir )
{
	if( m_array[row][column].side == BLACK )
		dir = InvertDir( dir );

	if( PieceMoveResult( row, column, dist, dir ) == KING )
		m_end = true;

	switch( m_array[row][column].type )
	{
		case PAWN: MovePawn( row, column, dist, dir ); break;
		case ROOK: MoveRook( row, column, dist, dir ); break;
		case KNIGHT: MoveKnight( row, column, dir ); break;
		case BISHOP: MoveBishop( row, column, dist, dir ); break;
		case QUEEN: MoveQueen( row, column, dist, dir ); break;
		case KING: MoveQueen( row, column, 1, dir ); break; //king moves same way as queen, just 1 space only
	}
	m_array[row][column] = Piece(); //empty square where the piece was
}

//Determines how far a piece can possibly be moved. Used for 'GetDistance' function that asks the user how many units to move a piece
short Chessboard::GetPieceMaxDist( short row, short column, Card::SPEC dir ) const
{
	switch( m_array[row][column].type )
	{
		case PAWN:
			if( ( m_array[row][column].side == BLACK && row == 1 ) || ( m_array[row][column].side == WHITE && row == 6 ) )
				if( dir == Card::N || dir == Card::S ) //not taking a piece diagonally
					return CanMovePawn( row, column, 2, dir ) != OOB ? 2 : 1;
			else return 1;
		case ROOK: return RookMoveDistance( row, column, dir );
		case BISHOP: return BishopMoveDistance( row, column, dir );
		case QUEEN: return QueenMoveDistance( row, column, dir );
		default: return -1;
	}
}

//Asks the user how many units to move a piece if they have more than 1 choice
short Chessboard::GetDistance( short row, short column, Card::SPEC dir ) const
{
	short max = GetPieceMaxDist( row, column, dir );
	if( max == 1 ) return 1; //dont bother asking if they have no choices

	cout << "You may move this piece " << ( max == 2 ? "either 1 or " : "between 1 and " ) << max << " squares.\nHow many squares would you like to move it?\n";

	pstring input;

	do
	{
		cin >> input;
		if( input.len() != 1 )
		{
			cout << "Input too long.\n";
			continue;
		}
		else if( input[0] < '1' || input[0] > max + '0' )
		{
			cout << "Please enter a number between 1 and " << max << ".\n";
			continue;
		}
		else //good input
		{
			max = input[0] - '0';
			break;
		}
	} while( true );
	return max;
}

//
// Prepare yourself for some gnarly code
//

//determines how far a rook can move, used for determining max move distance
short Chessboard::RookMoveDistance( short row, short column, Card::SPEC dir ) const
{
	short ret = 1; //we must be able to move atleast one square or we couldn't be here
	for( short i = 2; i < 7; ++i )
	{
		PIECE res = CanMoveRook( row, column, i, dir );
		if( res == NOPIECE ) //empty space
			ret++; //add 1 and keep going
		else if( res != OOB ) //found an emey
			return ret + 1; //add 1 and stop
		else
			return ret; //we can't go to this square, so stop at previous square
	}
	return ret; //literally can never get here but compiler yells at me so whatever
}

//determines how far a bishop can move, used for determining max move distance
short Chessboard::BishopMoveDistance( short row, short column, Card::SPEC dir ) const
{
	short ret = 1;
	for( short i = 2; i < 7; ++i )
	{
		PIECE res = CanMoveBishop( row, column, i, dir );
		if( res == NOPIECE )
			ret++;
		else if( res != OOB )
			return ret + 1;
		else
			return ret;
	}
	return ret;
}

//determines how far a queen/king can move, used for determining max move distance
short Chessboard::QueenMoveDistance( short row, short column, Card::SPEC dir ) const
{
	switch( dir )
	{
		case Card::N: return RookMoveDistance( row, column, dir );
		case Card::S: return RookMoveDistance( row, column, dir );
		case Card::E: return RookMoveDistance( row, column, dir );
		case Card::W: return RookMoveDistance( row, column, dir );
		default: return BishopMoveDistance( row, column, dir );
	}
}

//moves a pawn at a certain row and column a certain distance in a certain direction
void Chessboard::MovePawn( short row, short column, short dist, Card::SPEC dir )
{
	MoveQueen( row, column, dist, dir );
}

//moves a knight at a certain row and column a certain distance in a certain direction
void Chessboard::MoveKnight( short row, short column, Card::SPEC dir )
{
	switch( dir )
	{
		case Card::N: //up then right
			m_array[row - 2][column + 1] = m_array[row][column]; break;
		case Card::NE: //right then up
			m_array[row - 1][column + 2] = m_array[row][column]; break;
		case Card::E: //right then down
			m_array[row + 1][column + 2] = m_array[row][column]; break;
		case Card::SE: //down then right
			m_array[row + 2][column + 1] = m_array[row][column]; break;
		case Card::S: //down then left
			m_array[row + 2][column - 1] = m_array[row][column]; break;
		case Card::SW: //left then down
			m_array[row + 1][column - 2] = m_array[row][column]; break;
		case Card::W: //left then up
			m_array[row - 1][column - 2] = m_array[row][column]; break;
		case Card::NW: //up then left
			m_array[row - 2][column - 1] = m_array[row][column]; break;
	}
}

//moves a rook at a certain row and column a certain distance in a certain direction
void Chessboard::MoveRook( short row, short column, short dist, Card::SPEC dir )
{
	switch( dir )
	{
		case Card::N:
			m_array[row - dist][column] = m_array[row][column]; break;
		case Card::E:
			m_array[row][column + dist] = m_array[row][column]; break;
		case Card::S:
			m_array[row + dist][column] = m_array[row][column]; break;
		case Card::W:
			m_array[row][column - dist] = m_array[row][column]; break;
	}
}

//moves a bishop at a certain row and column a certain distance in a certain direction
void Chessboard::MoveBishop( short row, short column, short dist, Card::SPEC dir )
{
	switch( dir )
	{
		case Card::NW:
			m_array[row - dist][column - dist] = m_array[row][column]; break;
		case Card::NE:
			m_array[row - dist][column + dist] = m_array[row][column]; break;
		case Card::SE:
			m_array[row + dist][column + dist] = m_array[row][column]; break;
		case Card::SW:
			m_array[row + dist][column - dist] = m_array[row][column]; break;
	}
}

//moves a queen or king at a certain row and column a certain distance in a certain direction
void Chessboard::MoveQueen( short row, short column, short dist, Card::SPEC dir )
{
	if( dir == Card::N || dir == Card::S || dir == Card::E || dir == Card::W )
		MoveRook( row, column, dist, dir );
	else
		MoveBishop( row, column, dist, dir );
}

//returns the PIECE type that a pawn would move onto if it tried to make a move in a certain direction
PIECE Chessboard::CanMovePawn( short row, short column, short dist, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::N:
			if( row - dist < 0 )
				return OOB;
			if( m_array[row - dist][column].side == NOSIDE ) //piece infront is empty
				return NOPIECE;
			return OOB;
		case Card::NW:
			if( row == 0 || column == 0 )
				return OOB;
			if( IsOpSide( s, m_array[row - 1][column - 1].side ) )
				return m_array[row - 1][column - 1].type;
			return OOB;
		case Card::NE:
			if( row == 0 || column == 7 )
				return OOB;
			if( IsOpSide( s, m_array[row - 1][column + 1].side ) )
				return m_array[row - 1][column + 1].type;
			return OOB;
		case Card::S:
			if( row + dist > 7 )
				return OOB;
			if( m_array[row + dist][column].side == NOSIDE ) //if black side moves a pawn 'north' it becomes south, so we have to account for black side moves here
				return NOPIECE;
			return OOB;
		case Card::SE:
			if( row == 7 || column == 7 )
				return OOB;
			if( IsOpSide( s, m_array[row + 1][column + 1].side ) )
				return m_array[row + 1][column + 1].type;
			return OOB;
		case Card::SW:
			if( row == 7 || column == 0 )
				return OOB;
			if( IsOpSide( s, m_array[row + 1][column - 1].side ) )
				return m_array[row + 1][column - 1].type;
			return OOB;
		default: return OOB;
	}
}

//returns the PIECE type that a rook would move onto if it tried to make a move in a certain direction
PIECE Chessboard::CanMoveRook( short row, short column, short dist, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::N:
			if( row - dist < 0 )
				return OOB;
			if( s != m_array[row - dist][column].side )
				return m_array[row - dist][column].type;
			return OOB;
		case Card::E:
			if( column + dist > 7 )
				return OOB;
			if( s != m_array[row][column + dist].side )
				return m_array[row][column + dist].type;
			return OOB;
		case Card::S:
			if( row + dist > 7 )
				return OOB;
			if( s != m_array[row + dist][column].side )
				return m_array[row + dist][column].type;
			return OOB;
		case Card::W:
			if( column - dist < 0 )
				return OOB;
			if( s != m_array[row][column - dist].side )
				return m_array[row][column - dist].type;
			return OOB;
		default: return OOB;
	}
}

//returns the PIECE type that a knight would move onto if it tried to make a move in a certain direction
PIECE Chessboard::CanMoveKnight( short row, short column, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::N: //up then right
			if( row < 2 || column == 7 )
				return OOB;
			if( s != m_array[row - 2][column + 1].side )
				return m_array[row - 2][column + 1].type;
			return OOB;
		case Card::NE: //right then up
			if( row == 0 || column > 5 )
				return OOB;
			if( s != m_array[row - 1][column + 2].side )
				return m_array[row - 1][column + 2].type;
			return OOB;
		case Card::E: //right then down
			if( row == 7 || column > 5 )
				return OOB;
			if( s != m_array[row + 1][column + 2].side )
				return m_array[row + 1][column + 2].type;
			return OOB;
		case Card::SE: //down then right
			if( row > 5 || column == 7 )
				return OOB;
			if( s != m_array[row + 2][column + 1].side )
				return m_array[row + 2][column + 1].type;
			return OOB;
		case Card::S: //down then left
			if( row > 5 || column == 0 )
				return OOB;
			if( s != m_array[row + 2][column - 1].side )
				return m_array[row + 2][column + 1].type;
			return OOB;
		case Card::SW: //left then down
			if( row == 7 || column < 2 )
				return OOB;
			if( s != m_array[row + 1][column - 2].side )
				return m_array[row + 1][column - 2].type;
			return OOB;
		case Card::W: //left then up
			if( row == 0 || column < 2 )
				return OOB;
			if( s != m_array[row - 1][column - 2].side )
				return m_array[row - 1][column - 2].type;
			return OOB;
		case Card::NW: //up then left
			if( row < 2 || column == 0 )
				return OOB;
			if( s != m_array[row - 2][column - 1].side )
				return m_array[row - 2][column - 1].type;
			return OOB;
		default: return OOB;
	}
}

//returns the PIECE type that a bishop would move onto if it tried to make a move in a certain direction
PIECE Chessboard::CanMoveBishop( short row, short column, short dist, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::NW:
			if( row - dist < 0 || column - dist < 0 )
				return OOB;
			if( s != m_array[row - dist][column - dist].side )
				return m_array[row - dist][column - dist].type;
			return OOB;
		case Card::NE:
			if( row - dist < 0 || column + dist > 7 )
				return OOB;
			if( s != m_array[row - dist][column + dist].side )
				return m_array[row - dist][column + dist].type;
			return OOB;
		case Card::SE:
			if( row + dist > 7 || column + dist > 7 )
				return OOB;
			if( s != m_array[row + dist][column + dist].side )
				return m_array[row + dist][column + dist].type;
			return OOB;
		case Card::SW:
			if( row + dist > 7 || column - dist < 0 )
				return OOB;
			if( s != m_array[row + dist][column - dist].side )
				return m_array[row + dist][column - dist].type;
			return OOB;
		default: return OOB;
	}
}

//returns the PIECE type that a queen or king would move onto if it tried to make a move in a certain direction
PIECE Chessboard::CanMoveQueen( short row, short column, short dist, Card::SPEC dir ) const
{
	if( dir == Card::N || dir == Card::S || dir == Card::E || dir == Card::W )
		return CanMoveRook( row, column, dist, dir );
	else
		return CanMoveBishop( row, column, dist, dir );
}