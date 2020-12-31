#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    //this is a node in a linked list, designed for our program
    struct node* next;
    struct node* prev;
    char* word; //the value in the node (a word)
    bool used; //indicates if the word was already used for the note
};

struct linked_list {
    //this is a linked list struct
    struct node* first;
    struct node* last;
};

char* readline();
char** split_string(char*);
bool search_in_list(struct linked_list* list, char* word_to_find);
void list_push(struct linked_list* list, char* this_word);
void free_list(struct linked_list* list);
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note);

bool search_in_list(struct linked_list* list, char* word_to_find) {
    //run through the list, searching for an unused node with a specific value
    struct node* current_node = list->first;
    while (current_node != NULL) {
        if (strcmp(current_node->word, word_to_find) == 0) {
            if (current_node->used == false) {
                current_node->used = true;
                return true;
            }
        }
        current_node = current_node->next;
    }
    return false;
}

void list_push(struct linked_list* list, char* this_word) {
    //creates a node with a specific value, and adds it to the end of the list
    struct node* new_node = malloc(sizeof(struct node));
    new_node->word = this_word;
    new_node->next = NULL;
    new_node->prev = list->last;
    new_node->used = false;

    if (list->first == NULL) { // check is list is empty
        list->first = new_node;
    }
    else {
        list->last->next = new_node;
    }
    list->last = new_node;
}

void free_list(struct linked_list* list) {
    // frees the list from memory
    struct node* current_node = list->first;
    struct node* next_node;
    while (current_node != NULL) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
}

// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {
    // checks if it's possible to make the note using the magazine
    struct linked_list* magazine_words = malloc(sizeof(struct linked_list));
    magazine_words->first = NULL;
    magazine_words->last = NULL;

    for (int i = 0; i < magazine_count; i++) {
        // creates a list of the words in the magazine
        list_push(magazine_words, magazine[i]);
    }

    for (int i = 0; i < note_count; i++) {
        // searches the words in the note in the magazine list
        if(search_in_list(magazine_words, note[i]) == false) {
            // if didn't found word
            printf("No");
            free_list(magazine_words);
            return;
        }
    }

    printf("Yes");
    free_list(magazine_words);
    return;
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
