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

#ifndef _TAFL_H
#define _TAFL_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "dynamic-array.h"

typedef enum FrequencyStatus
{
   FrequencyStatusLicensed = 6,
   FrequencyStatusUnderReconsideration = 7
} FrequencyStatus;

typedef enum CoordinationCode
{
   CoordinationCodeFCC,
   CoordinationCodeFAA,
   CoordinationCodeJCS,
   CoordinationCodeNTIA,
   CoordinationCodeIFRBNotified = 26
} CoordinationCode;

typedef enum InternationCoordination
{
   InternationCoordinationNotRequired,
   InternationCoordinationNotReady,
   InternationCoordinationReady
} InternationCoordination;

typedef enum SignalPathEditStatus
{
   SignalPathEditStatusDataMissing,
   SignalPathEditStatusFailedOuterLimits,
   SignalPathEditStatusPassedInnerLimits,
   SignalPathEditStatusFailedInnerLimits
} SignalPathEditStatus;

typedef enum AntennaPolarization
{
   AntennaPolarizationHorizontal,
   AntennaPolarizationVertical,
   AntennaPolarizationHorizontalVerticalSelectable,
   AntennaPolarizationCircularRight,
   AntennaPolarizationCircularLeft,
   AntennaPolarizationCircular,
   AntennaPolarizationRotating,
   AntennaPolarizationElliptical,
   AntennaPolarizationLinear,
   AntennaPolarizationOther,
   AntennaPolarizationDual,
   AntennaPolarizationMixed,
   AntennaPolarizationSlantRight,
   AntennaPolarizationSlantLeft
} AntennaPolarization;

typedef enum IndustryCanadaAdministrativeOffice
{
   IndustryCanadaAdministrativeOfficeVancouverRegional = 11,
   IndustryCanadaAdministrativeOfficeVancouverDistrict = 12,
   IndustryCanadaAdministrativeOfficeVictoria = 13,
   IndustryCanadaAdministrativeOfficeKelowna = 15,
   IndustryCanadaAdministrativeOfficePrinceGeorge = 16,

   IndustryCanadaAdministrativeOfficeEdmonton = 22,
   IndustryCanadaAdministrativeOfficeCalgary = 23,
   IndustryCanadaAdministrativeOfficeYellowknife = 26,
   IndustryCanadaAdministrativeOfficeWinnipegRegional = 31,
   IndustryCanadaAdministrativeOfficeWinnipegDistrict = 32,
   IndustryCanadaAdministrativeOfficeRegina = 33,
   IndustryCanadaAdministrativeOfficeSaskatoon = 34,

   IndustryCanadaAdministrativeOfficeTorontoRegional = 41,
   IndustryCanadaAdministrativeOfficeTorontoDistrict = 42,
   IndustryCanadaAdministrativeOfficeBurlington = 43,
   IndustryCanadaAdministrativeOfficeLondon = 44,
   IndustryCanadaAdministrativeOfficeKitchener = 45,
   IndustryCanadaAdministrativeOfficeSaultSteMarie = 46,
   IndustryCanadaAdministrativeOfficeBelleville = 48,
   IndustryCanadaAdministrativeOfficeOttawa = 49,

   IndustryCanadaAdministrativeOfficeMontrealRegional = 51,
   IndustryCanadaAdministrativeOfficeMontrealDistrict = 52,
   IndustryCanadaAdministrativeOfficeSherbrooke = 53,
   IndustryCanadaAdministrativeOfficeChicoutimi = 54,
   IndustryCanadaAdministrativeOfficeQuebec = 55,
   IndustryCanadaAdministrativeOfficeHull = 56,

   IndustryCanadaAdministrativeOfficeMonctonRegioal = 61,
   IndustryCanadaAdministrativeOfficeHalifax = 63,
   IndustryCanadaAdministrativeOfficeSaintJohn = 65,
   IndustryCanadaAdministrativeOfficeStJohns = 66
} IndustryCanadaAdministrativeOffice;

typedef enum LicenseStatus
{
   LicenseStatusAuthorized = 5,
   LicenseStatusActive = 6,
   LicenseStatusUnderReconsideration = 7,
   LicenseStatusOther
} LicenseStatus;

typedef enum CompanyCode
{
   CompanyCodePrivateCommercial,
   CompanyCodePrivateCommercialCTV,
   CompanyCodePrivateBroadcasting,
   CompanyCodePublicCommercial,
   CompanyCodeExperimental,
   CompanyCodeCoast,
   CompanyCodeEarthAndSpace,
   CompanyCodeAircraft,
   CompanyCodeShip
} CompanyCode;

typedef enum StationClass
{
   StationClassAeronauticalRadioNavigationLand,
   StationClassAeronautical,
   StationClassBase,
   StationClassCoast,
   StationClassFixed,
   StationClassRadio,
   StationClassAircraft,
   StationClassMobile,
   StationClassShip
} StationClass;

typedef enum StationService
{
   StationServiceOfficialCorrespondance,
   StationServicePublicCorrespondance,
   StationServiceLimitedPublicCorrespondance,
   StationServicePrivateAgencyCorrespondance,
   StationServiceOperationTraffic
} StationService;

typedef enum AntennaPattern
{
   AntennaPatternOmniDirectional = 8000,
   AntennaPatternUniDirectional = 8200,
   AntennaPatternBiDirectional = 8800,
   AntennaPatternOther = 9400
} AntennaPattern;

typedef struct Station {
   long int transmit_frequency;
   long int receive_frequency;
   bool receive_only;

   FrequencyStatus frequency_status;

   long int record_identifier;

   char *station_location;
   CoordinationCode coordination_code;

   int latitude;
   int longitude;

   double effective_radiated_power;
   double antenna_gain;
   double antenna_azimuth;
   int antenna_elevation;
   int antenna_height;
   int antenna_farm;

   InternationCoordination internationa_coordination;
   bool in_coordination_zone;

   char *linked_station;
   bool multiple_liniked_stations;

   SignalPathEditStatus signal_path_edit_status;
   AntennaPolarization antenna_polorization;

   IndustryCanadaAdministrativeOffice district_office;

   int license_number;
   LicenseStatus license_status;
   CompanyCode company_code;

   char *licensee_name;
   StationClass station_class;
   StationService station_service;

   char *callsign;

   int number_of_mobiles;

   char *bandwidth;
   char *necessary_bandwidth;
   char *emission_class;

   struct tm date_assigned;

   double transmission_loss;
   double transmission_power;
   char *power_units;

   AntennaPattern antenna_pattern;
   double antenna_elevation_angle;

   int international_coordination_number;
} Station;

// tafl_load_stations(file) Loads stations from file.
//         NOTE: Currently there is no error checking, file must meet specs.
DynamicArray tafl_load_stations(FILE *file);

#endif
