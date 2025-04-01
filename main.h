typedef struct
{
        int x;
        int y;
} posType;

typedef struct
{
        posType coords[16];
        int posCount;
} playerType;

typedef struct
{
        posType w[3][4];
} winType;

typedef struct
{
        playerType uno;
        playerType dos;
        playerType tres;

        playerType f;
        posType w[3][4];

        int turn;
        int go;
        int over;

} stateType;

void flushBuffer();
void getInput(int *input, char prompt);
posType getPlayerMove(stateType *state);
void displayBoard(stateType *state);
int isElementOf(posType pos, playerType player);
int findPosIndex(posType pos, playerType player);
void deletePos(posType pos, playerType *player);
void fillSetF(stateType *state);
void setFUpdate(stateType *state);
void fillSetW(posType w[3][4]);
int isSetElementOfSetW(playerType player, posType w[3][4]);
void nextPlayerMove(posType pos, stateType *state);
void setOverState(stateType *state);
void gameOver(stateType *state);
