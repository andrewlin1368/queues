Write a class template FastQueue. It uses vector<> as an underlying container.

enqueue( element ) Adds a new element to the end of the queue. O(1) average. Possible relocation.

dequeue( ) Removes an element from the head of the queue. Does nothing if the queue is already empty. O(1).

front() Returns reference to the first element of the queue. Throws out_of_range if the container is empty.

back() Returns reference to the last element of the queue. Throws out_of_range if the container is empty.

at(index) Returns reference to the index-th element of the queue. Throws

out_of_range if the container size is less than index.

size() Returns the number of elements in the queue. Do not try to use vector::size() method! It won’t work for you!

capacity() Returns the size of allocated memory in terms of elements.

shrink_to_fit() Shrinks the size of allocated memory to exactly fit the elements

currently in queue. Reallocation is possible (almost unavoidable). Since you use

vector<>, you won’t be able to fully control the amount of allocated memory. Assume that vector<> always follows your size you specify during construction.

Do not try to use vector<> method shrink_to_fit(). Due to the nature of your

container, it won’t work for you. For the same reason, I suggest you to be careful with resize() and reserve() methods.