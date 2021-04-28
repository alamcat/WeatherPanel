#include <FS.h>
#include <WiFi.h>
#include <Wire.h>
#include <time.h> 
#include <SPIFFS.h>
#include <GxEPD2_BW.h>
#include <esp_sleep.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <U8g2_for_Adafruit_GFX.h>

#include "const.h"
#include "esp_bt.h"
#include "switcher.h"
#include "esp_wifi.h"

#include "fonts/u8g2_mfyuehei_14_gb2312.h"
#include "fonts/u8g2_mfyuehei_18_gb2312.h"
#include "fonts/u8g2_mfyuehei_45_number.h"

#define ENABLE_GxEPD2_GFX 0

// Current
String icon;
String city;
String currDay;
String currMon;
String currWeekDay;
String updateTimeStr;
uint8_t currTime;
JsonObject currWeather;

// Three days
uint8_t dayAfterTom;
JsonArray threeDaysWeather;

// Other
String locationCode;
String locationName;
HTTPClient httpClient;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
RTC_NOINIT_ATTR bool firstOpen = true;


/*
 * @brief Function for connecting wifi
 */
bool connectWifi(const char* ssid, const char* pwd)
{
    WiFi.begin(ssid, pwd);
    uint8_t times = 0;
    while (WiFi.status() != WL_CONNECTED && times < 30)
    {
        delay(500);
        Serial.printf(".");
        times++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnect to the WiFi successfully");
        return true;
    }
    else
    {
        Serial.println("\nCannot connect to the WiFi");
        return false;
    }
}

/*
 * @brief Initialise the system.
 */
void initSys()
{
    if (firstOpen == true)
    {
        display.firstPage();
        do
        {
            u8g2Fonts.setFont(u8g2_mfyuehei_18_gb2312);
            u8g2Fonts.drawUTF8(140, 100, "系统启动中");
            u8g2Fonts.setFont(u8g2_mfyuehei_14_gb2312);
            u8g2Fonts.drawUTF8(10, 270, "Made by: Alamcat v0.1");
            u8g2Fonts.drawUTF8(10, 290, "Data sources: QWeather, Taobao, ip-api");
            display.display();
        }
        while (display.nextPage());
    }
    if (!connectWifi(ssid, pwd)) 
    {
        display.firstPage();
        do
        {
            u8g2Fonts.setFont(u8g2_mfyuehei_18_gb2312);
            u8g2Fonts.drawUTF8(25, 100, "WIFI无法连接，请检查网络配置");
            display.display();
        }
        while (display.nextPage()); 
    }
}

/*
 * @brief Initialise the screen.
 */
void initScreen()
{
    display.init();
    SPI.end();
    SPI.begin(13, 12, 14, 15);
    u8g2Fonts.begin(display); 
    u8g2Fonts.setFontMode(1);
    u8g2Fonts.setFontDirection(0); 
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);
    u8g2Fonts.setBackgroundColor(GxEPD_WHITE);
}

/*
 * @brief Function for displaying the weather module
 */
void displayWeather()
{
    // Current area
    icon = currWeather["icon"].as<String>();
    String temp = currWeather["temp"].as<String>() + "°C";  
    String text = currWeather["text"].as<String>();
    String hourAndMin = updateTimeStr.substring(11, 16);
    String humidity =  currWeather["humidity"].as<String>() + "%";
    String windDir = currWeather["windDir"].as<String>();
    String windScale = currWeather["windScale"].as<String>() + "级";
    
    u8g2Fonts.setFont(u8g2_mfyuehei_18_gb2312);
    u8g2Fonts.drawUTF8(130, 35, temp.c_str());
    u8g2Fonts.drawUTF8(130, 80, text.c_str());
    
    u8g2Fonts.setFont(u8g2_mfyuehei_14_gb2312);
    u8g2Fonts.drawUTF8(130, 120, locationName.c_str());
    u8g2Fonts.drawUTF8(50, 140, hourAndMin.c_str());

    uint otherInfoOffsetX = 213;
    u8g2Fonts.drawUTF8(otherInfoOffsetX + 25, 30, windDir.c_str());
    u8g2Fonts.drawUTF8(otherInfoOffsetX + 25, 65, windScale.c_str());
    u8g2Fonts.drawUTF8(otherInfoOffsetX + 25, 100, humidity.c_str());

    display.drawInvertedBitmap(otherInfoOffsetX, 13, windDirIcon, 20, 20, GxEPD_BLACK);
    display.drawInvertedBitmap(otherInfoOffsetX, 48, windScaleIcon, 20, 20, GxEPD_BLACK);
    display.drawInvertedBitmap(otherInfoOffsetX, 83, humidityIcon, 20, 20, GxEPD_BLACK);

    display.drawInvertedBitmap(25, 123, upIcon, 18, 18, GxEPD_BLACK);
    display.drawInvertedBitmap(0, 0, getIconPointer(icon.toInt(), 128), 128, 128, GxEPD_BLACK);
    
    // Three days area
    uint16_t offsetX = 32;
    uint16_t offsetY = 265;
    uint16_t offsetXHeader = 35;

    u8g2Fonts.setFont(u8g2_mfyuehei_14_gb2312); 
    for (JsonObject day : threeDaysWeather)
    {
        String nextDayTempRange = day["tempMin"].as<String>() + "°C - " + day["tempMax"].as<String>() + "°C";
        String nextDayText = day["textDay"].as<String>();

        display.drawInvertedBitmap(offsetX + 18, offsetY - 80, getIconPointer(day["iconDay"].as<String>().toInt(),64), 64, 64, GxEPD_BLACK);
        u8g2Fonts.drawUTF8(offsetX, offsetY, nextDayTempRange.c_str());
        Serial.println(nextDayText.length());
        uint16_t offsetXText = offsetX + 42;
        if (nextDayText.length() == 6)
        {
            offsetXText = offsetX + 32;
        } 
        else if (nextDayText.length() == 9)
        {
            offsetXText = offsetX + 23;
        }
        else if (nextDayText.length() > 9)
        {
            offsetXText = offsetX + 12;
        }
        u8g2Fonts.drawUTF8(offsetXText, offsetY + 25, nextDayText.c_str());
        offsetX += 115;
    }
    u8g2Fonts.drawUTF8(offsetXHeader + 25, offsetY - 85, "今天");
    u8g2Fonts.drawUTF8(offsetXHeader + 140, offsetY - 85, "明天");
    u8g2Fonts.drawUTF8(offsetXHeader + 250, offsetY - 85, getWeekDay(dayAfterTom).c_str());

    // Sunrise and Sunset area
    String sunriseTime = threeDaysWeather[0]["sunrise"];
    String sunsetTime = threeDaysWeather[0]["sunset"];
    uint8_t sunriseHour = sunriseTime.substring(0,2).toInt();
    uint8_t sunsetHour = sunsetTime.substring(0,2).toInt();
    
    if ((currTime > sunriseHour && currTime > sunsetHour) || (currTime < sunriseHour && currTime < sunsetHour)) 
    {
        // Sunrise
        u8g2Fonts.drawUTF8(otherInfoOffsetX + 25, 135, sunriseTime.c_str());
        display.drawInvertedBitmap(otherInfoOffsetX, 119, sunrise, 20, 20, GxEPD_BLACK);
    }
    else 
    {
        // Sunset
        u8g2Fonts.drawUTF8(otherInfoOffsetX + 25, 135, sunsetTime.c_str());
        display.drawInvertedBitmap(otherInfoOffsetX, 119, sunset, 20, 20, GxEPD_BLACK);
    }
}

/*
 * @brief Function for displaying calendar module
 */
void displayCalendar()
{
    uint16_t dayX = 330;
    uint16_t monX = 325;
    monX = currMon.length() > 6 ? monX - 20 : monX;
    dayX = currDay.length() > 1 ? dayX - 20 : dayX;

    u8g2Fonts.setFont(u8g2_mfyuehei_45_number);
    u8g2Fonts.drawUTF8(dayX, 60, currDay.c_str());   
    u8g2Fonts.setFont(u8g2_mfyuehei_18_gb2312);
    u8g2Fonts.drawUTF8(monX, 100, currMon.c_str());
    u8g2Fonts.setFont(u8g2_mfyuehei_14_gb2312);
    u8g2Fonts.drawUTF8(320, 130, currWeekDay.c_str());
}

/*
 * @brief Function for getting the location code.
 */
void getLocationCode(String api)
{
    WiFiClientSecure client;
    client.setInsecure();
    httpClient.begin(client, api);
    uint8_t respondCode = httpClient.GET();
    if (respondCode == HTTP_CODE_OK || respondCode == HTTP_CODE_MOVED_PERMANENTLY) 
    {
        String payload = httpClient.getString();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);         
        JsonArray locations = doc["location"];
        locationCode = locations[0]["id"].as<String>();
        locationName = locations[0]["name"].as<String>();
    }
    httpClient.end();
    client.stop();
}

/*
 * @brief Function for getting the name of current city.
 */
void getCityRequest(String api)
{
    httpClient.begin(api);
    uint8_t respondCode = httpClient.GET();
    if (respondCode == HTTP_CODE_OK || respondCode == HTTP_CODE_MOVED_PERMANENTLY) 
    {
        String payload = httpClient.getString();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);           
        city = doc["city"].as<String>();
    }
    httpClient.end();
}

/*
 * @brief Function for getting the information of weather.
 */
void getWeatherRequest(String api, uint8_t apiType)
{
    WiFiClientSecure client;
    client.setInsecure();
    httpClient.begin(client, api);
    uint8_t respondCode = httpClient.GET();
    if (apiType == 2) // Three days
    {
        if (respondCode == HTTP_CODE_OK || respondCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
            String payload = httpClient.getString();
            DynamicJsonDocument doc1(3 * 1024 + 512);
            deserializeJson(doc1, payload); 
            
            threeDaysWeather = doc1["daily"]; 
        }      
    }
    else // Current
    {
        if (respondCode == HTTP_CODE_OK || respondCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
            String payload = httpClient.getString();
            DynamicJsonDocument doc2(72 * 512);
            deserializeJson(doc2, payload);
            updateTimeStr = doc2["updateTime"].as<String>();           
            currWeather = doc2["now"];
        }
    }
    httpClient.end();
    client.stop();
}

/*
 * @brief Function for getting the local time.
 */
void getLocalTime(String api)
{
    httpClient.begin(api);
    uint8_t respondCode = httpClient.GET();
    String timeStamp;
    if (respondCode == HTTP_CODE_OK || respondCode == HTTP_CODE_MOVED_PERMANENTLY) 
    {
        String payload = httpClient.getString();
        DynamicJsonDocument doc3(1024 * 10);
        deserializeJson(doc3, payload);    
        JsonObject timeData = doc3["data"];       
        timeStamp = timeData["t"].as<String>().substring(0, 10);
    }
    httpClient.end();

    char weekCharArray[10];
    char monCharArray[10];
    char dayCharArray[10];
    char timeCharArray[10];
    
    time_t timeStampStruct = (time_t)(atoi(timeStamp.c_str()) + timeOffset);
    strftime(weekCharArray, sizeof(weekCharArray), "%w", localtime(&timeStampStruct));
    strftime(monCharArray, sizeof(monCharArray), "%m", localtime(&timeStampStruct));
    strftime(dayCharArray, sizeof(dayCharArray), "%d", localtime(&timeStampStruct));
    strftime(timeCharArray, sizeof(timeCharArray), "%H", localtime(&timeStampStruct));

    currMon = monCharArray;
    currWeekDay = weekCharArray;
    currDay = dayCharArray;
    String currTimeStr = timeCharArray;

    currTime = currTimeStr.toInt();
    dayAfterTom = currWeekDay.toInt() + 2;
    dayAfterTom = dayAfterTom > 6 ? dayAfterTom % 7 : dayAfterTom;
    currMon = getMonStr(currMon.toInt());
    currWeekDay = getWeekDay(currWeekDay.toInt());
}

/*
 * @brief Controller for all requests.
 */
void requestController(String api, uint8_t apiType)
{
    if (apiType == 0) // Get the city
    {
        getCityRequest(api);
    }
    else if (apiType == 1) // Get the location code
    {
        getLocationCode(api);
    }
    else if (apiType == 4)// Get the weather of that location
    {
        getLocalTime(api);
    }
    else{
        getWeatherRequest(api, apiType);
    }
}

/*
 * @brief Controller for all displaying operations.
 */
void displayController()
{
    display.firstPage();
    do
    {
        display.drawLine(200, 15, 200, 135, GxEPD_BLACK);  // |
        display.drawLine(20, 150, 380, 150, GxEPD_BLACK);  // -

        displayWeather();
        displayCalendar();

        display.display();
    }
    while (display.nextPage());
}

/*
 * @brief deep sleep mechanism helps to save the energy.
 */
void deepSleep()
{
    esp_sleep_enable_timer_wakeup(sleepHour * 3);
    esp_deep_sleep_start();
    Serial.println(esp_sleep_get_wakeup_cause());
    esp_bt_controller_disable();
    esp_wifi_stop();
}


void setup()
{
    Serial.begin(115200); 
    initScreen();
    initSys();

    if (WiFi.status() == WL_CONNECTED)
    {
        // Do not change the order of request
        requestController(timeApi, 4);
        requestController(cityApi, 0);
        requestController(locApi + city, 1);
        requestController(weaApiNow + locationCode, 3);
        requestController(weaApiThree + locationCode, 2);

        displayController();

        firstOpen = false;
        deepSleep();
    } 
    else
    {
        esp_restart();
    }
}

void loop() 
{

}

