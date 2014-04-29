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

#include "string.h"

#include <stdlib.h>

#include "log.h"

// See header for details
bool string_equal(const char *str1, const char *str2, bool ignore_case)
{
   log_entering();
   int result = string_compare(str1, str2, ignore_case);
   log_exiting();
   return result == 0;
}// End of string_equal

// See header for details
int string_compare(const char *str1, const char *str2, bool ignore_case)
{
   log_entering();

   int result = 0;

   log_verbose("Comparing \"%s\" and \"%s\"", str1, str2);

   if (!str1 && !str2)
   {
      result = 0;
   }// End of if
   else if (!str1)
   {
      result = -1;
   }// End of else if
   else if (!str2)
   {
      result = 1;
   }// End of else if
   else if (!ignore_case)
   {
      result = strcmp(str1, str2);
   }// End of else if
   else
   {
      char *str1_lower = strdup(str1);
      char *str2_lower = strdup(str2);

      to_lowercase(str1_lower);
      to_lowercase(str2_lower);

      log_verbose("Comparing lower case \"%s\" and \"%s\"", str1_lower, str2_lower);

      result = strcmp(str1_lower, str2_lower);

      free(str1_lower);
      free(str2_lower);
   }// End of else
   
   log_verbose("Comparison Result: %d", result);

   log_exiting();
   return result;
}// End of string_compare

// See header for details
void to_uppercase(char *str)
{
   log_entering();

   log_verbose("Converting %s to uppercase", str);

   while(*str)
   {
      if (*str >= 'a' && *str <= 'z')
         *str = *str - 'a' + 'A';

      ++str;
   }// End of while

   log_verbose("Done converting. Result: %s", str);

   log_exiting();
}// End of to_uppercase

// See header for details
void to_lowercase(char *str)
{
   log_entering();

   log_verbose("Converting %s to lowercase", str);

   while(*str)
   {
      if (*str >= 'A' && *str <= 'Z')
         *str = *str - 'A' + 'a';

      ++str;
   }// End of while

   log_verbose("Done converting. Result: %s", str);

   log_exiting();
}// End of to_lowercase
