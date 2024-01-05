#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

struct deque * new_deque() {
    struct deque *new_deque = malloc(sizeof(struct deque));
    new_deque->elements = NULL;
    new_deque->size = 0;
    new_deque->nelements = 0;
    return new_deque;
}

void push_front_deque(struct deque * this, char * str) {
    if (this->nelements == this->size) {
        int new_size = (this->size == 0) ? 1 : this->size * 2;
        char **new_elements = malloc(new_size * sizeof(char *));
        new_elements[0] = str;
        for (int i = 0; i < this->nelements; i++) {
            new_elements[i + 1] = this->elements[i];
        }
        this->elements = new_elements;
        this->size = new_size;
    } else {
        for (int i = this->nelements; i > 0; i--) {
            this->elements[i] = this->elements[i - 1];
        }
        this->elements[0] = str;
    }
    this->nelements++;
}

char * pop_front_deque(struct deque * this) {
    char * first_element = this->elements[0];
    for (int i = 1; i < this->nelements; i++) {
        this->elements[i - 1] = this->elements[i];
    }
    this->nelements--;
    return first_element;
}

void push_back_deque(struct deque * this, char * str) {
    if (this->nelements == this->size) {
        int new_size = (this->size == 0) ? 1 : this->size * 2;
        char **new_elements = realloc(this->elements, new_size * sizeof(char *));
        if (new_elements == NULL) return;

        this->elements = new_elements;
        this->size = new_size;
    }

    this->elements[this->nelements] = strdup(str);
    this->nelements++;
}

char * pop_back_deque(struct deque * this) {
    if (this->nelements == 0) return NULL;
    char * back_element = this->elements[this->nelements - 1];
    this->nelements--;
    return back_element;
}

void free_deque(struct deque * this) {
    for (int i = 0; i < this->nelements; i++) {
        free(this->elements[i]);
    }
    free(this->elements);
    free(this);
}
// return a string from the deque at position "index", where the
// item at the front of the deque has index 0, and subsequent
// items are numbered successively. If there are fewer than index+1
// items in the deque, return a string containing the value "ERROR"
char * item_at_deque(struct deque * this, int index) {
    if (this->nelements < index) {
        return "ERROR";
    }
    return this->elements[index];
}
