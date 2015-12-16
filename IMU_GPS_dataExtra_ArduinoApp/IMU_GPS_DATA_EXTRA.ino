#include "Wire.h"
#include "N:\VS_TESTING\TEMP\GPS_2015_09_18\MPU6050_raw\I2Cdev\I2Cdev.h"
#include "N:\VS_TESTING\TEMP\GPS_2015_09_18\MPU6050_raw\MPU6050\MPU6050.h"
#include "N:\VS_TESTING\TEMP\GPS_2015_09_18\MPU6050_raw\I2Cdev\I2Cdev.cpp"
#include "N:\VS_TESTING\TEMP\GPS_2015_09_18\MPU6050_raw\MPU6050\MPU6050.cpp"

//----------------------------------//
#define GNRMC_TERM "$GNRMC,"		//定义要解析的指令，因为这条指令包含定位和时间信息

char nmeaSentence[68];
String latitude;		//纬度
String longitude;		//经度
String lndSpeed;		//速度
String gpsTime;			//UTC时间，本初子午线经度0度的时间，和北京时间差8小时
String beiJingTime;		//北京时间
//----------------------------------//

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO


// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

#define LED_PIN 13
bool blinkState = false;

void setup() {
// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
Fastwire::setup(400, true);
#endif


// initialize serial communication
// (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
// it's really up to you depending on your project)
Serial.begin(9600);


// initialize device
Serial.println("Initializing I2C devices...");
accelgyro.initialize();


// verify connection
Serial.println("Testing device connections...");
Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


// use the code below to change accel/gyro offset values
/*
Serial.println("Updating internal sensor offsets...");
// -76-23591688000
Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
Serial.print("\n");
accelgyro.setXGyroOffset(220);
accelgyro.setYGyroOffset(76);
accelgyro.setZGyroOffset(-85);
Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
Serial.print("\n");
*/


// configure Arduino LED for
pinMode(LED_PIN, OUTPUT);
}

//----------------------------------//
String getBeiJingTime(String s)
{
  int hour = s.substring(0,2).toInt();
  int minute = s.substring(2,4).toInt();
  int second = s.substring(4,6).toInt();

  hour += 8;

  if(hour > 24)
    hour -= 24;
  s = String(hour) + String(minute) + String(second);
  return s;
}

//Parse GNRMC NMEA sentence data from String
//String must be GNRMC or no data will be parsed
//Return Latitude
String parseGNRMcLat(String s)
{
  int pLoc = 0; //paramater location pointer
  int lEndLoc = 0; //lat parameter end location
  int dEndLoc = 0; //direction parameter end location
  String lat;
  /*make sure that we are parsing the GNRMC string. 
   Found that setting s.substring(0,5) == "GNRMC" caused a FALSE.
   There seemed to be a 0x0D and 0x00 character at the end. */
  if(s.substring(0,4) == "GNRM")
  {
    //Serial.println(s);
    for(int i = 0; i < 5; i++)
    {
      if(i < 3) 
      {
        pLoc = s.indexOf(',', pLoc+1);
        /*Serial.print("i < 3, pLoc: ");
         Serial.print(pLoc);
         Serial.print(", ");
         Serial.println(i);*/
      }
      if(i == 3)
      {
        lEndLoc = s.indexOf(',', pLoc+1);
        lat = s.substring(pLoc+1, lEndLoc);
        /*Serial.print("i = 3, pLoc: ");
         Serial.println(pLoc);
         Serial.print("lEndLoc: ");
         Serial.println(lEndLoc);*/
      }
      else
      {
        dEndLoc = s.indexOf(',', lEndLoc+1);
        lat = lat + " " + s.substring(lEndLoc+1, dEndLoc);
        /*Serial.print("i = 4, lEndLoc: ");
         Serial.println(lEndLoc);
         Serial.print("dEndLoc: ");
         Serial.println(dEndLoc);*/
      }
    }
    return lat; 
  }
  //}
  //}
}

//Parse GNRMC NMEA sentence data from String
//String must be GNRMC or no data will be parsed
//Return Longitude
String parseGNRMcLon(String s)
{
  int pLoc = 0; //paramater location pointer
  int lEndLoc = 0; //lat parameter end location
  int dEndLoc = 0; //direction parameter end location
  String lon;

  /*make sure that we are parsing the GNRMC string. 
   Found that setting s.substring(0,5) == "GNRMC" caused a FALSE.
   There seemed to be a 0x0D and 0x00 character at the end. */
  if(s.substring(0,4) == "GNRM")
  {
    //Serial.println(s);
    for(int i = 0; i < 7; i++)
    {
      if(i < 5) 
      {
        pLoc = s.indexOf(',', pLoc+1);
        /*Serial.print("i < 3, pLoc: ");
         Serial.print(pLoc);
         Serial.print(", ");
         Serial.println(i);*/
      }
      if(i == 5)
      {
        lEndLoc = s.indexOf(',', pLoc+1);
        lon = s.substring(pLoc+1, lEndLoc);
        /*Serial.print("i = 3, pLoc: ");
         Serial.println(pLoc);
         Serial.print("lEndLoc: ");
         Serial.println(lEndLoc);*/
      }
      else
      {
        dEndLoc = s.indexOf(',', lEndLoc+1);
        lon = lon + " " + s.substring(lEndLoc+1, dEndLoc);
        /*Serial.print("i = 4, lEndLoc: ");
         Serial.println(lEndLoc);
         Serial.print("dEndLoc: ");
         Serial.println(dEndLoc);*/
      }
    }
    return lon; 
  }
}

//Parse GNRMC NMEA sentence data from String
//String must be GNRMC or no data will be parsed
//Return Longitude
String parseGNRMcSpeed(String s)
{
  int pLoc = 0; //paramater location pointer
  int lEndLoc = 0; //lat parameter end location
  int dEndLoc = 0; //direction parameter end location
  String lndSpeed;

  /*make sure that we are parsing the GNRMC string. 
   Found that setting s.substring(0,5) == "GNRMC" caused a FALSE.
   There seemed to be a 0x0D and 0x00 character at the end. */
  if(s.substring(0,4) == "GNRM")
  {
    //Serial.println(s);
    for(int i = 0; i < 8; i++)
    {
      if(i < 7) 
      {
        pLoc = s.indexOf(',', pLoc+1);
        /*Serial.print("i < 8, pLoc: ");
         Serial.print(pLoc);
         Serial.print(", ");
         Serial.println(i);*/
      }
      else
      {
        lEndLoc = s.indexOf(',', pLoc+1);
        lndSpeed = s.substring(pLoc+1, lEndLoc);
        /*Serial.print("i = 8, pLoc: ");
         Serial.println(pLoc);
         Serial.print("lEndLoc: ");
         Serial.println(lEndLoc);*/
      }
    }
    return lndSpeed; 
  }
}


//Parse GNRMC NMEA sentence data from String
//String must be GNRMC or no data will be parsed
//Return Longitude
String parseGNRMcTime(String s)
{
  int pLoc = 0; //paramater location pointer
  int lEndLoc = 0; //lat parameter end location
  int dEndLoc = 0; //direction parameter end location
  String gpsTime;

  /*make sure that we are parsing the GNRMC string. 
   Found that setting s.substring(0,5) == "GNRMC" caused a FALSE.
   There seemed to be a 0x0D and 0x00 character at the end. */
  if(s.substring(0,4) == "GNRM")
  {
    //Serial.println(s);
    for(int i = 0; i < 2; i++)
    {
      if(i < 1) 
      {
        pLoc = s.indexOf(',', pLoc+1);
        /*Serial.print("i < 8, pLoc: ");
         Serial.print(pLoc);
         Serial.print(", ");
         Serial.println(i);*/
      }
      else
      {
        lEndLoc = s.indexOf(',', pLoc+1);
        gpsTime = s.substring(pLoc+1, lEndLoc);
        /*Serial.print("i = 8, pLoc: ");
         Serial.println(pLoc);
         Serial.print("lEndLoc: ");
         Serial.println(lEndLoc);*/
      }
    }
    return gpsTime; 
  }
}

// Turn char[] array into String object
String charToString(char *c)
{

  String val = "";

  for(int i = 0; i <= sizeof(c); i++) 
  {
    val = val + c[i];
  }

  return val;
}
//----------------------------------//

void loop() {
  
  //for (unsigned long start = millis(); millis() - start < 1000;)	//一秒钟内不停扫描GPS信息
  //{
    //while (Serial.available())	//串口获取到数据开始解析
    //{
// read raw accel/gyro measurements from device
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


// these methods (and a few others) are also available
//accelgyro.getAcceleration(&ax, &ay, &az);
//accelgyro.getRotation(&gx, &gy, &gz);


#ifdef OUTPUT_READABLE_ACCELGYRO
// display tab-separated accel/gyro x/y/z values
Serial.print("%IMU:");
Serial.print(ax); Serial.print(",");
Serial.print(ay); Serial.print(",");
Serial.print(az); Serial.print(",");
Serial.print(gx); Serial.print(",");
Serial.print(gy); Serial.print(",");
Serial.print(gz); Serial.println("*");
//Serial.println(gz); 
#endif


#ifdef OUTPUT_BINARY_ACCELGYRO
Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
#endif


// blink LED to indicate activity
blinkState = !blinkState;
digitalWrite(LED_PIN, blinkState);
//delay(200);

//-------------------------//
// For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)	//一秒钟内不停扫描GPS信息
  {
    while (Serial.available())	//串口获取到数据开始解析
    {
      char c = Serial.read();	//读取一个字节获取的数据

      switch(c)					//判断该字节的值
      {
      case '$':					//若是$，则说明是一帧数据的开始
        Serial.readBytesUntil('*', nmeaSentence, 67);		//读取接下来的数据，存放在nmeaSentence字符数组中，最大存放67个字节
        //Serial.println(nmeaSentence);
        latitude = parseGNRMcLat(nmeaSentence);	//获取纬度值
        longitude = parseGNRMcLon(nmeaSentence);//获取经度值
        lndSpeed = parseGNRMcSpeed(nmeaSentence);//获取速度值
        gpsTime = parseGNRMcTime(nmeaSentence);//获取GPS时间


        if(latitude > "")		//当不是空时候打印输出
        {
          //Serial.println("------------------------------------");
          Serial.println("$LAT:" + latitude);
        }

        if(longitude > "")		//当不是空时候打印输出
        {
          Serial.println("LOT:" + longitude);
        }  

        if(lndSpeed > "")		//当不是空时候打印输出
        {
          Serial.println("SPD:" + lndSpeed);
        }

        if(gpsTime > "")		//当不是空时候打印输出
        {
          Serial.println("TIM:" + gpsTime);
          beiJingTime = getBeiJingTime(gpsTime);	//获取北京时间 
          Serial.println("BJT:" + beiJingTime + "#");        
        }		
      }
    }
  }
//------------------------//
}
