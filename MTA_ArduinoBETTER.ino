#include <LiquidCrystal.h>
#include <ESP8266WiFi.h> //wifi library for Feather Huzzah
#include <ESP8266HTTPClient.h> //library to perform GET request to APIs
#include <ArduinoJson.h> //library to parse JSON data from APIs
//Wifi Credentials
const char* ssid = "Crocodile Magazine"; 
const char* password = "JungleR0ck"; 

const int rs = 14, en = 12, d4 = 16, d5 = 2, d6 = 5, d7 = 4; //GPIO pins of Feather Huzzah
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Corresponding LCD pins


void setup() {
  lcd.begin(16, 2);
  //lcd.print("Nassau Av");
  //Serial.begin(115200); //set baud to 115200
  WiFi.begin(ssid, password);
  //lcd.print("Searching For WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    //lcd.print("Connecting..");
    //lcd.clear();
   
  }
 
}


//string separating function

String getSplitValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}



void loop() {
   
    
  if (WiFi.status() == WL_CONNECTED) {
    //lcd.print("Connected Successfully!"); //confirm successful wifi connection
    HTTPClient http;  //create new object of class HTTPClient for MTA API
    HTTPClient http2;
    
    http.begin("http://easy-mtapi.herokuapp.com/by-id/e3da"); 
    http2.begin("http://api.timezonedb.com/v2.1/get-time-zone?key=K3PU5QS2CZQ6&format=json&by=zone&zone=America/New_York"); //Current Time API URL
   
    int httpCode = http.GET();
    int httpCode2 = http2.GET();
  
    
    
    const size_t bufferSize = 2*JSON_ARRAY_SIZE(1) + 2*JSON_ARRAY_SIZE(2) + 2*JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(1) + 9*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(8) + 540;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    const size_t bufferSize2 = JSON_OBJECT_SIZE(9) + 250;
    DynamicJsonBuffer jsonBuffer2(bufferSize2);
    
   
     JsonObject& root = jsonBuffer.parseObject(http.getStream()); //payload for train data
     JsonObject& root2 = jsonBuffer2.parseObject(http2.getString()); //payload for current time data

      JsonObject& data0 = root["data"][0];

      JsonArray& data0_N = data0["N"];
      
      const char* data0_N0_route = data0_N[0]["route"]; // "G"
      Serial.println(data0_N0_route);
      const char* data0_N0_time = data0_N[0]["time"]; // "2018-12-11T19:11:44-05:00"
      
      const char* data0_N1_route = data0_N[1]["route"]; // "G"
      const char* data0_N1_time = data0_N[1]["time"]; // "2018-12-11T19:20:05-05:00"
      
      const char* data0_N2_route = data0_N[2]["route"]; // "G"
      const char* data0_N2_time = data0_N[2]["time"]; // "2018-12-11T19:25:26-05:00"
      
      const char* data0_N3_route = data0_N[3]["route"]; // "G"
      const char* data0_N3_time = data0_N[3]["time"]; // "2018-12-11T19:32:00-05:00"
      
      JsonArray& data0_S = data0["S"];
      
      const char* data0_S0_route = data0_S[0]["route"]; // "G"
      const char* data0_S0_time = data0_S[0]["time"]; // "2018-12-11T19:07:45-05:00"
      
      const char* data0_S1_route = data0_S[1]["route"]; // "G"
      const char* data0_S1_time = data0_S[1]["time"]; // "2018-12-11T19:15:30-05:00"
      
      const char* data0_S2_route = data0_S[2]["route"]; // "G"
      const char* data0_S2_time = data0_S[2]["time"]; // "2018-12-11T19:23:30-05:00"
      
      const char* data0_S3_route = data0_S[3]["route"]; // "G"
      const char* data0_S3_time = data0_S[3]["time"]; // "2018-12-11T19:31:30-05:00"
      
      const char* data0_id = data0["id"]; // "e3da"
      const char* data0_last_update = data0["last_update"]; // "2018-12-11T19:06:41-05:00"
      
      float data0_location0 = data0["location"][0]; // 40.724635
      float data0_location1 = data0["location"][1]; // -73.951277
      
      const char* data0_name = data0["name"]; // "Nassau Av"
      
      const char* data0_routes0 = data0["routes"][0]; // "G"
      
      float data0_stops_G280 = data0["stops"]["G28"][0]; // 40.724635
      float data0_stops_G281 = data0["stops"]["G28"][1]; // -73.951277
      
      const char* updated = root["updated"]; // "2018-12-11T19:06:41-05:00"

      const char* formatted = root2["formatted"]; // current data/time
     
      String CurrentMinutes = getSplitValue(root2["formatted"] , ':', 1);
      String CurrentHours0 = getSplitValue(root2["formatted"], ' ', 1);
      String CurrentHours= getSplitValue(CurrentHours0, ':', 0);
      
      String NextTrainMinutesNorth1 = getSplitValue(data0_N0_time, 'T' , 1);
      String NextTrainMinutesNorth2 = getSplitValue(NextTrainMinutesNorth1, '-', 0);
      String NextTrainMinutesNorth3 = getSplitValue(NextTrainMinutesNorth2, ':', 1);
      String NextTrainHoursNorth = getSplitValue(NextTrainMinutesNorth2, ':',0);

      String NextTrainMinutesSouth1 = getSplitValue(data0_S0_time, 'T' , 1);
      String NextTrainMinutesSouth2 = getSplitValue(NextTrainMinutesSouth1, '-', 0);
      String NextTrainMinutesSouth3 = getSplitValue(NextTrainMinutesSouth2, ':', 1);
      String NextTrainHoursSouth = getSplitValue(NextTrainMinutesSouth2, ':', 0);
      
      int CurrentMinutes1 = CurrentHours.toInt()*60;
      
      int CurrentMinutes2 = CurrentMinutes1 + CurrentMinutes.toInt();

      int TimeTillNorthTrain0= NextTrainHoursNorth.toInt()*60;
      int TimeTillNorthTrain1 = TimeTillNorthTrain0 + NextTrainMinutesNorth3.toInt();

      int TimeTillSouthTrain0 = NextTrainHoursSouth.toInt()*60;
      int TimeTillSouthTrain1 = TimeTillSouthTrain0 + NextTrainMinutesSouth3.toInt();
      
      int TimeTillNorthTrain = TimeTillNorthTrain1 - CurrentMinutes2;
      int TimeTillSouthTrain = TimeTillSouthTrain1 - CurrentMinutes2;
      

      if (TimeTillNorthTrain != -1){
        lcd.setCursor(0,0);
        lcd.print("Court Sq:  ");
        lcd.print(TimeTillNorthTrain);
        lcd.print(" mins");
        lcd.setCursor(0,1);
        lcd.print("Church Av: ");
        lcd.print(TimeTillSouthTrain);
        lcd.print(" mins");
      
      }
     
  
    http.end();   //Close connection
  }
  // Delay
  delay(3000); 
  }
