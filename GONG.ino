#include <SPI.h>
#include <Adafruit_PCD8544.h>

// pin D7 - Serial clock out (SCLK)
// pin D6 - Serial data out (DIN)
// pin D5 - Data/Command select (D/C)
// pin D4 - LCD chip select (CS)
// pin D3 - LCD reset (RST)
// pin A1 - y pot
// pin A2 - x pot

int pts = 0;
int x = 25, y = 25, sx = 1, sy = 1;
unsigned short p1x, p1y, p2x, p2y;
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
  if (x == p1x && (p1y - 4 < y && y < p1y + 4 )){
    sx *= -1;
    pts += 1;
  }
  else if (x >= lcd.width() -2) {
    sx *= -1;
  }
  if (y <= 1 || y >= lcd.height() -2){
    sy *= -1;
  }
  y += sy;
  x += sx;
}

void end(){
  lcd.clearDisplay();
  lcd.print("wynik:");
  lcd.print(pts);
}

void setup() {
  lcd.begin();
  lcd.setContrast(80);
}

void loop() {

  p1x = analogRead(A2);
  p1x = map(p1x, 0, 1024, 0, lcd.width()/2);

  

  while (millis() - czas >= 1000/30){
    czas = millis();
    lcd.clearDisplay();

    p1y = analogRead(A1);
    p1y = map(p1y, 0, 1024, 4, lcd.height()+6);

    ballPosition();
  }

  lcd.drawLine(p1x, p1y+4, p1x, p1y-4, BLACK);
  lcd.drawLine(lcd.width()-1, 0, lcd.width()-1, lcd.height()-1, BLACK);

  drawBall();

  if (x < 0){
    end();
  }

  lcd.display();
}
