/*
   The MIT License (MIT)

   Copyright (c) 2014 Zachary Seguin

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

/*
   DynamicArray
   Dynamic array class, using a doubling strategy.

   NOTE: Currently only adding to back is supported.
   TODO: Add support for adding to front, at index, and removing.
*/

#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

struct DynamicArray;
typedef struct DynamicArray *DynamicArray;

typedef void (*FreeFunction)(void *);

// create_DynamicArray() Creates a new dynamic array.
DynamicArray create_DynamicArray(FreeFunction free_function);

// destroy_DynamicArray(array) Destroys the dynamic array.
void destroy_DynamicArray(DynamicArray array);

// DynamicArray_add(array) Adds an element to the rear of the array.
void DynamicArray_add(DynamicArray array, void *item);

// DynamicArray_count(array) Returns the number of elements in the array.
int DynamicArray_count(DynamicArray array);

// DynamicArray_element_at(array, index) Returns the item at index.
//                                    Returns NULL if item does not exist.
void *DynamicArray_element_at(DynamicArray array, int index);

#endif
