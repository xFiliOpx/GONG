#include <SPI.h>
#include <Adafruit_PCD8544.h>

// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

int x = 25, y = 25, sx = 1, sy = 1, c;
unsigned short ky, kx;
unsigned long long int czas;

Adafruit_PCD8544 lcd = Adafruit_PCD8544(7, 6, 5, 4, 3);

void drawBall(){
  lcd.drawPixel(x, y, BLACK);
  lcd.drawPixel(x+1, y, BLACK);
  lcd.drawPixel(x, y+1, BLACK);
  lcd.drawPixel(x-1, y, BLACK);
  lcd.drawPixel(x, y-1, BLACK);
}

void ballPosition(){
  if (x <= 1 || x >= lcd.width() -2){
      sx *= -1;
  }
  if (y <= 1 || y >= lcd.height() -2){
    sy *= -1;
  }
  y += sy;
  x += sx;
}

void setup() {
  lcd.begin();
  lcd.setContrast(80);
}

void loop() {

  kx = analogRead(A2);
  kx = map(kx, 0, 1024, 30, 100);

  

  while (millis() - czas >= 1000/60){
    czas = millis();
    lcd.clearDisplay();

    ky = analogRead(A1);
    ky = map(ky, 0, 1024, 4, lcd.height()+6);

    ballPosition();
  }

  lcd.drawLine(kx, ky+4, kx, ky-4, BLACK);
  lcd.drawLine(lcd.width()-1, 0, lcd.width()-1, lcd.height()-1, BLACK);

  drawBall();

  lcd.display();
}
