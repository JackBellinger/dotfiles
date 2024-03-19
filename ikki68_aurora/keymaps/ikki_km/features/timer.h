#pragma once
#include "quantum.h"

/* Define the timers 
(timer name, function to call on alert, color to make the alert flash, and the duration of th e timer) */
#define TIMER_TABLE \
	TIMER(TMR_FIVE,	logo,	Blue,	300)\
	TIMER(TMR_TEN,		logo,	Green,	600)\
	TIMER(TMR_THIRTY,	logo,	Orange,	1800)\
	TIMER(TMR_SIXTY,	logo,	Red,	3600)
#define NUM_TIMERS 4

typedef enum {
	#define TIMER(a, b, c, d) a,
		TIMER_TABLE
	#undef TIMER
} timer_names;

/* Generate function prototypes */
#define TIMER(a, b, c, d) void b(int);
	TIMER_TABLE
#undef TIMER

//this is what we call to start a timer
void send_timer(int timer);

//this doesn't work yet
typedef enum  {
	Purple,
	Blue,
	Green,
	Yellow,
	Orange,
	Red,
}AlertColor;

typedef enum {
	Stopped,
	Init,
	Running,
	Alerting
}TimerStatus;
//the alert functions take an int because it needs to know which alert to check
// since the timers can share an alert function
typedef void(*alert_func_p)(int);

//the data structure that hold all of the state for every timer, paralell arrays
struct timers_struct {
	//status: 0 = stopped, 1 = init, 2 = running, 3 = alerting
	TimerStatus status[NUM_TIMERS];
	//duration in seconds
	const uint16_t duration_s[NUM_TIMERS];
	//the qmk timer_read() function produces milliseconds but uint16_t max is 65535
	uint16_t elapsed_ms[NUM_TIMERS];
	//so we need to count by seconds ourselves to have timers longer than a minute
	uint16_t elapsed_s[NUM_TIMERS];
	//right now all the timers have the same alert function, but what if I want to change things up?
	alert_func_p alert[NUM_TIMERS];
	// what color to display for each timer alert: need to make custom rbg loops for this
	AlertColor alertColor[NUM_TIMERS];
};