#include <stdio.h>
#include "funcs.c"

int main()
{
        stateType state;

        state.turn = 1;
        state.go = 0;
        state.over = 0;

        state.uno.posCount = 0;
        state.dos.posCount = 0;
        state.tres.posCount = 0;
        state.f.posCount = 0;

        fillSetF(&state);
        fillSetW(state.w);

        while (state.over != 1)
        {
                nextPlayerMove(getPlayerMove(&state),&state);
                displayBoard(&state);
                gameOver(&state);
        }

        return 0;
}
