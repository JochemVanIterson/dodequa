#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

uint8_t DoFArray[] = { 254, 255, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
uint8_t calibrationArray[] = { 254, 255, 2, 1, 2, 3, 4};
unsigned long newTime;
unsigned long  oldTime;
int  completelyCalibrated;

/* This driver reads raw data from the BNO055
 *
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)

   Updated to send DATA to a dedicated MAX patch.
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();

// From the sensorApi changed to Serial.write
void displayCalStatus(void)
{
  // Get the four calibration values (0..3)
  // Any sensor data reporting 0 should be ignored,
  // 3 means 'fully calibrated"
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  calibrationArray[3] = system;
  calibrationArray[4] = gyro;
  calibrationArray[5] = accel;
  calibrationArray[6] = mag;
  completelyCalibrated = system + gyro + accel + mag; // When all sensors are calibrated this value becomes 12
  Serial.write(calibrationArray, 7);
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/

void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> accellero = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

  // Calibrate when not calibrated:
  if (completelyCalibrated < 12) {
    displayCalStatus();
  }

  /* Display the floating point data */
  DoFArray[3] = highByte(int((euler.x()) * 100));
  DoFArray[4] = lowByte(int((euler.x()) * 100));
  DoFArray[5] = highByte(int((euler.y()) * 100));
  DoFArray[6] = lowByte(int((euler.y()) * 100));
  DoFArray[7] = highByte(int((euler.z()) * 100));
  DoFArray[8] = lowByte(int((euler.z()) * 100));
  DoFArray[9] = highByte(int((accellero.x()) * 100));
  DoFArray[10] = lowByte(int((accellero.x()) * 100));
  DoFArray[11] = highByte(int((accellero.y()) * 100));
  DoFArray[12] = lowByte(int((accellero.y()) * 100));
  DoFArray[13] = highByte(int((accellero.z()) * 100));
  DoFArray[14] = lowByte(int((accellero.z()) * 100));

  while ((micros() - 10000) < oldTime) {
    delayMicroseconds(100);
  }
  oldTime = micros();
  // Serial.write(DoFArray,15);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(euler.x(), 4);
  Serial.print("\tY: ");
  Serial.print(euler.y(), 4);
  Serial.print("\tZ: ");
  Serial.print(euler.z(), 4);
  Serial.println("");
}
