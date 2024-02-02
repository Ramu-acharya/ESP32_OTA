#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//--------------------- Function Prototypes ------------------------------//
void printTemperature(uint8_t *address, int sensor_index = 0);



// Define fixed addresses for specific sensors
const int num_of_temp_sensor = 5;
String sensorNames[] = {"Battery", "VCU", "Dashboard", "Charger", "Motor"};

uint8_t addresses[num_of_temp_sensor][8] = {
    {0x28, 0xEC, 0xEA, 0x43, 0xD4, 0xE1, 0x3C, 0x6E},
    {0x28, 0x92, 0x5F, 0x43, 0xD4, 0xE1, 0x3C, 0x78},
    {0x28, 0xA9, 0xB1, 0x43, 0xD4, 0xE1, 0x3C, 0x15},
    {0x28, 0x75, 0x4E, 0x43, 0xD4, 0xE1, 0x3C, 0x65},
    {0x28, 0x1D, 0x12, 0x43, 0xD4, 0xE1, 0x3C, 0xB3}
};
// Array to hold the names of the sensors

// Array to hold data and addresses for 5 sensors
float sensorInfo[5][2]; // Column 0: Data, Column 1-8: Address

void setup(void) {
  Serial.begin(9600);
  
  sensors.begin();
   // locate devices on the bus
  Serial.print("\n\nLocatig devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices");

  Serial.println("\n\n-----------------------------------------");
  Serial.println("Custom Device Addresses:");
  for (int i = 0; i<num_of_temp_sensor; i++){
    Serial.print("Sensor Stored ADDR Value" + String(i+1) + ": ");
    for(int j=0; j<8; j++){
      if(addresses[i][j] < 16) Serial.print("0");//0x0C < 16
      Serial.print(addresses[i][j], HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }


  for (int i = 0; i<num_of_temp_sensor; i++)
   sensors.setResolution(addresses[i], 12);
 
  for (int i = 0; i<num_of_temp_sensor; i++){
  Serial.print("Sensor Resolution" + String(i+1) + ": ");
  Serial.println(sensors.getResolution(addresses[i]), DEC);
 }

  int numberOfDevices = sensors.getDeviceCount();
  Serial.print("Number of devices found: ");  Serial.println(numberOfDevices);
}

void loop(void) {
  sensors.requestTemperatures(); // request all connected temp sensors to measure temp data
  Serial.println("\n\n---------------------------------------------");
  for (int i = 0; i<num_of_temp_sensor; i++){
   printTemperature(addresses[i], i); 
  } 
  delay(5000);
}

// void printAddress(DeviceAddress deviceAddress) {
//   for (uint8_t i = 0; i < 8; i++) {
//     if (deviceAddress[i] < 16) {
//       Serial.print("0");
//     }
//     Serial.print(deviceAddress[i], HEX);
//   }
// }

void printTemperature(uint8_t *address, int sensor_index){
  float tempC = sensors.getTempC(address);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Error: Data Read failure for for Temp Sensor at: ");
    Serial.println(sensorNames[sensor_index]);
    return;
  }
 
  Serial.print("success: Data Temp Sensor at: ");
  Serial.print(sensorNames[sensor_index]);
  Serial.print(" Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC));
}

