  /*
   * CODE BY PBK IN 2021/7/2
   * REFERENCE : https://www.instructables.com/Absolute-Beginners-Guide-to-TFT-LCD-Displays-by-Ar/
   */
  
  #include <MCUFRIEND_kbv.h>  // 
  #include <Adafruit_GFX.h>   // the library must be included
  #include <TouchScreen.h>    // 必須匯入函式庫
  
  #if defined(__SAM3X8E__)
      #undef __FlashStringHelper::F(string_literal)
      #define F(string_literal) string_literal
  #endif
  
  /* wiring with UNO or Mega2560:
   *   5V      ==>  5V
   *   GND     ==>  Ground
   *   LCD_RD  ==>  A0  
   *   LCD_WR  ==>  A1  
   *   LCD_RS  ==>  A2  
   *   LCD_CS  ==>  A3  
   *   LCD_RST ==>  A4  
   *   LCD_D0  ==>  8  
   *   LCD_D1  ==>  9  
   *   LCD_D2  ==>  2
   *   LCD_D3  ==>  3
   *   LCD_D4  ==>  4
   *   LCD_D5  ==>  5
   *   LCD_D6  ==>  6
   *   LCD_D7  ==>  7
   */
  
  
  #define LCD_RESET A4
  #define LCD_CS A3
  #define LCD_CD A2
  #define LCD_WR A1
  #define LCD_RD A0
  
  #define YP A2  // !!!!! YOU SHOULD GO TO (FILE > EXAMPLES > MCUFRIEND_kbv > diagnose_Touchpins) TO CHECK OUT THE PINS OF THE TOUCH SCREEN !!!!!
  #define XM A3  // 重要!!!必須先到 (檔案 > 範例 > MCUFRIEND_kbv > diagnose_Touchpins) 來確認觸控螢幕的腳位序號是否正確，它會提示你這裡應該改成什麼
  #define YM 8
  #define XP 9
  
  #define TS_MINX 127  // 
  #define TS_MAXX 915
  
  #define TS_MINY 125
  #define TS_MAXY 965
  TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
  

  #define	BLACK   0x0000  // 0x(R)(G)(B)(對比度?越大越低)
  #define	BLUE    0x001F  // UTFT color code
  #define	RED     0xF800
  #define	GREEN   0x07E0
  #define CYAN    0x07FF
  #define MAGENTA 0xF81F
  #define YELLOW  0xFFE0
  #define WHITE   0xFFFF
  uint16_t CUSTOM = 0xFFFF;  // 自訂 
  uint16_t CUSTOM_r = 0xF00F;
  uint16_t CUSTOM_g = 0x0F0F;
  uint16_t CUSTOM_b = 0x00FF;
  
  
  MCUFRIEND_kbv tft;
  
  #define BOXSIZE 20
  //#define PENRADIUS 0.5
  byte PENRADIUS = 2;  // radius of the pen   畫筆粗細的半徑
  byte prev_PENRADIUS = 2;
  int oldcolor, currentcolor;
  
  void setup(void) {
    Serial.begin(9600);
    
    tft.reset();
  
    uint16_t identifier = tft.readID();   //  辨識驅動器類型
    if(identifier == 0x9325){
      Serial.println(F("Found ILI9325 LCD driver"));
    } 
    else if(identifier == 0x9328){
      Serial.println(F("Found ILI9328 LCD driver"));
    } 
    else if(identifier == 0x4535){
      Serial.println(F("Found LGDP4535 LCD driver"));
    }
    else if(identifier == 0x7575){
      Serial.println(F("Found HX8347G LCD driver"));
    } 
    else if(identifier == 0x9595){
      Serial.println(F("Found HX8347-I LCD driver"));
    } 
    else if(identifier == 0x4747){
      Serial.println(F("Found HX8347-D LCD driver"));
    } 
    else if(identifier == 0x8347){
      Serial.println(F("Found HX8347-A LCD driver"));
    }
    else if(identifier == 0x9341){
      Serial.println(F("Found ILI9341 LCD driver"));
    }
    else if(identifier == 0x7783){
      Serial.println(F("Found ST7781 LCD driver"));
    }
    else if(identifier == 0x8230){
      Serial.println(F("Found UC8230 LCD driver"));  
    }
    else if(identifier == 0x8357){
      Serial.println(F("Found HX8357D LCD driver"));
    } 
    else if(identifier==0x0101){     
        identifier=0x9341;
        Serial.println(F("Found 0x9341 LCD driver"));
    }
    else if(identifier==0x7793){     
         Serial.println(F("Found ST7793 LCD driver"));
    }
    else if(identifier==0xB509){     
         Serial.println(F("Found R61509 LCD driver"));
    }
    else if(identifier==0x9486){     
         Serial.println(F("Found ILI9486 LCD driver"));
    }
    else if(identifier==0x9488){     
         Serial.println(F("Found ILI9488 LCD driver"));
    }
    else {
      Serial.print(F("Unknown LCD driver chip: "));
      Serial.println(identifier, HEX);
      Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
      Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
      Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
      Serial.println(F("If using the breakout board, it should NOT be #defined!"));
      Serial.println(F("Also if using the breakout, double-check that all wiring"));
      Serial.println(F("matches the tutorial."));
      identifier=0x9488; 
    }
    tft.begin(identifier); 
  
    tft.fillScreen(BLACK);
  
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);                           // 1st layer tool, standard color select   第一層工具列：標準顏色選單
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
    tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, BLACK);
    tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);
    tft.fillRect(BOXSIZE * 15, 0, BOXSIZE, BOXSIZE, RED);
   
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);                         // 1st layer tool, a white frame standing for preset color      第一層工具列：顏色選單預設：紅色外白框
    currentcolor = RED;                                                  // preset color: red       預設：紅色畫筆

    for(int i = 0; i <= 100; i ++){                                      // 1st layer tool, for adjusting the pen lenth     第一層工具列：粗細調節
      tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);
    }
    tft.fillRect(200, 3, 3, BOXSIZE - 6, WHITE);                         // instruction of the pen lenth      粗細指示游標
    

    //tft.fillRect(BOXSIZE * 0.5, BOXSIZE + 2, 100, BOXSIZE - 4, WHITE);
    for(long j = 0; j < 16; j += 1){                                     // 2nd layer tool, manual color adjustment     第二層工具列：RGB顏色自訂
      tft.fillCircle(10 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (4096 * j)); // R
    }
    tft.drawRect(85, 23, 4, BOXSIZE - 6, WHITE);                         // instruction of the "R" color percentage     顏色深淺指示游標預設
    for(long j = 0; j < 16; j += 1){
      tft.fillCircle(102 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (128 * j)); // G 
    }
    tft.drawRect(177, 23, 4, BOXSIZE - 6, WHITE);
    for(long j = 0; j < 16; j += 1){
      tft.fillCircle(194 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (2 * j));   // B
    }
    tft.drawRect(269, 23, 4, BOXSIZE - 6, WHITE);
    
    pinMode(13, OUTPUT);
  }
  
  #define MINPRESSURE 10
  #define MAXPRESSURE 1000
  
  void loop(){
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
  
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //pinMode(YM, OUTPUT);

  
    if(p.z > MINPRESSURE && p.z < MAXPRESSURE) {                             // if being pressed     被按下了
  
      p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
      p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
      //p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
      //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
   
      if(p.y < BOXSIZE){                                                     // 1st layer tool being pressed     按了第一層工具列
         oldcolor = currentcolor;                                            // record the last used color     紀錄上次用的顏色
  
         if(p.x < BOXSIZE){                                                  // the red buttom is pressed    按下紅色按鈕
           currentcolor = RED; 
           tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);                      // instruct the color using now      指示現在的顏色
         } 
         else if(p.x < BOXSIZE * 2){
           currentcolor = YELLOW;
           tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if(p.x < BOXSIZE * 3){
           currentcolor = GREEN;                                             // 青草綠
           tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if(p.x < BOXSIZE*4){
           currentcolor = CYAN;                                              // 天空藍 (其實不太像~)
           tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if(p.x < BOXSIZE*5){
           currentcolor = BLUE;
           tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if(p.x < BOXSIZE * 6){
           currentcolor = MAGENTA;                                           // 洋紅色 (但是偏紫)
           tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
         }
         else if(p.x < BOXSIZE * 7){
           currentcolor = WHITE;
           tft.drawRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, BLACK);
         }
         else if(p.x < BOXSIZE*8){
           currentcolor = BLACK;
           tft.drawRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, WHITE);
         }
         else if(p.x > BOXSIZE * 14  &&  p.x < BOXSIZE * 15){                // custom color    自訂顏色顯示格
           currentcolor = CUSTOM;
           tft.drawRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, WHITE);
           //delay(100);
           //tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);
         }
         else if(p.x > BOXSIZE * 15){                                        // erase all, and change background into the color using now    全部清除 (以目前的顏色作為背景)
           tft.drawRect(BOXSIZE * 15, 0, BOXSIZE, BOXSIZE, WHITE);
           delay(100);
           tft.fillRect(BOXSIZE * 15, 0, BOXSIZE, BOXSIZE, RED);
           tft.fillRect(0, 40, 320, 440, currentcolor);
         }
  
         if(oldcolor != currentcolor){                                       // erase the white frame if not using the color    消除指示畫筆顏色用的白框
            if(oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
            if(oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
            if(oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
            if(oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
            if(oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
            if(oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
            if(oldcolor == WHITE) tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, WHITE);
            if(oldcolor == BLACK) tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, BLACK);
            if(oldcolor == CUSTOM) tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);
         }
        for(int i = 0; i <= 100; i ++){                                      // to refill the lenth instructer into the new color    換顏色時也改變線條粗細指示工具的顏色
          tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);
          delay(1);
        }
        tft.fillRect(PENRADIUS * 15 + 170, 3, 3, BOXSIZE - 6, WHITE);

        if(p.x > 150  &&  p.x < 280){                                        // detect the request pen lenth    偵測並計算指定的線條粗細
          PENRADIUS = (p.x - 170) / 15;
          //tft.fillRect(p.x, BOXSIZE + 3, 3, BOXSIZE - 6, WHITE);
          if(prev_PENRADIUS != PENRADIUS){
            tft.fillRect(160, 0, 120, BOXSIZE, BLACK);                       // fill it black    先蓋掉它
            for(int i = 0; i <= 100; i ++){
              tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);  // re-draw the icon    畫回工具
            }
            tft.fillRect(PENRADIUS * 15 + 170, 3, 3, BOXSIZE - 6, WHITE);    // re-draw the instructer    畫回線條粗細指示游標
            //delay(3);
            prev_PENRADIUS = PENRADIUS;
          }
        }
      }
      
      else if(p.y > BOXSIZE  &&  p.y < BOXSIZE * 2){                            // 2ndt layer tool being pressed     按了第二層工具列
        oldcolor = currentcolor;
        if(p.x > 4  &&  p.x < 91){                                              // R (caculate the red color (HEX))     偵測並計算紅色占比(十六進位)
          CUSTOM_r = 4096 * int((constrain(p.x, 10, 84) - 10) / 5);             // 16 ^ 3 = 4096
          tft.fillRect(0, BOXSIZE, 93, BOXSIZE, BLACK);                         // fill it black    先蓋掉它
          for(long j = 0; j < 16; j += 1){
            tft.fillCircle(10 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (4096 * j));  // re-draw the icon    畫回工具
          }
          tft.drawRect(constrain(p.x, 10, 85), 23, 4, BOXSIZE - 6, WHITE);      // re-draw the instructer  顏色深淺指示游標
        }
        else if(p.x > 96  &&  p.x < 183){                                       // G
          CUSTOM_g = 128 * int((constrain(p.x, 102, 176) - 102) / 5); 
          tft.fillRect(92, BOXSIZE, 93, BOXSIZE, BLACK);
          for(long j = 0; j < 16; j += 1){
            tft.fillCircle(102 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (128 * j));
          }
          tft.drawRect(constrain(p.x, 102, 177), 23, 4, BOXSIZE - 6, WHITE);
        }
        else if(p.x > 188  &&  p.x < 275){                                      // B
          CUSTOM_b = 2 * int((constrain(p.x, 193, 267) - 193) / 5); 
          tft.fillRect(184, BOXSIZE, 93, BOXSIZE, BLACK);
          for(long j = 0; j < 16; j += 1){
            tft.fillCircle(194 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (2 * j));
          }
          //tft.drawRect(269, 23, 4, BOXSIZE - 6, WHITE);
          tft.drawRect(constrain(p.x, 193, 268), 23, 4, BOXSIZE - 6, WHITE);
        }
        CUSTOM = CUSTOM_r + CUSTOM_g + CUSTOM_b;
        tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);                // fill the custom color icon    右上角顏色指示器刷新
        currentcolor = CUSTOM;

        for(int i = 0; i <= 100; i ++){                                         // change the color of lenth icon    刷新粗細調節器顏色
          tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);
          delay(1);
        }
        tft.fillRect(PENRADIUS * 15 + 170, 3, 3, BOXSIZE - 6, WHITE);
        tft.drawRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, WHITE);
        if (oldcolor != currentcolor) {
           if(oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
           if(oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
           if(oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
           if(oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
           if(oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
           if(oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
           if(oldcolor == WHITE) tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, WHITE);
           if(oldcolor == BLACK) tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, BLACK);
           if(oldcolor == CUSTOM) tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);
        }
      }
      
      if(((p.y-PENRADIUS) > BOXSIZE * 2)  &&  ((p.y+PENRADIUS) < tft.height())){  // if the painting area being pressed    繪畫區
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);                        // print the line by several circles    用很多圓堆成線
      }
    }
  }
