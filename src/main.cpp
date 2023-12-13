#include <AccelStepper.h>
const int
    ESTOP1_PIN = 12,
    ESTOP2_PIN = 13,
    START_PIN = 16,
    STOP_PIN = 15;

bool
    enable = false;

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
      enable = false;
      return false;
   }
}

void emergencySetup()
{
   pinMode(ESTOP1_PIN, INPUT_PULLUP);
   pinMode(ESTOP2_PIN, INPUT_PULLUP);
}

void enableSetup()
{
   pinMode(START_PIN, INPUT_PULLUP);
   pinMode(STOP_PIN, INPUT_PULLUP);
}

void stepperSetup()
{
   stepper.setEnablePin(8);
   stepper.setPinsInverted(false, false, true);
   stepper.setAcceleration(500);
   stepper.setMaxSpeed(1200);
   stepper.setSpeed(-1200);
}

void enableStepper(bool safe)
{
   if (safe)
   {
      const bool start = !digitalRead(START_PIN);
      const bool stop = !digitalRead(STOP_PIN);

      if (start && !stop)
      {
         enable = true;
      }
      else if (stop)
      {
         enable = false;
      }

      if (enable)
      {
         stepper.enableOutputs();
         stepper.runSpeed();
         // Serial.println("start");
      }
      else
      {
         stepper.disableOutputs();
         // Serial.println("stop");
      }
   }
}

void setup()
{
   // Serial.begin(9600);
   emergencySetup();
   enableSetup();
   stepperSetup();
}

void loop()
{
   enableStepper(emergencyStop());
}
