# hardware
First of all, I used an Arduino UNO for the basic of this project, and a 3.5" tft lcd module with touch screen (driver: ILI9488) is also needed.
# function
You can draw whatever you want on the tft screen, and then erase them. Also, it's a graphic editting system that could pick any color manually by adjusting the "RGB" percentage.
# WARNING
You should go to(FILE > EXAMPLES > MCUFRIEND_kbv > diagnose_Touchpins) to check out the pins of your touch screen, and you will know how to 
change the code from line 40 to 44, just like below.

必須先到 (檔案 > 範例 > MCUFRIEND_kbv > diagnose_Touchpins) 來確認觸控螢幕的腳位序號是否正確，它會提示你程式碼裡面的第40~43行應該改成什麼，也就是

#define YP A2  // default

#define XM A3  // 默認值

#define YM 8

#define XP 9

這幾行
# arduino-3.5-lcd-drawing
Enjoy it  :)

希望你喜歡
