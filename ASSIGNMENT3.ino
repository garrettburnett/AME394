/* Digit Light Sensor Module project
   tutorial url: http://osoyoo.com/?p=693
*/
#include <Wire.h>
#include <math.h>

int BH1750address = 0x23;

byte buff[2];


//TEMP HUMIDITY//
#define dht_dpin A1
byte bGlobalErr;
byte dht_dat[5];


void setup()

{
  InitDHT();
  Wire.begin();
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}




void loop()

{
  //LIGHT
  int i;
  uint16_t val_ls = 0;

  BH1750_Init(BH1750address);

  delay(200);

  if (2 == BH1750_Read(BH1750address))

  {

    val_ls = ((buff[0] << 8) | buff[1]) / 1.2;
    Serial.print("Light Sensor Value: ");
    Serial.println(val_ls, DEC); //val_lsÊ®½øÖÆÊä³ö



  }

  delay(150);

  //MOISTURE

  int val, val_old;
  val = digitalRead(3);
  digitalWrite(13, val);
  val_old = 1023 - analogRead(0);
  Serial.print("Moisture Sensor Value:");
  Serial.println(map(val_old, 0, 1023, 0, 100));

  //TEMP HUMIDITY
  ReadDHT();
  switch (bGlobalErr) {
    case 0:
      Serial.print("Current humdity = ");
      Serial.print(dht_dat[0], DEC);
      Serial.print(".");
      Serial.print(dht_dat[1], DEC);
      Serial.println("%  ");
      Serial.print("temperature = ");
      Serial.print(dht_dat[2], DEC);
      Serial.print(".");
      Serial.print(dht_dat[3], DEC);
      Serial.println("C  ");
      break;
    case 1:
      Serial.println("Error 1: DHT start condition 1 not met.");
      break;
    case 2:
      Serial.println("Error 2: DHT start condition 2 not met.");
      break;
    case 3:
      Serial.println("Error 3: DHT checksum error.");
      break;
    default:
      Serial.println("Error: Unrecognized code encountered.");
      break;
  }
  Serial.println(" ");
  Serial.println("____________________________");
  Serial.println(" ");

  delay(1000);
}




int BH1750_Read(int address)

{

  int i = 0;

  Wire.beginTransmission(address);

  Wire.requestFrom(address, 2);
  while (Wire.available())

  {

    buff[i] = Wire.read();

    i++;

  }

  Wire.endTransmission();

  return i;




}




void BH1750_Init(int address)

{

  Wire.beginTransmission(address);

  Wire.write(0x10);

  Wire.endTransmission();

}
void InitDHT() {
  pinMode(dht_dpin, OUTPUT);
  digitalWrite(dht_dpin, HIGH);
}


void ReadDHT() {
  bGlobalErr = 0;
  byte dht_in;
  byte i;
  digitalWrite(dht_dpin, LOW);
  delay(20);

  digitalWrite(dht_dpin, HIGH);
  delayMicroseconds(40);
  pinMode(dht_dpin, INPUT);
  //delayMicroseconds(40);
  dht_in = digitalRead(dht_dpin);

  if (dht_in) {
    bGlobalErr = 1;
    return;
  }
  delayMicroseconds(80);
  dht_in = digitalRead(dht_dpin);

  if (!dht_in) {
    bGlobalErr = 2;
    return;
  }
  delayMicroseconds(80);
  for (i = 0; i < 5; i++)
    dht_dat[i] = read_dht_dat();
  pinMode(dht_dpin, OUTPUT);
  digitalWrite(dht_dpin, HIGH);
  byte dht_check_sum =
    dht_dat[0] + dht_dat[1] + dht_dat[2] + dht_dat[3];
  if (dht_dat[4] != dht_check_sum)
  {
    bGlobalErr = 3;
  }
};

byte read_dht_dat() {
  byte i = 0;
  byte result = 0;
  for (i = 0; i < 8; i++) {
    while (digitalRead(dht_dpin) == LOW);
    delayMicroseconds(30);
    if (digitalRead(dht_dpin) == HIGH)
      result |= (1 << (7 - i));
    while (digitalRead(dht_dpin) == HIGH);
  }
  return result;
}
