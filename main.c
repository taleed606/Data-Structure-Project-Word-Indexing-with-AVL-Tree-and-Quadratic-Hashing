// Taleed Hamadneh || #1220006 || Section 3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct AVLnode *AVLNode;
typedef struct HashTable *HashTable;

struct AVLnode
{
    char word[20];
    AVLNode Left;
    AVLNode Right;
    int frequency; // for duplicates
    int Height;    // Balance information
};

struct HashTable
{

    char *Array[100]; // array of words
    int *Frequency;   // pointer to array of frequencies
    int TableSize;    // prime table size
    int Capacity;     // how many empty cells
};

int isRead = 0;        // become 1 when reading the file
int isCreatedAVL = 0;  // if tree is created
int isNotFound = 0;    // when deletion if the word is not found , make it 1
int count = 0;         // to count nodes of AVL tree
int isCreatedHash = 0; // if the table is created
int isSymbol = 1;      // when its 1 dont insert, when its zero - > insert

// AVL
AVLNode MakeEmpty(AVLNode T);              // create the AVL tree
AVLNode Find(char word[20], AVLNode T);    // find word in te avl tree
AVLNode FindMin(AVLNode T);                // find the node that have the min ascii word
AVLNode FindMax(AVLNode T);                // ...... max......
int Height(AVLNode P);                     // height of a node
int Max(int Lhs, int Rhs);                 // max between two numbers
AVLNode SingleRotateWithLeft(AVLNode K2);  // left single rotation
AVLNode SingleRotateWithRight(AVLNode K1); // right single rotation
AVLNode DoubleRotateWithLeft(AVLNode K3);
AVLNode DoubleRotateWithRight(AVLNode K1);
AVLNode Insert(char word[20], AVLNode T);     // insert word to the avl tree
void PrintInOrder(AVLNode t);                 // traverse the tree inorder
int getBalance(AVLNode N);                    // return the balance at a specific node
void Rfile(char text[100]);                   // read the input file and store the text
int isLetter(char c);                         // check if the char is alpha, space or not
AVLNode CreateAVL(AVLNode T, char text[200]); // function to insert the input file to the tree
void menu();                                  // display the menu to the user
AVLNode deleteNode(char word[20], AVLNode T); // delete specific word from the tree
int CountNodes(AVLNode T);

// Hash
int isPrime(int x);   // to check if the number is prime or not
int nextPrime(int x); // to find the first prime number after specific number
int Hash(char word[20], int TableSize);
HashTable CreateTable(int datasize);
void insertHash(char word[20], HashTable Table); // insert the word to the hash
void insertHash_withfreq(char word[20], int frequency, HashTable Table);
int FindHash(char word[20], HashTable Table);
void RemoveFromTable(int index, HashTable Table);
void printTable(HashTable Table);
int CheckFull(HashTable Table); // if its 65% full
void DisposeHash(HashTable Table);
void AVLtoHASH(AVLNode T, HashTable Table);
HashTable ReHash(int oldsize, HashTable Table); // move the data to another table
void mostfreq(HashTable Table);                 // most frequent word in the table
int numofunique(HashTable Table);               // total number of unique words (frequency 1)
void threshold(HashTable Table, int x);         // words repeated more than specific threshold in the tree from the hash table
void edit_text(char text[20]);                  // to remove symbols and numbers from the text

int main()
{

    AVLNode tree = NULL;
    tree = MakeEmpty(tree);
    HashTable Table = NULL;
    char text[200] = {0};
    char word[20] = {0};
    int index;         // used for find function to know where is the word
    int thresholdfreq; // the user choose it to print all greater than it
    menu();
    int t = 0;
    scanf("%d", &t);
    while (t != 11)
    {
        if (t > 0 && t < 12)
        {
            switch (t)
            {
            case 1:
                if (isRead == 1) // check if the file was read
                {
                    printf("You have already loaded the file\n\n");
                }
                else
                {
                    Rfile(text);
                }
                break;
            case 2:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 1)
                {
                    printf("You have already created the tree\n\n");
                }
                else
                {
                    tree = CreateAVL(tree, text);
                    printf("Tree has been created successfully\n\n");
                }
                break;

            case 3:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't insert\n\n");
                }
                else
                {
                    printf("Please enter the word you want to insert\n");
                    scanf("%s", &word);
                    edit_text(word);
                    if (isSymbol)
                    {
                        printf("invalid input!! there is no letters in it !!\n\n");
                    }
                    else
                    {
                        strlwr(word);
                        Insert(word, tree);
                        printf("Word has been inserted successfully\n\n");
                        isSymbol = 1;
                    }
                }
                break;

            case 4:
                isNotFound = 0; // initialize it
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't insert\n\n");
                }
                else
                {
                    printf("Please enter the word you want to delete\n");
                    scanf("%s", &word);
                    edit_text(word);
                    strlwr(word);
                    tree = deleteNode(word, tree);
                    if (isNotFound == 0)
                    {
                        printf("Word has been deleted successfully\n\n");
                    }
                }
                break;

            case 5:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't print\n\n");
                }
                else
                {
                    PrintInOrder(tree);
                    printf("\n");
                }
                break;
            case 6:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't create\n\n");
                }
                else if (isCreatedHash == 1)
                {
                    printf("You have already created the Table\n\n");
                }

                else
                {
                    int datasize = CountNodes(tree);
                    Table = CreateTable(datasize);
                    count = 0; // return its value to zero
                    AVLtoHASH(tree, Table);
                    printf("Table has been created Successfully\n\n");
                    printTable(Table);
                }
                break;
            case 7:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't insert\n\n");
                }
                else if (isCreatedHash == 0)
                {
                    printf("Table is not created!! can't insert\n\n");
                }
                else if (CheckFull(Table))
                {
                    printf("PLease enter the word you want to insert\n");
                    scanf("%s", &word);
                    edit_text(word);
                    if (isSymbol)
                    {
                        printf("invalid input!! there is no letters in it !!\n\n");
                    }
                    else
                    {
                        strlwr(word);
                        printf("The Table is 65/100 Full,,, Creating new Table.... \n");
                        Table = ReHash(Table->TableSize, Table);
                        insertHash(word, Table);
                        printTable(Table);
                        isSymbol = 1;
                    }
                }

                else
                {
                    printf("PLease enter the word you want to insert\n");
                    scanf("%s", &word);
                    edit_text(word);
                    if (isSymbol)
                    {
                        printf("invalid input!! there is no letters in it !!\n\n");
                    }
                    else
                    {
                        strlwr(word);
                        insertHash(word, Table);
                        printTable(Table);
                        isSymbol = 1;
                    }
                }
                break;
            case 8:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't delete\n\n");
                }
                else if (isCreatedHash == 0)
                {
                    printf("Table is not created!! can't delete\n\n");
                }
                else if (Table->Capacity == Table->TableSize)
                {
                    printf("No data to delete...Table is empty...\n\n");
                }

                else
                {

                    printf("Please enter the word you want to delete\n");
                    scanf("%s", &word);
                    edit_text(word);
                    strlwr(word);
                    index = FindHash(word, Table);
                    if (index == -1)
                    {
                        printf("Can't delete, word is not inserted yet\n\n");
                    }
                    else
                    {
                        RemoveFromTable(index, Table);
                    }
                    printTable(Table);
                }
                break;
            case 9:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't search\n\n");
                }
                else if (isCreatedHash == 0)
                {
                    printf("Table is not created!! can't search\n\n");
                }
                else if (Table->Capacity == Table->TableSize)
                {
                    printf("No data to search on...Table is empty...\n\n");
                }

                else
                {

                    printf("PLease enter the word you want to search for\n");
                    scanf("%s", &word);
                    edit_text(word);
                    strlwr(word);
                    index = FindHash(word, Table);
                    if (index == -1)
                    {
                        printf("This word does not exist :(\n\n");
                    }
                    else
                    {
                        printf("%s Frequency is %d\n\n", word, Table->Frequency[index]);
                    }
                }

                break;

            case 10:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (isCreatedAVL == 0)
                {
                    printf("Tree is not created!! can't Print\n\n");
                }
                else if (isCreatedHash == 0)
                {
                    printf("Table is not created!! can't Print\n\n");
                }
                else if (Table->Capacity == Table->TableSize)
                {
                    printf("No data to print...Table is empty...\n\n  ");
                }
                else
                {
                    printf("\t*****WORDS STATISTICS*****\n\n");
                    printf("*** Total number of Unique words (1 frequency) is %d\n", numofunique(Table));
                    printf("\n");
                    mostfreq(Table);
                    printf("\n");
                    printf("Please enter the frequency you need to be the threshold\n");
                    scanf("%d", &thresholdfreq);
                    threshold(Table, thresholdfreq);
                    printf("\n");
                }
                break;

            default:
                break;
            }
            menu();
            scanf("%d", &t);
        }

        else
        {
            printf("!!! Please enter number between 1 and 11 !!!\n\n");
            menu();
            scanf("%d", &t);
        }
    }
    printf("Bye Bye");

    DisposeHash(Table); // Free all allocated memories
    MakeEmpty(tree);
}

void Rfile(char text[200])
{
    FILE *input;
    char temp[70] = {0};
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf(" Sorry... Can't open this file :( \n ");
        fclose(input);
        return;
    }

    char c = fgetc(input); // reads only one char from the file and checks if its letter or symbol
    while (c != EOF)
    {
        if (c == '\n')
        {
            c = ' '; // if its the end of the line, make it space between words
        }
        if (isLetter(c))
        {                           // if its letter or space, add it to the text, else don't add it
            text[strlen(text)] = c; // add it to the end of the text
        }
        c = fgetc(input);
    }

    if (strcmp(text, "") == 0) // empty file
    {
        printf("Can't Load.. This file is empty\n\n");
        fclose(input);
        return;
    }
    fclose(input);
    strlwr(text); // turn all the input to lower case
    printf("File has been loaded Successfully\n\n");
    isRead = 1;
}
void menu()
{
    printf("\nPlease choose one \n");
    printf("1. Load data from the file.\n");
    printf("2. Create the AVL tree.\n");
    printf("3. Insert a word to the AVL tree.\n");
    printf("4. delete a word from the AVL tree.\n");
    printf("5. Print the words as sorted in the AVL tree.\n");
    printf("6. Create the Hash Table.\n");
    printf("7. Insert a word to the Hash table.\n");
    printf("8. delete a word from the hash table.\n");
    printf("9. Search for a word in the hash table and print its frequency.\n");
    printf("10. Print words statistics.\n");
    printf("11. Exit the application.\n");
}

AVLNode CreateAVL(AVLNode T, char text[200])
{ // splitting the text into words, and insert each word to the tree as a node
    char *token = strtok(text, " ");
    while (token != NULL)
    {
        T = Insert(token, T);
        token = strtok(NULL, " ");
    }
    isCreatedAVL = 1;
    return T;
}

AVLNode MakeEmpty(AVLNode T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

AVLNode Find(char word[20], AVLNode T)
{
    if (T == NULL)
        return NULL;
    if (strcmp(word, T->word) < 0) // if the ascii is less than the node , go Left
        return Find(word, T->Left);
    else if (strcmp(word, T->word) > 0) // if the ascii is greater than the node, go Right
        return Find(word, T->Right);
    else
        return T;
}
AVLNode FindMin(AVLNode T)
{ // return the node that has the min ascii word
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

AVLNode FindMax(AVLNode T)
{ // return the node that has the max ascii word
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;

    return T;
}

int Height(AVLNode P)
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

int Max(int Lhs, int Rhs)
{
    return Lhs > Rhs ? Lhs : Rhs;
}

AVLNode SingleRotateWithLeft(AVLNode K2)
{
    AVLNode K1 = NULL;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1;

    return K1;
}

AVLNode SingleRotateWithRight(AVLNode K1)
{
    AVLNode K2 = NULL;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
    K2->Height = Max(Height(K2->Right), K1->Height) + 1;

    return K2;
}

AVLNode DoubleRotateWithLeft(AVLNode K3)
{
    K3->Left = SingleRotateWithRight(K3->Left);
    return SingleRotateWithLeft(K3);
}

AVLNode DoubleRotateWithRight(AVLNode K1)
{
    K1->Right = SingleRotateWithLeft(K1->Right);
    return SingleRotateWithRight(K1);
}

AVLNode Insert(char word[20], AVLNode T)
{
    if (T == NULL)
    {
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct AVLnode));
        if (T == NULL)
            printf("Out of space!!!");
        else
        {
            strcpy(T->word, word);
            T->Height = 0;
            T->frequency = 1; // initialize the frequency (no duplicates)
            T->Left = T->Right = NULL;
        }
    }
    else if (strcmp(word, T->word) < 0)
    {
        T->Left = Insert(word, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2)
            if (strcmp(word, T->Left->word) < 0) // if the ascii is less than the node , go Left
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
    }
    else if (strcmp(word, T->word) > 0)
    {
        T->Right = Insert(word, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2)
            if (strcmp(word, T->Right->word) > 0) // if the ascii is greater than the node , go Right
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    /*Else X is in the tree already; we'll increase the frequency */
    else
    {
        T->frequency++;
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

// in-order print to see the elements
void PrintInOrder(AVLNode t)
{
    if (t != NULL)
    {
        PrintInOrder(t->Left);
        printf("%s #%d\t", t->word, t->frequency);
        PrintInOrder(t->Right);
    }
}

int getBalance(AVLNode N) // return the balance of the root
{
    // if the answer was -1 make it zero, else keep it the same
    // if there was left and no right, the Left = 1 , right = -1 , in this case i made right=0 to keep the balance = 1
    int leftH, rightH;

    if (Height(N->Left) == -1)
    {
        leftH = 0;
    }
    else
    {
        leftH = Height(N->Left);
    }

    if (Height(N->Right) == -1)
    {
        rightH = 0;
    }
    else
    {
        rightH = Height(N->Right);
    }

    return leftH - rightH;
}

int isLetter(char c)
{ // used to remove symbols and numbers from the text

    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32) // if its letter or space return 1
    {

        return 1;
    }

    return 0;
}

AVLNode deleteNode(char word[20], AVLNode T)
{
    if (T == NULL)
    {
        printf("Can't delete !! The word Does not exist\n");
        isNotFound = 1;
    }

    else if (strcmp(word, T->word) > 0)
    { // if the ascii is greater than the node , go Right
        T->Right = deleteNode(word, T->Right);
    }
    else if (strcmp(word, T->word) < 0)
    { // if the ascii is less than the node , go Left
        T->Left = deleteNode(word, T->Left);
    }
    else
    { /* Found element to be deleted */

        if (T->frequency > 1)
        {
            T->frequency--;
            return T;
        }

        AVLNode tempCell;

        if (T->Left && T->Right)
        { // Two children

            tempCell = FindMin(T->Right); // min in right => root
            strcpy(T->word, tempCell->word);
            T->frequency = tempCell->frequency;
            T->Right = deleteNode(T->word, T->Right);
        }

        else
        { /* One or zero children */

            tempCell = T;

            if (T->Left != NULL)
            {
                T = T->Left;
            }
            else if (T->Right != NULL)
            {
                T = T->Right;
            }
            else
            {
                free(tempCell);
                T = NULL;
                return T;
            }

            free(tempCell);
        }
    }

    // Balance Check
    if (T != NULL)
    {
        T->Height = Max(Height(T->Right), Height(T->Left)) + 1;
        int balance = getBalance(T);

        if (balance > 1)
        {
            if (strcmp(T->Left->word, word) > 0)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
        else if (balance < -1)
        {
            if (strcmp(word, T->Right->word) > 0)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }

    return T;
}

int CountNodes(AVLNode T)
{ // returns the number of nodes in the tree => used for knowing the data for the hash table

    if (T != NULL)
    {
        CountNodes(T->Left);
        count += T->frequency;
        CountNodes(T->Right);
    }
    return count;
}

int isPrime(int x)
{ // checks if the number is prime or not

    if (x <= 1)
        return 0;

    for (int i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return 0;

    return 1;
}

int nextPrime(int x)
{ // returns the next prime number after specific one

    x++;
    while (!isPrime(x))
    {
        x++;
    }

    return x;
}

int Hash(char word[20], int TableSize)
{ // hash function for string

    int hashValue = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hashValue = ((hashValue << 5) + word[i]) % TableSize;
    }

    return hashValue;
}

HashTable CreateTable(int datasize)
{

    HashTable Table = (HashTable)malloc(sizeof(struct HashTable));
    if (Table == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }
    int TableSize = nextPrime(2 * datasize + 1); // first prime after 2*datasize (+1 is useless, we can write only 2*datasize)

    Table->Frequency = (int *)malloc(sizeof(int) * TableSize);
    if (Table->Frequency == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }

    for (int i = 0; i < TableSize; i++)
    {
        Table->Array[i] = (char *)(malloc(sizeof(char) * 20)); // assume the word only 20 char
        Table->Frequency[i] = 0;                               // initial value
        if (Table->Array[i] == NULL)
        {
            printf("Out of space.\n");
            return NULL;
        }
    }

    Table->TableSize = Table->Capacity = TableSize;

    for (int i = 0; i < TableSize; i++)
    {
        strcpy(Table->Array[i], "EMPTY"); // to know if the cell is empty or not
    }
    isCreatedHash = 1;
    return Table;
}

void insertHash(char word[20], HashTable Table)
{
    // Note: I've used quadratic hashing to handle the collision
    int Tablesize = Table->TableSize;
    int hash = Hash(word, Tablesize);

    for (int i = 0; i <= Tablesize; i++)
    {
        int index = (hash + i * i) % Tablesize;
        if (strcmp(Table->Array[index], "EMPTY") == 0)
        {
            strcpy(Table->Array[index], word);
            Table->Capacity--; // after insertion, one empty cell disappeares
            Table->Frequency[index] = 1;
            printf("Word has been added successfully to the table\n\n");
            return;
        }

        else if (strcmp(Table->Array[index], word) == 0)
        {
            Table->Frequency[index]++;
            printf("Word is already inserted, frequency updated\n\n");
            return;
        }
    }
}
void insertHash_withfreq(char word[20], int frequency, HashTable Table)
{ // used for moving from tree to hash, and rehashing
    int tablesize = Table->TableSize;
    int hash = Hash(word, tablesize);

    for (int i = 0; i <= tablesize; i++)
    {
        int index = (hash + i * i) % tablesize;

        if (strcmp(Table->Array[index], "EMPTY") == 0)
        {
            strcpy(Table->Array[index], word);
            Table->Capacity--;
            Table->Frequency[index] = frequency;
            return;
        }
    }
}

int FindHash(char word[20], HashTable Table)
{ // find specific word in the hash quadratically
    int tablesize = Table->TableSize;
    int hash = Hash(word, tablesize);
    for (int i = 0; i <= tablesize; i++)
    {
        int index = (hash + i * i) % tablesize;
        if (strcmp(Table->Array[index], word) == 0)
        {
            return index;
        }
    }
    return -1;
}

void RemoveFromTable(int index, HashTable Table)
{
    // note that i've tried to make the cell = usedcell, but the problem was that when inserting an already inserted word, it cant know that (adding it twice in the table)
    // also, I've tried to use find before insert but it takes too much time, and it seems like an array not a hash !!! (no fast indexing)
    if (Table->Frequency[index] > 1)
    {
        Table->Frequency[index]--;
        printf("Word has %d frequency... Frequency decreased\n\n", Table->Frequency[index] + 1); // because deacreased above
    }
    else
    {
        strcpy(Table->Array[index], "EMPTY");
        Table->Capacity++;
        Table->Frequency[index] = 0;
        printf("Word has been deleted successfully from the table\n\n");
    }
}

void printTable(HashTable Table)
{

    for (int i = 0; i < Table->TableSize; i++)
    {
        printf("%s #%d\n", Table->Array[i], Table->Frequency[i]);
    }
}

int CheckFull(HashTable Table)
{
    // because i've used quadratic, then if its 65% used, it considered as full
    return ((double)(Table->TableSize - Table->Capacity)) / ((double)(Table->TableSize)) >= 0.65;
}

void DisposeHash(HashTable Table)
{

    for (int i = 0; i < Table->TableSize; i++)
    {
        free(Table->Array[i]);
    }

    free(Table->Frequency);

    free(Table);
}

void AVLtoHASH(AVLNode T, HashTable Table)
{ // inorder moving
    if (T != NULL)
    {
        AVLtoHASH(T->Left, Table);
        insertHash_withfreq(T->word, T->frequency, Table);
        AVLtoHASH(T->Right, Table);
    }
}

HashTable ReHash(int oldsize, HashTable Table)
{
    int newsize = nextPrime(oldsize * 2); // the new size should be the next prime of the double oldsize
    HashTable ReTable = (HashTable)malloc(sizeof(struct HashTable));
    if (ReTable == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }

    ReTable->Frequency = (int *)malloc(sizeof(int) * newsize);
    if (ReTable->Frequency == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }

    for (int i = 0; i < newsize; i++)
    {
        ReTable->Array[i] = (char *)(malloc(sizeof(char) * 20)); // assume the word only 20 char
        ReTable->Frequency[i] = 0;                               // initial value
        if (ReTable->Array[i] == NULL)
        {
            printf("Out of space.\n");
            return NULL;
        }
    }

    ReTable->TableSize = ReTable->Capacity = newsize;

    for (int i = 0; i < newsize; i++)
    {
        strcpy(ReTable->Array[i], "EMPTY"); // to know if the cell is empty or not
    }

    for (int i = 0; i < oldsize; i++)
    {
        if (strcmp(Table->Array[i], "EMPTY") != 0)
        {
            insertHash_withfreq(Table->Array[i], Table->Frequency[i], ReTable);
        }
    }
    DisposeHash(Table); // free the old hash
    return ReTable;
}

void mostfreq(HashTable Table)
{
    int tablesize = Table->TableSize;
    int max = 0;
    for (int i = 0; i < tablesize; i++)
    {
        if (strcmp(Table->Array[i], "EMPTY") != 0)
        {
            if (Table->Frequency[i] > max)
            {
                max = Table->Frequency[i];
            }
        }
    }
    for (int i = 0; i < tablesize; i++)
    {
        if (Table->Frequency[i] == max)
        {
            printf("*** %s with frequency %d is the most frequent word\n", Table->Array[i], Table->Frequency[i]);
        }
    }
}

int numofunique(HashTable Table)
{
    int count = 0;
    int tablesize = Table->TableSize;
    for (int i = 0; i < tablesize; i++)
    {
        if (Table->Frequency[i] == 1)
        {
            count++;
        }
    }
    return count;
}

void threshold(HashTable Table, int x)
{
    int exist = 1;
    int tablesize = Table->TableSize;
    for (int i = 0; i < tablesize; i++)
    {
        if (Table->Frequency[i] > x)
        {
            printf("*** Word's frequency greater than %d is %s with frequency %d\n", x, Table->Array[i], Table->Frequency[i]);
            exist = 0; // to know if there is words greater than x or not
        }
    }

    if (exist)
    {
        printf("*** Sorry.. No words have frequency greter than %d\n", x);
    }
}

void edit_text(char text[20])
{ // remove symbols and numbers from the text
    char copy[20] = {0};
    char temp[20] = {0};
    strcpy(copy, text);
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = '\0';
    }

    for (int i = 0; i < strlen(copy); i++)
    {
        if (isLetter(copy[i]) == 1)
        {
            temp[strlen(temp)] = copy[i];
            isSymbol = 0;
        }
    }

    strcpy(text, temp);
}
