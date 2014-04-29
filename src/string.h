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

#include <string.h>
#include <stdbool.h>

// string_equal(str1, str2, ignore_case) Returns whether or not str1 and str2 are equal.
//                                          If ignore_case is true, then case is ignored.
bool string_equal(const char *str1, const char *str2, bool ignore_case);

// string_compare(str1, str2, ignore_case) Compares str1 to str2.
//                                           If ignore_case is true, then case is ignored.
int string_compare(const char *str1, const char *str2, bool ignore_case);

// to_uppercase(str) Converts the characters in str to uppercase.
void to_uppercase(char *str);

// to_lowercase(str) Converts the characters in str to lowercase.
void to_lowercase(char *str);
