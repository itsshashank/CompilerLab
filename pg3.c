#include<stdio.h>
#include<stdlib.h>
struct node
{
    int q;
    struct node *l;
};

static int set[20], nostate, noalpha, s, notransition, c, r, buffer[20];
char alphabet[20];
static int e_closure[20][20] = {0};
struct node *transition[20][20] = {NULL};
struct node *new_transition[20][20] = {NULL};
int flag[20];

int isinput(char c)
{
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;
    return -1;
}

void insert_trasit(int r, char c, int s)
{
    int j;
    struct node *temp;
    j = isinput(c);
    if (j == -1)
    {
        printf("error\n");
        exit(0);
    }
    temp = (struct node *)malloc(sizeof(struct node));
    temp->q = s;
    temp->l = transition[r][j];
    transition[r][j] = temp;
}

void findclosure(int x, int sta)
{
    struct node *temp;
    int i;
    if (buffer[x])
        return;
    e_closure[sta][c++] = x;
    buffer[x] = 1;
    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL)
    {
        temp = transition[x][noalpha - 1];
        while (temp != NULL)
        {
            findclosure(temp->q, sta);
            temp = temp->l;
        }
    }
}

void print_e_closure(int i)
{
    int j;
    flag[i]=0;
    printf("{");
    if(e_closure[i][0]!=0)
        printf("q%d", e_closure[i][0]);
    for (j = 1; e_closure[i][j] != 0; j++){
        flag[i]=1;
        printf(",q%d", e_closure[i][j]);
    }
    printf("}\n");
    printf(" FLag : %d",flag[i]);
}

void insert2newt(){
    //add old trasitions
    for(int i=1;i <=nostate;i++)
    {
        for(int j=0;j<noalpha-1;j++){
            new_transition[i][j]= transition[i][j];
        }
        if(flag[i]==1){
            int j=1;
            while (e_closure[i][j]!=0) {
                for(int k=0;k<noalpha-1 ;k++){
                    insert_trasit(i, alphabet[k],e_closure[i][j]);
                }
                j++;
            }
        }
    }
}

void print_new(){
    insert2newt();
    struct node *temp;
    printf("\n NFA");
    for(int i=1;i<=nostate;i++){
        printf("\n\t Q%d",i);
        for(int j=0;j<noalpha;j++){
            printf("\n\t\t on %c :",alphabet[j]);
            temp = new_transition[i][j];
            printf("%d",temp->q);
            while(temp!=NULL){
                printf(",%d",temp->q);
                temp = temp-> l;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int i, j, k, m, t, n;
    printf("Enter the number of alphabets?\n");
    scanf("%d", &noalpha);
    getchar();
    printf("\nEnter alphabets? and epsilon as e at the end\n");
    for (i = 0; i < noalpha; i++)
    {
        alphabet[i] = getchar();
        getchar();
    }
    printf("\nEnter the number of states?\n");
    scanf("%d", &nostate);
    printf("\nEnter no of transition?\n");
    scanf("%d", &notransition);
    printf("\nEnter transition? A on 1 -> B\n");
    for (i = 0; i < notransition; i++)
    {
        scanf("%d %lc %d", &r, &c, &s);
        insert_trasit(r, c, s);
    }
    printf("\ne-closure of states");
    for (i = 1; i <= nostate; i++)
    {
        c = 0;
        for (j = 0; j < 20; j++)
        {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }
        findclosure(i, i);
        printf("\ne-closure(q%d): ", i);
        print_e_closure(i);
    }
    print_new();
    return 0;
}