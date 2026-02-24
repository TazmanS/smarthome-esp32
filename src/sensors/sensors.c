#include "sensors.h"

#include "sensors/lcd1602/lcd1602.h"
#include "sensors/leds/leds.h"
#include "sensors/pir_motion/pir_motion.h"
#include "sensors/servo/servo.h"
#include "sensors/lm35/lm35.h"
#include "sensors/photocell/photocell.h"
#include "sensors/motor/motor.h"

void sensors_init()
{
  lcd1602_init();
  leds_init();
  lm35_init();
  photocell_init();
  pir_motion_init();
  servos_init();
  motors_init();
}