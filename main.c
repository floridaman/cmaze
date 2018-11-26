#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void dig(int x, int y);
int get_direction(char xy, int direction);
int opposite(int direction);
void shuffle(int *array, size_t n);
int is_between(int value, int min, int max);
char compare_south(int x, int y);
char compare_east(int x, int y);
void print_maze();
void print_maze_ascii();

//bit mask
int N = 1, E = 2, S = 4, W = 8;

//maze width
int width = 50;

//define maze array
int maze[50][50];

int main()
{
    srand ( time(NULL) );
    printf("Generating square maze with a side length of %d units...", width);
    dig(0, 0);
    print_maze_ascii();
    return 0;
}

void dig(int x, int y)
{
    int directions[] = {N, E, S, W};
    shuffle(&directions, 4);
    for(int i = 0; i < 4; i++)
    {
        int dir = directions[i];
        int opp = opposite(dir);
        int nx = x + get_direction('x',dir), ny = y + get_direction('y',dir);

        if(is_between(nx, 0, width - 1) && is_between(ny, 0, width - 1) && maze[ny][nx] == 0)
        {

            maze[y][x] = maze[y][x] | dir;
            maze[ny][nx] = maze[ny][nx] | opp;
            dig(nx, ny);
        }
    }
}

void print_maze()
{
    printf("\n\n");
    for(int y = 0; y < width; y++)
    {
        for(int x = 0; x < width; x++)
        {
            //printf("\n (%d,%d) %d",x,y,maze[x][y]);
            printf("%02d ",maze[y][x]);
            if(x == width - 1)
            {
                printf("\n");
            }
        }
    }
}

void print_maze_ascii()
{
    printf("\n ");
    for(int i = 0; i < width * 2 - 1; i++)
    {
        printf("_");
    }
    printf("\n");
    for(int y = 0; y < width; y++)
    {
        printf("|");
        for(int x = 0; x < width; x++)
        {
            printf("%c",compare_south(x,y));
            if((maze[y][x] & E) != 0)
            {
                printf("%c",compare_east(x,y));
            }
            else
            {
                printf("|");
            }
        }
        printf("\n");
    }
}

char compare_east(int x, int y)
{
    if(((maze[y][x] | maze[y][x+1]) & S) != 0)
    {
        return ' ';
    }
    else
    {
        return '_';
    }
}

char compare_south(int x, int y)
{
    if((maze[y][x] & S) != 0)
    {
        return ' ';
    }
    else
    {
        return '_';
    }
}

int get_direction(char xy, int direction)
{
    switch(xy)
    {
        case 'x':
        {
            if(direction == N)
            {
                return 0;
            }
            else if (direction == E)
            {
                return 1;
            }
            else if (direction == S)
            {
                return 0;
            }
            else
            {
                return -1;
            }
            break;
        }
        case 'y':
        {
            if(direction == N)
            {
                return -1;
            }
            else if (direction == E)
            {
                return 0;
            }
            else if (direction == S)
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        }
    }
}

int opposite(int direction)
{
    if(direction == N)
    {
        return S;
    }
    else if (direction == E)
    {
        return W;
    }
    else if (direction == S)
    {
        return N;
    }
    else
    {
        return E;
    }
}

void shuffle(int *array, size_t n)
{
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int is_between(int value, int min, int max)
{
    if (value >= min && value <= max){
        return 1;
    }
    return 0;
}
