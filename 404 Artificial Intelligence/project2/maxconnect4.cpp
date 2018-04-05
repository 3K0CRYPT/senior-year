#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>

class GameStatus {
 private:
 public:
  // std::vector<long> gameBoard[6];
  // long  gameData[42];
  long gameBoard[6][7];
  long  currentTurn;
  int   player1Score;
  int   player2Score;
  int   pieceCount;
  int   depth;
  FILE* gameFile;

  GameStatus() {
    // gameBoard[0] = &(gameData[0]);
    // gameBoard[1] = &(gameData[7]);
    // gameBoard[2] = &(gameData[14]);
    // gameBoard[3] = &(gameData[21]);
    // gameBoard[4] = &(gameData[28]);
    // gameBoard[5] = &(gameData[35]);
    
     for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 7; j++) {
        gameBoard[i][j] = 0;  
      }
     }

    // int i;
    // for (i = 0; i < 42; i++) gameData[i] = 0;

    currentTurn  = 1;
    player1Score = 0;
    player2Score = 0;
    pieceCount   = 0;
    gameFile     = 0;
    depth        = 1;
  }

  GameStatus(const GameStatus& rhs) {
    // gameData = new long[42];
    // memcpy(gameData, rhs.gameData, 42);
    // for (int i = 0; i < 42; i++) gameData[i] = rhs.gameData[i];
    // std::copy_n(rhs.gameData, 42, gameData);

    // gameBoard[1] = &(gameData[7]);
    // gameBoard[2] = &(gameData[14]);
    // gameBoard[3] = &(gameData[21]);
    // gameBoard[4] = &(gameData[28]);
    // gameBoard[5] = &(gameData[35]);
    
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 7; j++) {
        gameBoard[i][j] = rhs.gameBoard[i][j]; 
      }
     }

    currentTurn  = rhs.currentTurn;
    player1Score = rhs.player1Score;
    player2Score = rhs.player2Score;
    pieceCount   = rhs.pieceCount;
    depth        = rhs.depth;
  }

  void print() const {
    int i = 0;
    int j = 0;
    // char chars[] = {'-', '@', 'X'};
    printf(" -----------------\n");
    for (i = 0; i < 6; i++) {
      printf(" | ");
      for (j = 0; j < 7; j++) {
        // printf("%c ", chars[gameBoard[i][j]] );
        printf("%li ", gameBoard[i][j]);
      }
      printf("| \n");
    }
    printf(" -|1|2|3|4|5|6|7|-\n");
    // printf("Scores\t1: %i - 2: %i\n", player1Score, player2Score);
    // fflush(stdout);
  }

  int play(int column) {
    // if column full, return 1
    if (gameBoard[0][column] != 0) return 0;
    int i;
    // starting at the bottom of the board, place the piece into the
    // first empty spot
    for (i = 5; i >= 0; i--) {
      if (gameBoard[i][column] == 0) {
        gameBoard[i][column] = currentTurn;
        pieceCount++;
        return 1;
      }
    }
    return 0;
  }

  void countScore() {
    player1Score = 0;
    player2Score = 0;

    // check horizontally
    int i;
    for (i = 0; i < 6; i++) {
      // check player 1
      if (gameBoard[i][0] == 1 && gameBoard[i][1] == 1 &&
          gameBoard[i][2] == 1 && gameBoard[i][3] == 1) {
        player1Score++;
      }
      if (gameBoard[i][1] == 1 && gameBoard[i][2] == 1 &&
          gameBoard[i][3] == 1 && gameBoard[i][4] == 1) {
        player1Score++;
      }
      if (gameBoard[i][2] == 1 && gameBoard[i][3] == 1 &&
          gameBoard[i][4] == 1 && gameBoard[i][5] == 1) {
        player1Score++;
      }
      if (gameBoard[i][3] == 1 && gameBoard[i][4] == 1 &&
          gameBoard[i][5] == 1 && gameBoard[i][6] == 1) {
        player1Score++;
      }
      // check player 2
      if (gameBoard[i][0] == 2 && gameBoard[i][1] == 2 &&
          gameBoard[i][2] == 2 && gameBoard[i][3] == 2) {
        player2Score++;
      }
      if (gameBoard[i][1] == 2 && gameBoard[i][2] == 2 &&
          gameBoard[i][3] == 2 && gameBoard[i][4] == 2) {
        player2Score++;
      }
      if (gameBoard[i][2] == 2 && gameBoard[i][3] == 2 &&
          gameBoard[i][4] == 2 && gameBoard[i][5] == 2) {
        player2Score++;
      }
      if (gameBoard[i][3] == 2 && gameBoard[i][4] == 2 &&
          gameBoard[i][5] == 2 && gameBoard[i][6] == 2) {
        player2Score++;
      }
    }

    // check vertically
    int j;
    for (j = 0; j < 7; j++) {
      // check player 1
      if (gameBoard[0][j] == 1 && gameBoard[1][j] == 1 &&
          gameBoard[2][j] == 1 && gameBoard[3][j] == 1) {
        player1Score++;
      }
      if (gameBoard[1][j] == 1 && gameBoard[2][j] == 1 &&
          gameBoard[3][j] == 1 && gameBoard[4][j] == 1) {
        player1Score++;
      }
      if (gameBoard[2][j] == 1 && gameBoard[3][j] == 1 &&
          gameBoard[4][j] == 1 && gameBoard[5][j] == 1) {
        player1Score++;
      }
      // check player 2
      if (gameBoard[0][j] == 2 && gameBoard[1][j] == 2 &&
          gameBoard[2][j] == 2 && gameBoard[3][j] == 2) {
        player2Score++;
      }
      if (gameBoard[1][j] == 2 && gameBoard[2][j] == 2 &&
          gameBoard[3][j] == 2 && gameBoard[4][j] == 2) {
        player2Score++;
      }
      if (gameBoard[2][j] == 2 && gameBoard[3][j] == 2 &&
          gameBoard[4][j] == 2 && gameBoard[5][j] == 2) {
        player2Score++;
      }
    }

    // check diagonally

    // check player 1
    if (gameBoard[2][0] == 1 && gameBoard[3][1] == 1 &&
        gameBoard[4][2] == 1 && gameBoard[5][3] == 1) {
      player1Score++;
    }
    if (gameBoard[1][0] == 1 && gameBoard[2][1] == 1 &&
        gameBoard[3][2] == 1 && gameBoard[4][3] == 1) {
      player1Score++;
    }
    if (gameBoard[2][1] == 1 && gameBoard[3][2] == 1 &&
        gameBoard[4][3] == 1 && gameBoard[5][4] == 1) {
      player1Score++;
    }
    if (gameBoard[0][0] == 1 && gameBoard[1][1] == 1 &&
        gameBoard[2][2] == 1 && gameBoard[3][3] == 1) {
      player1Score++;
    }
    if (gameBoard[1][1] == 1 && gameBoard[2][2] == 1 &&
        gameBoard[3][3] == 1 && gameBoard[4][4] == 1) {
      player1Score++;
    }
    if (gameBoard[2][2] == 1 && gameBoard[3][3] == 1 &&
        gameBoard[4][4] == 1 && gameBoard[5][5] == 1) {
      player1Score++;
    }
    if (gameBoard[0][1] == 1 && gameBoard[1][2] == 1 &&
        gameBoard[2][3] == 1 && gameBoard[3][4] == 1) {
      player1Score++;
    }
    if (gameBoard[1][2] == 1 && gameBoard[2][3] == 1 &&
        gameBoard[3][4] == 1 && gameBoard[4][5] == 1) {
      player1Score++;
    }
    if (gameBoard[2][3] == 1 && gameBoard[3][4] == 1 &&
        gameBoard[4][5] == 1 && gameBoard[5][6] == 1) {
      player1Score++;
    }
    if (gameBoard[0][2] == 1 && gameBoard[1][3] == 1 &&
        gameBoard[2][4] == 1 && gameBoard[3][5] == 1) {
      player1Score++;
    }
    if (gameBoard[1][3] == 1 && gameBoard[2][4] == 1 &&
        gameBoard[3][5] == 1 && gameBoard[4][6] == 1) {
      player1Score++;
    }
    if (gameBoard[0][3] == 1 && gameBoard[1][4] == 1 &&
        gameBoard[2][5] == 1 && gameBoard[3][6] == 1) {
      player1Score++;
    }

    if (gameBoard[0][3] == 1 && gameBoard[1][2] == 1 &&
        gameBoard[2][1] == 1 && gameBoard[3][0] == 1) {
      player1Score++;
    }
    if (gameBoard[0][4] == 1 && gameBoard[1][3] == 1 &&
        gameBoard[2][2] == 1 && gameBoard[3][1] == 1) {
      player1Score++;
    }
    if (gameBoard[1][3] == 1 && gameBoard[2][2] == 1 &&
        gameBoard[3][1] == 1 && gameBoard[4][0] == 1) {
      player1Score++;
    }
    if (gameBoard[0][5] == 1 && gameBoard[1][4] == 1 &&
        gameBoard[2][3] == 1 && gameBoard[3][2] == 1) {
      player1Score++;
    }
    if (gameBoard[1][4] == 1 && gameBoard[2][3] == 1 &&
        gameBoard[3][2] == 1 && gameBoard[4][1] == 1) {
      player1Score++;
    }
    if (gameBoard[2][3] == 1 && gameBoard[3][2] == 1 &&
        gameBoard[4][1] == 1 && gameBoard[5][0] == 1) {
      player1Score++;
    }
    if (gameBoard[0][6] == 1 && gameBoard[1][5] == 1 &&
        gameBoard[2][4] == 1 && gameBoard[3][3] == 1) {
      player1Score++;
    }
    if (gameBoard[1][5] == 1 && gameBoard[2][4] == 1 &&
        gameBoard[3][3] == 1 && gameBoard[4][2] == 1) {
      player1Score++;
    }
    if (gameBoard[2][4] == 1 && gameBoard[3][3] == 1 &&
        gameBoard[4][2] == 1 && gameBoard[5][1] == 1) {
      player1Score++;
    }
    if (gameBoard[1][6] == 1 && gameBoard[2][5] == 1 &&
        gameBoard[3][4] == 1 && gameBoard[4][3] == 1) {
      player1Score++;
    }
    if (gameBoard[2][5] == 1 && gameBoard[3][4] == 1 &&
        gameBoard[4][3] == 1 && gameBoard[5][2] == 1) {
      player1Score++;
    }
    if (gameBoard[2][6] == 1 && gameBoard[3][5] == 1 &&
        gameBoard[4][4] == 1 && gameBoard[5][3] == 1) {
      player1Score++;
    }

    // check player 2
    if (gameBoard[2][0] == 2 && gameBoard[3][1] == 2 &&
        gameBoard[4][2] == 2 && gameBoard[5][3] == 2) {
      player2Score++;
    }
    if (gameBoard[1][0] == 2 && gameBoard[2][1] == 2 &&
        gameBoard[3][2] == 2 && gameBoard[4][3] == 2) {
      player2Score++;
    }
    if (gameBoard[2][1] == 2 && gameBoard[3][2] == 2 &&
        gameBoard[4][3] == 2 && gameBoard[5][4] == 2) {
      player2Score++;
    }
    if (gameBoard[0][0] == 2 && gameBoard[1][1] == 2 &&
        gameBoard[2][2] == 2 && gameBoard[3][3] == 2) {
      player2Score++;
    }
    if (gameBoard[1][1] == 2 && gameBoard[2][2] == 2 &&
        gameBoard[3][3] == 2 && gameBoard[4][4] == 2) {
      player2Score++;
    }
    if (gameBoard[2][2] == 2 && gameBoard[3][3] == 2 &&
        gameBoard[4][4] == 2 && gameBoard[5][5] == 2) {
      player2Score++;
    }
    if (gameBoard[0][1] == 2 && gameBoard[1][2] == 2 &&
        gameBoard[2][3] == 2 && gameBoard[3][4] == 2) {
      player2Score++;
    }
    if (gameBoard[1][2] == 2 && gameBoard[2][3] == 2 &&
        gameBoard[3][4] == 2 && gameBoard[4][5] == 2) {
      player2Score++;
    }
    if (gameBoard[2][3] == 2 && gameBoard[3][4] == 2 &&
        gameBoard[4][5] == 2 && gameBoard[5][6] == 2) {
      player2Score++;
    }
    if (gameBoard[0][2] == 2 && gameBoard[1][3] == 2 &&
        gameBoard[2][4] == 2 && gameBoard[3][5] == 2) {
      player2Score++;
    }
    if (gameBoard[1][3] == 2 && gameBoard[2][4] == 2 &&
        gameBoard[3][5] == 2 && gameBoard[4][6] == 2) {
      player2Score++;
    }
    if (gameBoard[0][3] == 2 && gameBoard[1][4] == 2 &&
        gameBoard[2][5] == 2 && gameBoard[3][6] == 2) {
      player2Score++;
    }

    if (gameBoard[0][3] == 2 && gameBoard[1][2] == 2 &&
        gameBoard[2][1] == 2 && gameBoard[3][0] == 2) {
      player2Score++;
    }
    if (gameBoard[0][4] == 2 && gameBoard[1][3] == 2 &&
        gameBoard[2][2] == 2 && gameBoard[3][1] == 2) {
      player2Score++;
    }
    if (gameBoard[1][3] == 2 && gameBoard[2][2] == 2 &&
        gameBoard[3][1] == 2 && gameBoard[4][0] == 2) {
      player2Score++;
    }
    if (gameBoard[0][5] == 2 && gameBoard[1][4] == 2 &&
        gameBoard[2][3] == 2 && gameBoard[3][2] == 2) {
      player2Score++;
    }
    if (gameBoard[1][4] == 2 && gameBoard[2][3] == 2 &&
        gameBoard[3][2] == 2 && gameBoard[4][1] == 2) {
      player2Score++;
    }
    if (gameBoard[2][3] == 2 && gameBoard[3][2] == 2 &&
        gameBoard[4][1] == 2 && gameBoard[5][0] == 2) {
      player2Score++;
    }
    if (gameBoard[0][6] == 2 && gameBoard[1][5] == 2 &&
        gameBoard[2][4] == 2 && gameBoard[3][3] == 2) {
      player2Score++;
    }
    if (gameBoard[1][5] == 2 && gameBoard[2][4] == 2 &&
        gameBoard[3][3] == 2 && gameBoard[4][2] == 2) {
      player2Score++;
    }
    if (gameBoard[2][4] == 2 && gameBoard[3][3] == 2 &&
        gameBoard[4][2] == 2 && gameBoard[5][1] == 2) {
      player2Score++;
    }
    if (gameBoard[1][6] == 2 && gameBoard[2][5] == 2 &&
        gameBoard[3][4] == 2 && gameBoard[4][3] == 2) {
      player2Score++;
    }
    if (gameBoard[2][5] == 2 && gameBoard[3][4] == 2 &&
        gameBoard[4][3] == 2 && gameBoard[5][2] == 2) {
      player2Score++;
    }
    if (gameBoard[2][6] == 2 && gameBoard[3][5] == 2 &&
        gameBoard[4][4] == 2 && gameBoard[5][3] == 2) {
      player2Score++;
    }
  }

  ~GameStatus() {}
  // ~GameStatus() { delete[] gameData; }
};

void printGameBoardToFile(GameStatus& currentGame) {
  int i = 0;
  int j = 0;
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 7; j++) {
      fprintf(currentGame.gameFile, "%li", currentGame.gameBoard[i][j]);
    }
    fprintf(currentGame.gameFile, "\n");
  }
  fprintf(currentGame.gameFile, "%d\r\n", currentGame.currentTurn);
  printf("Game exported to file.");
}

void minSearch(int* bestInfo, int* ab, GameStatus& currentGame);

void maxSearch(int* bestInfo, int* ab, GameStatus& currentGame) {
  --currentGame.depth;  //Took a step down
  currentGame.currentTurn = 2;
  if (currentGame.depth < 0) return; // Reached the bottom, end the search.
  
  int max[2] = {-1, -9999};

  for (int c = 0; c < 7; c++) { // Iterate over columns for potential moves.

    GameStatus potentialGame(currentGame);
    if (!potentialGame.play(c)) continue;  //If invalid, don't care
    potentialGame.countScore(); //Evaluate the move.

    int potentialBest[2] = {-1, potentialGame.player1Score}; //Store score
    minSearch(potentialBest, ab, potentialGame); //Check min move

    if (max[0] < 0 || potentialBest[1] > max[1]) {
      max[1] = potentialBest[1];
      max[0] = c;
      int why = potentialBest[1];
      ab[0] = why; // alpha = next move
      // printf("max %i %i\n", ab[0], ab[1]);
      // fflush(stdout);
    }
    
    if (potentialBest[1] >= ab[1]) break;
    if (potentialBest[1] > ab[0]) ab[0] = potentialBest[1];
  }
  bestInfo[0] = max[0];
  bestInfo[1] = max[1];
  return;
}

void minSearch(int* bestInfo, int* ab, GameStatus& currentGame) {
  --currentGame.depth;  //Took a step down
  currentGame.currentTurn = 1;

  if (currentGame.depth < 0) return;

  int min[2] = {-1, 9999};

  for (int c = 0; c < 7; c++) { // Iterate over columns for potential moves.

    GameStatus potentialGame(currentGame);
    if (!potentialGame.play(c)) continue;  //If invalid, don't care
    potentialGame.countScore();         //Evaluate the move.

    int potentialBest[2] = {-1, potentialGame.player2Score};
    maxSearch(potentialBest, ab, potentialGame); //Otherwise, keep checking

    if (min[0] < 0 || potentialBest[1] < min[1]) {
      min[1] = potentialBest[1];
      min[0] = c;
      int why = potentialBest[1];
      ab[1] = why; // alpha = next move
      // printf("min %i %i\n", ab[0], ab[1]);
      // fflush(stdout);
    }
    
    if (potentialBest[1] <= ab[0]) break;
    if (potentialBest[1] < ab[1]) ab[1] = potentialBest[1];
  }
  bestInfo[0] = min[0];
  bestInfo[1] = min[1];
  return;
}


// The AI section.  Currently plays randomly.
void aiPlay(GameStatus& currentGame) {
  GameStatus gameCopy(currentGame);         // Make a copy just for safety
  int        results[2] = {-1, -99999};     // [Column, Score]
  int        ab[2]      = {-99999, 99999};  // [Alpha, Beta] pruning
  fflush(stdout);
  // minimax(results, ab, gameCopy, true);  // Do the minimax search.
  maxSearch(results, ab, gameCopy); // Do the minimax search.
  printf("Got results: %i, %i\t[%i, %i]\n\n", results[0], results[1], ab[0], ab[1]);
  fflush(stdout);

  currentGame.play(results[0]);  //Play the move

  printf("\n\nMove %li: Player %li (AI), column %li\n", currentGame.pieceCount, currentGame.currentTurn, results[0] + 1);
  fflush(stdout);
  currentGame.currentTurn = !(currentGame.currentTurn - 1) + 1;

  fflush(stdout);  // Stupid dumb windows
}

void humanPlay(GameStatus& currentGame) {
  int result = 0, col;

  do {
    printf("Column #: ");
    fflush(stdout);
    scanf("%d", &col);

    result = currentGame.play(col - 1);  //Random
  } while (!result);

  printf("\n\nMove %li: Player %li (Human), column %li\n", currentGame.pieceCount, currentGame.currentTurn, col);
  // if (currentGame.currentTurn == 1) currentGame.currentTurn = 2;
  // else if (currentGame.currentTurn == 2) currentGame.currentTurn = 1;
  currentGame.currentTurn = !(currentGame.currentTurn - 1) + 1;
  fflush(stdout);  // Stupid dumb windows
}

int main(int argc, char** argv) {
  bool   interactive  = false;
  bool   computerTurn = false;  // Whether or not it's computer-next or human-next
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

  int   depth  = atoi(command_line[4]);
  char* input  = command_line[2];
  char* output = command_line[3];

  if (interactive && output == "computer-next") computerTurn = true;

  char* game_mode = command_line[1];

  if (strcmp(game_mode, "interactive") == 0) {
    printf("Starting interactive session.\n");
    interactive = true;
  } else if (strcmp(game_mode, "one-move") != 0) {
    printf("%s is an unrecognized game mode\n", game_mode);
    return 0;
  } else {
    interactive  = false;
    computerTurn = true;
    //Prevents waiting for user input in one-move mode
  }

  // Any arg that's not "computer-next" will default top human-turn.

  GameStatus currentGame;  // Initialize game instance
  printf("\nMaxConnect-4 game\n");

  // set currentTurn
  char current      = 0;
  currentGame.depth = depth;
  // Initialize gameboard (count number of previous turns, load file to 2D array) from input
  currentGame.gameFile = fopen(input, "r");
  printf("Initial state:\n");
  if (currentGame.gameFile != 0) {
    for (int i = 0; i < 6; i++)
      for (int j = 0; j < 7; j++) {
        do {
          current = getc(currentGame.gameFile);
        } while ((current == ' ') || (current == '\n') || (current == '\r'));

        currentGame.gameBoard[i][j] = current - 48;
        if (currentGame.gameBoard[i][j] > 0) currentGame.pieceCount++;
      }

    do {
      current = getc(currentGame.gameFile);
    } while ((current == ' ') || (current == '\n') || (current == '\r'));

    currentGame.currentTurn = current - 48;
    fclose(currentGame.gameFile);
  }

  do {  // Loop this part while we're in interactive mode.

    currentGame.print();
    currentGame.countScore();
    printf("Score: Player 1 = %d, Player 2 = %d\n\n", currentGame.player1Score, currentGame.player2Score);

    unsigned char checksum = 0;
    for (int i = 0; i < 7; i++)
      if (currentGame.gameBoard[0][i]) checksum++;

    // if (currentGame.pieceCount == 42)
    if (checksum > 6) {
      printf("\nBOARD FULL\n");
      printf("Game over!\n\n");
      return 1;
    }

    if (computerTurn)
      aiPlay(currentGame);
    else
      humanPlay(currentGame);
    // humanPlay(currentGame);
    computerTurn            = !computerTurn;
    currentGame.currentTurn = (int)computerTurn + 1;  //Human = 1, Computer = 2 always
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