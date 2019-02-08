#include <stdio.h>
#include <stdlib.h>
#include "bboard.h"
#include "simpleio.h"
#include <ctype.h>
#include <time.h>



struct bboard
{
    char mtx[MAX_ROWS][MAX_COLS];
    char mtx_undo[MAX_ROWS][MAX_COLS];
    int nrows;
    int ncols;
    int score;
    int score_undo;
    int pop_combo;
    char temp_c;
    int check;
};

BBoardPtr bb_create_from_mtx(char mtx[][MAX_COLS],int nrows,int ncols)
{
    
    if((nrows>1&&nrows<=MAX_ROWS)&&(ncols>1&&ncols<=MAX_COLS))
    {
        BBoardPtr s  = malloc(sizeof(struct bboard));
        s->score=0;
        s->nrows=nrows;
        s->ncols=ncols;
        int i=0;
        int j=0;
        while(i<nrows)
        {
            while (j<ncols)
            {
                s->mtx[i][j]=mtx[i][j];
                j++;
            }
            j=0;
            i++;
        }
        return s;
    }
    else
        return NULL;
}


int bb_undo(BBoardPtr b)
{
   
    if(b->score!=b->score_undo)
    {
        int i=0;
        int j=0;
        while(i<b->nrows)
        {
            while (j<b->ncols)
            {
                b->mtx[i][j]=b->mtx_undo[i][j];
                j++;
            }
            j=0;
            i++;
        }
        b->score=b->score_undo;
      
        return 1;//undo was succesful
    
    }
    return 0; //undo unsuccesful
}

int bb_score(BBoardPtr b)
{

    b->score= b->score+(b->pop_combo*(b->pop_combo-1));
    b->pop_combo=0;
    return b->score;
}

void bb_destroy(BBoardPtr b)
{
    if(b!=NULL)
        free(b);
}

int bb_float_one_step(BBoardPtr b)
{
    
    int r=0;
    int c=0;
   
    while (c<b->ncols)
    {
        while (r<b->nrows-1)
        {
            if ((b->mtx[r][c]==None)&&(b->mtx[r+1][c]==Red||b->mtx[r+1][c]==Blue||b->mtx[r+1][c]==Green||b->mtx[r+1][c]==Yellow))
            {
                b->mtx[r][c]=b->mtx[r+1][c];
                b->mtx[r+1][c]=None;
            }
            r++;
        }
        r=0;
        c++;
    }
    return 0;
}

int bb_is_compact(BBoardPtr b)
{
    /*
     this does not move anything this is just checking
     if it needs to move
     */
    
    int r=0;
    int c=0;
 
    if (b->temp_c!='\0')
    {
        b->temp_c='\0';
        b->check=0;
    }
 
    while (c<b->ncols)
    {
        while (r<b->nrows-1)
        {
            if ((b->mtx[r][c]==None)&&(b->mtx[r+1][c]==Red||b->mtx[r+1][c]==Blue||b->mtx[r+1][c]==Green||b->mtx[r+1][c]==Yellow))
            {
                return 0;// the ballon is should be higher
            }
            r++;
        }
        r=0;
        c++;
    }
    
    return 1;//if the ballon is high as possible
    
    
}


int bb_pop(BBoardPtr b, int r, int c)
{
    if(b->mtx[r][c]!=' '||b->check==1)
    {
    if((r<b->nrows&&c<b->ncols)||b->check==1)
    {
        int count=0;
    
        if (b->temp_c=='\0')
        {
            int i=0;
            int j=0;
            while(i<b->nrows)
            {
                while (j<b->ncols)
                {
                    b->mtx_undo[i][j]=b->mtx[i][j];
                    j++;
                }
                j=0;
                i++;
            }
            b->score_undo=b->score;

            b->temp_c=b->mtx[r][c];
        }
    
        if(r-1>=0&&b->temp_c==b->mtx[r-1][c])
        {
            b->mtx[r][c]=' ';
            b->pop_combo++;
            b->check=1;
            bb_pop(b,r-1,c);
        }
        count++;
        if (c+1<b->ncols&&b->temp_c==b->mtx[r][c+1])
        {
            b->mtx[r][c]=' ';
            b->pop_combo++;
            b->check=1;
            bb_pop(b,r,c+1);
        }
        count++;
        if (r+1<b->nrows&&b->temp_c==b->mtx[r+1][c])
        {
            b->mtx[r][c]=' ';
            b->pop_combo++;
            b->check=1;
            bb_pop(b,r+1,c);
        }
        count++;
        if (c-1>=0&&b->temp_c==b->mtx[r][c-1])
        {
            b->mtx[r][c]=' ';
            b->pop_combo++;
            b->check=1;
            bb_pop(b,r,c-1);
        }
        count++;
    
        if(count==4&&b->check==1)
        {
            b->mtx[r][c]=' ';
            b->pop_combo++;
        }

    }
    else
        printf("\nOut of range. Try again :)\n");
    }
    else
        printf("\nBlank spot. Try again or quit\n");
    return 0;
}

BBoardPtr bb_create(int nrows, int ncols)
{
    char convert[]={Red,Blue,Green,Yellow,None};
    srand( (unsigned)time(NULL));
    if((nrows>1&&nrows<=MAX_ROWS)&&(ncols>1&&ncols<=MAX_COLS))
    {
        BBoardPtr s  = malloc(sizeof(struct bboard));
        s->score=0;
        s->nrows=nrows;
        s->ncols=ncols;
        int i=0;
        int j=0;
        while(i<nrows)
        {
            while (j<ncols)
            {
                s->mtx[i][j]=convert[rand()%4];
                j++;
            }
            j=0;
            i++;
        }
        return s;
    }
    else
        return NULL;
}

void bb_display(BBoardPtr b)
{
    int i=1;
    int j=0;

    if (b->nrows>=10)
    {
        printf("  +");
    }
    else
        printf("  +");
    while (i<=(b->ncols)*2)
    {
        printf("-");
        i++;
    }
    printf("+\n");
    i=0;
    while(i<b->nrows)
    {
        if (i>=10)
            printf("%i|",i);
        else
            printf(" %i|",i);
        
        
        while (j<b->ncols)
        {
            printf(" %c",b->mtx[i][j]);
            j++;
        }
        printf("|\n");
        j=0;
        i++;
    }
    
    i=1;
    printf("  +");
    while (i<=(b->ncols)*2)
    {
        printf("-");
        i++;
    }
    printf("+\n   ");
    i=0;
    
    
    while (i<b->ncols)
    {
        printf(" %i",i/10);
        i++;
    }
    printf("\n   ");
    i=0;
    j=0;
    while (i<b->ncols)
    {
        if (i%10==0)
        {
            j=0;
        }
        printf(" %i",j);
        i++;
        j++;
    }
    printf("\n");

}
