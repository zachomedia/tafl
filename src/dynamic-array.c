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

#include "dynamic-array.h"

#include <stdlib.h>
#include <assert.h>

#include "log.h"

struct DynamicArray
{
   FreeFunction free_function;

   int count;
   int max;
   void **data;
};

// See header for details
void do_nothing(void *ptr)
{
   log_entering();
   log_exiting();
}// End of do_nothing

// See header for details
DynamicArray create_DynamicArray(FreeFunction free_function)
{
   log_entering();

   DynamicArray array = malloc(sizeof(struct DynamicArray));

   array->free_function = free_function;
   array->count = 0;
   array->max = 0;
   array->data = NULL;

   log_exiting();
   return array;
}// End of create_DynamicArray

// See header for details
void destroy_DynamicArray(DynamicArray array)
{
   log_entering();

   for (int x = 0; x < array->count; ++x)
   {
      array->free_function(array->data[x]);
   }

   free(array);

   log_exiting();
}// End of destroy_DynamicArray

// DynamicArray_double(array) Doubles the dynamic array.
static void DynamicArray_double(DynamicArray array)
{
   log_entering();

   if (array->max == 0)
      array->max = 1;
   else
      array->max *= 2;

   log_debug("New max: %d", array->max);

   array->data = realloc(array->data, sizeof(void *) * array->max);

   log_exiting();
}// End of DynamicArray_double method

// See header for details
void DynamicArray_add(DynamicArray array, void *item)
{
   log_entering();

   if (array->count == array->max)
      DynamicArray_double(array);

   array->data[array->count] = item;
   array->count += 1;

   log_verbose("Array contains %d elements", array->count);

   log_exiting();
}// End of DynamicArray_add

// See header for details
int DynamicArray_count(DynamicArray array)
{
   log_entering();

   assert(array);

   log_exiting();
   return array->count;
}// End of DynamicArray_count

// DynamicArray_element_at(array, index) Returns the item at index.
//                                    Returns NULL if item does not exist.
void *DynamicArray_element_at(DynamicArray array, int index)
{
   log_entering();

   assert(array);
   void *item = NULL;

   if (index >= 0 && index <= array->count)
      item = array->data[index];

   log_exiting();
   return item;
}// End of DynamicArray_element_at
