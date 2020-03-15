/*
  Filename   : queue.c
  Author     : Leandro Martinez
  Course     : CSCI 380-01
  Assignment : Program 1, Singly linked list queue
  Description: Create a singly linked list queue, add elements in the head or tail, reverse them, free them, check its size.
*/

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /*Check if malloc returns NULL*/
    if (q == NULL)
    {
    	return NULL;
    }
    /*intialize head, tail, and size*/
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
	/*if q is NULL return*/
	if (q == NULL)
	{
		return;
	}

	/* pointers used to traverse the queue as elements are freed, c = current, t = temp*/
	list_ele_t *c = q->head;
	list_ele_t *t = q->head;

	/*While current is not equal to NULL, set temp to current, current to next element and free temp*/
	while( c != NULL)
	{
		t = c;
		c = c->next;
		free(t);
	}

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
	/*if q is NULL return false*/
	if (q == NULL)
	{
		return false;
	}

	/*Create list_ele_t pointer to hold the inserted value*/
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    
    /*if pointer can't be allocated, return false*/
    if (newh == NULL)
    {
    	return false;
    }
    
    ++q->size;
    newh->value = v;
    newh->next = q->head;
    q->head = newh;
    if(q->size == 1)
    {
		q->tail = newh;
	}
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
    {
    	return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
    {
    	return false;
    }
    ++q->size;
    newt->value = v;
    newt->next = NULL;
    if (q->size == 1)
    {
    	q->head = newt;
    	q->tail = newt;
    }
    else
    {
    	q->tail->next = newt;
    	q->tail = newt;
    }
    

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
	if (q == NULL || q->head == NULL || q->size == 0)
		{
			return false;
		}
	if (vp != NULL) 
	{
		*vp = q->head->value;
	}
	list_ele_t *newh = q->head->next;
	free(q->head);
	q->head = newh; 
	--q->size;
	return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
	if(q == NULL)
		return 0;
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
	if(q == NULL || q->size == 0){
		return;
	}

	list_ele_t *c = q->head->next;
	list_ele_t *p = q->head;
	q->head = q->head->next;
	p->next = NULL;
	q->tail = p; 

	while(q->head != NULL)
	{
		q->head = q->head->next;
		c->next = p;
		p = c;
		c = q->head;
	}
	q->head = p;
}

