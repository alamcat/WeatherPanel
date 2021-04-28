// WIFI
const char* ssid = "Your ssid";
const char* pwd = "Your password";
// QWeather api key
const String key = "Your QWeather api";

// UTC+8
const uint16_t timeOffset = 28800; 
// Deep sleep parameters
const uint64_t sleepMin = 60000000; // One min
const uint64_t sleepHour = 3600000000; // One hour

// API
String cityApi = "http://ip-api.com/json/";
String timeApi = "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp";
String locApi = "https://geoapi.qweather.com/v2/city/lookup?gzip=n&key=" + key + "&location=";
String weaApiNow = "https://devapi.qweather.com/v7/weather/now?gzip=n&key=" + key + "&location=";
String weaApiThree = "https://devapi.qweather.com/v7/weather/3d?gzip=n&key=" + key + "&location=";

// Driver for waveshare ESP32 Driver board and E-Paper 4.2 inch
GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=5*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));