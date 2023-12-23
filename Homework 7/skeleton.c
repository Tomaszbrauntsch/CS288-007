#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0

/*
Created By: Tomasz Brauntsch
CS 288-007
Professor Ding
December 5, 2023 
*/

/*   THIS IS NOT A COMPLETE PROGRAM.    */


struct state {
    int tiles[N][N];
    int f, g, h;
    short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
    struct state *next;
    struct state *parent;			/* used to trace back the solution */
};

int goal_rows[NxN];
int goal_columns[NxN];
struct state *start,*goal;
struct state *fringe = NULL, *closed = NULL;
struct state *succ_states[4];
int z = 0;

void print_a_state(struct state *pstate) {
    int i,j;
    for (i=0;i<N;i++) {
        for (j=0;j<N;j++)
            printf("%2d ", pstate->tiles[i][j]);
        printf("\n");
    }
    printf("\n");
}

void initialize(char **argv){
    int i,j,k,index, tile;

    start=(struct state *) malloc(sizeof(struct state));
    index = 1;
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) {
            tile=atoi(argv[index++]);
            start->tiles[j][k]=tile;
            if(tile==0) {
                start->zero_row=j;
                start->zero_column=k;
            }
        }
    start->f=0;
    start->g=0;
    start->h=0;
    start->next=NULL;
    start->parent=NULL;
    printf("initial state\n");
    print_a_state(start);

    goal=(struct state *) malloc(sizeof(struct state));
    goal_rows[0]=3;
    goal_columns[0]=3;

    for(index=1; index<NxN; index++){
        j=(index-1)/N;
        k=(index-1)%N;
        goal_rows[index]=j;
        goal_columns[index]=k;
        goal->tiles[j][k]=index;
    }
    goal->tiles[N-1][N-1]=0;	      /* empty tile=0 */
    goal->f=0;
    goal->g=0;
    goal->h=0;
    goal->next=NULL;
    printf("goal state\n");
    print_a_state(goal);

}

/* merge the remaining states pointed by succ_states[] into fringe.
 * Insert states based on their f values --- keep f values sorted. */
void merge_to_fringe() {
    int k, x, y;
//    struct state *curr_succ;
    /* Create a node that will appended to the fringe */
    for (k = 0; k < N; k++) {

        if (succ_states[k] != NULL) {

//            curr_succ = (struct state *) malloc(sizeof(struct state));
//            for (x = 0; x < N; x++) {
//                for (y = 0; y < N; y++) {
//                    curr_succ->tiles[x][y] = succ_states[k]->tiles[x][y];
//                }
//            }
//            curr_succ->f = succ_states[k]->f;
//            curr_succ->g = succ_states[k]->g;
//            curr_succ->h = succ_states[k]->h;
//            curr_succ->zero_row = succ_states[k]->zero_row;
//            curr_succ->zero_column = succ_states[k]->zero_column;
//            curr_succ->next = NULL;
//            curr_succ->parent = succ_states[k]->parent;
            if (fringe == NULL) {
                fringe = succ_states[k];
            } else {
                struct state *fringecpy = fringe;
                struct state *prev = NULL;
                while ((fringecpy != NULL) && (fringecpy->f < succ_states[k]->f)) {
                    prev = fringecpy;
                    fringecpy = fringecpy->next;
                }
//                if (prev == NULL) {
//                    succ_states[k]->next = fringe;
//                    fringe = succ_states[k];
//                } else {
//                    prev->next = succ_states[k];
//                    succ_states[k]->next = fringecpy;
//                }
            }
        }
    }
}




//    int k;
//    int x,y;
//    if(fringe != NULL){
//        while(fringe->next != NULL) {
//            fringe = fringe->next;
//        }
//        for(k = 0;k < N; k++){
//            if(succ_states[k] != NULL) {
//                fringe->next = succ_states[k];
//                fringe = fringe->next;
//            }
//        }
//        fringe->next = NULL;
//    }
//    else{

//        struct state {
//            int tiles[N][N];
//            int f, g, h;
//            short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
//            struct state *next;
//            struct state *parent;			/* used to trace back the solution */
//        };
//        for(x = 0; x < N; x++){
//            for(y = 0; y < N; y++){
//                fringe->tiles[x][y] = succ_states[0]->tiles[x][y];
//            }
//        }
//        fringe = succ_states[0];
//        fringe->parent = NULL;
//        for(k = 1; k < N; k++){
//            fringe->next = succ_states[k];
//            fringe = fringe->next;
//            fringe->parent = succ_states[k-1];
//        }
//        fringe->next = NULL;
//    }
//}

/*swap two tiles in a state*/
void swap(int row1,int column1,int row2,int column2, struct state * pstate){
    /* if difference in row,col do the moving */
    struct state * curr_pstate = pstate;
    int tempValue = 0;
    if((row1 < row2) && (column1 == column2)){ /* move down */
        tempValue = curr_pstate->tiles[row2][column1];
        curr_pstate->tiles[row2][column1] = pstate->tiles[row1][column1];
        curr_pstate->tiles[row1][column1] = tempValue;
        curr_pstate->zero_row = (short) row2;
        curr_pstate->zero_column = (short) column1;
    }
    else if((row1 > row2) && (column1 == column2)){ /* move up */
        tempValue = pstate->tiles[row2][column1];
        curr_pstate->tiles[row2][column1] = pstate->tiles[row1][column1];
        curr_pstate->tiles[row1][column1] = tempValue;
        curr_pstate->zero_row = (short) row2;
        curr_pstate->zero_column = (short) column1;

    }
    else if((row1 == row2) && (column1 < column2)){ /* move right */
        tempValue = pstate->tiles[row1][column2];
        curr_pstate->tiles[row1][column2] = pstate->tiles[row1][column1];
        curr_pstate->tiles[row1][column1] = tempValue;
        curr_pstate->zero_row = (short) row1;
        curr_pstate->zero_column = (short) column2;
    }
    else if((row1 == row2) && (column1 > column2)){ /* move left */
        tempValue = pstate->tiles[row1][column2];
        curr_pstate->tiles[row1][column2] = pstate->tiles[row1][column1];
        curr_pstate->tiles[row1][column1] = tempValue;
        curr_pstate->zero_row = (short) row1;
        curr_pstate->zero_column = (short) column2;
    }
}

/*update the f,g,h function values for a state pointed by a pointer in succ_states */
void update_fgh(int i) {
    /* work on the succ_states[i] not getting the information (may need to go one by one and insert manually)
     * Once this is done, update_fgh will be done, just see if the succ_states hold the f,g,h then we are completed
    /* i is the position of the succ_state we want */
    struct state *pstate = succ_states[i];
    if(pstate == NULL){
        return;
    }
    int g,h;
    int x1, x2, y1, y2;
    int iX,iY;
    g = h = 0;

    for (x1 = 0; x1 < N; x1++){
        for (y1 = 0; y1 < N; y1++){ /* for each element in the pstate */
            for (x2 = 0; x2 < N; x2++){ /* for each element in the goal state */
                for(y2 = 0; y2 < N; y2++){
                    if((pstate->tiles[x1][y1] == start->tiles[x2][y2]) && (pstate->tiles[x1][y1] != 0)){
                        g += abs(x1-x2) + abs(y1-y2);
                    }
                }
            }
        }
    }

//    while(pstate->parent!=NULL){
//        pstate = pstate->parent;
//        g++;
//    }
    pstate = succ_states[i];
    pstate->g = g;

    /* for each element in the pstate find state at 0,0 and see where it is in the target add the distance, rinse and repeat */
    for (x1 = 0; x1 < N; x1++){
        for (y1 = 0; y1 < N; y1++){ /* for each element in the pstate */
            for (x2 = 0; x2 < N; x2++){ /* for each element in the goal state */
                for(y2 = 0; y2 < N; y2++){
                    if((pstate->tiles[x1][y1] == goal->tiles[x2][y2]) && (pstate->tiles[x1][y1] != 0)){
                        h += abs(x1-x2) + abs(y1-y2);
                    }
                }
            }
        }
    }
    pstate->h = h;
    pstate->f = h + g;
    /* insert information into succ_states; */
    /*
    f = g + h
    g = each step from start to current state || + 1 each iter
    h = manhattan distance (abs(current_nodeX - goal_nodeX) + abs(current_nodeY - goal_nodeY))
    */
}

/* 0 goes down by a row */
void move_down(struct state * pstate){
    if(pstate->zero_row+1 < N){
        swap((int)pstate->zero_row, (int)pstate->zero_column, (int)pstate->zero_row + 1, (int)pstate->zero_column,pstate);
    }
}

/* 0 goes right by a column */
void move_right(struct state * pstate){
    if(pstate->zero_column+1 < N){
        swap((int)pstate->zero_row, (int)pstate->zero_column, (int)pstate->zero_row, (int)pstate->zero_column + 1,pstate);
    }
}

/* 0 goes up by a row */
void move_up(struct state * pstate){
    if(pstate->zero_row-1 >= 0){
        swap((int)pstate->zero_row, (int)pstate->zero_column, (int)pstate->zero_row - 1, (int)pstate->zero_column,pstate);
    }
}

/* 0 goes left by a column */
void move_left(struct state * pstate){
//    printf("Left: %d\t%d\t%d\t%d\n", (int)pstate->zero_row, (int)pstate->zero_column, (int)pstate->zero_row, (int)pstate->zero_column - 1);
    if(pstate->zero_column-1 >= 0){
        swap((int)pstate->zero_row, (int)pstate->zero_column, (int)pstate->zero_row, (int)pstate->zero_column - 1,pstate);
    }
}

void expand_succ(){
    int i;
    for(i = 0; i < N;i++){
        if(succ_states[i] == NULL) {
            succ_states[i] = (struct state *) malloc(sizeof(struct state));
        }
    }
}

/* expand a state, and get its children states. Children states pointed by the pointers in succ_states.
 */

void expand(struct state *selected) {
    /*
    succ_states 0 = left
    succ_states 1 = up
    succ_states 2 = right
    succ_states 3 = down
    */
    expand_succ();
    int loop, i, j;
    /* selected_mod will move said state and then reset it back to original and move accordingly */
	/* intializes the succ_states */
    for(loop = 0; loop < N; loop++){
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                succ_states[loop]->tiles[i][j] = selected->tiles[i][j];
            }
        }
        succ_states[loop]->f = selected->f;
        succ_states[loop]->g = selected->g;
        succ_states[loop]->h = selected->h;
        succ_states[loop]->zero_row = selected->zero_row;
        succ_states[loop]->zero_column = selected->zero_column;
    }
    move_left(succ_states[0]);

    move_up(succ_states[1]);

    move_right(succ_states[2]);

    move_down(succ_states[3]);

    for(i = 0; i < N; i++){
        succ_states[i]->parent=selected;
        succ_states[i]->next=NULL;
    }
}

int states_same(struct state *a,struct state *b) {
    int flg=FALSE;
    if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
        flg=TRUE;
    return flg;
}


void free_states(struct state * badstate, struct state * myfringe){
    struct state * fringeChange = myfringe;
    struct state *prev = NULL;
    while (fringeChange != NULL){
        if(fringeChange == badstate){
            if(prev == NULL){
                myfringe = fringeChange->next;
            }
            else{
                prev->next = fringeChange->next;
            }
            free(fringeChange);
            break;
        }
            prev = fringeChange;
            fringeChange = fringeChange->next;
    }
}

/* Filtering:
 * check the state pointed by succ_states[i] to determine whether this state is repeating.
 * free the state if it is repeating.
 */
void filter(int i, struct state *pstate_list) {
    struct state *pstate = succ_states[i];
    /* succ_states[i] is being freed, so search pstate_list->next and see if it is the same as succ_states */
    /* use the states_same */
    struct state *pstateL = pstate_list;
    struct state *prev = NULL;
    int notfound = 1;
    int same_status;
    while (((pstate != NULL) && (pstateL != NULL)) && (notfound)) {
        if(states_same(pstate,pstateL)){
            succ_states[i] = NULL;
            notfound = 0;
        }
        else{
            pstateL = pstateL->next;
        }
    }
}
int main(int argc,char **argv) {
    int iter,cnt;
    struct state *curr_state, *cp, *solution_path;
    int ret, i, pathlen=0, index[N-1];

    solution_path=NULL;
    initialize(argv);	/* init initial and goal states */
    fringe=start;

    iter=0;

    for(i = 0; i < N; i++){
        succ_states[i] = (struct state *) malloc(sizeof(struct state));
    }
    while (fringe!=NULL) {
        curr_state=fringe;
        fringe=fringe->next;  /* get the first state from fringe to expand */


        /* SOME NOTES FOR DEBUGGING:
         * Fix segmentation faults first. If the program cannot produce correct results,
         * select an initial layout close to the goal layout, and debug the program with it.
         * gdb is recommended. You may also print data on the screen. But this is not as
         * convenient as using gdb.
         *
         * If your program does not crash, but the result is not correct, you can
         * print the state pointed by curr_state for the list of states examined during the search
         *
         */
        if(states_same(curr_state,goal)){ /* a solution is found */
            do{ /* trace back and add the states on the path to a list */
                curr_state->next=solution_path;
                solution_path=curr_state;
                curr_state=curr_state->parent;
                pathlen++;
            } while(curr_state!=NULL);
            printf("Path (lengh=%d):\n", pathlen);
            curr_state=solution_path;

            /* print out the states on the list */
            /* does this work? Initial to final */
            /* start */
            // for(i=0;i<pathlen;i++){ /* might need to do a pathlen - 1*/
            // 	curr_state = curr_state->parent;
            // }
            for(i = 0;i<pathlen;i++){ /* might need to do a pathlen - 1*/
                print_a_state(curr_state);
                curr_state=curr_state->next;
            }
            /* end */

            break;
        }
        expand(curr_state);       /* generate new states */


        for(i=0;i<4;i++){
            filter(i,fringe); /* Check succ_states[i] agaist fringe to see if it is repeatng */
            filter(i,closed); /* Check succ_states[i] agaist closed to see if it is repeatng */
            update_fgh(i); /* evaluate the state if it is not repeating */
        }


        merge_to_fringe(); /* add new states to fringe */

        curr_state->next=closed;
        closed=curr_state;	/* curr_state has been checked/expand, add it to closed */
        /* print out something so that you know your program is still making progress
         */
        if(iter++ %1000 == 0) printf("iter %d\n", iter);

        /* make the fringe go back to the first state / the parent state so it can repeat */

        z++;
    }
    for(i = 0; i < N; i++){
        free(succ_states[i]);
    }
    return 0;
} /* end of main */
