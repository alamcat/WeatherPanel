# include "switcher.h"

/*
 * @brief Function for selecting the weather icon.
 */
const unsigned char* getIconPointer(uint16_t code, uint8_t bitType)
{
    const unsigned char* p;
    switch(code)
    {
        case 100:
        p = bitType == 64 ? gImage_64_100 : gImage_128_100;
        break;
        case 101:
        p = bitType == 64 ? gImage_64_101 : gImage_128_101;
        break;
        case 102:
        p = bitType == 64 ? gImage_64_102 : gImage_128_102;
        break;
        case 103:
        p = bitType == 64 ? gImage_64_103 : gImage_128_103;
        break;
        case 104:
        p = bitType == 64 ? gImage_64_104 : gImage_128_104;
        break;
        case 150:
        p = bitType == 64 ? gImage_64_150 : gImage_128_150;
        break;
        case 153:
        p = bitType == 64 ? gImage_64_153 : gImage_128_153;
        break;
        case 154:
        p = bitType == 64 ? gImage_64_154 : gImage_128_154;
        break;
        case 300:
        p = bitType == 64 ? gImage_64_300 : gImage_128_300;
        break;
        case 301:
        p = bitType == 64 ? gImage_64_301 : gImage_128_301;
        break;
        case 302:
        p = bitType == 64 ? gImage_64_302 : gImage_128_302;
        break;
        case 303:
        p = bitType == 64 ? gImage_64_303 : gImage_128_303;
        break;
        case 304:
        p = bitType == 64 ? gImage_64_304 : gImage_128_304;
        break;
        case 305:
        p = bitType == 64 ? gImage_64_305 : gImage_128_305;
        break;
        case 306:
        p = bitType == 64 ? gImage_64_306 : gImage_128_306;
        break;
        case 307:
        p = bitType == 64 ? gImage_64_307 : gImage_128_307;
        break;
        case 308:
        p = bitType == 64 ? gImage_64_308 : gImage_128_308;
        break;
        case 309:
        p = bitType == 64 ? gImage_64_309 : gImage_128_309;
        break;
        case 310:
        p = bitType == 64 ? gImage_64_310 : gImage_128_310;
        break;
        case 311:
        p = bitType == 64 ? gImage_64_311 : gImage_128_311;
        break;
        case 312:
        p = bitType == 64 ? gImage_64_312 : gImage_128_312;
        break;
        case 313:
        p = bitType == 64 ? gImage_64_313 : gImage_128_313;
        break;
        case 314:
        p = bitType == 64 ? gImage_64_314 : gImage_128_314;
        break;
        case 315:
        p = bitType == 64 ? gImage_64_315 : gImage_128_315;
        break;
        case 316:
        p = bitType == 64 ? gImage_64_316 : gImage_128_316;
        break;
        case 317:
        p = bitType == 64 ? gImage_64_317 : gImage_128_317;
        break;
        case 318:
        p = bitType == 64 ? gImage_64_318 : gImage_128_318;
        break;
        case 350:
        p = bitType == 64 ? gImage_64_350 : gImage_128_350;
        break;
        case 351:
        p = bitType == 64 ? gImage_64_351 : gImage_128_351;
        break;
        case 399:
        p = bitType == 64 ? gImage_64_399 : gImage_128_399;
        break;
        case 400:
        p = bitType == 64 ? gImage_64_400 : gImage_128_400;
        break;
        case 401:
        p = bitType == 64 ? gImage_64_401 : gImage_128_401;
        break;
        case 402:
        p = bitType == 64 ? gImage_64_402 : gImage_128_402;
        break;
        case 403:
        p = bitType == 64 ? gImage_64_403 : gImage_128_403;
        break;
        case 404:
        p = bitType == 64 ? gImage_64_404 : gImage_128_404;
        break;
        case 405:
        p = bitType == 64 ? gImage_64_405 : gImage_128_405;
        break;
        case 406:
        p = bitType == 64 ? gImage_64_406 : gImage_128_406;
        break;
        case 407:
        p = bitType == 64 ? gImage_64_407 : gImage_128_407;
        break;
        case 408:
        p = bitType == 64 ? gImage_64_408 : gImage_128_408;
        break;
        case 409:
        p = bitType == 64 ? gImage_64_409 : gImage_128_409;
        break;
        case 410:
        p = bitType == 64 ? gImage_64_410 : gImage_128_410;
        break;
        case 456:
        p = bitType == 64 ? gImage_64_456 : gImage_128_456;
        break;
        case 457:
        p = bitType == 64 ? gImage_64_457 : gImage_128_457;
        break;
        case 499:
        p = bitType == 64 ? gImage_64_499 : gImage_128_499;
        break;
        case 500:
        p = bitType == 64 ? gImage_64_500 : gImage_128_500;
        break;
        case 501:
        p = bitType == 64 ? gImage_64_501 : gImage_128_501;
        break;
        case 502:
        p = bitType == 64 ? gImage_64_502 : gImage_128_502;
        break;
        case 503:
        p = bitType == 64 ? gImage_64_503 : gImage_128_503;
        break;
        case 504:
        p = bitType == 64 ? gImage_64_504 : gImage_128_504;
        break;
        case 507:
        p = bitType == 64 ? gImage_64_507 : gImage_128_507;
        break;
        case 508:
        p = bitType == 64 ? gImage_64_508 : gImage_128_508;
        break;
        case 509:
        p = bitType == 64 ? gImage_64_509 : gImage_128_509;
        break;
        case 510:
        p = bitType == 64 ? gImage_64_510 : gImage_128_510;
        break;
        case 511:
        p = bitType == 64 ? gImage_64_511 : gImage_128_511;
        break;
        case 512:
        p = bitType == 64 ? gImage_64_512 : gImage_128_512;
        break;
        case 513:
        p = bitType == 64 ? gImage_64_513 : gImage_128_513;
        break;
        case 514:
        p = bitType == 64 ? gImage_64_514 : gImage_128_514;
        break;
        case 515:
        p = bitType == 64 ? gImage_64_515 : gImage_128_515;
        break;
        case 900:
        p = bitType == 64 ? gImage_64_900 : gImage_128_900;
        break;
        case 901:
        p = bitType == 64 ? gImage_64_901 : gImage_128_901;
        break;
        case 999:
        p = bitType == 64 ? gImage_64_999 : gImage_128_999;
        break;
    }
    return p;
}

String getMonStr(uint8_t mon)
{
    String currMon = "N/A";
    switch(mon)
    {
      case 1:
      currMon = "一月";
      break;
      case 2:
      currMon = "二月";
      break;
      case 3:
      currMon = "三月";
      break;
      case 4:
      currMon = "四月";
      break;
      case 5:
      currMon = "五月";
      break;
      case 6:
      currMon = "六月";
      break;
      case 7:
      currMon = "七月";
      break;
      case 8:
      currMon = "八月";
      break;
      case 9:
      currMon = "九月";
      break;
      case 10:
      currMon = "十月";
      break;
      case 11:
      currMon = "十一月";
      break;
      case 12:
      currMon = "十二月";
      break;
    }
    return currMon;
}

String getWeekDay(uint8_t week)
{
    String currWeekDay = "N/A";
    switch(week)
    {
        case 0:
        currWeekDay = "星期日";
        break;
        case 1:
        currWeekDay = "星期一";
        break;
        case 2:
        currWeekDay = "星期二";
        break;
        case 3:
        currWeekDay = "星期三";
        break;
        case 4:
        currWeekDay = "星期四";
        break;
        case 5:
        currWeekDay = "星期五";
        break;
        case 6:
        currWeekDay = "星期六";
        break;
    }
    return currWeekDay;
}