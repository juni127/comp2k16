/*
	Inclua essa biblioteca assim:

	#define TYPE tipo_necessario
	#include "ed.h"
	#undef TYPE
*/

#define TOKENPASTE(x, y) x ## y

#define LIST(T) TOKENPASTE(list_, T)
typedef struct LIST (TYPE){
	TYPE* DATA;
	struct LIST (TYPE)* NEXT;
}LIST (TYPE);

#define QUEUE(T) TOKENPASTE(queue_, T)
typedef struct QUEUE (TYPE){
	LIST (TYPE) * FIRST;
	LIST (TYPE) * LAST;
}QUEUE (TYPE);

#define ADD_AT_END(T) TOKENPASTE(add_end_, T)
LIST (TYPE) *ADD_AT_END (TYPE) (LIST (TYPE) * list, TYPE* DATA){
	LIST (TYPE) *novo = (LIST (TYPE)*) malloc(sizeof(LIST (TYPE)));
	novo->DATA = DATA;
	novo->NEXT = NULL;
	if(list == NULL)
		return novo;
	LIST (TYPE) *aux = list;
	while(aux->NEXT != NULL)
		aux = aux->NEXT;
	aux->NEXT = novo;
	return list;
}

#define REMOVE(T) TOKENPASTE(remove_, T)
LIST (TYPE) *REMOVE (TYPE) (LIST (TYPE) * list, int index){
	int x;
	LIST (TYPE) *aux = list;
	for(x = 0; x < index-1 && aux != NULL; x++, aux = aux->NEXT);
	if(aux == NULL)
		return list;
	if(aux->NEXT == NULL)
		return list;
	aux->NEXT = aux->NEXT->NEXT;
	return list;
}

#define REMOVE_FIRST(T) TOKENPASTE(remove_first_, T)
LIST (TYPE) *REMOVE_FIRST (TYPE) (LIST (TYPE) * list){
	if(list == NULL)
		return NULL;
	LIST (TYPE) * aux = list;
	list = list->NEXT;
	aux->NEXT = NULL;
	return list;
}

#define PURGE_FIRST(T) TOKENPASTE(purge_first_, T)
LIST (TYPE) *PURGE_FIRST (TYPE) (LIST (TYPE) * list){
	if(list == NULL)
		return NULL;
	LIST (TYPE) * aux = list;
	list = list->NEXT;
	free(aux);
	return list;
}

#define QUEUE_INIT(T) TOKENPASTE(queue_init_, T)
QUEUE (TYPE) QUEUE_INIT (TYPE) (){
	QUEUE(TYPE) result;
	result.FIRST = NULL;
	result.LAST = NULL;
	return result;
}

#define QUEUE_SIZE(T) TOKENPASTE(queue_size_, T)
int QUEUE_SIZE (TYPE) (QUEUE (TYPE) queue){
	LIST (TYPE) * aux = queue.FIRST;
	int x = 0;
	for(; aux != NULL; x++, aux = aux->NEXT);
	return x;
}

#define QUEUE_GET(T) TOKENPASTE(queue_get_, T)
TYPE * QUEUE_GET (TYPE) (QUEUE (TYPE) queue){
	return queue.FIRST->DATA;
}

#define QUEUE_ADD(T) TOKENPASTE(queue_add_, T)
void QUEUE_ADD (TYPE) (QUEUE (TYPE) * queue, TYPE* DATA){
	queue->FIRST = ADD_AT_END (TYPE) (queue->FIRST, DATA);
	if(queue->LAST == NULL)
		queue->LAST = queue->FIRST;
	else
		queue->LAST = queue->LAST->NEXT;
}

#define QUEUE_REMOVE(T) TOKENPASTE(queue_remove_, T)
LIST (TYPE) *QUEUE_REMOVE (TYPE) (QUEUE (TYPE) * queue){
	LIST(TYPE) *result = queue->FIRST;
	queue->FIRST = REMOVE_FIRST (TYPE) (queue->FIRST);
	if(queue->FIRST == NULL)queue->LAST = NULL;
	return result;
}

#define QUEUE_PURGE(T) TOKENPASTE(queue_purge_, T)
void QUEUE_PURGE (TYPE) (QUEUE (TYPE) * queue){
	queue->FIRST = PURGE_FIRST (TYPE) (queue->FIRST);
	if(queue->FIRST == NULL)queue->LAST = NULL;
}
