#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "queue.h"
#include "display.h"
#include "game.h"
#include "led.h"
//#include "queue.c"


extern queue_t Direction;// queue for use from knob to game logic
extern queue_t Locations;

extern queue_t light;
