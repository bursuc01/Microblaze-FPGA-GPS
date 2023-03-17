/////*
////TinyGPS++ - a small GPS library for Arduino providing universal NMEA parsing
////Based on work by and "distanceBetween" and "courseTo" courtesy of Maarten Lamers.
////Suggestion to add satellites, courseTo(), and cardinal() by Matt Monson.
////Location precision improvements suggested by Wayne Holder.
////Copyright (C) 2008-2022 Mikal Hart
////All rights reserved.
////
////This library is free software; you can redistribute it and/or
////modify it under the terms of the GNU Lesser General Public
////License as published by the Free Software Foundation; either
////version 2.1 of the License, or (at your option) any later version.
////
////This library is distributed in the hope that it will be useful,
////but WITHOUT ANY WARRANTY; without even the implied warranty of
////MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
////Lesser General Public License for more details.
////
////You should have received a copy of the GNU Lesser General Public
////License along with this library; if not, write to the Free Software
////Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//#define __TinyGPSPlus_h
//
////#if defined(ARDUINO) && ARDUINO >= 100
////#include "Arduino.h"
////#else
////#include "WProgram.h"
////#endif
////#include <limits.h>
//
//#define _GPS_VERSION "1.0.3" // software version of this library
//#define _GPS_MPH_PER_KNOT 1.15077945
//#define _GPS_MPS_PER_KNOT 0.51444444
//#define _GPS_KMPH_PER_KNOT 1.852
//#define _GPS_MILES_PER_METER 0.00062137112
//#define _GPS_KM_PER_METER 0.001
//#define _GPS_FEET_PER_METER 3.2808399
//#define _GPS_MAX_FIELD_SIZE 15
//
//
//struct TinyGPSLocation
//{
//   friend class TinyGPSPlus;
//public:
//   bool isValid() const    { return valid; }
//   bool isUpdated() const  { return updated; }
//   const RawDegrees &rawLat()     { updated = false; return rawLatData; }
//   const RawDegrees &rawLng()     { updated = false; return rawLngData; }
//   double lat();
//   double lng();
//
//   TinyGPSLocation() : valid(false), updated(false)
//   {}
//
//private:
//   bool valid, updated;
//   RawDegrees rawLatData, rawLngData, rawNewLatData, rawNewLngData;
//   void commit();
//   void setLatitude(const char *term);
//   void setLongitude(const char *term);
//};
//
//class TinyGPSPlus
//{
//public:
//  TinyGPSPlus();
//  bool encode(char c); // process one character received from GPS
//  TinyGPSPlus &operator << (char c) {encode(c); return *this;}
//
//  TinyGPSLocation location;
//
//};
