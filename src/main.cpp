#include <AccelStepper.h>

const int
    ESTOP1_PIN = 12,
    ESTOP2_PIN = 13;

AccelStepper stepper(AccelStepper::DRIVER, 2, 5, true);

const bool emergencyStop()
{
   const bool eStop1 = digitalRead(ESTOP1_PIN);
   const bool eStop2 = digitalRead(ESTOP1_PIN);

   if (!eStop1 && !eStop2)
   {
      stepper.enableOutputs();
      return true;
   }
   else
   {
      stepper.disableOutputs();
      return false;
   }
}

void emergencySetup()
{
   pinMode(ESTOP1_PIN, INPUT_PULLUP);
   pinMode(ESTOP2_PIN, INPUT_PULLUP);
}

void stepperRun(const bool run)
{
   if (run)
   {
      stepper.runSpeed();
   }
}

void stepperSetup()
{
   stepper.setEnablePin(8);
   stepper.setPinsInverted(false, false, true);
   stepper.setAcceleration(500);
   stepper.setMaxSpeed(1000);
   stepper.setSpeed(-1000);   
}

void setup()
{
   //Serial.begin(9600);
   emergencySetup();
   stepperSetup();
}

void loop()
{
   const bool run = emergencyStop();
   stepperRun(run);
   //Serial.println(run);
}
