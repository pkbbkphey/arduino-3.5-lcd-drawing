# test photo #
<img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo.jpg" width="30%"> <img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo4.jpg" width="42.61%"> <br>
<img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo6.jpg" width="46.77%"><img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo2.jpg" width="26.3%"> <br>
<img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo3.jpg" width="36.5%"><img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo5.jpg" width="36.5%">

# hardware #
First of all, I used an Arduino UNO for the basic of this project, and a 3.5" tft lcd module with touch screen (driver: ILI9488) is also needed.

# function #
You can draw whatever you want on the tft screen, and then erase them. Also, it's a graphic editting system that could pick any color manually by adjusting the "RGB" percentage, and the width of the pen can also be adjusted.

# <img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/warming_icon.png" width="3%"> BEFORE STARTING... #
You should go to(FILE > EXAMPLES > MCUFRIEND_kbv > diagnose_Touchpins) to check out the pins of your touch screen, and you will know how to 
change the code from line 40 to 43, just like the code below.

> #define YP A2  // default <br>
  #define XM A3 <br>
  #define YM 8 <br>
  #define XP 9 <br>

***
