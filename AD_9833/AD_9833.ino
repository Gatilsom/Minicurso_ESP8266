
#include <MD_AD9833.h>
#include <SPI.h>

// Pins for SPI comm with the AD9833 IC
#define DATA  D2	///< SPI Data pin number
#define CLK   D1	///< SPI Clock pin number
#define FSYNC D4	///< SPI Load pin number (FSYNC in AD9833 usage)

// MD_AD9833	AD(FSYNC);  // Hardware SPI
MD_AD9833	AD(DATA, CLK, FSYNC); // Arbitrary SPI pins

void setup(void)
{
  pinMode(A0, OUTPUT);
  Serial.begin(115200);
        while (!Serial) delay(100);
	AD.begin();

    AD.setMode(MD_AD9833::MODE_TRIANGLE);
  delay(2000);

AD.setFrequency(MD_AD9833::CHAN_0 ,10000);
for(int i=0; i<5 ; i++){
Serial.print("freq_a: ");
Serial.println(AD.getActiveFrequency());
Serial.print("teta_a: ");
Serial.println(AD.getActivePhase());
Serial.print("freq: ");
Serial.println(AD.getFrequency(MD_AD9833::CHAN_0 ));
Serial.print("teta: ");
Serial.println(AD.getPhase(MD_AD9833::CHAN_0 ));
Serial.println("--------------------");

delay(1000);
}
}

void loop(void)
{
  Serial.println(analogRead(A0));
delay(1);
}
