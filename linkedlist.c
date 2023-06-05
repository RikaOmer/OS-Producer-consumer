#include <stdio.h>
#include <stdlib.h>
#include "openFile.h"

typedef struct {
int id;
int numberofproduce;
int queuesize;
} Details;
// Define the structure for a linked list element

typedef struct detailNode {
    Details value;
    struct derailNode* next;
} detailNode;
