
/**
  * @file       Time.h
  * @brief      Library of low level time and date functions
  * @author     Rodrigo Barbosa Nunes
  * @version    1.0
  * @date       2013
  *
  * The Time library implements various basic functions for time manipulation.
  * It's a modified version of the time library in Akafugu Corporation's VFD-Modular-Clock.
  *
  */

#ifndef _Time_h
#define _Time_h

#include <inttypes.h>

///To simplify notation and make the code easier to read
typedef unsigned long time_t;

///Enumeration of the status of the time
typedef enum {timeNotSet, timeNeedsSync, timeSet
}  timeStatus_t ;

///Enumeration of the days of the week
typedef enum {
    dowInvalid, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, dowSaturday
} timeDayOfWeek_t;

///Enumeration of the fields of time
typedef enum {
    tmSecond, tmMinute, tmHour, tmWday, tmDay,tmMonth, tmYear, tmNbrFields
} tmByteFields;

///Struct with the time elements
typedef struct  {
  uint8_t Second;
  uint8_t Minute;
  uint8_t Hour;
  uint8_t Wday;   // day of week, sunday is day 1
  uint8_t Day;
  uint8_t Month;
  uint8_t Year;   // offset from 1970;
} 	tmElements_t, TimeElements, *tmElementsPtr_t;

//convenience macros to convert to and from tm years

//Full four digit year
#define  tmYearToCalendar(Y) ((Y) + 1970)
#define  CalendarYrToTm(Y)   ((Y) - 1970)

//Offset is from 2000
#define  tmYearToY2k(Y)      ((Y) - 30)
#define  y2kYearToTm(Y)      ((Y) + 30)

typedef time_t(*getExternalTime)();
//typedef void  (*setExternalTime)(const time_t); // not used in this version


/*==============================================================================*/
/* Useful Constants */

///Number of seconds in a minute
#define SECS_PER_MIN  (60UL)

///Number of seconds in a hour
#define SECS_PER_HOUR (3600UL)

///Number of seconds in a day
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)

///Number of days in a week
#define DAYS_PER_WEEK (7UL)

///Number of seconds in a week
#define SECS_PER_WEEK (SECS_PER_DAY * DAYS_PER_WEEK)

///Number of seconds in a year
#define SECS_PER_YEAR (SECS_PER_WEEK * 52UL)

///Number of seconds in the year 2000
#define SECS_YR_2000  (946684800UL)

/* Useful Macros for getting elapsed time */

///Gives the number of seconds in a time
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)

///Gives the number of minutes in a time
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)

///Gives the number of hours in a time
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)

/**
  * @brief Gives the day of the week in a time
  *
  * - 1 = Sunday
  * - 2 = Monday
  * - 3 = Tuesday
  * - 4 = Wednesday
  * - 5 = Thursday
  * - 6 = Friday
  * - 7 = Saturday
  */
#define dayOfWeek(_time_)  ((( _time_ / SECS_PER_DAY + 4)  % DAYS_PER_WEEK)+1)

///Gives the number of days in a time since Jan 1 1970
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)

///Gives the number of seconds in a time since last midnight
#define elapsedSecsToday(_time_)  (_time_ % SECS_PER_DAY)

// The following macros are used in calculating alarms and assume the clock is set to a date later than Jan 1 1971
// Always set the correct time before settting alarms
#define previousMidnight(_time_) (( _time_ / SECS_PER_DAY) * SECS_PER_DAY)  // time at the start of the given day
#define nextMidnight(_time_) ( previousMidnight(_time_)  + SECS_PER_DAY )   // time at the end of the given day
#define elapsedSecsThisWeek(_time_)  (elapsedSecsToday(_time_) +  ((dayOfWeek(_time_)-1) * SECS_PER_DAY) )   // note that week starts on day 1
#define previousSunday(_time_)  (_time_ - elapsedSecsThisWeek(_time_))      // time at the start of the week for the given time
#define nextSunday(_time_) ( previousSunday(_time_)+SECS_PER_WEEK)          // time at the end of the week for the given time


/* Useful Macros for converting elapsed time to a time_t */

///Converts minutes to seconds
#define minutesToTime_t ((M)) ( (M) * SECS_PER_MIN)

///Converts hours to seconds
#define hoursToTime_t   ((H)) ( (H) * SECS_PER_HOUR)

///Converts days to seconds (fixed on Jul 22 2011)
#define daysToTime_t    ((D)) ( (D) * SECS_PER_DAY)

///Converts weeks to seconds
#define weeksToTime_t   ((W)) ( (W) * SECS_PER_WEEK)

/*============================================================================*/
/*  time and date functions   */

///Gives actual hour
int     hour();

///Gives the hour for the given time
int     hour(time_t t);

///Gives the hour now in 12 hour format
int     hourFormat12();

///Gives the hour for the given time in 12 hour format
int     hourFormat12(time_t t);

///Indicates if time now is AM
uint8_t isAM();

///Indicates if time entered is AM
uint8_t isAM(time_t t);

///Indicates if time now is PM
uint8_t isPM();

///Indicates if time entered is PM
uint8_t isPM(time_t t);

///Gives the minutes now
int     minute();

///Gives the minutes for the entered time
int     minute(time_t t);

///Gives the seconds now
int     second();

///Gives the seconds for the entered time
int     second(time_t t);

///Gives the days now
int     day();

///Gives the days for the entered time
int     day(time_t t);

///Gives the day of the week now
int     weekday();

///Gives the day of the week for the entered time
int     weekday(time_t t);

///Gives the month now
int     month();

///Gives the month for the entered time
int     month(time_t t);

///Gives the year now
int     year();

///Gives the year for the entered time
int     year(time_t t);

///Gives the current time in seconds (since Jan 1 1970)
time_t now();

///Set actual time
void    setTime(time_t t);

///Set actual time and date
void    setTime(int hr,int min,int sec,int day, int month, int yr);

///Adjust current time
void    adjustTime(long adjustment);

/* date strings */

///Length of longest date string (excluding terminating null)
#define dt_MAX_STRING_LEN 9

char* monthStr(uint8_t month);
char* dayStr(uint8_t day);
char* monthShortStr(uint8_t month);
char* dayShortStr(uint8_t day);

/* time sync functions	*/
timeStatus_t timeStatus(); // indicates if time has been set and recently synchronized
void    setSyncProvider( getExternalTime getTimeFunction); // identify the external time provider
void    setSyncInterval(time_t interval); // set the number of seconds between re-sync

/* low level functions to convert to and from system time                     */
void breakTime(time_t time, tmElements_t &tm);  // break time_t into elements
time_t makeTime(tmElements_t &tm);  // convert time elements into time_t


#endif /* _Time_h */

