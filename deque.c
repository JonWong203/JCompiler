/*
 * Copyright ©2022 Travis McGaha.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Pennsylvania
 * CIS 2400 for use solely during Fall Semester 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>
#include <stdlib.h>

#include "deque.h"


///////////////////////////////////////////////////////////////////////////////
// Deque implementation.


// Allocates and returns a pointer to a new Deque.
// It is the Caller's responsibility to at some point call Deque_Free to free
// the associated memory.
//
// Arguments: none.
//
// Returns:
// - the newly-allocated linked list, or NULL on error.
Deque* Deque_Allocate() {
	Deque* ptr = malloc(sizeof(Deque));
	ptr->num_elements = 0;
	ptr->front = NULL;
	ptr->back = NULL;
  return ptr;
}

// TODO: The rest of the Deque functions described in Deque.h


// Free a Deque that was previously allocated by Deque_Allocate.
//
// Arguments:
// - dq: the deque to free.  It is unsafe to use "dq" after this
//   function returns.
void Deque_Free(Deque *dq) {
	int val;
	while(dq->num_elements > 0){
		Deque_Pop_Front(dq, &val);
	}
	free(dq);
}

// Return the number of elements in the deque.
//
// Arguments:
// - dq:  the deque to query.
//
// Returns:
// - deque size.
int Deque_Size(Deque *dq) {
	return dq->num_elements;
	//int* int_ptr = malloc(typeof(int));
	//int_ptr = dq->num_elements;
	//return int_ptr;
}


// Adds a new element to the front of the Deque.
//
// Arguments:
// - dq: the Deque to push onto.
// - payload: the payload to push to the front
void Deque_Push_Front(Deque *dq, int *payload){
	DequeNode *node_ptr = malloc(sizeof(DequeNode));
	if (node_ptr == NULL) {
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
	// Initialize node_ptr
	node_ptr->payload = *payload;
	node_ptr->prev = NULL;
	// Update first element
	if (dq->num_elements == 0) {
		node_ptr->next = NULL;
		dq->front = node_ptr;
		dq->back = node_ptr;
	}
	else {
		node_ptr->next = dq->front;
		dq->front->prev = node_ptr;
		dq->front = node_ptr;
	}
	// Update size
	dq->num_elements = dq->num_elements + 1;
}


// Pop an element from the front of the deque.
//
// Arguments:Invalid write of size 
// - dq: the Deque to pop from.
// - payload_ptr: a return parameter; on success, the popped node's payload
//   is returned through this parameter.
//
// Returns:
// - false on failure (eg, the deque is empty).
// - true on success.
bool Deque_Pop_Front(Deque *dq, int *payload_ptr){
	if (dq->num_elements == 0) {
		return false;
	}
	// Store popped value
	*payload_ptr = dq->front->payload;
	// Get pointer for old first
	DequeNode *node_ptr = dq->front;
	if (dq->num_elements == 1) {
		dq->front = NULL;
		dq->back = NULL;
	}
	else {
		dq->front = dq->front->next;
		dq->front->prev = NULL;
	}
	// Free the old first
	free(node_ptr);
	node_ptr = NULL; // is this repetitive?
	//decrease size by 1
	dq->num_elements = dq->num_elements - 1;
	return true;
}


// Peeks at the element at the front of the deque.
//
// Arguments:
// - dq: the Deque to peek.
// - payload_ptr: a return parameter; on success, the peeked node's payload
//   is returned through this parameter.
//
// Returns:
// - false on failure (eg, the deque is empty).
// - true on success.
bool Deque_Peek_Front(Deque *dq, int *payload_ptr){
	if (dq->num_elements == 0) {
	return false;
	}
	*payload_ptr = dq->front->payload;
	return true;
}

// Pushes a new element to the end of the deque.
//
// This is the "end" version of Deque_Push_Front.
//
// Arguments:
// - dq: the Deque to push onto.
// - payload: the payload to push to the end
void Deque_Push_Back(Deque *dq, int *payload){
	DequeNode *node_ptr = malloc(sizeof(DequeNode));
	if (node_ptr == NULL){
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
	// Initialize node_ptr
	node_ptr->payload = *payload;
	node_ptr->next = NULL;
	// Update first element
	if (dq->num_elements == 0) {
		node_ptr->prev = NULL;
		dq->front = node_ptr;
		dq->back = node_ptr;
	}
	else {
		node_ptr->prev = dq->back;
		dq->back->next = node_ptr;
		dq->back = node_ptr;
	}
	// Update size
	dq->num_elements = dq->num_elements +1;
}

// Pops an element from the end of the deque.
//
// This is the "end" version of Deque_Pop_Front.
//
// Arguments:
// - dq: the Deque to remove from
// - payload_ptr: a return parameter; on success, the popped node's payload
//   is returned through this parameter.
//
// Returns:
// - false: on failure (eg, the deque is empty).
// - true: on success.
bool Deque_Pop_Back(Deque *dq, int *payload_ptr){
	if (dq->num_elements == 0) {
	return false;
	}
	// Initialize payload_ptr value
	*payload_ptr = dq->back->payload;
	// Get node to be removed
	DequeNode *node_ptr = dq->back;
	if (dq->num_elements == 1){
		dq->front = NULL;
		dq->back = NULL;
	}
	else {
		dq->back = dq->back->prev;
		dq->back->next = NULL;
	}
	free(node_ptr);
	node_ptr = NULL; // is this repetitive
	// Decrease size
	dq->num_elements = dq->num_elements - 1;
	return true;
}

// Peeks at the element at the back of the deque.
//
// Arguments:
// - dq: the Deque to peek.
// - payload_ptr: a return parameter; on success, the peeked node's payload
//   is returned through this parameter.
//
// Returns:
// - false on failure (eg, the deque is empty).
// - true on success.
bool Deque_Peek_Back(Deque *dq, int *payload_ptr){
	if (dq->num_elements == 0) {
		return false;
	}
	*payload_ptr = dq->back->payload;
	return true;
}


///////////////////////////////////////////////////////////////////////////////
// DQIterator implementation.


DQIterator* DQIterator_Allocate(Deque *dq) {
  // TODO: The rest of this function
  DQIterator* deq_iterator = malloc(sizeof(DQIterator));
  //DequeNode* deq_node = malloc(sizeof(DequeNode));
  if (deq_iterator == NULL) {
  	printf("ERROR");
  	exit(EXIT_FAILURE);
  }
  deq_iterator->deque = dq;
  deq_iterator->node = dq->front;
  return deq_iterator;
}

// TODO: The rest of the DQIterator functions described in Deque.h

// When you're done with an iterator, you must free it by calling this
// function.
//
// Arguments:
// - iter: the iterator to free. Don't use it after freeing it.
void DQIterator_Free(DQIterator *iter){
	free(iter);
}

// Tests to see whether the iterator is pointing at a valid element.
// Note tha a iterator on the last element of a deque would still be valid.
// An invalid iterator is one that is past the end of the Deque.
//
// Arguments:
// - iter: the iterator to test.
//
// Returns:
// - true: if iter is not past the end of the deque.
// - false: if iter is past the end of the deque.
bool DQIterator_IsValid(DQIterator *iter){
	return iter->node != NULL;
}

// Advance the iterator, i.e. move to the next node in the deque.  The
// passed-in iterator must be valid (eg, not "past the end").
// Passing in an invalid iterator is undefined behaviour.
//
// Arguments:
// - iter: the iterator.
//
// Returns:
// - true: if the iterator has been advanced to the next node.
// - false: if the iterator is no longer valid after the
//   advancing has completed (eg, it's now "past the end").
bool DQIterator_Next(DQIterator *iter){
	if (!DQIterator_IsValid(iter) || iter->node->next == NULL){
		iter->node = NULL;
		return false;
	}
	iter->node = iter->node->next;
	return true;
}

// Returns the payload of the node that the iterator currently points
// at.  The passed-in iterator must be valid (eg, not "past the end").
// Passing in an invalid iterator is undefined behaviour.
//
// Arguments:
// - iter: the iterator to fetch the payload from.
// - payload: a "return parameter" through which the payload is returned.
void DQIterator_Get(DQIterator *iter, int payload){
	payload = iter->node->payload;
	//if (DQIterator_IsValid(iter)){
	//	*payload = iter->node->payload;
	//}

}


// Remove the node the iterator is pointing to.  After deletion, the iterator
// may be in one of the following three states:
// - if there was only one element in the list, the iterator is now invalid
//   and cannot be used.  In this case, the caller is recommended to free
//   the now-invalid iterator.
// - if the deleted node had a successor (ie, it was pointing at the end),
//   the iterator is now pointing at the successor.
// - if the deleted node was the end, the iterator is now pointing at the
//    predecessor.
//
// The passed-in iterator must be valid (eg, not "past the end").
// Passing in an invalid iterator is undefined behaviour.
//
// Arguments:
// - iter:  the iterator to delete from.
//
// Returns:
// - true if the deletion succeeded, the deque is still non-empty,
//   and thus the iterator is still valid.
//
// - false if the deletion succeeded, but the deque is now empty.
//   and thus the iterator is now invalid.
bool DQIterator_Remove(DQIterator *iter){
	DequeNode *newCurr = iter->node;
	if (newCurr->prev == NULL && newCurr->next == NULL){
		free(newCurr);
		iter->node = NULL;
		iter->deque->front = NULL;
		iter->deque->back = NULL;
		iter->deque->num_elements = iter->deque->num_elements - 1;
		return false;
	}
	else {
		int val;
		if(newCurr->next == NULL){
			iter->node = iter->node->prev;
			Deque_Pop_Back(iter->deque, &val);
		}
		else if(newCurr->prev == NULL){
			iter->node = iter->node->next;
			Deque_Pop_Front(iter->deque, &val);
		}
		else {
			//iter->node->prev = iter->node->prev;
			iter->node = iter->node->next;
			iter->node->prev = iter->node->prev->prev;
			iter->node->next = iter->node->next;
			iter->node->prev->next = iter->node;
			iter->deque->num_elements = iter->deque->num_elements - 1;
			free(newCurr);
			newCurr = NULL;
		}
	}
	return true;
}


// Rewind an iterator to the front of its deque.
//
// Arguments:
// - iter: the iterator to rewind.
void DQIterator_Rewind(DQIterator *iter){
	iter->node = iter->deque->front;
}

