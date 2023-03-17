/////*
////TinyGPS++ - a small GPS library for Arduino providing universal NMEA parsing
////Based on work by and "distanceBetween" and "courseTo" courtesy of Maarten Lamers.
////Suggestion to add satellites, courseTo(), and cardinal() by Matt Monson.
////Location precision improvements suggested by Wayne Holder.
////Copyright (C) 2008-2013 Mikal Hart
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
////*/
//
//#include "TinyGPS++.h"
//
//#include <string.h>
//#include <ctype.h>
//#include <stdlib.h>
//
//#define _GPRMCterm   "GPRMC"
//#define _GPGGAterm   "GPGGA"
//#define _GNRMCterm   "GNRMC"
//#define _GNGGAterm   "GNGGA"
//
//TinyGPSPlus::TinyGPSPlus()
//  :  parity(0)
//  ,  isChecksumTerm(false)
//  ,  curSentenceType(GPS_SENTENCE_OTHER)
//  ,  curTermNumber(0)
//  ,  curTermOffset(0)
//  ,  sentenceHasFix(false)
//  ,  customElts(0)
//  ,  customCandidates(0)
//  ,  encodedCharCount(0)
//  ,  sentencesWithFixCount(0)
//  ,  failedChecksumCount(0)
//  ,  passedChecksumCount(0)
//{
//  term[0] = '\0';
//}
//
////
//// public methods
////
//
//bool TinyGPSPlus::encode(char c)
//{
//  ++encodedCharCount;
//
//  switch(c)
//  {
//  case ',': // term terminators
//    parity ^= (uint8_t)c;
//  case '\r':
//  case '\n':
//  case '*':
//    {
//      bool isValidSentence = false;
//      if (curTermOffset < sizeof(term))
//      {
//        term[curTermOffset] = 0;
//        isValidSentence = endOfTermHandler();
//      }
//      ++curTermNumber;
//      curTermOffset = 0;
//      isChecksumTerm = c == '*';
//      return isValidSentence;
//    }
//    break;
//
//  case '$': // sentence begin
//    curTermNumber = curTermOffset = 0;
//    parity = 0;
//    curSentenceType = GPS_SENTENCE_OTHER;
//    isChecksumTerm = false;
//    sentenceHasFix = false;
//    return false;
//
//  default: // ordinary characters
//    if (curTermOffset < sizeof(term) - 1)
//      term[curTermOffset++] = c;
//    if (!isChecksumTerm)
//      parity ^= c;
//    return false;
//  }
//
//  return false;
//}
//
//#define COMBINE(sentence_type, term_number) (((unsigned)(sentence_type) << 5) | term_number)
//
//// Processes a just-completed term
//// Returns true if new sentence has just passed checksum test and is validated
//bool TinyGPSPlus::endOfTermHandler()
//{
//  // If it's the checksum term, and the checksum checks out, commit
//  if (isChecksumTerm)
//  {
//    byte checksum = 16 * fromHex(term[0]) + fromHex(term[1]);
//    if (checksum == parity)
//    {
//      passedChecksumCount++;
//      if (sentenceHasFix)
//        ++sentencesWithFixCount;
//
//      switch(curSentenceType)
//      {
//      case GPS_SENTENCE_GPRMC:
//        date.commit();
//        time.commit();
//        if (sentenceHasFix)
//        {
//           location.commit();
//           speed.commit();
//           course.commit();
//        }
//        break;
//      case GPS_SENTENCE_GPGGA:
//        time.commit();
//        if (sentenceHasFix)
//        {
//          location.commit();
//          altitude.commit();
//        }
//        satellites.commit();
//        hdop.commit();
//        break;
//      }
//
//      // Commit all custom listeners of this sentence type
//      for (TinyGPSCustom *p = customCandidates; p != NULL && strcmp(p->sentenceName, customCandidates->sentenceName) == 0; p = p->next)
//         p->commit();
//      return true;
//    }
//
//    else
//    {
//      ++failedChecksumCount;
//    }
//
//    return false;
//  }
//
//  // the first term determines the sentence type
//  if (curTermNumber == 0)
//  {
//    if (!strcmp(term, _GPRMCterm) || !strcmp(term, _GNRMCterm))
//      curSentenceType = GPS_SENTENCE_GPRMC;
//    else if (!strcmp(term, _GPGGAterm) || !strcmp(term, _GNGGAterm))
//      curSentenceType = GPS_SENTENCE_GPGGA;
//    else
//      curSentenceType = GPS_SENTENCE_OTHER;
//
//    // Any custom candidates of this sentence type?
//    for (customCandidates = customElts; customCandidates != NULL && strcmp(customCandidates->sentenceName, term) < 0; customCandidates = customCandidates->next);
//    if (customCandidates != NULL && strcmp(customCandidates->sentenceName, term) > 0)
//       customCandidates = NULL;
//
//    return false;
//  }
//
//  if (curSentenceType != GPS_SENTENCE_OTHER && term[0])
//    switch(COMBINE(curSentenceType, curTermNumber))
//  {
//    case COMBINE(GPS_SENTENCE_GPRMC, 1): // Time in both sentences
//    case COMBINE(GPS_SENTENCE_GPGGA, 1):
//      time.setTime(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 2): // GPRMC validity
//      sentenceHasFix = term[0] == 'A';
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 3): // Latitude
//    case COMBINE(GPS_SENTENCE_GPGGA, 2):
//      location.setLatitude(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 4): // N/S
//    case COMBINE(GPS_SENTENCE_GPGGA, 3):
//      location.rawNewLatData.negative = term[0] == 'S';
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 5): // Longitude
//    case COMBINE(GPS_SENTENCE_GPGGA, 4):
//      location.setLongitude(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 6): // E/W
//    case COMBINE(GPS_SENTENCE_GPGGA, 5):
//      location.rawNewLngData.negative = term[0] == 'W';
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 7): // Speed (GPRMC)
//      speed.set(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 8): // Course (GPRMC)
//      course.set(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPRMC, 9): // Date (GPRMC)
//      date.setDate(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPGGA, 6): // Fix data (GPGGA)
//      sentenceHasFix = term[0] > '0';
//      break;
//    case COMBINE(GPS_SENTENCE_GPGGA, 7): // Satellites used (GPGGA)
//      satellites.set(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPGGA, 8): // HDOP
//      hdop.set(term);
//      break;
//    case COMBINE(GPS_SENTENCE_GPGGA, 9): // Altitude (GPGGA)
//      altitude.set(term);
//      break;
//  }
//
//  // Set custom values as needed
//  for (TinyGPSCustom *p = customCandidates; p != NULL && strcmp(p->sentenceName, customCandidates->sentenceName) == 0 && p->termNumber <= curTermNumber; p = p->next)
//    if (p->termNumber == curTermNumber)
//         p->set(term);
//
//  return false;
//}
