#ifndef DICTIONARY_H
#define DICTIONARY_H
#define HASHSIZE 31013
typedef struct Chain Chain;
typedef struct Chain { /* table entry: */
    Chain *next; /* next entry in chain */
    char *name; /* defined name */
    long value;
}Chain;

typedef struct Dictionary Dictionary;

struct Dictionary{
  Chain* hashtab[HASHSIZE];   
};

Dictionary* new_dictionary();
void set_var(Dictionary *dict, char *name, long value);
long get_var(Dictionary *dict, char *name);
void free_dict(Dictionary* dict);
Chain *put(Dictionary* dict, char *name, long value);
void print_dict(Dictionary* dict);
Chain *get(Dictionary* dict, char *s);
unsigned hash(char *s);

#endif
