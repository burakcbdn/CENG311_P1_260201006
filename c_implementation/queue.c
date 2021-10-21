#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;


/* 
    defines the amount of integers in the file change accordingly
    it is 20 by default since default file has 20 elements
    *function used instead of variable because of pow function
*/
int arrayLen() {
    //return pow(2, 27);
    return 20;
}

int leftChild(int i) {
    return (2 * i) + 1;
}

int rightChild(int i) {
    return (2 * i) + 2;
}

int parent(int i) {
    return (i - 1) / 2;
}

void switchToParent(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/* 
    Creates priorty queue for unordered list of data (values are the priorties)
    [queue] -> current state of priorty queue
    [currentIndex] -> index of last added element
    [element] -> element to be queued
*/
void queue(int queue[], int currentIndex, int element) {
    // first add element to end of queue
    queue[currentIndex] = element;

    // then push element to parents index untill it's smaller than parent
    while (element > queue[parent(currentIndex)]) {
        switchToParent(queue, currentIndex, parent(currentIndex));
        currentIndex = parent(currentIndex);
    }
}

/*
    Converts array to Node sturcture
    [node] -> pointer to root node pointer
    [priorityQueue] -> array representation of priority queue
    [index] -> current index
*/
void convert(Node **node, int priorityQueue[], int index) {
    if (index < arrayLen()) {
        // allocate memory for node
        *node = malloc(sizeof(**node));

        (*node)->data = priorityQueue[index];

        (*node)->left = NULL;  // should assign the nodes to null
        (*node)->right = NULL; // in case of there is no more node

        // insert left and right nodes to root node recursively
        convert(&(*node)->left, priorityQueue, leftChild(index));
        convert(&(*node)->right, priorityQueue, rightChild(index));
    }
}

int *readFile() {

    FILE *filePointer;

    // change to file name that contains amount of data required
    // data.txt contains 20 element by default.
    char fileName[] = "data.txt";

    filePointer = fopen(fileName, "r");

    int *numbers = malloc(arrayLen() * sizeof(int));

    int element;
    int i = 0;

    while (fscanf(filePointer, "%d", &element) == 1) {
        numbers[i] = element;
        i++;
    }

    return numbers;
}

/*
    Traverses node structure of priorty queue into array representation.
    [node] -> pointer to node
    [arr] -> array to represent structure
    [index] -> current index
*/
void traverseTree(Node *node, int arr[], int index) {
    arr[index] = node->data;

    if (node->left != NULL) {
        traverseTree(node->left, arr, leftChild(index));
    }

    if (node->right != NULL) {
        traverseTree(node->right, arr, rightChild(index));
    }
}

void writeToFile(Node *node) {
    int *traversed = malloc(arrayLen() * sizeof(int));

    traverseTree(node, traversed, 0);

    FILE *filePointer;

    filePointer = fopen("result.txt", "w");

    for (int i = 0; i < arrayLen(); i++) {
        fprintf(filePointer, "%d ", traversed[i]);
    }
}

int main() {

    int *numberPointer = readFile();

    clock_t t;
    t = clock();
    int *priorityQueue = malloc(arrayLen() * sizeof(int));
    ;
    int size = -1;

    for (int i = 0; i < arrayLen(); i++) {
        queue(priorityQueue, i, *(numberPointer + i));
    }

    t = clock() - t;
    double executionTime = ((double)t) / CLOCKS_PER_SEC;

    printf("Creating queue took %f seconds \n", executionTime);

    Node *node;

    convert(&node, priorityQueue, 0);

    writeToFile(node);

    return 0;
}
