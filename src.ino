/*
   Kalman Filter Implementation 
   DHT11/12 & XY-MD02
   errorEst = estimation uncertainty
   errorMea = measurement uncertainty
*/
#include <ModbusMaster.h>
#include "DHT.h"

///////// PIN /////////
#define MAX485_DE      4
#define MAX485_RE_NEG  0
#define RX2 16
#define TX2 17
#define dhtPin 21
#define dhtType DHT11
#define WIFISSID "your-ssid"
#define PASSWORD "your-password"

ModbusMaster node;
DHT dht(dhtPin, dhtType);

uint8_t result;
float temp, hum, temp2, hum2;
unsigned char dataArduino[3];
boolean publishCek;
float errorEst = 0.035, errorMea = 0.035;
float kalmanGain, currentEst, lastEst, estimated_value;

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX2, TX2);
  node.begin(1, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  dht.begin();
}

void loop()
{
  // Data Frame --> 01 04 00 01 00 02 20 0B
  result = node.readInputRegisters(0x0001, 2);
  if (result == node.ku8MBSuccess)            // add !(isnan(humi) || isnan(temp)) when use DHT sensor
  {
    temp = node.getResponseBuffer(0) / 10.0f;
    hum = node.getResponseBuffer(1) / 10.0f;
    estimated_value = run_kalmanFilter(hum);
    //    komunikasi_pc(hum, estimated_value);
    Serial.print("hum = ");
    Serial.print(hum);
    Serial.print(" KF = ");
    Serial.print(estimated_value);
    Serial.println();
  }
}
