#include "timer.h"
// #include "deferred_exec.h"
// deferred exec is a way to make qmk handle the timing.
//it can only have so many, and you only get a callback when the thing is done
// would be great for other features but I want to update the leds during the timer
// so I need to hook into the update loop (matrix_scan_user)
#define RGB_MODE_DEFAULT RGBLIGHT_MODE_RAINBOW_SWIRL
#define RGB_MODE_ALERT RGBLIGHT_MODE_ALTERNATING
#define RGB_MODE_TESTING RGBLIGHT_MODE_STATIC_LIGHT
#define RGBLIGHT_LED_COUNT 19

//check timers.h for struct explanation
struct timers_struct timers = {
	{ //status
	#define TIMER(a,b,c,d) false,
		TIMER_TABLE
	#undef TIMER
	},{ //duration_s
	#define TIMER(a,b,c,d) d,
		TIMER_TABLE
	#undef TIMER
	},{ //elapsed_ms
	#define TIMER(a,b,c,d) 0,
		TIMER_TABLE
	#undef TIMER
	},{ //elapsed_s
	#define TIMER(a,b,c,d) 0,
		TIMER_TABLE
	#undef TIMER
	},{ //alert
	#define TIMER(a,b,c,d) &b,
		TIMER_TABLE
	#undef TIMER
	},{ //alertColor
	#define TIMER(a,b,c,d) c,
		TIMER_TABLE
	#undef TIMER
	}
};

void reset_timer(int timer) {
	timers.elapsed_ms[timer] = 0;
	timers.elapsed_s[timer] = 0;
}

void logo(int timer){ // Set one of the 4 logo leds for each quarter of the duration
	if(timers.status[timer] == Alerting){
		// Setting alert color this way does not work 
		// I think I'll have to make a custom rgbmode
		switch (timers.alertColor[timer]) {
			case Purple: rgblight_sethsv_noeeprom(HSV_PURPLE);
			case Blue: rgblight_sethsv_noeeprom(HSV_BLUE);
			case Green: rgblight_sethsv_noeeprom(HSV_GREEN);
			case Yellow: rgblight_sethsv_noeeprom(HSV_YELLOW);
			case Orange: rgblight_sethsv_noeeprom(HSV_ORANGE);
			case Red: rgblight_sethsv_noeeprom(HSV_RED);
		}
		rgblight_mode_noeeprom(RGB_MODE_ALERT); // this flashes red even after setting the color
		if( timers.elapsed_s[timer] >= (timers.duration_s[timer] + 5)) {
			reset_timer(timer);
			timers.status[timer] = Stopped;
			rgblight_reload_from_eeprom();
		}
	}
	else if(timers.status[timer] == Running){
		const uint16_t duration_part = timers.duration_s[timer] / 4;
		// Set one of the 4 logo leds for each quarter of the duration
		switch (timers.elapsed_s[timer] / duration_part) {
			case 0: rgblight_sethsv_at(HSV_GREEN, 19); break;
			case 1: rgblight_sethsv_at(HSV_GREEN, 18); break;
			case 2: rgblight_sethsv_at(HSV_GREEN, 17); break;
			case 3: rgblight_sethsv_at(HSV_GREEN, 16); break;
			case 4: timers.status[timer] = Alerting;
		}
	}  
	else if(timers.status[timer] == Init){
		//set the rgb mode to static so it doesn't change the leds outside the timer
		//can only some leds be static for timer and the rest be animated?
		rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
		//turn off all the leds
		for( int i = 0; i <= RGBLIGHT_LED_COUNT; i++){
			rgblight_sethsv_at(HSV_OFF, i);
		}
		timers.status[timer] = Running;
	}
}

void matrix_scan_user(void) {
	//for each running timer, increment it each second
	// not sure on the call rate of this function 
	//but it's probably not going to be off by more than a ms or 2 each second
	for(int i=0; i < NUM_TIMERS; i++){
		if(timers.status[i] > 0){
			if(timer_elapsed(timers.elapsed_ms[i])>1000) {
				timers.elapsed_s[i]++;
				timers.elapsed_ms[i] = timer_read();
				timers.alert[i](i);
			}
		}
	}
}

void send_timer(int timer) {
	reset_timer(timer); 
	timers.status[timer] = Init; 
	timers.elapsed_ms[timer] = timer_read();
}