#ifndef FAST_QUEUE_H
#define FAST_QUEUE_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

template <typename T>
class FastQueue
{
public:
	FastQueue(); //default constructor
	void enqueue(const T & element); //Adds a new element to the end of the queue.
	void dequeue(); //Removes an element from the head of the queue. Does nothing if the queue is already empty.
	T & front(); //Returns reference to the first element of the queue. Throws out_of_range if the container is empty.
	T & back(); //Returns reference to the last element of the queue. Throws out_of_range if the container is empty.
	T & at(const int & index); //Returns reference to the index-th element of the queue. Throws out_of_range if the container size is less than index.
	int size(); //Returns the number of elements in the queue.
	int capacity(); //Returns the size of allocated memory in terms of elements.
	void shrink_to_fit(); //Shrinks the size of allocated memory to exactly fit the element currently in queue.
private:
	std::vector<T> storage; // uses vector<T> as an underlying container.
	int size_of_storage; //size of container
	int number_of_elements; //elements in container
	int first; //first element of the queue.
};
#endif

template <typename T>
FastQueue<T>::FastQueue() //default constructor
{
	size_of_storage = 1; //initialize size of container to hold atleast 1 item
	storage.reserve(size_of_storage); //create a default storage size of 1
	number_of_elements = 0;	//elements in storage
	first = 0; //first element is at storage[0]
}

template <typename T>
void FastQueue<T>::enqueue(const T & element) //Adds a new element to the end of the queue.
{
  if ( number_of_elements < size_of_storage) //checks if there is space in container
  {
    storage[(first + number_of_elements) % size_of_storage] = element; //adds element to end of queue
    number_of_elements++; //increase number of elements
  }
  else //if container is full 
  {
    std::vector<T> new_storage; //create a new container
    size_of_storage *= 2; //size of container doubles to hold new element
    new_storage.reserve(size_of_storage); //container has space to fit number of elements
    for (int i = 0; i < number_of_elements; i++)
      new_storage[i] = storage[(first + i) % size_of_storage]; //new container contains elements of old container with relocation  
    storage.swap(new_storage); //swap the containers
    first = 0; //first element should start at 0 again
    storage[(first + number_of_elements) % size_of_storage] = element; //stores element into end of old container  
    number_of_elements++; //increase number of elements	
  }
}

template <typename T>
void FastQueue<T>::dequeue() //Removes an element from the head of the queue. Does nothing if the queue is already empty.
{
	if (number_of_elements != 0) // check if there are elements in container
	{
		first = (first + 1) % size_of_storage; //sets first element to next element in case if first element not at 0
		number_of_elements--; //decrease number of elements
	}
	else
	{
		return; //does nothing if container empty
	}
}

template <typename T>
T & FastQueue<T>::front() //Returns reference to the first element of the queue. Throws out_of_range if the container is empty
{
	if (number_of_elements == 0) //checks if container is empty
		throw std::out_of_range("container is empty"); //out of range
	else
	{
		return storage[first]; //returns reference to first element 
	}
}

template <typename T> 
T & FastQueue<T>::back() //Returns reference to the last element of the queue. Throws out_of_range if the container is empty.
{
	if (number_of_elements == 0) //checks if container is empty
		throw std::out_of_range("container is empty"); //out of range
	else
	{
		return storage[(first + number_of_elements - 1) % size_of_storage]; //returns reference to last element taken into account possible relocations
	}
}

template <typename T>
T & FastQueue<T>::at(const int & index) //Returns reference to the index-th element of the queue. Throws out_of_range if the container size is less than index.
{
	if ((size_of_storage < index) || (number_of_elements == 0) || (index == 0)) //checks if there are elements, storage, and index-th element should start from 1
		throw std::out_of_range("container size less than index"); //out of range
	else
	{
		return storage[(first + index - 1) % size_of_storage]; //returns reference to index-th element
  }
}

template <typename T>
int FastQueue<T>::size() //Returns the number of elements in the queue.
{
	return number_of_elements; //elements in container
}

template <typename T>
int FastQueue<T>::capacity() //Returns the size of allocated memory in terms of elements.
{
	return size_of_storage; //size of the container
}

template <typename T>
void FastQueue<T>::shrink_to_fit() //Shrinks the size of allocated memory to exactly fit the element currently in queue.
{	
	std::vector<T> another_new_storage; //create a new storage
	another_new_storage.reserve(number_of_elements); //have new container be able to hold the exact amount of elements
	for (int i = 0; i < number_of_elements; i++) 
		another_new_storage[i] = storage[(first + i) % size_of_storage]; //assign new storage the elements in old storage with relocation
	storage.swap(another_new_storage); //swap the containers
	size_of_storage = number_of_elements; //storage size is now amount of elements
	first = 0; //first element should be at 0
}
