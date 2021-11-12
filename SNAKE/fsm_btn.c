// Implement a state machine in C.

#include "stm32l053xx.h"
#include <stdint.h>
#include "fsm_btn.h"
#include <assert.h>
extern void gpio_init(void);

// Initializer:
void init_btn(uint32_t mask_for_btn, 
		volatile uint32_t *pin_ptr, 
		struct btn_struct *pb)  
{
		gpio_init();
		pb->state = UP;
		pb->mask_for_btn = mask_for_btn;
		pb->pin_ptr = pin_ptr;
 }

// Collect input from HW and translate to state-input-alphabet 
enum btn_level read_btn(struct btn_struct *pb) // Correct for ACTIVE-LOW.
 {
    if ((*(pb->pin_ptr) & pb->mask_for_btn) == 0) return BTN_ACTIVE;
    else return BTN_INACTIVE;
 }

// The state-transition table or Moore diagram written into C code
enum btn_edge update_btn(struct btn_struct *pb)
{
    enum btn_level b = read_btn(pb);
		enum btn_edge eA = INACTIVE;
		enum btn_edge eB = INACTIVE;
    switch(pb->state)
    {
    case (UP):    
        if (b == BTN_ACTIVE) { pb->state = MAYBE_PRESSED; eA = INACTIVE;}
        else                 { pb->state = UP; eA = INACTIVE;}
        break;
        case (MAYBE_PRESSED):
                if (b == BTN_ACTIVE){ pb->state = DOWN; eA = ACTIVATING_EDGE;}
                else                { pb->state = UP; eA = INACTIVE;}
        break;
        case (DOWN):
                if (b == BTN_ACTIVE) { pb->state = DOWN; eA = ACTIVE;}
                else                 { pb->state = MAYBE_RELEASED; eA = ACTIVE;}
        break;
        case (MAYBE_RELEASED):
                if (b == BTN_ACTIVE) { pb->state = DOWN; eA = ACTIVE;}
                else                 { pb->state = UP; eA = DEACTIVATING_EDGE;}
        break;
        default:  // Required by MISRA - accept the warning.
             pb->state = UP; // In release - minimize damage.
			 eA = INACTIVE;
             assert(0 && "Unhandled special enum constant!"); // In debug phase - crash!
    }
		
		
		
		switch(pb->state) //state machine for eB
    {
    case (DOWN):    
        if (b == BTN_ACTIVE) { pb->state = MAYBE_PRESSED; eB = INACTIVE;}
        else                 { pb->state = UP; eB = INACTIVE;}
        break;
        case (MAYBE_PRESSED):
                if (b == BTN_ACTIVE){ pb->state = DOWN; eB = ACTIVATING_EDGE;}
                else                { pb->state = UP; eB = INACTIVE;}
        break;
        case (UP):
                if (b == BTN_ACTIVE) { pb->state = DOWN; eB = ACTIVE;}
                else                 { pb->state = MAYBE_RELEASED; eB = ACTIVE;}
        break;
        case (MAYBE_RELEASED):
                if (b == BTN_ACTIVE) { pb->state = DOWN; eB = ACTIVE;}
                else                 { pb->state = UP; eB = DEACTIVATING_EDGE;}
        break;
        default:  // Required by MISRA - accept the warning.
             pb->state = UP; // In release - minimize damage.
			 eB = INACTIVE;
             assert(0 && "Unhandled special enum constant!"); // In debug phase - crash!
    }
	return eA;
 }

	


