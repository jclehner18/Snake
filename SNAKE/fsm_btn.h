// Implement a Mealy state machine in C.

/* Copyright 2021 John Lehner & Josiah Mortorff

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/



#include "stm32l053xx.h"
#include <stdint.h>

    // The state alphabet:
enum btn_status{UP, DOWN, MAYBE_PRESSED, MAYBE_RELEASED};

    // The state machine input values:
enum btn_level {BTN_ACTIVE, BTN_INACTIVE};

	// The state machine output values
enum btn_edge {ACTIVE, INACTIVE, ACTIVATING_EDGE, DEACTIVATING_EDGE};

    // The state machine's memory:
struct btn_struct{uint32_t mask_for_btn; 
                  volatile uint32_t *pin_ptr; 
                  enum btn_status state;};

    // Initialization:
void init_btn(uint32_t mask_for_btn, 
              volatile uint32_t *pin_ptr, 
              struct btn_struct *pb);

    // Collect input from HW and translate to state-input-alphabet 
enum btn_level read_btn(struct btn_struct *pb);
 
    // The state-transition table or Moore diagram written into C code
enum btn_edge update_btn(struct btn_struct *pb);



