#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#ifdef INT
typedef int     value_type;
typedef double      key_type;
#endif

#ifdef CHAR
typedef char     value_type[80];
typedef int      key_type;
#endif

typedef struct NODE{
  value_type value;
  key_type   key;
  struct NODE* next;
  struct NODE* sort;
}Node;

typedef struct{
  int size;
  Node * head;
  Node * tail;
  Node * head_sort;
  Node * tail_sort;
}Sorted_List;

//FUNCTION HEADERS
int           size                  (Sorted_List *);
int           push                  (Sorted_List * , value_type   , key_type );
int           append                (Sorted_List * , value_type   , key_type );
int           remove_first          (Sorted_List * , value_type * , key_type *);
int           remove_last           (Sorted_List * , value_type * , key_type *);
int           remove_smallest_key   (Sorted_List * , value_type * , key_type *);
int           remove_largest_key    (Sorted_List * , value_type * , key_type *);
void          print_list            (Sorted_List *);
void          print_sort            (Sorted_List *);
void          sort_list_key         (Sorted_List *);
void          empty_list            (Sorted_List *);
void          destroy_list          (Sorted_List *);
void          insert_list_sort      (Node ** , Node* );
Node         *insert_value          (Node *  , value_type , key_type );
Node         *add_front             (Node ** , value_type , key_type );
Node         *find_prev             (Node *  , key_type );
Node         *find_prev_sort        (Node *  , key_type );
Node         *remove_within         (Sorted_List * , key_type );
Node         *remove_after          (Node *);
Node         *remove_after_sort     (Node *);
Node         *remove_head           (Sorted_List *);
Sorted_List  *create_list           ();