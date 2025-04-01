#include <stdio.h>
#include "color.h"
#include "main.h"

void flushBuffer()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}

void getInput(int *input, char prompt)
{
        do
        {
                printf("Enter %c coordinate: ", prompt);
                scanf("%d", input);
                flushBuffer();

                if (*input < 1 || *input > 4)
                        printf("%s%s%s", COLOR_REDBOLD, "Invalid input. Please enter again.\n", COLOR_RESET);
        }
        while (*input < 1 || *input > 4);
}

posType getPlayerMove(stateType *state)
{
        posType pos;
        int valid = 0;

        if (!state->turn)
                printf("=== %s ===\n", "Dos Turn");
        else if (state->turn && !state->go)
                printf("=== %s ===\n", "Tres Turn");
        else if (state->turn && state->go)
                printf("=== %s ===\n", "Uno Turn");

        do
        {
                getInput(&pos.x, 'X');
                getInput(&pos.y, 'Y');

                if (!state->turn)
                {
                        if (isElementOf(pos, state->uno) || isElementOf(pos, state->tres))
                                valid = 1;
                        else
                                printf("%s%s%s", 
                                       COLOR_REDBOLD, 
                                       "Coordinate isn't taken. Please enter an occupied coordinate\n", 
                                       COLOR_RESET);
                }

                else if (state->turn && !state->go)
                {
                        if (isElementOf(pos, state->f) && !isElementOf(pos, state->uno))
                                valid = 1;
                        else
                                printf("%s%s%s", 
                                       COLOR_REDBOLD, 
                                       "Coordinate has been taken. Please enter an empty coordinate\n", 
                                       COLOR_RESET);
                }

                else if (state->turn && state->go)
                {
                        if (isElementOf(pos, state->f) && !isElementOf(pos, state->tres))
                                valid = 1;
                        else
                                printf("%s%s%s", 
                                       COLOR_REDBOLD, 
                                       "Coordinate has been taken. Please enter an empty coordinate\n", 
                                       COLOR_RESET);
                }
        }
        while (valid != 1);

        return pos;
}

void displayBoard(stateType *state)
{
        posType tempPos;
        int i, j;

        printf("\n");

        for (i = 1; i <= 4; i++)
        {
                for (j = 1; j <= 4; j++)
                {
                        tempPos.x = j;
                        tempPos.y = i;

                        if (isElementOf(tempPos, state->uno))
                                printf(" %c ", 'X');
                        else if (isElementOf(tempPos, state->tres))
                                printf(" %c ", 'O');
                        else if (isElementOf(tempPos, state->f))
                                printf(" %c ", ' ');

                        if (j < 4)
                                printf("|");
                }
                printf("\n");
                if (i < 4)
                        printf("---------------\n");
        }
        printf("\n");
}

int isElementOf(posType pos, playerType player)
{
        int found = 0;
        int i = 0;

        while (found != 1 && i < player.posCount)
        {
                if (player.coords[i].x == pos.x && player.coords[i].y == pos.y)
                        found = 1;
                i++;
        }

        return found;
}

int findPosIndex(posType pos, playerType player)
{
        int index = -1;
        int i;

        for (i = 0; i < player.posCount; i++)
        {
                if (player.coords[i].x == pos.x && player.coords[i].y == pos.y)
                        index = i;
        }
        return index;
}

void deletePos(posType pos, playerType *player)
{
        int i;
        int posIndex = findPosIndex(pos, *player);

        if (posIndex != -1)
        {
                for (i = posIndex; i < player->posCount - 1; i++)
                        player->coords[i] = player->coords[i + 1];
                player->posCount--;
        }
}

void fillSetF(stateType *state)
{
        int i = 0;
        int j, k;

        for (j = 1; j <= 4; j++)
        {
                for (k = 1; k <= 4; k++)
                {
                        state->f.coords[i].x = j;
                        state->f.coords[i].y = k;
                        state->f.posCount++;
                        i++;
                }
        }
}

void setFUpdate(stateType *state)
{
        fillSetF(state);

        int i;

        for (i = 0; i < state->uno.posCount; i++)
                deletePos(state->uno.coords[i], &state->f);

        for (i = 0; i < state->tres.posCount; i++)
                deletePos(state->tres.coords[i], &state->f);
}

void fillSetW(posType w[3][4])
{
        int i = 0;
        int j = 4;

        while (i < 4)
        {
                w[1][i].x = i;
                w[1][i].y = j;

                i++;
                j--;
        }

        for (i = 0; i < 4; i++)
        {
                w[0][i].x = 1;
                w[0][i].y = i;
        }

        for (i = 0; i < 4; i++)
        {
                w[2][i].x = 4;
                w[2][i].y = i;
        }
}

int isSetElementOfSetW(playerType player, posType w[3][4])
{
        int i = 0;
        int j = 0; 
        int setElementOfW = 0;
        int totalMatch;

        for (i = 0; i < 3; i++)
        {
                totalMatch = 0;

                for (j = 0; j < 4; j++) // checks if each element of W
                {                       // is part of player
                        if (isElementOf(w[i][j], player))
                                totalMatch += 1;
                }
                if(totalMatch == 4)
                        setElementOfW = 1;
        }

        return setElementOfW;
}

void nextPlayerMove(posType pos, stateType *state)
{
        if (state->turn == 1 && state->go == 1 && isElementOf(pos, state->f))
        {
                state->uno.coords[state->uno.posCount] = pos;
                state->uno.posCount++;

                state->turn = !state->turn;
                state->go = !state->go;
        }
        else if (!state->turn && (isElementOf(pos, state->uno) || isElementOf(pos, state->tres)))
        {
                deletePos(pos, &state->uno);
                deletePos(pos, &state->tres);

                state->turn = !state->turn;
        }
        else if (state->turn && !state->go && isElementOf(pos, state->f))
        {
                state->tres.coords[state->tres.posCount] = pos;
                state->tres.posCount++;

                state->go = !state->go;
        }
        setFUpdate(state); // maintains system fact for set F
}


void setOverState(stateType *state)
{
        int unoWin = isSetElementOfSetW(state->uno, state->w);
        int tresWin = isSetElementOfSetW(state->tres, state->w);

        if (unoWin || tresWin || state->f.posCount == 0)
                state->over = 1;
}

void gameOver(stateType *state)
{
        setOverState(state);

        if (state->over == 1)
        {
                int unoWin = isSetElementOfSetW(state->uno, state->w);
                int tresWin = isSetElementOfSetW(state->tres, state->w);

                if (unoWin)
                        printf("%s Uno Win! %s", COLOR_GREEN, COLOR_RESET);
                else if (tresWin)
                        printf("%s Tres Win! %s", COLOR_GREEN, COLOR_RESET);
                else if (state->f.posCount == 0)
                        printf("%s Dos Win! %s", COLOR_GREEN, COLOR_RESET);
        }
}
