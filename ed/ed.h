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
	struct LIST (TYPE)* PREV;
}LIST (TYPE);

#define QUEUE(T) TOKENPASTE(queue_, T)
typedef struct QUEUE (TYPE){
	LIST (TYPE) * FIRST;
	LIST (TYPE) * LAST;
}QUEUE (TYPE);

#define STACK(T) TOKENPASTE(stack_, T)
typedef struct STACK (TYPE){
	LIST (TYPE) * LAST;
}STACK (TYPE);

#define SIZE(T) TOKENPASTE(size_, T)
int SIZE (TYPE) (LIST (TYPE) * list){
	int x;
	for(x = 0; list != NULL; x++, list = list->NEXT);
	return x;
}

#define GET(T) TOKENPASTE(get_, T)
LIST (TYPE) * GET (TYPE) (LIST (TYPE) * list, int index){
	int x;
	for(x = 0; list != NULL && x < index; x++, list = list->NEXT);
	return list;
}

#define GET_LAST(T) TOKENPASTE(get_last_, T)
LIST (TYPE) * GET_LAST (TYPE) (LIST (TYPE) * list){
	return GET (TYPE) (list, (SIZE (TYPE) (list)) - 1);
}

#define GET_DATA(T) TOKENPASTE(get_data_, T)
TYPE * GET_DATA (TYPE) (LIST (TYPE) * list, int index){
	int x;
	for(x = 0; list != NULL && x < index; x++, list = list->NEXT);
	if(list == NULL)
		return NULL;
	return list->DATA;
}

#define GET_FIRST_DATA(T) TOKENPASTE(get_first_data_, T)
TYPE * GET_FIRST_DATA (TYPE) (LIST (TYPE) * list){
	if(list == NULL)
		return NULL;
	return list->DATA;
}

#define GET_LAST_DATA(T) TOKENPASTE(get_last_data_, T)
TYPE * GET_LAST_DATA (TYPE) (LIST (TYPE) * list){
	return GET (TYPE) (list, SIZE(TYPE) (list) - 1)->DATA;
}

#define ADD_AT_END(T) TOKENPASTE(add_end_, T)
LIST (TYPE) *ADD_AT_END (TYPE) (LIST (TYPE) * list, TYPE* DATA){
	LIST (TYPE) *novo = (LIST (TYPE)*) malloc(sizeof(LIST (TYPE)));
	novo->DATA = DATA;
	novo->NEXT = NULL;
	novo->PREV = NULL;
	if(list == NULL)
		return novo;
	LIST (TYPE) *aux = list;
	while(aux->NEXT != NULL)
		aux = aux->NEXT;
	aux->NEXT = novo;
	novo->PREV = aux;
	return list;
}

#define ADD_AT_BEGIN(T) TOKENPASTE(add_begin_, T)
LIST (TYPE) *ADD_AT_BEGIN (TYPE) (LIST (TYPE) * list, TYPE* DATA){
	LIST (TYPE) *novo = (LIST (TYPE) *) malloc(sizeof(LIST (TYPE)));
	novo->DATA = DATA;
	novo->NEXT = list;
	novo->PREV = NULL;
	if(list != NULL)
		list->PREV = novo;
	return novo;
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
	aux->NEXT->PREV = aux;
	return list;
}

#define PURGE(T) TOKENPASTE(purge_, T)
LIST (TYPE) *PURGE (TYPE) (LIST (TYPE) * list, int index){
	int x;
	LIST (TYPE) *aux = list, *aux2;
	for(x = 0; x < index-1 && aux != NULL; x++, aux = aux->NEXT);
	if(aux == NULL)
		return list;
	if(aux->NEXT == NULL)
		return list;
	if(aux->PREV == NULL){
		aux->NEXT->PREV = NULL;
		aux2 = aux->NEXT;
		free(aux);
		return aux2;
	}
	aux->PREV->NEXT = aux->NEXT;
	aux->NEXT->PREV = aux->PREV;
	free(aux);
	return list;
}

#define REMOVE_FIRST(T) TOKENPASTE(remove_first_, T)
LIST (TYPE) *REMOVE_FIRST (TYPE) (LIST (TYPE) * list){
	if(list == NULL)
		return NULL;
	list = list->NEXT;
	if(list != NULL){
		list->PREV->NEXT = NULL;
		list->PREV = NULL;
	}
	return list;
}

#define PURGE_FIRST(T) TOKENPASTE(purge_first_, T)
LIST (TYPE) *PURGE_FIRST (TYPE) (LIST (TYPE) * list){
	if(list == NULL)
		return NULL;
	LIST (TYPE) * aux = list;
	list = list->NEXT;
	if(list != NULL)
		list->PREV = NULL;
	free(aux);
	return list;
}

#define PURGE_NODE(T) TOKENPASTE(purge_node_, T)
LIST (TYPE) *PURGE_NODE (TYPE) (LIST (TYPE) * list){
	if(list == NULL)
		return NULL;
	LIST (TYPE) * aux;
	if(list->PREV == NULL){
		aux = list->NEXT;
		free(list->DATA);
		free(list);
		if(aux != NULL)
			aux->PREV = NULL;
		return aux;
	}
	for(aux = list; aux->PREV != NULL; aux = aux->PREV);
	list->PREV->NEXT = list->NEXT;
	if(list->NEXT != NULL)
		list->NEXT->PREV = list->PREV;
	free(list->DATA);
	free(list);
	return aux;
}

#define PURGE_ALL(T) TOKENPASTE(purge_all_, T)
LIST (TYPE) *PURGE_ALL (TYPE) (LIST (TYPE) * list){
	if(list == NULL)return NULL;
	PURGE_ALL(TYPE)(list->NEXT);
	free(list);
	return NULL;
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
	return SIZE (TYPE) (queue.FIRST);
}

#define QUEUE_GET_FIRST(T) TOKENPASTE(queue_get_first_, T)
TYPE * QUEUE_GET_FIRST (TYPE) (QUEUE (TYPE) queue){
	return queue.FIRST->DATA;
}

#define QUEUE_GET_LAST(T) TOKENPASTE(queue_get_last_, T)
TYPE * QUEUE_GET_LAST (TYPE) (QUEUE (TYPE) queue){
	return queue.LAST->DATA;
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
