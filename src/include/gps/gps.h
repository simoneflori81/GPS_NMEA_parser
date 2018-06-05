/**
 * \file            gps.h
 * \brief           GPS main file
 */

/*
 * Copyright (c) 2018 Tilen Majerle
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of GPS NMEA parser.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 */
#ifndef __GPS_H
#define __GPS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stdint.h"
#include "stddef.h"

#ifndef GPS_CFG_DOUBLE
#define GPS_CFG_DOUBLE                      1
#endif

#ifndef GPS_CFG_STATEMENT_GPGGA
#define GPS_CFG_STATEMENT_GPGGA             1
#endif

#ifndef GPS_CFG_STATEMENT_GPGSA
#define GPS_CFG_STATEMENT_GPGSA             1
#endif

#ifndef GPS_CFG_STATEMENT_GPRMC
#define GPS_CFG_STATEMENT_GPRMC             1
#endif

#ifndef GPS_CFG_STATEMENT_GPGSV
#define GPS_CFG_STATEMENT_GPGSV             1
#endif

#if GPS_CFG_DOUBLE                  
typedef double gps_float_t;
#else
typedef float gps_float_t;
#endif

/**
 * \brief           GPS main structure
 */
typedef struct {
#if GPS_CFG_STATEMENT_GPGGA || __DOXYGEN__
    /* Information related to GPGGA statement */
    gps_float_t latitude;                       /*!< Latitude in units of degrees */
    gps_float_t longitude;                      /*!< Longitude in units of degrees */
    gps_float_t altitude;                       /*!< Altitude in units of meters */
    uint8_t sats_in_use;                        /*!< Number of satellites in use */
    uint8_t fix;                                /*!< Fix status. `0` = invalid, `1` = GPS fix, `2` = DGPS fix, `3` = PPS fix */
    uint8_t hours;                              /*!< Hours in UTC */
    uint8_t minutes;                            /*!< Minutes in UTC */
    uint8_t seconds;                            /*!< Seconds in UTC */
#endif /* GPS_CFG_STATEMENT_GPGGA || __DOXYGEN__ */

#if GPS_CFG_STATEMENT_GPGSA || __DOXYGEN__
    /* Information related to GPGSA statement */
    gps_float_t dop_h;                          /*!< Dolution of precision, horizontal */
    gps_float_t dop_v;                          /*!< Dolution of precision, vertical */
    gps_float_t dop_p;                          /*!< Dolution of precision, position */
    uint8_t fix_mode;                           /*!< Fix mode. `1` = NO fix, `2` = 2D fix, `3` = 3D fix */
    uint8_t satellites_ids[12];                 /*!< List of satellite IDs in use. Valid range is `0` to `sats_in_use` */
#endif /* GPS_CFG_STATEMENT_GPGSA || __DOXYGEN__ */

#if GPS_CFG_STATEMENT_GPGSV || __DOXYGEN__
    /* Information related to GPGSV statement */
    uint8_t sats_in_view;                       /*!< Number of satellites in view */
#endif /* GPS_CFG_STATEMENT_GPGSV || __DOXYGEN__ */

#if GPS_CFG_STATEMENT_GPRMC || __DOXYGEN__
    /* Information related to GPRMC statement */
    uint8_t is_valid;                           /*!< GPS valid status */
    gps_float_t speed;                          /*!< Ground speed in knots */
    gps_float_t coarse;                         /*!< Ground coarse */
    gps_float_t variation;                      /*!< Magnetic variation */
    uint8_t date;                               /*!< Fix date */
    uint8_t month;                              /*!< Fix month */
    uint8_t year;                               /*!< Fix year */
#endif /* GPS_CFG_STATEMENT_GPRMC || __DOXYGEN__ */

#if !__DOXYGEN__
    struct {
        uint8_t stat;                           /*!< Statement index */
        char term_str[13];                      /*!< Current term in string format */
        uint8_t term_pos;                       /*!< Current index position in term */
        uint8_t term_num;                       /*!< Current term number */
        
        uint8_t star;                           /*!< Star detected flag */
        
        uint8_t crc_calc;                       /*!< Calculated CRC string */
        
        union {
            uint8_t dummy;
#if GPS_CFG_STATEMENT_GPGGA
            struct {
                gps_float_t latitude, longitude, altitude;
                uint8_t sats_in_use, fix, hours, minutes, seconds;
            } gga;
#endif /* GPS_CFG_STATEMENT_GPGGA */
#if GPS_CFG_STATEMENT_GPGSA
            struct {
                gps_float_t dop_h, dop_v, dop_p;
                uint8_t fix_mode, satellites_ids[12];
            } gsa;
#endif /* GPS_CFG_STATEMENT_GPGSA */
#if GPS_CFG_STATEMENT_GPGSV
            struct {
                uint8_t sats_in_view;
            } gsv;
#endif /* GPS_CFG_STATEMENT_GPGSV */
#if GPS_CFG_STATEMENT_GPRMC
            struct {
                uint8_t is_valid, date, month, year;
                gps_float_t speed, coarse, variation;
            } rmc;
#endif /* GPS_CFG_STATEMENT_GPRMC */
        } data;                                 /*!< Union with data for each information */
    } p;                                        /*!< Structure with private data */
#endif /* !__DOXYGEN__ */
} gps_t;

#if GPS_CFG_STATEMENT_GPRMC || __DOXYGEN__
#define gps_is_valid(_gh)           ((_gh)->is_valid)
#else
#define gps_is_valid(_gh)           (0)
#endif /* GPS_CFG_STATEMENT_GPRMC || __DOXYGEN__ */

/**
 * \brief           List of optional speed transformation from GPS values (in knots)
 */
typedef enum {
    /* Metric values */
    gps_speed_kps,                              /*!< Kilometers per second */
    gps_speed_kph,                              /*!< Kilometers per hour */
    gps_speed_mps,                              /*!< Meters per second */
    gps_speed_mpm,                              /*!< Meters per minute */

    /* Imperial values */
    gps_speed_mips,                             /*!< Miles per second */
    gps_speed_mph,                              /*!< Miles per hour */
    gps_speed_fps,                              /*!< Foots per second */
    gps_speed_fpm,                              /*!< Foots per minute */

    /* Optimized for runners/joggers */
    gps_speed_mpk,                              /*!< Minutes per kilometer */
    gps_speed_spk,                              /*!< Seconds per kilometer */
    gps_speed_sp100m,                           /*!< Seconds per 100 meters */
    gps_speed_mipm,                             /*!< Minutes per mile */
    gps_speed_spm,                              /*!< Seconds per mile */
    gps_speed_sp100y,                           /*!< Seconds per 100 yards */

    /* Nautical values */
    gps_speed_smph,                             /*!< Sea miles per hour */
} gps_speed_t;

uint8_t     gps_init(gps_t* gh);
uint8_t     gps_process(gps_t* gh, const void* data, size_t len);

uint8_t     gps_distance_bearing(gps_float_t las, gps_float_t los, gps_float_t lae, gps_float_t loe, gps_float_t* d, gps_float_t* b);
gps_float_t gps_to_speed(gps_float_t sik, gps_speed_t ts);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPS_H */
