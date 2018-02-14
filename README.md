# LinearSearch-OpenCL
LinearSearch OpenCl using C++

A simple approach is to do linear search, i.e

Start from the leftmost element of arr[] and one by one compare x with each element of arr[]
If x matches with an element, return the index.
If x doesn’t match with any of elements, return -1 and "Not Found in the Array Below!" will shows up.

The code include krenel.cl as programsource.

The time complexity of above algorithm is O(n).
Linear search is rarely used practically because other search algorithms such as the binary search algorithm and hash tables allow significantly faster searching comparison to Linear search.
