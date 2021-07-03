  /*
   * REFERENCE : https://www.instructables.com/Absolute-Beginners-Guide-to-TFT-LCD-Displays-by-Ar/
   */
  
  #include <MCUFRIEND_kbv.h>
  #include <Adafruit_GFX.h>    // Core graphics library
  #include <TouchScreen.h>
  
  #if defined(__SAM3X8E__)
      #undef __FlashStringHelper::F(string_literal)
      #define F(string_literal) string_literal
  #endif
  
  // wiring with UNO or Mega2560:
  //--------------POWER Pins--------------------------------
  //   5V  connects to DC 5V
  //   GND connects to Ground
  //   3V3 do not need to connect(NC)
  //--------------LCD Display Pins--------------------------
  //   LCD_RD   connects to Analog pin A0  
  //   LCD_WR   connects to Analog pin A1  
  //   LCD_RS   connects to Analog pin A2  
  //   LCD_CS   connects to Analog pin A3  
  //   LCD_RST  connects to Analog pin A4  
  //   LCD_D0   connects to digital pin 8  
  //   LCD_D1   connects to digital pin 9  
  //   LCD_D2   connects to digital pin 2
  //   LCD_D3   connects to digital pin 3
  //   LCD_D4   connects to digital pin 4
  //   LCD_D5   connects to digital pin 5
  //   LCD_D6   connects to digital pin 6
  //   LCD_D7   connects to digital pin 7
  //--------------SD-card fuction Pins ----------------------
  //This Connection Only for UNO, Do not support Mega2560
  //because they use different Hardware-SPI Pins
  //SD_SS    connects to digital pin 10
  //SD_DI    connects to digital pin 11
  //SD_DO    connects to digital pin 12
  //SD_SCK   connects to digital pin 13
  
  
  #define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
  #define LCD_CS A3   // Chip Select goes to Analog 3
  #define LCD_CD A2  // Command/Data goes to Analog 2
  #define LCD_WR A1  // LCD Write goes to Analog 1
  #define LCD_RD A0 // LCD Read goes to Analog 0
  
  #define YP A2  // must be an analog pin, use "An" notation!
  #define XM A3  // must be an analog pin, use "An" notation!
  #define YM 8   // can be a digital pin
  #define XP 9   // can be a digital pin    //XP = 9, XM = A3, YP = A2, YM = 8;
  
  //Param For 3.5"
  #define TS_MINX 127
  #define TS_MAXX 915
  
  #define TS_MINY 125
  #define TS_MAXY 965    // TS_LEFT = 136, TS_RT = 907, TS_TOP = 942, TS_BOT = 139;
  // For better pressure precision, we need to know the resistance
  // between X+ and X- Use any multimeter to read it
  // For the one we're using, its 300 ohms across the X plate
  TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
  
  
  // Assign human-readable names to some common 16-bit color values:
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
  byte PENRADIUS = 2;
  byte prev_PENRADIUS = 2;
  int oldcolor, currentcolor;
  
  void setup(void) {
    Serial.begin(9600);
    Serial.println(F("TFT LCD test"));
  
    tft.reset();
  
    uint16_t identifier = tft.readID();
    if(identifier == 0x9325) {
      Serial.println(F("Found ILI9325 LCD driver"));
    } else if(identifier == 0x9328) {
      Serial.println(F("Found ILI9328 LCD driver"));
    } else if(identifier == 0x4535) {
      Serial.println(F("Found LGDP4535 LCD driver"));
    }else if(identifier == 0x7575) {
      Serial.println(F("Found HX8347G LCD driver"));
    } else if(identifier == 0x9595) {
      Serial.println(F("Found HX8347-I LCD driver"));
    } else if(identifier == 0x4747) {
      Serial.println(F("Found HX8347-D LCD driver"));
    } else if(identifier == 0x8347) {
      Serial.println(F("Found HX8347-A LCD driver"));
    }else if(identifier == 0x9341) {
      Serial.println(F("Found ILI9341 LCD driver"));
    }else if(identifier == 0x7783) {
      Serial.println(F("Found ST7781 LCD driver"));
    }else if(identifier == 0x8230) {
      Serial.println(F("Found UC8230 LCD driver"));  
    }else if(identifier == 0x8357) {
      Serial.println(F("Found HX8357D LCD driver"));
    } else if(identifier==0x0101){     
        identifier=0x9341;
        Serial.println(F("Found 0x9341 LCD driver"));
    }else if(identifier==0x7793){     
         Serial.println(F("Found ST7793 LCD driver"));
    }else if(identifier==0xB509){     
         Serial.println(F("Found R61509 LCD driver"));
    }else if(identifier==0x9486){     
         Serial.println(F("Found ILI9486 LCD driver"));
    }else if(identifier==0x9488){     
         Serial.println(F("Found ILI9488 LCD driver"));
    }else {
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
  
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);  // 第一層工具列：顏色選單
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
    tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, BLACK);
    tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);
    tft.fillRect(BOXSIZE * 15, 0, BOXSIZE, BOXSIZE, RED);
   
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);  // 第一層工具列：顏色選單預設：紅色外白框
    currentcolor = RED;

    for(int i = 0; i <= 100; i ++){  // 第一層工具列：粗細調節
      tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);
    }
    tft.fillRect(200, 3, 3, BOXSIZE - 6, WHITE);  // 粗細指示游標
    

    //tft.fillRect(BOXSIZE * 0.5, BOXSIZE + 2, 100, BOXSIZE - 4, WHITE);
    for(long j = 0; j < 16; j += 1){  // 第二層工具列：RGB顏色自訂
      tft.fillCircle(10 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (4096 * j));
      //CUSTOM = 0xF00F
      //Serial.println(uint16_t(4096 * j, HEX));  //uint16_t RED = 0x0800 + 0xF000; <== 成功
      //delay(50);
    }
    tft.drawRect(85, 23, 4, BOXSIZE - 6, WHITE);  // 顏色深淺指示游標預設
    for(long j = 0; j < 16; j += 1){
      tft.fillCircle(102 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (128 * j));
      //Serial.println(uint16_t(4096 * j, HEX));
    }
    tft.drawRect(177, 23, 4, BOXSIZE - 6, WHITE);
    for(long j = 0; j < 16; j += 1){
      tft.fillCircle(194 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (2 * j));
      //Serial.println(uint16_t(4096 * j, HEX));
    }
    tft.drawRect(269, 23, 4, BOXSIZE - 6, WHITE);
    
    
    pinMode(13, OUTPUT);

    /*for(uint16_t k = 0; k <= 300; k ++){
      tft.vertScroll(0, 300, k);
      delay(10);
    }
    delay(1000);
    for(uint16_t k = 300; k >= 0; k -= 1){
      tft.vertScroll(0, 300, k);
      delay(10);
    }*/
  }
  
  #define MINPRESSURE 10
  #define MAXPRESSURE 1000
  
  void loop(){
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
  
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //pinMode(YM, OUTPUT);
  
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      /*
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      */
      
      if (p.y < (TS_MINY-5)) {
        Serial.println("erase");
        // press the bottom of the screen to erase 
        tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
      }
  
      p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
      p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
      //p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
      //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
   
      if (p.y < BOXSIZE){
         oldcolor = currentcolor;
  
         if (p.x < BOXSIZE){ 
           currentcolor = RED; 
           tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if (p.x < BOXSIZE * 2){
           currentcolor = YELLOW;
           tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if (p.x < BOXSIZE * 3){
           currentcolor = GREEN;     // 青草綠
           tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if (p.x < BOXSIZE*4){
           currentcolor = CYAN;      // 天空藍
           tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if (p.x < BOXSIZE*5){
           currentcolor = BLUE;
           tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
         } 
         else if (p.x < BOXSIZE * 6){
           currentcolor = MAGENTA;   // 紫
           tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
         }
         else if (p.x < BOXSIZE * 7){
           currentcolor = WHITE;
           tft.drawRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, BLACK);
         }
         else if (p.x < BOXSIZE*8){
           currentcolor = BLACK;
           tft.drawRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, WHITE);
         }
         else if (p.x > BOXSIZE * 14  &&  p.x < BOXSIZE * 15){
           currentcolor = CUSTOM;
           tft.drawRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, WHITE);
           //delay(100);
           //tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);
         }
         else if (p.x > BOXSIZE * 15){
           tft.drawRect(BOXSIZE * 15, 0, BOXSIZE, BOXSIZE, WHITE);
           delay(100);
           tft.fillRect(BOXSIZE * 15, 0, BOXSIZE, BOXSIZE, RED);
           tft.fillRect(0, 40, 320, 440, currentcolor);
         }
  
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
        for(int i = 0; i <= 100; i ++){  // 換顏色
          tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);
          delay(1);
        }
        tft.fillRect(PENRADIUS * 15 + 170, 3, 3, BOXSIZE - 6, WHITE);

        if(p.x > 150  &&  p.x < 280){
          PENRADIUS = (p.x - 170) / 15;
          //tft.fillRect(p.x, BOXSIZE + 3, 3, BOXSIZE - 6, WHITE);
          if(prev_PENRADIUS != PENRADIUS){
            tft.fillRect(160, 0, 120, BOXSIZE, BLACK);
            for(int i = 0; i <= 100; i ++){
              tft.fillCircle(i + 170, BOXSIZE * 0.5, i / 15, currentcolor);
            }
            tft.fillRect(PENRADIUS * 15 + 170, 3, 3, BOXSIZE - 6, WHITE);
            //delay(3);
            prev_PENRADIUS = PENRADIUS;
          }
        }
      }
      
      else if(p.y > BOXSIZE  &&  p.y < BOXSIZE * 2){
        oldcolor = currentcolor;
        if(p.x > 4  &&  p.x < 91){
          CUSTOM_r = 4096 * int((constrain(p.x, 10, 84) - 10) / 5);  // - 61440
          //tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM_r);  // 右上角顏色指示器
          tft.fillRect(0, BOXSIZE, 93, BOXSIZE, BLACK);
          for(long j = 0; j < 16; j += 1){  // 第二層工具列：RGB顏色自訂
            tft.fillCircle(10 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (4096 * j));
          }
          tft.drawRect(constrain(p.x, 10, 85), 23, 4, BOXSIZE - 6, WHITE);  // 顏色深淺指示游標
        }
        else if(p.x > 96  &&  p.x < 183){
          CUSTOM_g = 128 * int((constrain(p.x, 102, 176) - 102) / 5); 
          //tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM_g);  // 右上角顏色指示器
          tft.fillRect(92, BOXSIZE, 93, BOXSIZE, BLACK);
          for(long j = 0; j < 16; j += 1){
            tft.fillCircle(102 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (128 * j));
          }
          tft.drawRect(constrain(p.x, 102, 177), 23, 4, BOXSIZE - 6, WHITE);  // 顏色深淺指示游標
        }
        else if(p.x > 188  &&  p.x < 275){
          CUSTOM_b = 2 * int((constrain(p.x, 193, 267) - 193) / 5); 
          //tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM_b);  // 右上角顏色指示器
          tft.fillRect(184, BOXSIZE, 93, BOXSIZE, BLACK);
          for(long j = 0; j < 16; j += 1){
            tft.fillCircle(194 + j * 5, BOXSIZE * 1.5, 6, 0x0000 + (2 * j));
          }
          //tft.drawRect(269, 23, 4, BOXSIZE - 6, WHITE);
          tft.drawRect(constrain(p.x, 193, 268), 23, 4, BOXSIZE - 6, WHITE);  // 顏色深淺指示游標
        }
        CUSTOM = CUSTOM_r + CUSTOM_g + CUSTOM_b;
        tft.fillRect(BOXSIZE * 14, 0, BOXSIZE, BOXSIZE, CUSTOM);  // 右上角顏色指示器
        currentcolor = CUSTOM;

        for(int i = 0; i <= 100; i ++){  // 換粗細調節顏色
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
      
      if(((p.y-PENRADIUS) > BOXSIZE * 2)  &&  ((p.y+PENRADIUS) < tft.height())){
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
      }
    }
  }
