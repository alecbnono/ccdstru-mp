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
        playerType uno;
        playerType dos;
        playerType tres;

        playerType f;

        int turn;
        int go;
        int over;

} stateType;

void flushBuffer();
void getPlayerMove(int *input, char prompt[]);
void displayBoard(stateType *state);
int isElementOf(posType pos, playerType player);
int findPosIndex(posType pos, playerType player);
void deletePos(posType pos, playerType *player);
void setFUpdate(stateType *state);
void nextPlayerMove(posType pos, stateType *state);
void fillSetF(stateType *state);
