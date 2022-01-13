# test photo #
<img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo.jpg" width="30%"> <img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo4.jpg" width="42.61%"> <br>
<img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo6.jpg" width="46.77%"><img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo2.jpg" width="26.3%"> <br>
<img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo3.jpg" width="36.5%"><img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/test_photo5.jpg" width="36.5%">

# hardware #
First of all, I used an Arduino UNO for the basic of this project, and a 3.5" tft lcd module with touch screen (driver: ILI9488) is also needed.

需要一塊 Arduino UNO 開發板，還有 3.5 吋的 tft lcd 觸控螢幕 (ILI9488驅動器) 直插到開發板上，最好再加一隻觸控筆。
# function #
You can draw whatever you want on the tft screen, and then erase them. Also, it's a graphic editting system that could pick any color manually by adjusting the "RGB" percentage, and the width of the pen can also be adjusted.

可以在螢幕上任意塗鴉，也有橡皮擦的功能，除了有幾個基本色彩，還可以變更背景顏色與自定義色彩，藉由調動螢幕上的 RGB 調節器，可以混出自己想要的顏色，同時，也可以自行調整畫筆的粗細。
# <img src="https://github.com/pkbbkphey/arduino-3.5-lcd-drawing/blob/main/test_photo/warming_icon.png" width="3%"> BEFORE STARTING... #
You should go to(FILE > EXAMPLES > MCUFRIEND_kbv > diagnose_Touchpins) to check out the pins of your touch screen, and you will know how to 
change the code from line 40 to 43, just like the code below.

必須先到 (檔案 > 範例 > MCUFRIEND_kbv > diagnose_Touchpins) 來確認觸控螢幕的腳位序號是否正確，它會提示你程式碼裡面的第 40~43 行應該改成什麼，也就是

> #define YP A2  // default <br>
  #define XM A3  // 默認值 <br>
  #define YM 8 <br>
  #define XP 9 <br>

這幾行
***
