#include <WiFi.h>




const char* ssid = "THRYV 9383";
const char* password = "123456789";




WiFiServer server(5000);




void setup()
{
  Serial.begin(115200);




  delay(1000);




  Serial.println();
  Serial.println("ESP32-WROOM - RECEIVER");
  Serial.println("BNO055 Wi-Fi Receiver");




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




  Serial.print("ESP32-WROOM IP address: ");




  Serial.println(WiFi.localIP());




  server.begin();




  Serial.println("TCP server started.");




  Serial.println("Waiting for ESP32-C3...");
}




void loop()
{




  WiFiClient client = server.available();








  if (client)
  {
    Serial.println();
    Serial.println("ESP32-C3 connected!");








    while (client.connected())
    {
      if (client.available())
      {




        String data = client.readStringUntil('\n');


        data.trim();


        int comma1 = data.indexOf(',');
        int comma2 = data.indexOf(',', comma1 + 1);
        int comma3 = data.indexOf(',', comma2 + 1);
        int comma4 = data.indexOf(',', comma3 + 1);
        int comma5 = data.indexOf(',', comma4 + 1);
        int comma6 = data.indexOf(',', comma5 + 1);


        if (comma6 != -1)
        {


          String sendTime = data.substring(0, comma1);


          String accX = data.substring(comma1 + 1, comma2);
          String accY = data.substring(comma2 + 1, comma3);
          String accZ = data.substring(comma3 + 1, comma4);


          String gyroX = data.substring(comma4 + 1, comma5);
          String gyroY = data.substring(comma5 + 1, comma6);
          String gyroZ = data.substring(comma6 + 1);


          Serial.print("SEND_TIME: ");
          Serial.print(sendTime);
          Serial.print(" ms | ACC: ");


          Serial.print(accX);
          Serial.print(", ");


          Serial.print(accY);
          Serial.print(", ");


          Serial.print(accZ);


          Serial.print(" | GYRO: ");


          Serial.print(gyroX);
          Serial.print(", ");


          Serial.print(gyroY);
          Serial.print(", ");


          Serial.println(gyroZ);




        }
      }
    }






    Serial.println("ESP32-C3 disconnected.");
  }








  delay(500);
}
