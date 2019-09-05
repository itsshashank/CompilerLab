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
    printf("{");
    if(e_closure[0][0]!=0)
        printf("q%d", e_closure[i][0]);
    for (j = 1; e_closure[i][j] != 0; j++)
        printf(",q%d", e_closure[i][j]);
    printf("}\n");
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
    return 0;
}