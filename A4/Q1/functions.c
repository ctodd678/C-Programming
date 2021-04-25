#include "header.h"

#ifdef INT
void print_list(Sorted_List * list){
  Node * printThis = list->head;  //FOR TRAVERSAL
  int i = 0;                //FOR NODE POSITION
  printf("\n\nprint_all:  Insertion Order\n");
  while (printThis != NULL)
  {
    printf("%d    %.2lf  %d" , i + 1, printThis->key , printThis->value);
    printf("\n");
    printThis = printThis->next;
    i++;
  }
}

void print_sort(Sorted_List * list){
  Node * printThis = list->head_sort;  //FOR TRAVERSAL
  int i = 0;                      //FOR NODE POSITION
  printf("\n\nprint_sort:  Key Sort Order\n");
  while (printThis != NULL)
  {
    printf("%d    %.2lf  %d" , i + 1, printThis->key , printThis->value);
    printf("\n");
    printThis = printThis->sort;
    i++;
  }
}
#endif

#ifdef CHAR
void print_list(Sorted_List * list){
  Node * printThis = list->head;  //FOR TRAVERSAL
  int i = 0;                //FOR NODE POSITION
  printf("\n\nprint_all:  Insertion Order\n");
  while (printThis != NULL)
  {
    printf("%d    %d  %s" , i + 1, printThis->key , printThis->value);
    printf("\n");
    printThis = printThis->next;
    i++;
  }
}

void print_sort(Sorted_List * list){
  Node * printThis = list->head_sort;  //FOR TRAVERSAL
  int i = 0;                      //FOR NODE POSITION
  printf("\n\nprint_sort:  Key Sort Order\n");
  while (printThis != NULL)
  {
    printf("%d    %d  %s" , i + 1, printThis->key , printThis->value);
    printf("\n");
    printThis = printThis->sort;
    i++;
  }
}
#endif



Sorted_List * create_list () {    
  Sorted_List * new_list = malloc(sizeof(Sorted_List));    
  
  new_list->head = NULL;
  new_list->tail = NULL;      
  new_list->head_sort = NULL;
  new_list->tail_sort = NULL;         
  new_list->size = 0;    

  return new_list;
}

int size (Sorted_List * list){

  printf("size:       List size = %d" , list->size);

  return list->size;
}

int push (Sorted_List * list , value_type d , key_type f){

  if(list->head == NULL){
    list->tail = list->head;
  }
  
  Node * new_node = add_front(&(list->head) , d , f);
  list->head_sort = list->head;


  int result = (new_node != NULL);
    if(result == 1){
      list->size++;
    }

  return result;
}

int append (Sorted_List * list , value_type d , key_type f){

  int result = FAILURE;     
  Node *last = list->head; 

  if (last != NULL) {         
    while (last->next != NULL) {             
      last = last->next;        
     }     
  }     

  if (last != NULL){
    result = (insert_value(last, d , f) != NULL);
  }             

  if (result == SUCCESS){
    list->size++;   
  } 

  if(last->next != NULL){
    list->tail = last->next;
  }
  else{
    list->tail = last;
  }

  return result; 
}

int remove_first (Sorted_List * list , value_type *d , key_type *f) {  
  
  Node * removed;
  Node * prev = find_prev_sort(list->head_sort, list->head->key);
  Node * head = list->head->next;

  /*SET RETURN VALUES*/
  #ifdef CHAR
  strcpy(*d , list->head->value);
  #endif
  #ifdef INT
  *d = list->head->value;
  #endif
  *f = list->head->key; 

  /*REMOVE NODE*/
  if(prev != NULL){
    removed = remove_after_sort(prev);
  }
  list->head = head;
  list->size--;

  removed = NULL;
  free(removed);

  return SUCCESS;
}

int remove_last (Sorted_List * list , value_type *d , key_type *f) {  
  Node * removed , *removed_tail, *prev;
  key_type oldTail = list->tail->key;
  
  /*SET RETURN VALUES*/
  #ifdef CHAR
  strcpy(*d , list->tail->value);
  #endif
  #ifdef INT
  *d = list->tail->value;
  #endif
  *f = list->tail->key;

  /*REMOVE LARGEST FROM INSERTION ORDER*/
  prev = find_prev(list->head, list->tail->key);
   if(prev != NULL){
    list->tail = prev;
    removed = remove_after(prev);
  }
  
  /*REMOVE LARGEST FROM SORT ORDER*/
  list->tail_sort = find_prev_sort(list->head_sort, oldTail);
  if(list->tail_sort != NULL){
    removed_tail = remove_after_sort(list->tail_sort);
  }

  /*FREE AND DELETE*/
  removed = NULL;
  removed_tail = NULL;
  free(removed);
  free(removed_tail);

  list->size--;

  return SUCCESS;
}

int remove_smallest_key (Sorted_List * list , value_type *d , key_type *f) {  
  Node * head = list->head;
  Node * head_sort = list->head_sort->sort;
  Node * removed;
  

  value_type small_value;
  key_type small_key = 10000;

  /*FIND SMALLESTVALUE IN LIST*/
  while(head != NULL){
    if(small_key > head->key){
      #ifdef CHAR
      strcpy(small_value , head->value);
      #endif
      #ifdef INT
      small_value = head->value;
      #endif
      small_key = head->key;
    }
    head = head->next;
  }

  /*SET RETURN VALUES*/
  #ifdef CHAR
  strcpy(*d , small_value);
  #endif
  #ifdef INT
  *d = small_value;
  #endif
  *f = small_key;

  /*REMOVE SMALLEST FROM INSERTION ORDER*/
  Node * prev = find_prev(list->head, small_key);
   if(prev != NULL){
    removed = remove_after(prev);
  }
  list->head_sort = head_sort;

  removed = NULL;
  free(removed);

  list->size--;

  return SUCCESS;
}

int remove_largest_key (Sorted_List * list , value_type *d , key_type *f) {  
  Node *head = list->head;
  Node *removed , *removed_tail, *prev;

  value_type big_value;
  key_type   big_key = 0;

  /*FIND LARGEST VALUE IN LIST*/
  while(head != NULL){
    if(big_key < head->key){
      #ifdef CHAR
      strcpy(big_value , head->value);
      #endif
      #ifdef INT
      big_value = head->value;
      #endif
      big_key = head->key;
    }
    head = head->next;
  }

  /*SET RETURN VALUES*/
  #ifdef CHAR
  strcpy(*d , big_value);
  #endif
  #ifdef INT
  *d = big_value;
  #endif
  *f = big_key;

  /*REMOVE LARGEST FROM INSERTION ORDER*/
  prev = find_prev(list->head, big_key);
   if(prev != NULL){
    removed = remove_after(prev);
  }

  /*REMOVE LARGEST FROM SORT ORDER*/
  list->tail_sort = find_prev_sort(list->head_sort, big_key);
  if(list->tail_sort != NULL){
    removed_tail = remove_after_sort(list->tail_sort);
  }

  removed = NULL;
  removed_tail = NULL;
  free(removed);
  free(removed_tail);

  list->size--;

  return SUCCESS;
}

void insert_list_sort(Node** head, Node* sortNode){
  
	Node toSort;
  Node* temp = &toSort;
	toSort.sort = *head;

  //COMPARE VALUES AND INSERT NODE
	while (temp->sort != NULL && temp->sort->key < sortNode->key){
    temp = temp->sort;
  }

	sortNode->sort = temp->sort;
	temp->sort = sortNode;
	*head = toSort.sort;
}

void sort_list_key(Sorted_List* list){
	Node* sorted = NULL; 	      // sorted HEAD POINTER
	Node* temp = list->head_sort;	  // temp POINTER TO TRAVERSE LIST
	Node* sort;                // sort1 POINTER 

  key_type big_key = 0;
  //LOOP THROUGH & SORT LIST
	while (temp != NULL){
    if(big_key < temp->key){
      big_key = temp->key;
      list->tail_sort = temp;
    }
		sort = temp->sort;
		insert_list_sort(&sorted , temp); //INSERT NODE INTO SORTED POSITION
		temp = sort;
	}
	list->head_sort = sorted;
}

void empty_list(Sorted_List * list){

  Node * new_head = list->head, * old_node = NULL; 

  while ( new_head != NULL ) {         
    old_node = new_head;            
    new_head = new_head->next;         
    free ( old_node );     
  }
  free(new_head);
  
  free(list->tail);
  list->size = 0;

  printf("\nempty:      size = %d" , list->size);

}

void destroy_list(Sorted_List * list){
  if(list->size != 0){
    empty_list(list);
  }
  free(list);
}

Node * insert_value(Node * prev, value_type d, key_type f){
     
  Node * new_node = malloc(sizeof(Node));     
  if (new_node != NULL) { 
    #ifdef CHAR
    strcpy(new_node->value , d);
    #endif
    #ifdef INT
    new_node->value = d;
    #endif        
    new_node->key = f;         
    new_node->next = prev->next;
    new_node->sort = prev->sort;           
    prev->next = new_node;
    prev->sort = new_node;     
  }     
  return new_node; 
}

Node * add_front(Node ** head, value_type d, key_type f){ 

  Node * new_node = malloc(sizeof(Node));  

  if(new_node != NULL){
    #ifdef CHAR
    strcpy(new_node->value , d);
    #endif
    #ifdef INT
    new_node->value = d;
    #endif
    new_node->key = f;
    new_node->next = *head;
    new_node->sort = *head;
    *head = new_node;
  }
  return new_node; 
}

Node * find_prev(Node * head, key_type f){
  Node *temp = head, *prev = NULL;   
     
  while ((temp != NULL) && (temp->key != f)) {         
    prev = temp;         
    temp = temp->next;   
  }     
  return prev;
}

Node * find_prev_sort(Node * head, key_type f){
  Node *temp = head, *prev = NULL;   
     
  while ((temp != NULL) && (temp->key != f)) {         
    prev = temp;         
    temp = temp->sort;   
  }     
  return prev;
}

Node * remove_after ( Node * node ){    
  Node * remove = node->next;    
  node->next = remove->next;    
  remove->next = NULL;    
  return remove; 
}

Node * remove_after_sort ( Node * node ){    
  Node * remove = node->sort;    
  node->sort = remove->sort;    
  remove->sort = NULL;    
  return remove; 
}

Node * remove_within(Sorted_List * list , key_type f){
  Node * removed = NULL;     
  Node * prev = find_prev(list->head, f);     
  if (prev != NULL){
      removed = remove_after(prev);     
  }
  else
  {
    printf("\nRIP");
  }          
  return removed;
}

