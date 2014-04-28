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

/* LIBRARIES */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* PROJECT */
#include "log.h"
#include "dynamic-array.h"
#include "tafl.h"

/* CONSTANT VARIABLES */


/* INSTANCE VARIABLES */


/* FORWARD DECLARATIONS (As Required) */


int main(int argc, const char **argv)
{
   log_entering();

   //const char *filename = "sample.txt";
   const char *filename = "ltaf_ont_tafl.txt";
   log_warning("Using fixed file: %s", filename);

   FILE *tafl_file = fopen(filename, "r");
   DynamicArray stations = tafl_load_stations(tafl_file);

   printf("\n\n\n");
   for (int x = 0; x < DynamicArray_count(stations); ++x)
   {
      Station *station = DynamicArray_element_at(stations, x);

      printf("%d - %s - %s\n", x + 1, station->licensee_name, station->station_location);
      printf("   TX: %ld, RX: %ld\n", station->transmit_frequency, station->receive_frequency);
      printf("   Callsign: %s\n", station->callsign);
   }
   printf("\n\n\n");

   destroy_DynamicArray(stations);

   log_exiting();
}// End of main method
