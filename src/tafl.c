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

#include "tafl.h"

#include <stdlib.h>
#include <string.h>

#include "log.h"

static void conditional_free(void *ptr)
{
   log_entering();

   if (ptr) free(ptr);

   log_exiting();
}// End of conditional_free

static void free_station(void *ptr)
{
   log_entering();

   if (!ptr)
   {
      log_debug("Station pointer is NULL");
      log_exiting();
      return;
   }

   Station *station = (Station*)ptr;

   // Free text elements
   conditional_free(station->station_location);
   conditional_free(station->linked_station);
   conditional_free(station->licensee_name);
   conditional_free(station->callsign);
   conditional_free(station->bandwidth);
   conditional_free(station->necessary_bandwidth);
   conditional_free(station->emission_class);
   conditional_free(station->power_units);

   // Free station
   free(station);

   log_exiting();
}// End of free_station

static char *field_string(FILE *file, int length)
{
   log_entering();

   log_verbose("Reading %d characters", length);
   char *field = malloc(sizeof(char) * (length + 1));

   for (int x = 0; x < length; ++x)
      fscanf(file, "%c", &field[x]);

   field[length] = '\0';

   log_exiting();
   return field;
}// End of field_string method

static long int field_long_int(FILE *file, int length)
{
   log_entering();

   char *temp = field_string(file, length);
   long int num = 0;

   num = atol(temp);
   log_verbose("Long int (string): \"%s\"", temp);
   log_verbose("Long int: %ld", num);
   free(temp);

   log_exiting();
   return num;
}

static int field_int(FILE *file, int length)
{
   log_entering();

   char *temp = field_string(file, length);
   int num = 0;

   num = atoi(temp);
   log_verbose("Int (string): \"%s\"", temp);
   log_verbose("Int: %d", num);
   free(temp);

   log_exiting();
   return num;
}

static double field_double(FILE *file, int length)
{
   log_entering();

   char *temp = field_string(file, length);
   double num = 0;

   num = atof(temp);
   log_verbose("Double (string): \"%s\"", temp);
   log_verbose("Double: %f", num);
   free(temp);

   log_exiting();
   return num;
}

static bool field_bool(FILE *file)
{
   log_entering();

   char *temp = field_string(file, 1);
   bool ret = false;
   log_verbose("Bool (string): \"%s\"", temp);

   if (temp[0] == '1') ret = true;
   log_verbose("Bool: %d", ret);

   free(temp);

   log_exiting();
   return ret;
}

static void field_discard(FILE *file, int length)
{
   log_entering();

   char *temp = field_string(file, length);
   log_verbose("Discarding \"%s\"", temp);
   free(temp);

   log_exiting();
}

// See header for details
DynamicArray tafl_load_stations(FILE *file)
{
   log_entering();

   DynamicArray stations = create_DynamicArray(free_station);

   log_verbose("Rewinding file");
   rewind(file);

   while (!feof(file))
   {
      Station *station = malloc(sizeof(Station));

      station->transmit_frequency = field_long_int(file, 12);
      log_verbose("Transmit Frequency: %ld Hz", station->transmit_frequency);

      station->receive_only = field_bool(file);
      log_verbose("Receive Only: %s", (station->receive_only) ? "yes" : "no");

      field_discard(file, 1);

      station->receive_frequency = field_long_int(file, 12);
      log_verbose("Transmit Frequency: %ld Hz", station->transmit_frequency);

      field_discard(file, 2);

      station->frequency_status = field_int(file, 1);
      log_verbose("Frequency Status: %d", station->frequency_status);

      field_discard(file, 1);

      station->record_identifier = field_long_int(file, 11);
      log_verbose("Record Identifier: %ld", station->record_identifier);

      field_discard(file, 1);

      station->station_location = field_string(file, 35);
      log_verbose("Station Location: %s", station->station_location);

      field_discard(file, 1);

      log_warning("Skipping \"Coordination Code\"");
      field_discard(file, 2);

      field_discard(file, 1);

      station->latitude = field_int(file, 6);
      log_verbose("Latitude: %d", station->latitude);

      field_discard(file, 1);

      station->longitude = field_int(file, 7);
      log_verbose("Longitude: %d", station->longitude);

      field_discard(file, 1);

      station->effective_radiated_power = field_double(file, 5);
      log_verbose("Effective Radiated Power: %f", station->effective_radiated_power);

      field_discard(file, 1);

      station->antenna_gain = field_double(file, 5);
      log_verbose("Antenna Gain: %f", station->antenna_gain);

      field_discard(file, 1);

      station->antenna_azimuth = field_double(file, 6);
      log_verbose("Antenna Azimuth: %f", station->antenna_azimuth);

      field_discard(file, 1);

      station->antenna_elevation = field_int(file, 5);
      log_verbose("Antenna Elevation: %d", station->antenna_elevation);

      field_discard(file, 1);

      station->antenna_height = field_int(file, 4);
      log_verbose("Antenna Height: %d", station->antenna_height);

      field_discard(file, 1);

      station->antenna_farm = field_int(file, 4);
      log_verbose("Antenna Farm: %d", station->antenna_farm);

      field_discard(file, 1);

      log_warning("Skipping \"International Coordination\"");
      field_discard(file, 1);

      field_discard(file, 1);

      station->in_coordination_zone = field_bool(file);
      log_verbose("In Coordination Zone: %s", (station->in_coordination_zone) ? "yes" : "no");

      field_discard(file, 1);

      station->linked_station = field_string(file, 6);
      log_verbose("Linked Station: %s", station->linked_station);

      station->multiple_liniked_stations = field_bool(file);
      log_verbose("Multiple Linked Stations: %s", (station->multiple_liniked_stations) ? "yes" : "no");

      field_discard(file, 1);

      log_warning("Skipping \"Signal Path Edit Status\"");
      field_discard(file, 1);

      field_discard(file, 1);

      log_warning("Skipping \"Antenna Polarization\"");
      field_discard(file, 1);

      field_discard(file, 1);

      station->district_office = field_int(file, 2);
      log_verbose("District Office: %d", station->district_office);

      station->license_number = field_int(file, 7);
      log_verbose("License Number: %d", station->license_number);

      field_discard(file, 2);

      station->license_status = field_int(file, 1);
      log_verbose("License Status: %d", station->license_status);

      field_discard(file, 2);

      log_warning("Skipping \"Company Code\"");
      field_discard(file, 9);

      field_discard(file, 1);

      station->licensee_name = field_string(file, 18);
      log_verbose("Licensee Name: %s", station->licensee_name);

      field_discard(file, 1);

      log_warning("Skipping \"Station Class\"");
      field_discard(file, 2);

      field_discard(file, 2);

      log_warning("Skipping \"Station Service\"");
      field_discard(file, 2);

      field_discard(file, 1);

      // blanks
      field_discard(file, 5);

      field_discard(file, 1);

      station->callsign = field_string(file, 6);
      log_verbose("Callsign: %s", station->callsign);

      field_discard(file, 1);

      station->number_of_mobiles = field_int(file, 4);
      log_verbose("Number of Mobiles: %d", station->number_of_mobiles);

      field_discard(file, 1);

      station->bandwidth = field_string(file, 9);
      log_verbose("Bandwidth: %s", station->bandwidth);

      station->necessary_bandwidth = field_string(file, 4);
      log_verbose("Neccessary Bandwidth: %s", station->necessary_bandwidth);

      station->emission_class = field_string(file, 5);
      log_verbose("Emission Class: %s", station->emission_class);

      field_discard(file, 2);

      char *date = field_string(file, 8);
      log_verbose("String Date: %s", date);

      if (strptime(date, "%Y%m%d", &station->date_assigned))
      {
         log_verbose("Parsed date successfully");
         char temp[] = "### ##, ####";
         strftime(temp, sizeof(temp), "%b %d, %Y", &station->date_assigned);
         log_verbose("Date Assigned: %s", temp);
      }
      else
      {
         log_error("Failed to parse date");
      }

      free(date);

      field_discard(file, 2);

      station->transmission_loss = field_double(file, 5);
      log_verbose("Transmission Loss: %f", station->transmission_loss);

      field_discard(file, 1);

      station->transmission_power = field_double(file, 5);
      log_verbose("Transmission Power: %f", station->transmission_power);

      station->power_units = field_string(file, 3);
      log_verbose("Power Units: %s", station->power_units);

      field_discard(file, 1);

      log_warning("Skipping \"Antenna Pattern\"");
      field_discard(file, 4);

      field_discard(file, 1);

      station->antenna_elevation_angle = field_double(file, 4);
      log_verbose("Antenna Elevation Angle: %f", station->antenna_elevation_angle);

      field_discard(file, 1);

      station->international_coordination_number = field_int(file, 7);
      log_verbose("International Coordination Number: %d", station->international_coordination_number);

      field_discard(file, 2);

      DynamicArray_add(stations, station);

      field_discard(file, 2);

   }// End of while

   log_exiting();
   return stations;
}// End of tafl_load_stations
