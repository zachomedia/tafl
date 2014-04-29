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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

/* PROJECT */
#include "log.h"
#include "dynamic-array.h"
#include "string.h"

#include "tafl.h"

/* APPLICATION OPTIONS */
static struct option long_options[] =
{
   { "callsign", optional_argument, NULL, 'c' },
   { "file", optional_argument, NULL, 'f' },
   {0, 0, 0, 0}
};

struct SearchOptions
{
   const char *filename;
   const char *callsign;
   const char *licensee_name;
};
typedef struct SearchOptions SearchOptions;

/* METHODS */
static void print_usage(void)
{
   log_entering();

   printf("Usage: tafl -f filename [options]\n");
   printf("\t OPTIONS\n");
   printf("\t\t-f\n");
   printf("\t\t--file: Path the TAFL file.\n\n");
   printf("\t\t-c\n");
   printf("\t\t--callsign: Filter results by callsign.\n");

   log_exiting();
}// End of print_usage method

int main(int argc, char **argv)
{
   zs_log_configure();
   log_entering();

   /* COMMAND LINE OPTIONS*/
   SearchOptions options;
   int c = 0;

   log_debug("Getting command line options");
   while (true)
   {
      int index = 0;

      c = getopt_long(argc, argv, "c:f:", long_options, &index);
      if (c == -1)
      {
         log_debug("Parsed all command line options.");
         break;
      }// End of if

      log_debug("Parsing option %d, %s", c, long_options[index].name);

      switch(c)
      {
         case 'c':
            options.callsign = optarg;
            log_info("Filtering by callsign: %s", options.callsign);
            break;

         case 'f':
            options.filename = optarg;
            log_info("Using TAFL file %s", options.filename);
            break;
      }// End of switch
   }// End of while

   // Ensure that a filename is provided
   if (!options.filename)
   {
      print_usage();
      log_exiting();
      return EXIT_FAILURE;
   }// End of if

   printf("Loading stations...\n");

   /* Get station information */
   FILE *tafl_file = fopen(options.filename, "r");

   DynamicArray stations = tafl_load_stations(tafl_file);

   fclose(tafl_file);
   tafl_file = NULL;

   printf("Stations loaded.\nSearching...\n");


   /* FILTER */
   DynamicArray matching_stations = create_DynamicArray(do_nothing);

   for (int x = 0; x < DynamicArray_count(stations); ++x)
   {
      Station *station = (Station *)DynamicArray_element_at(stations, x);
      bool keep = true;

      if (options.callsign)
         keep = keep && string_equal(station->callsign, options.callsign, true);

      if (keep)
         DynamicArray_add(matching_stations, station);
   }// End of for

   printf("\n\n\n");
   for (int x = 0; x < DynamicArray_count(matching_stations); ++x)
   {
      Station *station = (Station *)DynamicArray_element_at(matching_stations, x);

      printf("%s - %s\n", station->licensee_name, station->station_location);
      printf("   TX: %f MHz, RX: %f MHz\n", station->transmit_frequency / 1000000.0, station->receive_frequency  / 1000000.0);
      printf("   Callsign: %s\n", station->callsign);
   }
   printf("\n\n\n");
   printf("Found %d %s.\n", DynamicArray_count(matching_stations), (DynamicArray_count(matching_stations) == 1) ? "station" : "stations");

   destroy_DynamicArray(matching_stations);
   destroy_DynamicArray(stations);

   log_exiting();
   zs_log_cleanup();
}// End of main method
