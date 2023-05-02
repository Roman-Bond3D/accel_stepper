#include <AccelStepper.h>

const int
    ESTOP1_PIN = 12,
    ESTOP2_PIN = 13;

AccelStepper stepper(AccelStepper::DRIVER, 2, 5, true);

const bool emergencyStop()
{
   const bool eStop1 = digitalRead(ESTOP1_PIN);
   const bool eStop2 = digitalRead(ESTOP1_PIN);

   if (eStop1 && eStop2)
   {
      return true;
   } else 
   {
      return false;
   }
}

void stepperSetup()
{
   stepper.setEnablePin(8);
   // stepper.setPinsInverted(false, false, true);
   stepper.setAcceleration(750);
   stepper.setMaxSpeed(1000);
   stepper.setSpeed(500);
}

void stepperRun(const bool run)
{
   if (run)
   {
      stepper.runSpeed();
   }
   else
   {
      stepper.stop();
   }
}

void setup()
{
   pinMode(ESTOP1_PIN, INPUT);
   pinMode(ESTOP2_PIN, INPUT);

   stepperSetup();
}

void loop()
{   
   stepperRun(emergencyStop());
}
