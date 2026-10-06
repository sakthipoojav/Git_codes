#include <Wire.h>
#include <WiFi.h>


#define SDA_PIN 6
#define SCL_PIN 7


#define BNO055_ADDRESS 0x28
#define CHIP_ID_REG    0x00
#define OPR_MODE_REG   0x3D
#define ACC_X_LSB      0x08
#define GYRO_X_LSB     0x14


const char* ssid = "THRYV 9383";
const char* password = "123456789";




const char* serverIP = "192.168.137.221";
const int serverPort = 5000;


WiFiClient client;


void setup()
{
  Serial.begin(115200);


  delay(1000);


  Serial.println();
  Serial.println("ESP32-C3 - BNO055");
  Serial.println("Acceleration Test");


  Wire.begin(SDA_PIN, SCL_PIN);


  Wire.setClock(100000);


  Serial.println("I2C started");


  Wire.beginTransmission(BNO055_ADDRESS);


  Wire.write(CHIP_ID_REG);


  Wire.endTransmission();


  Wire.requestFrom(BNO055_ADDRESS, 1);


  if (Wire.available())
  {
    uint8_t chipID = Wire.read();


    Serial.print("BNO055 CHIP ID = 0x");
    Serial.println(chipID, HEX);


    if (chipID == 0xA0)
    {
      Serial.println("BNO055 detected!");
    }
    else
    {
      Serial.println("Wrong CHIP ID!");
      Serial.println("Expected 0xA0");
    }
  }
  else
  {
    Serial.println("BNO055 not detected!");
  }


  Wire.beginTransmission(BNO055_ADDRESS);


  Wire.write(OPR_MODE_REG);
  Wire.write(0x00);


  Wire.endTransmission();


  delay(20);


  Wire.beginTransmission(BNO055_ADDRESS);


  Wire.write(OPR_MODE_REG);
  Wire.write(0x0C);


  Wire.endTransmission();


  delay(500);


  Serial.println("BNO055 configured!");
  Serial.println("Starting acceleration readings...");
  Serial.println();


   WiFi.mode(WIFI_STA);


  WiFi.begin(ssid, password);


  Serial.println("Connecting to Wi-Fi...");




  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);


    Serial.print(".");
  }




  Serial.println();


  Serial.println("Wi-Fi connected!");




  Serial.print("ESP32-C3 IP address: ");


  Serial.println(WiFi.localIP());


   Serial.println("Connecting to ESP32-WROOM...");




  while (!client.connect(serverIP, serverPort))
  {
    Serial.println("Connection failed!");


    Serial.println("Trying again...");


    delay(2000);
  }




  Serial.println("Connected to ESP32-WROOM!");


  Serial.println();
  Serial.println("Starting IMU transmission...");


}




void loop()
{

  //read accelero
  Wire.beginTransmission(BNO055_ADDRESS);


  Wire.write(ACC_X_LSB);


  Wire.endTransmission();


  int bytesReceived = Wire.requestFrom(BNO055_ADDRESS, 6);


  if (bytesReceived == 6)
  {
    uint8_t data[6];
    for (int i = 0; i < 6; i++)
    {
      data[i] = Wire.read();
  }

    
    //read gyro
    Wire.beginTransmission(BNO055_ADDRESS);


    Wire.write(GYRO_X_LSB);


    Wire.endTransmission();


    int gyroBytesReceived = Wire.requestFrom(BNO055_ADDRESS, 6);


    if (gyroBytesReceived == 6)
    {
      uint8_t gyroData[6];


    for (int i = 0; i < 6; i++)
    {
      gyroData[i] = Wire.read();
    }

      // timestamp

    unsigned long timestamp = millis();
    


    uint8_t lsb[3] = { data[0], data[2], data[4]};
    uint8_t msb[3] ={data[1], data[3], data[5]};


    int16_t acc_x_raw = (int16_t)(((uint16_t)msb[0] << 8) | lsb[0]);
    int16_t acc_y_raw = (int16_t)(((uint16_t)msb[1] << 8) | lsb[1]);
    int16_t acc_z_raw =(int16_t)(((uint16_t)msb[2] << 8) | lsb[2]);


    float acc_x = (float)acc_x_raw / 100.0f;
    float acc_y = (float)acc_y_raw / 100.0f;
    float acc_z = (float)acc_z_raw / 100.0f;



    uint8_t gyro_lsb[3] = { gyroData[0], gyroData[2], gyroData[4]};
    uint8_t gyro_msb[3] = { gyroData[1], gyroData[3], gyroData[5]};


    int16_t gyro_x_raw = (int16_t)(((uint16_t)gyro_msb[0] << 8) | gyro_lsb[0]);
    int16_t gyro_y_raw = (int16_t)(((uint16_t)gyro_msb[1] << 8) | gyro_lsb[1]);
    int16_t gyro_z_raw = (int16_t)(((uint16_t)gyro_msb[2] << 8) | gyro_lsb[2]);


    float gyro_x = (float)gyro_x_raw / 16.0f;
    float gyro_y = (float)gyro_y_raw / 16.0f;
    float gyro_z = (float)gyro_z_raw / 16.0f;



    if (client.connected())
    {

        client.print(timestamp);
        client.print(",");

        client.print(acc_x, 2);
        client.print(",");

        client.print(acc_y, 2);
        client.print(",");

        client.print(acc_z, 2);
        client.print(",");

        client.print(gyro_x, 2);
        client.print(",");

        client.print(gyro_y, 2);
        client.print(",");

        client.println(gyro_z, 2);
      
        client.flush();


        Serial.print("SEND_TIME: ");
        Serial.print(timestamp);

        Serial.print(" ms | ACC: ");

        Serial.print(acc_x, 2);
        Serial.print(", ");

        Serial.print(acc_y, 2);
        Serial.print(", ");

        Serial.print(acc_z, 2);

        Serial.print(" | GYRO: ");

        Serial.print(gyro_x, 2);
        Serial.print(", ");

        Serial.print(gyro_y, 2);
        Serial.print(", ");

        Serial.println(gyro_z, 2);
      }
      else
      {
        Serial.println("WROOM disconnected!");
      }

    }
    else
    {
      Serial.println("BNO055 gyroscope read failed!");
    }

  }
  else
  {
    Serial.println("BNO055 accelerometer read failed!");
  }


  delay(5);
}