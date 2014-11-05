#include "Chessboard.h"


//	[0,0]			[0,8]


//	[8,0]			[8,8]

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
	return p.side == WHITE ? toupper( center ) : center;
}

char idx_to_row( short idx )
{
	return ( 8-idx ) + '0';
}

short row_to_idx( char row )
{
	return 8 - ( row - '0' );
}

char idx_to_column( short idx )
{
	if( idx != 7 )
		return ( ( 8*idx ) / 7 ) + 'a';
	else return 'h'; //darn integer division
}

short column_to_idx( char column )
{
	return ( ( 7*column ) / 8 ) - 84;
}

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

bool Chessboard::GameOver() const
{
	short count = 0;
	for( short row = 0; row < 8; ++row )
	{
		for( short column = 0; column < 8; ++column )
		{
			if( m_array[row][column].type == KING )
				count++;
		}
	}
	return count != 2; //if there's not two kings game is over
}

void Chessboard::Move( Player & ply )
{
	int idx = 0;
	bool * invalid = new bool[ply.GetHand().GetCards().size()]; //keep track of which cards are invalid
	bool all_invalid = true;
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
		cout << "Since you can't play any cards, select a card to discard and draw another.\n";
		int result;
		do
		{
			cin >> result;
			result--;
			if( result < 0 || result > idx )
				cout << "Invalid choice. Please choose another.\n";

		} while( result < 0 || result > idx );
		ply.GetHand().Play( result, ply.GetGraveyard() ); //put card in graveyard

		if( ply.GetDeck().IsEmpty() ) //if we're out of cards then return all graveyard to deck
		{
			ply.GetGraveyard().ReturnToDeck( ply.GetDeck() );
			ply.GetDeck().Shuffle();
		}
		ply.GetHand().Draw( ply.GetDeck() ); //get new card;

		system( "CLS" ); //redraw game
		cout << this->ToString( ply.GetSide() );
		this->Move( ply ); //move again
	}
	else
	{
		pstring input;
		int result;
		bool valid = false;
		do
		{
			valid = true;
			cin >> input;
			if( input.len() != 1 )
			{
				valid = false;
				cout << "Input too long. Input only one number.\n";
			}
			else if( !isdigit( input[0] ) )
			{
				valid = false;
				cout << "Please input a number.\n";
			}
			result = input[0] - '0';
			result--;

			if( valid )
			{
				if( result < 0 || result >= idx || invalid[result] )
				{
					valid = false;
					cout << "Invalid choice. Please choose another.\n";
				}
				else
				{
					valid = true;
				}
			}


		} while( !valid );

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
			MovePiece( pos[0], pos[1], dist, dir );
			delete [] pos;
		}
		//these units don't have variable move distances, so we can ignore choosing move distance
		else if( to_play.GetPiece() == KNIGHT || to_play.GetPiece() == KING )
		{
			short * pos = GetPiece( to_play, ply.GetSide() );
			MovePiece( pos[0], pos[1], 1, dir );
			delete [] pos;
		}
		else //every other unit we need to get their move distance once we choose the unit
		{
			short * pos = GetPiece( to_play, ply.GetSide() );
			int dist = GetDistance( pos[0], pos[1], dir ); //get the number of units to move the piece
			MovePiece( pos[0], pos[1], dist, dir );
			delete [] pos;
		}
	}

	delete [] invalid;
}

bool IsOpSide( SIDE s1, SIDE s2 )
{
	if( s1 == WHITE && s2 == BLACK ) return true;
	else if( s1 == BLACK && s2 == WHITE ) return true;
	else return false;
}

bool Chessboard::CanPieceMove( short row, short column, Card::SPEC dir ) const
{
	switch( m_array[row][column].type )
	{
		case PAWN:
			return CanMovePawn( row, column, 1, dir ) != SELF_NIL;
		case ROOK:
			return CanMoveRook( row, column, 1, dir ) != SELF_NIL;
		case KNIGHT:
			return CanMoveKnight( row, column, dir ) != SELF_NIL;
		case BISHOP:
			return CanMoveBishop( row, column, 1, dir ) != SELF_NIL;
		case QUEEN:
			return CanMoveQueen( row, column, 1, dir ) != SELF_NIL;
		case KING:
			return CanMoveQueen( row, column, 1, dir ) != SELF_NIL; //King has same movement pattern as Queen
		default: return false;
	}
}

bool Chessboard::IsValidMove( SIDE side, const Card & c ) const
{
	for( short row = 0; row < 8; ++row )
	{
		for( short column = 0; column < 8; ++column )
		{
			const Piece & pce = m_array[row][column]; //make the code look a bit nicer
			if( side == pce.side && pce.type == c.GetPiece() )
			{
				if( CanPieceMove( row, column, c.GetSpec() ) )
					return true;
			}
		}
	}
	return false; //if we got here, we never returned true on any of the 'CanMoves', so they all returned false
}

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

	bool invalid = false;
	pstring input;

	cout << "Enter the column and row of the piece you'd like to move.\n";

	do
	{
		invalid = false;
		cin >> input;
		input.tolower();

		if( input.len() > 2 )
		{
			invalid = true;
			cout << "Input is too long. Column must be between 'a' and 'h'. Row must be between '1' and '8'.\n";
		}
		else if( input.len() < 2 )
		{
			invalid = true;
			cout << "Input is too short. Column must be between 'a' and 'h'. Row must be between '1' and '8'.\n";
		}

		if( !invalid && isdigit( input[0] ) && isalpha( input[1] ) ) //detect flipped input
		{
			char t = input[0];
			input[0] = input[1];
			input[1] = t;
		}

		if( !invalid && input[0] >= 'a' && input[0] <= 'h' && input[1] >= '1' && input[1] <= '8' ) //have valid input up to this point
		{
			pos[0] = row_to_idx( input[1] ); //flip em because chess notation says so
			pos[1] = column_to_idx( input[0] );

			if( m_array[pos[0]][pos[1]].side != side )
			{
				invalid = true;
				cout << "You dont't own that piece!\n";
			}
			else if( m_array[pos[0]][pos[1]].type != c.GetPiece() )
			{
				invalid = true;
				cout << "Wrong piece type selected.\n";
			}
			else if( !CanPieceMove( pos[0], pos[1], c.GetSpec() ) )
			{
				invalid = true;
				cout << "You can't move that piece\n";
			}
			else
				invalid = false;
		}
		else
		{
			invalid = true;
			cout << "Invalid location selected.\n";
		}

	} while( invalid );

	return pos; //got a valid array location that holds a piece of the right type and side
}

void Chessboard::MovePiece( short row, short column, short dist, Card::SPEC dir )
{
	if( m_array[row][column].side == BLACK )
		dir = InvertDir( dir );

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

short Chessboard::GetDistance( short row, short column, Card::SPEC dir ) const
{
	short max = 1;

	switch( m_array[row][column].type )
	{
		case PAWN: max = CanMovePawn( row, column, 2, dir ) != SELF_NIL ? 2 : 1; break;
		case ROOK: max = RookMoveDistance( row, column, dir ); break;
		case BISHOP: max = BishopMoveDistance( row, column, dir); break;
		case QUEEN: max = QueenMoveDistance( row, column, dir ); break;
	}

	if( max == 1 ) return 1;
	cout << "You may move this piece between 1 and " << max << " squares.\nHow many squares would you like to move it?\n";

	pstring input;
	bool invalid = true;

	do
	{
		cin >> input;
		if( input.len() != 1 )
		{
			cout << "Input too long.\n";
			invalid = true;
		}
		else if( input[0] < '1' || input[0] > max + '0' )
		{
			cout << "Please enter a number between 1 and " << max << ".\n";
			invalid = true;
		}
		else //good input
		{
			invalid = false;
			max = input[0] - '0';
		}
	} while( invalid );
	return max;
}

//
// Prepare yourself for some gnarly code
//

short Chessboard::RookMoveDistance( short row, short column, Card::SPEC dir ) const
{
	short ret = 1; //we must be able to move atleast one square or we couldn't be here
	for( short i = 2; i < 7; ++i )
	{
		MOVE_RESULT res = CanMoveRook( row, column, i, dir );
		if( res == EMPTY )
			ret++; //add 1 and keep going
		else if( res == ENEMY )
			return ret+1; //add 1 and stop
		else
			return ret; //we can't go to this square, so stop at previous square
	}
	return ret;
}

short Chessboard::BishopMoveDistance( short row, short column, Card::SPEC dir ) const
{
	short ret = 1;
	for( short i = 2; i < 7; ++i )
	{
		MOVE_RESULT res = CanMoveBishop( row, column, i, dir );
		if( res == EMPTY )
			ret++;
		else if( res == ENEMY )
			return ret + 1;
		else
			return ret;
	}
	return ret;
}

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

void Chessboard::MovePawn( short row, short column, short dist, Card::SPEC dir )
{
	MoveQueen( row, column, dist, dir );
}

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

void Chessboard::MoveRook( short row, short column, short dist, Card::SPEC dir )
{
	switch( dir )
	{
		case Card::N:
			m_array[row-dist][column] = m_array[row][column]; break;
		case Card::E:
			m_array[row][column+dist] = m_array[row][column]; break;
		case Card::S:
			m_array[row+dist][column] = m_array[row][column]; break;
		case Card::W:
			m_array[row][column-dist] = m_array[row][column]; break;
	}
}

void Chessboard::MoveBishop( short row, short column, short dist, Card::SPEC dir )
{
	switch( dir )
	{
		case Card::NW:
			m_array[row-dist][column-dist] = m_array[row][column]; break;
		case Card::NE:
			m_array[row-dist][column+dist] = m_array[row][column]; break;
		case Card::SE:
			m_array[row+dist][column+dist] = m_array[row][column]; break;
		case Card::SW:
			m_array[row+dist][column-dist] = m_array[row][column]; break;
	}
}

void Chessboard::MoveQueen( short row, short column, short dist, Card::SPEC dir )
{
	switch( dir )
	{
		case Card::N:
			MoveRook( row, column, dist, dir ); break;
		case Card::S:
			MoveRook( row, column, dist, dir ); break;
		case Card::E:
			MoveRook( row, column, dist, dir ); break;
		case Card::W:
			MoveRook( row, column, dist, dir ); break;
		default: MoveBishop( row, column, dist, dir );
	}
}

MOVE_RESULT Chessboard::CanMovePawn( short row, short column, short dist, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::N:
			if( row - dist < 0 ) 
				return SELF_NIL;
			if( m_array[row-dist][column].side == NOSIDE ) //piece infront is empty
				return EMPTY;
			return SELF_NIL;
		case Card::NW:
			if( row == 0 || column == 0 )
				return SELF_NIL;
			if( IsOpSide( s, m_array[row-1][column-1].side ) )
				return ENEMY;
			return SELF_NIL;
		case Card::NE:
			if( row == 0 || column == 7 )
				return SELF_NIL;
			if( IsOpSide( s, m_array[row-1][column+1].side ) )
				return ENEMY;
			return SELF_NIL;
		case Card::S:
			if( row + dist > 7 )
				return SELF_NIL;
			if( m_array[row+dist][column].side == NOSIDE ) //if black side moves a pawn 'north' it becomes south, so we have to account for black side moves here
				return EMPTY;
			return SELF_NIL;
		case Card::SE:
			if( row == 7 || column == 7 )
				return SELF_NIL;
			if( IsOpSide( s, m_array[row+1][column+1].side ) )
				return ENEMY;
			return SELF_NIL;
		case Card::SW:
			if( row == 7 || column == 0 )
				return SELF_NIL;
			if( IsOpSide( s, m_array[row+1][column-1].side ) )
				return ENEMY;
			return SELF_NIL;
		default: return SELF_NIL;
	}
}

MOVE_RESULT Chessboard::CanMoveRook( short row, short column, short dist, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::N:
			if( row - dist < 0 )
				return SELF_NIL;
			if( m_array[row-dist][column].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row-dist][column].side )
				return ENEMY;
			return SELF_NIL;
		case Card::E:
			if( column + dist > 7 )
				return SELF_NIL;
			if( m_array[row][column+dist].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row][column+dist].side )
				return ENEMY;
			return SELF_NIL;
		case Card::S:
			if( row + dist > 7 ) 
				return SELF_NIL;
			if( m_array[row+dist][column].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row+dist][column].side )
				return ENEMY;
			return SELF_NIL;
		case Card::W:
			if( column - dist < 0 )
				return SELF_NIL;
			if( m_array[row][column-dist].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row][column-dist].side )
				return ENEMY;
			return SELF_NIL;
		default: return SELF_NIL;
	}
}

MOVE_RESULT Chessboard::CanMoveKnight( short row, short column, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::N: //up then right
			if( row < 2 || column == 7 )
				return SELF_NIL;
			if( s != m_array[row-2][column+1].side )
				return ENEMY;
			return SELF_NIL;
		case Card::NE: //right then up
			if( row == 0 || column > 5 )
				return SELF_NIL;
			if( s != m_array[row-1][column+2].side )
				return ENEMY;
			return SELF_NIL;
		case Card::E: //right then down
			if( row == 7 || column > 5 )
				return SELF_NIL;
			if( s != m_array[row+1][column+2].side )
				return ENEMY;
			return SELF_NIL;
		case Card::SE: //down then right
			if( row > 5 || column == 7 )
				return SELF_NIL;
			if( s != m_array[row+2][column+1].side )
				return ENEMY;
			return SELF_NIL;
		case Card::S: //down then left
			if( row > 5 || column == 0 )
				return SELF_NIL;
			if( s != m_array[row+2][column-1].side )
				return ENEMY;
			return SELF_NIL;
		case Card::SW: //left then down
			if( row == 7 || column < 2 )
				return SELF_NIL;
			if( s != m_array[row+1][column-2].side )
				return ENEMY;
			return SELF_NIL;
		case Card::W: //left then up
			if( row == 0 || column < 2 )
				return SELF_NIL;
			if( s != m_array[row-1][column-2].side )
				return ENEMY;
			return SELF_NIL;
		case Card::NW: //up then left
			if( row < 2 || column == 0 )
				return SELF_NIL;
			if( s != m_array[row-2][column-1].side )
				return ENEMY;
			return SELF_NIL;
		default: return SELF_NIL;
	}
}

MOVE_RESULT Chessboard::CanMoveBishop( short row, short column, short dist, Card::SPEC dir ) const
{
	SIDE s = m_array[row][column].side;
	if( s == BLACK )
		dir = InvertDir( dir );
	switch( dir )
	{
		case Card::NW:
			if( row - dist < 0 || column - dist < 0 )
				return SELF_NIL;
			if( m_array[row-dist][column-dist].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row-dist][column-dist].side )
				return ENEMY;
			return SELF_NIL;
		case Card::NE:
			if( row - dist < 0 || column + dist > 7 )
				return SELF_NIL;
			if( m_array[row-dist][column+dist].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row-dist][column+dist].side )
				return ENEMY;
			return SELF_NIL;
		case Card::SE:
			if( row + dist > 7 || column + dist > 7 )
				return SELF_NIL;
			if( m_array[row+dist][column+dist].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row+dist][column+dist].side )
				return ENEMY;
			return SELF_NIL;
		case Card::SW:
			if( row + dist > 7 || column - dist < 0 )
				return SELF_NIL;
			if( m_array[row+dist][column-dist].side == NOSIDE )
				return EMPTY;
			if( s != m_array[row+dist][column-dist].side )
				return ENEMY;
			return SELF_NIL;
		default: return SELF_NIL;
	}
}

MOVE_RESULT Chessboard::CanMoveQueen( short row, short column, short dist, Card::SPEC dir ) const
{
	switch( dir )
	{
		case Card::N: return CanMoveRook( row, column, dist, dir );
		case Card::S: return CanMoveRook( row, column, dist, dir );
		case Card::E: return CanMoveRook( row, column, dist, dir );
		case Card::W: return CanMoveRook( row, column, dist, dir );
		default: return CanMoveBishop( row, column, dist, dir );
	}
}