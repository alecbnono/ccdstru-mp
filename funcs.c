#include <stdio.h>
#include "color.h"
#include "main.h"

void flushBuffer()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}

void getPlayerMove(int *input, char prompt[])
{
        do
        {
                printf("%s ", prompt);
                scanf("%d", input);
                flushBuffer();

                if (*input < 1 || *input > 4)
                        printf("%s%s%s", COLOR_REDBOLD, "Invalid input. Please enter again.\n", COLOR_RESET);
        }
        while (*input < 1 || *input > 4);
}

void displayBoard(stateType *state)
{
        printf("%c | %c | %c | %c");
        printf("------------------");
        printf("%c | %c | %c | %c");
        printf("------------------");
        printf("%c | %c | %c | %c");
        printf("------------------");
        printf("%c | %c | %c | %c");
}

int isElementOf(posType pos, playerType player)
{
        int found = 0;
        int i;

        for (i = 0; i < player.posCount; i++)
        {
                if (player.coords[i].x == pos.x && player.coords[i].y == pos.y)
                        found = 1;
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

void nextPlayerMove(posType pos, stateType *state)
{
        if (state->turn == 1 && state->go == 1 && isElementOf(pos, state->f))
        {
                state->uno.coords[state->uno.posCount] = pos;
                state->uno.posCount++;

                state->turn = !state->turn;
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

void gameOver(stateType *state)
{
        if ()
        {
        
        }
}
