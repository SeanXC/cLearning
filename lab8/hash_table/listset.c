#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new()
{
    struct listset *result;
    result = malloc (sizeof(struct listset));
    result->head = NULL;
    return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item)
{
    struct listnode *current = this->head;
    int result = 0;
    while (current!=NULL)
    {
        if((strcmp(current->str, item))==0)
        {
            result = 1;
            break;
        }
        current = current->next;
    }
    return result;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item)
{
    if(!listset_lookup(this, item))
    {
        struct listnode *newNode;
        newNode = malloc(sizeof(struct listnode));
        newNode->str = item;

        //list is empty
        if (this->head == NULL)
        {
            this->head = newNode;
            newNode->next = NULL;
        }
            //list is not empty
        else
        {
            newNode->next = this->head;
            this->head = newNode;
        }
    }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
    if (this->head == NULL) {
        return;
    } else if (strcmp(this->head->str, item) == 0) {
        struct listnode *temp = this->head;
        this->head = temp->next;
        free(temp);
        return;
    } else {
        struct listnode *current = this->head;

        while (current->next != NULL) {
            if (strcmp(current->next->str, item) == 0) {
                struct listnode *tmp;
                tmp = current->next;
                current->next = current->next->next;
                free(tmp);
                return;
            }
            current = current->next;
        }
    }
}
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
                   struct listset * src2)
{
    struct listnode *destNode = src1->head;
    while (destNode!=NULL)
    {
        listset_add(dest, destNode->str);
        destNode = destNode->next;
    }
    struct listnode *src1Node = src1->head;
    while (src1Node!=NULL)
    {
        if(!listset_lookup(src2, src1Node->str))
        {
            listset_add(dest, src1Node->str);
        }
        src1Node = src1Node->next;
    }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
                       struct listset * src2)
{
    struct listnode *src1Node = src1->head;
    while (src1Node!=NULL)
    {
        if(listset_lookup(src2, src1Node->str))
        {
            listset_add(dest, src1Node->str);
        }
        src1Node = src1Node->next;
    }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
    struct  listnode *p;
    p = this->head;
    int count = 0;
    while ((p!=NULL))
    {
        count++;
        p=p->next;
    }
    return count;
    //for (p=this->head; p!=NULL;p=p->next)
    //{
    //count++;
    //}
}

// print the elements of the list set
void listset_print(struct listset * this) {
    struct listnode * p;

    for ( p = this->head; p != NULL; p = p->next ) {
        printf("%s, ", p->str);
    }
    printf("\n");
}
