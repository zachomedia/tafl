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

#include "log.h"

#include <stdarg.h>
#include <stdio.h>

static FILE *log_file;

// See header for details
void zs_log_configure(void)
{
   log_file = fopen("tafl.log", "w");
}// End of zl_log_configure

// See header for details
void zs_log(const char *filename, const char *method, int line, LogLevel level, const char *format, ...)
{
   if (!log_file || level == LogLevelVerbose)
      return;

   va_list args;
   va_start(args, format);

   fprintf(log_file, "[");
   switch(level)
   {
      case LogLevelCritical:
         fprintf(log_file, "CRITICAL");
         break;

      case LogLevelError:
         fprintf(log_file, "  ERROR");
         break;

      case LogLevelWarning:
         fprintf(log_file, "WARNING");
         break;

      case LogLevelInfo:
         fprintf(log_file, "   INFO");
         break;

      case LogLevelDebug:
         fprintf(log_file, "  DEBUG");
         break;

      case LogLevelVerbose:
         fprintf(log_file, "VERBOSE");
         break;
   }
   fprintf(log_file, "] ");

   vfprintf(log_file, format, args);
   fprintf(log_file, " // %s():%d - %s\n", method, line, filename);

   va_end(args);
}// End of log method

// See header for details
void zs_log_cleanup(void)
{
   if (!log_file)
      return;
   fclose(log_file);
}// End of zl_log_cleanup
