#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

const int deskSize = 1000;

const int pigeonInCount = 1000;
const int hawkInCount = 1000;
const int foodInCount = 1000000;


typedef enum creatureType {pigeon,hawk,food,empty} creatureType;
typedef struct creature
{
    creatureType type;
    int healthPoint;
    int flag;
}creature;

typedef struct nodeType{
    creature creatures[5];
}nodeType;

nodeType node [1000][1000];



int createNode (int counts[3]);
int iteration (int *pigeons, int *hawks);


int main() {
    int i, hawkCount,pigeonCount;
    int counts [3]={pigeonInCount,hawkInCount,foodInCount};

    hawkCount=hawkInCount;
    pigeonCount=pigeonInCount;

    createNode(counts);
    for (i=0; i<100; i++)
    {
        iteration(&pigeonCount,&hawkCount);
        if (1) printf("%d %d \n", pigeonCount, hawkCount);
    }

    return 0;
}

int createNode (int counts[3])
{
    int   x, y, i[3]={0,0,0},j,k,l;
    creatureType type;
    unsigned int stime;
    long ltime;

    for (j=0; j<deskSize; j++)
    {
        for (k=0; k<deskSize; k++)
        {
            for (l=0; l<5;l++)
            node[j][k].creatures[l].type=empty;
            node[j][k].creatures[l].flag=0;
        }
    }

    ltime=time(NULL);
    stime= (unsigned int) ltime/2;

    srand(stime);
    do
    {
        type = (creatureType) rand () % 3;
        if (i[type]<counts[type]) {
            x = rand() % deskSize;
            y = rand() % deskSize;
            for (j=0; j<5; j++)
            {
                if (node[x][y].creatures[j].type==empty)
                {
                    node[x][y].creatures[j].type=type;
                    node[x][y].creatures[j].healthPoint=10;
                    i[type]++;
                    break;
                }
            }
        }
    }while ((i[0]<counts[0]) || (i[1]<counts[1]) || (i[2]<counts[2]));
    return 0;
}

int iteration (int *pigeons, int *hawks)
{
    int directions[][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    int creatureCount, pigeonCount, hawkCount, foodCount;
    int i,j,l,k,x,y,tmp,winHawk,eater,foodaccumulate;

    for (i=0; i<deskSize; i++)
    {
        for (j = 0; j < deskSize; j++)
        {
            for (l = 0; l<5; l++)
            node[i][j].creatures[l].flag=0;
        }
    }
    for (i=0; i<deskSize; i++)
    {
        for (j=0; j<deskSize; j++)
        {
            pigeonCount=0;
            hawkCount=0;
            foodCount=0;

            for (l=0; l<5; l++)
            {
                if ((node[i][j].creatures[l].type==pigeon)&&(node[i][j].creatures[l].flag==0))
                {
                    if (node[i][j].creatures[l].healthPoint==1) {
                        (*pigeons)--;
                        node[i][j].creatures[l].type = empty;
                        node[i][j].creatures[l].healthPoint=0;
                    }
                    else {
                        node[i][j].creatures[l].healthPoint--;
                        pigeonCount++;
                    }
                    continue;
                }
                if ((node[i][j].creatures[l].type==hawk)&&(node[i][j].creatures[l].flag==0))
                {
                    if (node[i][j].creatures[l].healthPoint==1) {
                        (*hawks)--;
                        node[i][j].creatures[l].type = empty;
                        node[i][j].creatures[l].healthPoint=0;
                    }
                    else {
                        node[i][j].creatures[l].healthPoint--;
                        hawkCount++;
                    }
                    continue;
                }
                if (node[i][j].creatures[l].type==food)
                {foodCount++; continue;}
            }
            creatureCount=pigeonCount+hawkCount;


            if (creatureCount!=0)
            for (l=0; l<5; l++)
            {
                if (foodCount==0)
                {
                    //anyway go away
                    tmp=rand()%4;
                    x=(i+directions[tmp][0] + deskSize) % deskSize;
                    y=(j+directions[tmp][1] + deskSize) % deskSize;
                    for (k=0; k<5; k++)
                    {
                        if (node[x][y].creatures[k].type == empty)
                        {
                            node[x][y].creatures[k].type = node[i][j].creatures[l].type;
                            node[x][y].creatures[k].healthPoint = node[i][j].creatures[l].healthPoint;
                            node[x][y].creatures[k].flag=1;
                            node[i][j].creatures[l].type=empty;
                            node[i][j].creatures[l].healthPoint=0;
                            break;
                        }
                    }

                    continue;
                }

                if ((creatureCount>1)&&(node[i][j].creatures[l].type==pigeon))
                {
                    //pigeon go away
                    tmp=rand()%4;
                    x=(i+directions[tmp][0] + deskSize) % deskSize;
                    y=(j+directions[tmp][1] + deskSize) % deskSize;
                    for (k=0; k<5; k++)
                    {
                        if (node[x][y].creatures[k].type == empty)
                        {
                            node[x][y].creatures[k].type = node[i][j].creatures[l].type;
                            node[x][y].creatures[k].healthPoint = node[i][j].creatures[l].healthPoint;
                            node[x][y].creatures[k].flag=1;
                            node[i][j].creatures[l].type=empty;
                            node[i][j].creatures[l].healthPoint=0;
                            break;
                        }
                    }
                    pigeonCount--;
                    creatureCount--;

                    continue;
                }

                if ((hawkCount>1) && (node[i][j].creatures[l].type==hawk))
                {
                    //hawk fight
                    winHawk=l;
                    for (k = l+1; k<5; k++)
                    {
                        if (node[i][j].creatures[k].type==hawk)
                        {
                            if (node[i][j].creatures[winHawk].healthPoint>=node[i][j].creatures[k].healthPoint)
                            {
                                node[i][j].creatures[k].type=empty;
                                node[i][j].creatures[k].healthPoint=0;
                            }
                            else
                            {
                                node[i][j].creatures[winHawk].type=empty;
                                node[i][j].creatures[winHawk].healthPoint=0;
                                winHawk=k;
                            }
                            hawkCount--;
                            creatureCount--;
                            (*hawks)--;
                        }
                    }
                }

                foodaccumulate=0;
                eater=0;
                if (creatureCount==1)
                {
                    for (k=0; k<5; k++)
                    {
                        if (node[i][j].creatures[k].type!=food) eater=k;
                        else
                        {
                            node[i][j].creatures[k].type=empty;
                            node[i][j].creatures[k].healthPoint=0;
                            foodaccumulate+=10;
                        }
                    }
                    node[i][j].creatures[eater].healthPoint+=foodaccumulate;
                    node[i][j].creatures[eater].flag=1;
                }

            }
        }
    }

    return 0;
}