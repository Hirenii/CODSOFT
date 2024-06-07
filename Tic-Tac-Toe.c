#include<stdio.h>
#include<limits.h>

// Defining the Constants 
const char player= 'X';
const char computer= 'O';

char board[10]={' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Function Prototypes
void printBoard();
int isMovesLeft();
int checkWinningLines(int a, int b, int c);
int calculate();
int minmax(int isMax);
void findBestStep(int *bestStep);
int main();

void printBoard()
{
	printf("\n\n");
    printf("\n     |     |     ");
    printf("\n  %c  |  %c  |  %c  ",board[1],board[2],board[3]);
    printf("\n_____|_____|_____");
    printf("\n     |     |     ");
    printf("\n  %c  |  %c  |  %c  ",board[4],board[5],board[6]);
    printf("\n_____|_____|_____");
    printf("\n     |     |     ");
    printf("\n  %c  |  %c  |  %c  ",board[7],board[8],board[9]);
    printf("\n     |     |     ");
    printf("\n\n");
}

int isMovesLeft()
{
	int i;
	for(i=1;i<10;i++)
	{
		if(board[i]==' ')
		{
			return 1;
		}
	}
	return 0;
}

int checkWinningLines(int a, int b, int c)
{
	if (board[a] == board[b] && board[b] == board[c] && board[a] != ' ')
	{
        return board[a] == 'O' ? 10 : -10;
    }
    return 0;
}

int calculate()
{
	int score;
	
	// Check Rows
    if ((score = checkWinningLines(1, 2, 3)) != 0) return score;
    if ((score = checkWinningLines(4, 5, 6)) != 0) return score;
    if ((score = checkWinningLines(7, 8, 9)) != 0) return score;

	// Check Columns
    if ((score = checkWinningLines(1, 4, 7)) != 0) return score;   
    if ((score = checkWinningLines(2, 5, 8)) != 0) return score;
    if ((score = checkWinningLines(3, 6, 9)) != 0) return score;

	// Check Diagonals
    if ((score = checkWinningLines(1, 5, 9)) != 0) return score;   
    if ((score = checkWinningLines(3, 5, 7)) != 0) return score;

    return 0;
}

int minmax(int isMax)
{
	int score=calculate();
	
	// If the Computer Wins
    if (score == 10) return score;
    
    // If the Player Wins
    if (score == -10) return score;
    
    // If no Moves are Left
    if (!isMovesLeft()) return 0;
    
	if(isMax)
	{
		int best=INT_MIN;
		int i;
		for(i=1;i<10;i++)
		{
    		if(board[i] == ' ')
			{
        		board[i] = computer;
        		int moreVal = minmax(0);
        		
        		best= moreVal > best ? moreVal : best;
        		
				board[i] = ' ';
			}
		}
		
		return best;
	}
	else
	{
		int best=INT_MAX;
		int i;
		for(i=1;i<10;i++)
		{
    		if(board[i] == ' ')
			{
        		board[i] = player;
				int moreVal = minmax(1);
				
				best = moreVal < best ? moreVal : best;
				
				board[i] = ' ';	
			}
		}

        return best;
	}
}

void findBestStep(int *bestStep)
{
	int best=INT_MIN;
	
	*bestStep=-1;
	int i;
	for(i=1;i<10;i++)
	{
		if(board[i]==' ')
		{
			board[i]=computer;
			int moreVal=minmax(0);
		
			board[i]=' ';
			if(moreVal>best)
			{
				*bestStep=i;
				best=moreVal;
			}
		}
	}
}
int main() 
{
	int move;
	char currentPlayer=player;
	
	printf("\n Welcome to Tic-Tac-Toe !!");
	
	printf("\n\n");
    printf("\n     |     |     ");
    printf("\n  1  |  2  |  3  ");
    printf("\n_____|_____|_____");
    printf("\n     |     |     ");
    printf("\n  4  |  5  |  6  ");
    printf("\n_____|_____|_____");
    printf("\n     |     |     ");
    printf("\n  7  |  8  |  9  ");
    printf("\n     |     |     ");
    printf("\n\n");
	
	// Main Loop of the Game
	while(isMovesLeft() && calculate()==0)
	{
		if(currentPlayer==player)
		{
			printf("\n Enter your move (1-9) : ");
			scanf("%d",&move);
			
			if(move < 1 || move > 9 || board[move] == 'X' || board[move] == 'O')
			{
				printf("\n Invalid move. Try Again.");
				continue;
			}
			
			board[move]=player;
			
			currentPlayer=computer;
		}
		
		else
		{
			int bestStep;
			// For Computer to Find the Best Move
			findBestStep(&bestStep);
			board[bestStep]=computer;
			currentPlayer=player;
		}
		
		printBoard();
	}
	
	// To Determine and To Print the Final Result of the Game
	int totalPoints=calculate();
	
	if(totalPoints==10)
	{
		printf("\n Computer Wins !");
	}
	else if(totalPoints==-10)
	{
		printf("\n You Win !");
	}
	else
	{
		printf("\n Its a Tie !");
	}
	
	return 0;
}

