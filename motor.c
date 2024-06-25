//MOTOR


#include <stdio.h>
#include "pico/stdlib.h"

int main() {
  uint en = 21;
  uint out1 = 5;
  uint out2 = 20;

  gpio_init(en); 
  gpio_init(out1); // en
  gpio_init(out2);

  gpio_set_dir(en, GPIO_OUT);
  gpio_set_dir(out1, GPIO_OUT);
  gpio_set_dir(out2, GPIO_OUT);

  gpio_put(en, 1);
  gpio_put(out1, 1);
  gpio_put(out2, 0);

  while(1) {
    printf("Out 1 = %d, Out 2 = %d \n", out1, out2);
    tight_loop_contents();
  }
}


