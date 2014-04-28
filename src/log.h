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

typedef enum LogLevel { LogLevelCritical, LogLevelError, LogLevelWarning, LogLevelInfo, LogLevelDebug, LogLevelVerbose } LogLevel;

// log(filename, method, line, format, ...) Logs information to the console.
void zs_log(const char *filename, const char *method, int line, LogLevel level, const char *format, ...);

#define log_critical(format, ...) zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelCritical, format, ##__VA_ARGS__)
#define log_error(format, ...) zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelError, format, ##__VA_ARGS__)
#define log_warning(format, ...) zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelWarning, format, ##__VA_ARGS__)
#define log_info(format, ...) zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelInfo, format, ##__VA_ARGS__)
#define log_debug(format, ...) zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelDebug, format, ##__VA_ARGS__)
#define log_verbose(format, ...) zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelVerbose, format, ##__VA_ARGS__)

#define log_entering() zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelDebug, "Entering")
#define log_exiting() zs_log(__FILE__, __FUNCTION__, __LINE__, LogLevelDebug, "Exiting")
