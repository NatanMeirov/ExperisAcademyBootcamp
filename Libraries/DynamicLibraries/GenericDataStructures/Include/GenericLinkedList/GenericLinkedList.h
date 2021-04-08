/**
 * @file GenericLinkedList.h
 * @author Natan Meirov (NatanMeirov@gmail.com)
 * @brief Create a Generic Double Linked List data type that stores pointer to user provided elements of generic type
 * Using head and tail sentinels
 * Each node is allocated in the heap, and stores a pointer to user proveded element
 * Supports LinkedListIterator functionality
 * In version 2.1: Performance improvements
 * @version 2.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

/* Includes: */

#include <stddef.h>  /* size_t */


/* Defines: */

typedef struct LinkedList LinkedList;

typedef enum LinkedListResult
{
	LINKEDLIST_SUCCESS = 0,
	LINKEDLIST_UNINITIALIZED_ERROR,			    /* Not Initialized LinkedList error or NULL pointer error */
	LINKEDLIST_ALLOCATION_ERROR,				/* Node allocation failed due to heap error   */
    LINKEDLIST_UNDERFLOW_ERROR
} LinkedListResult;


/* ------------------------------------------- Main API Functions ------------------------------------ */

/** 
 * @brief Dynamically creates a new LinkedList object
 * @return LinkedList* - on success / NULL - on failure
 */
LinkedList* LinkedListCreate(void);


/** 
 * @brief Dynamically deallocates a previously allocated LinkedList, NULLs the LinkedList's pointer
 * @param[in] _list: LinkedList to be deallocated
 * @param[in] _elementDestroy: A function pointer to be used to destroy each element in the given LinkedList,
 * 			 				   or a NULL if no such destroy is required
 * @return None
 */
void LinkedListDestroy(LinkedList** _list, void (*_elementDestroy)(void* _element));


/** 
 * @brief Inserts a new element to be the head of the LinkedList (inserts it to the first place)
 * @details Time complexity: O(1)
 * @param[in] _list: A list to insert an element to its first place
 * @param[in] _element: An element to add, can be NULL
 * @return LinkedListResult - success or error status code
 * @retval LINKEDLIST_SUCCESS on success
 * @retval LINKEDLIST_UNINITIALIZED_ERROR on error - given pointer is NULL
 * @retval LINKEDLIST_ALLOCATION_ERROR on error - failed to allocate memory for a node
 */
LinkedListResult LinkedListInsertHead(LinkedList* _list, void* _element);


/** 
 * @brief Inserts a new data element to be the tail of the LinkedList (inserts it to the last place)
 * @details Time complexity: O(1)
 * @param[in] _list: A list to insert an element to its last place
 * @param[in] _element: An element to add, can be NULL
 * @return LinkedListResult - success or error status code
 * @retval LINKEDLIST_SUCCESS on success
 * @retval LINKEDLIST_UNINITIALIZED_ERROR on error - given pointer is NULL
 * @retval LINKEDLIST_ALLOCATION_ERROR on error - failed to allocate memory for a node
 */
LinkedListResult LinkedListInsertTail(LinkedList* _list, void* _element);


/** 
 * @brief Removes a data element from the head (start) of the LinkedList
 * @details Time complexity: O(1)
 * @param[in] _list: LinkedList to remove an element from its first place
 * @param[out] _pElement: A pointer to a variable that used to return the removed element's value by reference
 * @return LinkedListResult - success or error status code
 * @retval LINKEDLIST_SUCCESS on success
 * @retval LINKEDLIST_UNINITIALIZED_ERROR on error - given pointer is NULL
 * @retval LINKEDLIST_UNDERFLOW_ERROR on error - empty, no elements to remove
 *
 * @warning If _pElement is NULL: function will fail and return LINKEDLIST_UNINITIALIZED_ERROR
 */
LinkedListResult LinkedListRemoveHead(LinkedList* _list, void** _pElement);


/** 
 * @brief Removes a data element from the tail (end) of the LinkedList
 * @details Time complexity: O(1)
 * @param[in] _list: LinkedList to remove an element from its last place
 * @param[out] _pElement: A pointer to a variable that used to return the removed element's value by reference
 * @return LinkedListResult - success or error status code
 * @retval LINKEDLIST_SUCCESS on success
 * @retval LINKEDLIST_UNINITIALIZED_ERROR on error - given pointer is NULL
 * @retval LINKEDLIST_UNDERFLOW_ERROR on error - empty, no elements to remove
 *
 * @warning If _pElement is NULL: function will fail and return LINKEDLIST_UNINITIALIZED_ERROR
 */
LinkedListResult LinkedListRemoveTail(LinkedList* _list, void** _pElement);


/**
 * @brief Gets the actual number of elements in the LinkedList
 * @details Time complexity: O(n)
 * @param[in] _list: LinkedList to get its actual number of elements
 * @return size_t - number of elements in LinkedList, on success / MAX_SIZE_T (-1 in size_t - is the maximum size_t value), on failure
 */
size_t LinkedListSize(const LinkedList* _list);


/**
 * @brief Checks if a given LinkedList is empty or not
 * @details Time complexity: O(1)
 * @param[in] _list: A LinkedList to check if is empty
 * @return int - 0 if LinkedList is not empty or 1 if LinkedList is empty, on success / -1, on failure
 */
int LinkedListIsEmpty(const LinkedList* _list);

/* --------------------------------------- End of Main API Functions ---------------------------------- */

#endif /* #ifndef __LINKEDLIST_H__ */
