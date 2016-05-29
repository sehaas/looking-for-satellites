#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>

const char SPACE = ' ';
const char EAST = 'E';
const char WEST = 'W';
const char NORTH = 'N';
const char SOUTH = 'S';

LiquidCrystal_I2C lcd(0x27,16,2) ;
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("  looking for   "));
  lcd.setCursor(0,1);
  lcd.print(F("  satellites... "));
}

/* prints in format qDD MM.MMM */
void printCoord(const int deg, const double min, const char quadrant) {
  lcd.print(quadrant);
  lcd.print(deg);
  lcd.print(SPACE);
  if (min < 10.0d) {
    lcd.print(0);
  }
  lcd.print(min, 3);
}

void loop() {
  while (Serial.available()) {
    gps.encode(Serial.read());
  }
  if (gps.location.isUpdated()) {
    int latDegrees = gps.location.rawLat().deg;
    unsigned long billionthsLat = gps.location.rawLat().billionths;
    double latMinutes = ((billionthsLat / 1000) * 6.0f) / 100000L;    
    int lngDegrees = gps.location.rawLng().deg;
    unsigned long billionthsLng = gps.location.rawLng().billionths;
    double lngMinutes = ((billionthsLng / 1000) * 6.0f) / 100000L;    

    /* line 1 */
    lcd.setCursor(0,0);
    printCoord(latDegrees, latMinutes, gps.location.rawLat().negative ? SOUTH : NORTH);
    
    lcd.print(SPACE);
    double m = 1000.0d;
    double meters = gps.altitude.meters();
    while (meters < m) {
      lcd.print(SPACE);
      m /= 10.0d;
    }
    lcd.print(meters, 0);
    lcd.print(F("m"));

    /* line 2 */
    lcd.setCursor(0,1);
    printCoord(lngDegrees, lngMinutes, gps.location.rawLng().negative ? WEST : EAST);

    lcd.print(SPACE);
    unsigned int sats = gps.satellites.value();
    if (sats < 10) {
      lcd.print(SPACE);
    }
    lcd.print(sats);
    lcd.print(F("sat"));
  }
}
