#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>


class gameStatus {
 private:

 public:
  long* gameData;
  long* gameBoard[6];
  long currentTurn;
  int player1Score;
  int player2Score;
  int pieceCount;
  int depth;
  FILE* gameFile;

  gameStatus() {
    gameData = new long[42];
    gameBoard[0] = &(gameData[0]);
    gameBoard[1] = &(gameData[7]);
    gameBoard[2] = &(gameData[14]);
    gameBoard[3] = &(gameData[21]);
    gameBoard[4] = &(gameData[28]);
    gameBoard[5] = &(gameData[35]);

    int i;
    for (i = 0; i < 42; i++) {
      gameData[i] = 0;
    }
    
    currentTurn = 1;
    player1Score = 0;
    player2Score = 0;
    pieceCount = 0;
    gameFile = 0;
    depth = 1;
  }

  ~gameStatus() { delete[] gameData; }
};

// Output current game status to console
void printGameBoard(gameStatus& currentGame) {
  int i = 0;
  int j = 0;
  char chars[] = {'-', '@', 'X'};
  printf(" -----------------\n");
  for (i = 0; i < 6; i++) {
    printf(" | ");
    for (j = 0; j < 7; j++) {
      printf("%li ", currentGame.gameBoard[i][j] );
    }
    printf("| \n");
  }
  printf(" -|1|2|3|4|5|6|7|-\n");
}

// Output current game status to file
void printGameBoardToFile(gameStatus& currentGame) {
  int i = 0;
  int j = 0;
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 7; j++) {
      fprintf(currentGame.gameFile, "%li", currentGame.gameBoard[i][j]);
    }
    fprintf(currentGame.gameFile, "\n");
  }
  fprintf(currentGame.gameFile, "%d\r\n", currentGame.currentTurn);
}

// Given a column and which player it is,
// place that player's piece in the requested column
int playPiece(int column, gameStatus& currentGame) {
  // if column full, return 1
  if (currentGame.gameBoard[0][column] != 0) return 0;
  int i;
  // starting at the bottom of the board, place the piece into the
  // first empty spot
  for (i = 5; i >= 0; i--) {
    if (currentGame.gameBoard[i][column] == 0) {
      currentGame.gameBoard[i][column] = currentGame.currentTurn;
      currentGame.pieceCount++;
      return 1;
    }
  }
  return 0;
}

void countScore(gameStatus& currentGame) {
  currentGame.player1Score = 0;
  currentGame.player2Score = 0;

  // check horizontally
  int i;
  for (i = 0; i < 6; i++) {
    // check player 1
    if (currentGame.gameBoard[i][0] == 1 && currentGame.gameBoard[i][1] == 1 &&
        currentGame.gameBoard[i][2] == 1 && currentGame.gameBoard[i][3] == 1) {
      currentGame.player1Score++;
    }
    if (currentGame.gameBoard[i][1] == 1 && currentGame.gameBoard[i][2] == 1 &&
        currentGame.gameBoard[i][3] == 1 && currentGame.gameBoard[i][4] == 1) {
      currentGame.player1Score++;
    }
    if (currentGame.gameBoard[i][2] == 1 && currentGame.gameBoard[i][3] == 1 &&
        currentGame.gameBoard[i][4] == 1 && currentGame.gameBoard[i][5] == 1) {
      currentGame.player1Score++;
    }
    if (currentGame.gameBoard[i][3] == 1 && currentGame.gameBoard[i][4] == 1 &&
        currentGame.gameBoard[i][5] == 1 && currentGame.gameBoard[i][6] == 1) {
      currentGame.player1Score++;
    }
    // check player 2
    if (currentGame.gameBoard[i][0] == 2 && currentGame.gameBoard[i][1] == 2 &&
        currentGame.gameBoard[i][2] == 2 && currentGame.gameBoard[i][3] == 2) {
      currentGame.player2Score++;
    }
    if (currentGame.gameBoard[i][1] == 2 && currentGame.gameBoard[i][2] == 2 &&
        currentGame.gameBoard[i][3] == 2 && currentGame.gameBoard[i][4] == 2) {
      currentGame.player2Score++;
    }
    if (currentGame.gameBoard[i][2] == 2 && currentGame.gameBoard[i][3] == 2 &&
        currentGame.gameBoard[i][4] == 2 && currentGame.gameBoard[i][5] == 2) {
      currentGame.player2Score++;
    }
    if (currentGame.gameBoard[i][3] == 2 && currentGame.gameBoard[i][4] == 2 &&
        currentGame.gameBoard[i][5] == 2 && currentGame.gameBoard[i][6] == 2) {
      currentGame.player2Score++;
    }
  }

  // check vertically
  int j;
  for (j = 0; j < 7; j++) {
    // check player 1
    if (currentGame.gameBoard[0][j] == 1 && currentGame.gameBoard[1][j] == 1 &&
        currentGame.gameBoard[2][j] == 1 && currentGame.gameBoard[3][j] == 1) {
      currentGame.player1Score++;
    }
    if (currentGame.gameBoard[1][j] == 1 && currentGame.gameBoard[2][j] == 1 &&
        currentGame.gameBoard[3][j] == 1 && currentGame.gameBoard[4][j] == 1) {
      currentGame.player1Score++;
    }
    if (currentGame.gameBoard[2][j] == 1 && currentGame.gameBoard[3][j] == 1 &&
        currentGame.gameBoard[4][j] == 1 && currentGame.gameBoard[5][j] == 1) {
      currentGame.player1Score++;
    }
    // check player 2
    if (currentGame.gameBoard[0][j] == 2 && currentGame.gameBoard[1][j] == 2 &&
        currentGame.gameBoard[2][j] == 2 && currentGame.gameBoard[3][j] == 2) {
      currentGame.player2Score++;
    }
    if (currentGame.gameBoard[1][j] == 2 && currentGame.gameBoard[2][j] == 2 &&
        currentGame.gameBoard[3][j] == 2 && currentGame.gameBoard[4][j] == 2) {
      currentGame.player2Score++;
    }
    if (currentGame.gameBoard[2][j] == 2 && currentGame.gameBoard[3][j] == 2 &&
        currentGame.gameBoard[4][j] == 2 && currentGame.gameBoard[5][j] == 2) {
      currentGame.player2Score++;
    }
  }

  // check diagonally

  // check player 1
  if (currentGame.gameBoard[2][0] == 1 && currentGame.gameBoard[3][1] == 1 &&
      currentGame.gameBoard[4][2] == 1 && currentGame.gameBoard[5][3] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][0] == 1 && currentGame.gameBoard[2][1] == 1 &&
      currentGame.gameBoard[3][2] == 1 && currentGame.gameBoard[4][3] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][1] == 1 && currentGame.gameBoard[3][2] == 1 &&
      currentGame.gameBoard[4][3] == 1 && currentGame.gameBoard[5][4] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][0] == 1 && currentGame.gameBoard[1][1] == 1 &&
      currentGame.gameBoard[2][2] == 1 && currentGame.gameBoard[3][3] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][1] == 1 && currentGame.gameBoard[2][2] == 1 &&
      currentGame.gameBoard[3][3] == 1 && currentGame.gameBoard[4][4] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][2] == 1 && currentGame.gameBoard[3][3] == 1 &&
      currentGame.gameBoard[4][4] == 1 && currentGame.gameBoard[5][5] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][1] == 1 && currentGame.gameBoard[1][2] == 1 &&
      currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][4] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][2] == 1 && currentGame.gameBoard[2][3] == 1 &&
      currentGame.gameBoard[3][4] == 1 && currentGame.gameBoard[4][5] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][4] == 1 &&
      currentGame.gameBoard[4][5] == 1 && currentGame.gameBoard[5][6] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][2] == 1 && currentGame.gameBoard[1][3] == 1 &&
      currentGame.gameBoard[2][4] == 1 && currentGame.gameBoard[3][5] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][3] == 1 && currentGame.gameBoard[2][4] == 1 &&
      currentGame.gameBoard[3][5] == 1 && currentGame.gameBoard[4][6] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][3] == 1 && currentGame.gameBoard[1][4] == 1 &&
      currentGame.gameBoard[2][5] == 1 && currentGame.gameBoard[3][6] == 1) {
    currentGame.player1Score++;
  }

  if (currentGame.gameBoard[0][3] == 1 && currentGame.gameBoard[1][2] == 1 &&
      currentGame.gameBoard[2][1] == 1 && currentGame.gameBoard[3][0] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][4] == 1 && currentGame.gameBoard[1][3] == 1 &&
      currentGame.gameBoard[2][2] == 1 && currentGame.gameBoard[3][1] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][3] == 1 && currentGame.gameBoard[2][2] == 1 &&
      currentGame.gameBoard[3][1] == 1 && currentGame.gameBoard[4][0] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][5] == 1 && currentGame.gameBoard[1][4] == 1 &&
      currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][2] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][4] == 1 && currentGame.gameBoard[2][3] == 1 &&
      currentGame.gameBoard[3][2] == 1 && currentGame.gameBoard[4][1] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][3] == 1 && currentGame.gameBoard[3][2] == 1 &&
      currentGame.gameBoard[4][1] == 1 && currentGame.gameBoard[5][0] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[0][6] == 1 && currentGame.gameBoard[1][5] == 1 &&
      currentGame.gameBoard[2][4] == 1 && currentGame.gameBoard[3][3] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][5] == 1 && currentGame.gameBoard[2][4] == 1 &&
      currentGame.gameBoard[3][3] == 1 && currentGame.gameBoard[4][2] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][4] == 1 && currentGame.gameBoard[3][3] == 1 &&
      currentGame.gameBoard[4][2] == 1 && currentGame.gameBoard[5][1] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[1][6] == 1 && currentGame.gameBoard[2][5] == 1 &&
      currentGame.gameBoard[3][4] == 1 && currentGame.gameBoard[4][3] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][5] == 1 && currentGame.gameBoard[3][4] == 1 &&
      currentGame.gameBoard[4][3] == 1 && currentGame.gameBoard[5][2] == 1) {
    currentGame.player1Score++;
  }
  if (currentGame.gameBoard[2][6] == 1 && currentGame.gameBoard[3][5] == 1 &&
      currentGame.gameBoard[4][4] == 1 && currentGame.gameBoard[5][3] == 1) {
    currentGame.player1Score++;
  }

  // check player 2
  if (currentGame.gameBoard[2][0] == 2 && currentGame.gameBoard[3][1] == 2 &&
      currentGame.gameBoard[4][2] == 2 && currentGame.gameBoard[5][3] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][0] == 2 && currentGame.gameBoard[2][1] == 2 &&
      currentGame.gameBoard[3][2] == 2 && currentGame.gameBoard[4][3] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][1] == 2 && currentGame.gameBoard[3][2] == 2 &&
      currentGame.gameBoard[4][3] == 2 && currentGame.gameBoard[5][4] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][0] == 2 && currentGame.gameBoard[1][1] == 2 &&
      currentGame.gameBoard[2][2] == 2 && currentGame.gameBoard[3][3] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][1] == 2 && currentGame.gameBoard[2][2] == 2 &&
      currentGame.gameBoard[3][3] == 2 && currentGame.gameBoard[4][4] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][2] == 2 && currentGame.gameBoard[3][3] == 2 &&
      currentGame.gameBoard[4][4] == 2 && currentGame.gameBoard[5][5] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][1] == 2 && currentGame.gameBoard[1][2] == 2 &&
      currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][4] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][2] == 2 && currentGame.gameBoard[2][3] == 2 &&
      currentGame.gameBoard[3][4] == 2 && currentGame.gameBoard[4][5] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][4] == 2 &&
      currentGame.gameBoard[4][5] == 2 && currentGame.gameBoard[5][6] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][2] == 2 && currentGame.gameBoard[1][3] == 2 &&
      currentGame.gameBoard[2][4] == 2 && currentGame.gameBoard[3][5] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][3] == 2 && currentGame.gameBoard[2][4] == 2 &&
      currentGame.gameBoard[3][5] == 2 && currentGame.gameBoard[4][6] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][3] == 2 && currentGame.gameBoard[1][4] == 2 &&
      currentGame.gameBoard[2][5] == 2 && currentGame.gameBoard[3][6] == 2) {
    currentGame.player2Score++;
  }

  if (currentGame.gameBoard[0][3] == 2 && currentGame.gameBoard[1][2] == 2 &&
      currentGame.gameBoard[2][1] == 2 && currentGame.gameBoard[3][0] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][4] == 2 && currentGame.gameBoard[1][3] == 2 &&
      currentGame.gameBoard[2][2] == 2 && currentGame.gameBoard[3][1] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][3] == 2 && currentGame.gameBoard[2][2] == 2 &&
      currentGame.gameBoard[3][1] == 2 && currentGame.gameBoard[4][0] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][5] == 2 && currentGame.gameBoard[1][4] == 2 &&
      currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][2] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][4] == 2 && currentGame.gameBoard[2][3] == 2 &&
      currentGame.gameBoard[3][2] == 2 && currentGame.gameBoard[4][1] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][3] == 2 && currentGame.gameBoard[3][2] == 2 &&
      currentGame.gameBoard[4][1] == 2 && currentGame.gameBoard[5][0] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[0][6] == 2 && currentGame.gameBoard[1][5] == 2 &&
      currentGame.gameBoard[2][4] == 2 && currentGame.gameBoard[3][3] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][5] == 2 && currentGame.gameBoard[2][4] == 2 &&
      currentGame.gameBoard[3][3] == 2 && currentGame.gameBoard[4][2] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][4] == 2 && currentGame.gameBoard[3][3] == 2 &&
      currentGame.gameBoard[4][2] == 2 && currentGame.gameBoard[5][1] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[1][6] == 2 && currentGame.gameBoard[2][5] == 2 &&
      currentGame.gameBoard[3][4] == 2 && currentGame.gameBoard[4][3] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][5] == 2 && currentGame.gameBoard[3][4] == 2 &&
      currentGame.gameBoard[4][3] == 2 && currentGame.gameBoard[5][2] == 2) {
    currentGame.player2Score++;
  }
  if (currentGame.gameBoard[2][6] == 2 && currentGame.gameBoard[3][5] == 2 &&
      currentGame.gameBoard[4][4] == 2 && currentGame.gameBoard[5][3] == 2) {
    currentGame.player2Score++;
  }
}

void minimax(gameStatus& currentGame, int* bestInfo, bool max) {
  --currentGame.depth;  //Took a step down
  currentGame.currentTurn = max + 1;
  if (currentGame.depth < 0) return; // Reached the bottom, end the search.
  
  for (int c = 0; c < 6; c++) { // Iterate over columns for potential moves.
  
    gameStatus potentialGame;
    potentialGame = currentGame;    //Make a copy of current state.
    // for (int i = 0; i < 42; i++) {printf("%i ", currentGame.gameData[i]);} printf("\n");
    printGameBoard(potentialGame);
    playPiece(c, potentialGame);

    
    int result = playPiece(c, potentialGame); //Play the move
    //IT'S NOT PLAYPIECE
    
    if (!result) continue;                    //If invalid, don't care
    
    countScore(potentialGame); //Evaluate the move.
    //IT'S NOT COUNTSCORE

    int potentialInfo[2];
    memcpy(potentialInfo, bestInfo, 2); // Make a copy of current best info before messing with it in recursion.
    
    minimax(potentialGame, potentialInfo, !max); //Otherwise, keep checking 
    printf("\n");
    
    if (max) {  //If current move evaluation is MAX player
      if(potentialInfo[1] > bestInfo[1]) {  //MAX play wants a higher score
          bestInfo[1] = potentialInfo[1];
          bestInfo[0] = c;
        }
    }
    else {  //Then it's MIN player
      if(potentialInfo[1] < bestInfo[1]) {  //MIN wants lower score
          bestInfo[1] = potentialInfo[1];
          bestInfo[0] = c;
        }
    }    
    
  }
    
  return;
}

// The AI section.  Currently plays randomly.
void aiPlay(gameStatus& currentGame) {
  int results[2] =  { 0, -1000 }; // [Column, Score], records best move and its respective score
  
  gameStatus gameCopy;
  gameCopy = currentGame; // Make a copy just for safety
  
  minimax(gameCopy, results, true); // Do the minimax search.
  
  // printGameBoard(currentGame);
  // int col = 0;
  // scanf ("%d",&col);
  
  
  printf("Got results: %i, %i\n\n", results[0], results[1]);
  printGameBoard(currentGame);
  
  playPiece(results[0], currentGame); //Play the move
  
  // if (result == 0) aiPlay(currentGame);
  // else {
    printf("\n\nMove %li: Player %li (AI), column %li\n", currentGame.pieceCount, currentGame.currentTurn, results[0] + 1);
    if (currentGame.currentTurn == 1) currentGame.currentTurn = 2;
    else if (currentGame.currentTurn == 2) currentGame.currentTurn = 1;
  // }
  
  fflush(stdout); // Stupid dumb windows
}

void humanPlay(gameStatus& currentGame) {
  int result = 0, col;
  
  do {
    printf("Column #: ");
    fflush(stdout);
    scanf ("%d",&col);
    
    result = playPiece(col-1, currentGame);  //Random
  } while(!result);
  
    printf("\n\nMove %li: Player %li (Human), column %li\n", currentGame.pieceCount, currentGame.currentTurn, col);
    if (currentGame.currentTurn == 1) currentGame.currentTurn = 2;
    else if (currentGame.currentTurn == 2) currentGame.currentTurn = 1;
  fflush(stdout); // Stupid dumb windows
}

int main(int argc, char** argv) {
  bool interactive = false;
  bool computerTurn = false;  // Whether or not it's computer-next or human-next
  char** command_line = argv;

  if (argc != 5) {
    printf("Four command-line arguments are needed:\n");
    printf(
        "Usage: %s interactive [input_file] [computer-next/human-next] "
        "[depth]\n",
        command_line[0]);
    printf("or:  %s one-move [input_file] [output_file] [depth]\n",
           command_line[0]);

    return 0;
  }

  char* game_mode = command_line[1];

  if (strcmp(game_mode, "interactive") == 0) {
    printf("Starting interactive session.\n");
    interactive = true;
  } 
  else if (strcmp(game_mode, "one-move") != 0) {
    printf("%s is an unrecognized game mode\n", game_mode);
    return 0;
  }

  int depth = atoi(command_line[4]);
  char* input = command_line[2];
  char* output = command_line[3]; 
  
  // Any arg that's not "computer-next" will default top human-turn.
  if (interactive && output == "computer-next") computerTurn = true;
  
  gameStatus currentGame;  // Initialize game instance
  printf("\nMaxConnect-4 game\n");

  // set currentTurn
  char current = 0;
  currentGame.depth = depth;
  // Initialize gameboard (count number of previous turns, load file to 2D array) from input
  currentGame.gameFile = fopen(input, "r");
  printf("Initial state:\n");
  if (currentGame.gameFile != 0) {
    for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) {
        do { current = getc(currentGame.gameFile); } while ((current == ' ') || (current == '\n') || (current == '\r'));

        currentGame.gameBoard[i][j] = current - 48;
        if (currentGame.gameBoard[i][j] > 0) currentGame.pieceCount++;
    }

    do { current = getc(currentGame.gameFile); } while ((current == ' ') || (current == '\n') || (current == '\r'));

    currentGame.currentTurn = current - 48;
    fclose(currentGame.gameFile);
  }

  do { // Loop this part while we're in interactive mode.
  
    printGameBoard(currentGame);
    countScore(currentGame);
    printf("Score: Player 1 = %d, Player 2 = %d\n\n", currentGame.player1Score, currentGame.player2Score);

    // Seed random number generator
    int seed = time(NULL);
    srand(seed);

    if (currentGame.pieceCount == 42) {
      printf("\nBOARD FULL\n");
      printf("Game over!\n\n");
      return 1;
    }

    if (computerTurn) aiPlay(currentGame);
    else humanPlay(currentGame);
    // humanPlay(currentGame);    
    computerTurn = !computerTurn;
    currentGame.currentTurn = (int)computerTurn + 1;
    
  } while (interactive);

  currentGame.gameFile = fopen(output, "w");
  if (currentGame.gameFile != 0) {
    printGameBoardToFile(currentGame);
    fclose(currentGame.gameFile);
  } else {
    printf("error: could not open output file %s\n", output);
  }

  return 1;
}