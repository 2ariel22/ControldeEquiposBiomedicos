#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Inicializar la comunicación con la pantalla OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error al inicializar la pantalla OLED"));
    for(;;);
  }

  // Limpiar el buffer de la pantalla
  display.clearDisplay();

  // Establecer el tamaño del texto
  display.setTextSize(1);

  // Establecer el color del texto
  display.setTextColor(SSD1306_WHITE);

  // Imprimir "Hola Mundo"
  display.setCursor(0,0);
  display.println("Hola Mundo!");

  // Mostrar en la pantalla
  display.display();
}

void loop() {
  // Nada más se realiza en el loop
}
