#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include <SPI.h>

#define OLED_PIXEL_WIDTH  64
#define OLED_PIXEL_HEIGHT 48
#define OLED_PIXEL_WIDTH_OFFSET 32

#define OLED_DC     8
#define OLED_CS     10
#define OLED_RESET  7

#define OLED_PIXEL_COUNT              (OLED_PIXEL_WIDTH * OLED_PIXEL_HEIGHT)
#define OLED_PIXEL_TO_X_INDEX(index)  (index % OLED_PIXEL_WIDTH)
#define OLED_PIXEL_TO_Y_INDEX(index)  (index / OLED_PIXEL_WIDTH)

#if (OLED_PIXEL_COUNT <= UINT_LEAST8_MAX)
  #define OLED_BUFFER_INDEX_TYPE uint8_t
#elif (OLED_PIXEL_COUNT <= UINT_LEAST16_MAX)
  #define OLED_BUFFER_INDEX_TYPE uint16_t
#elif (OLED_PIXEL_COUNT <= UINT_LEAST32_MAX)
  #define OLED_BUFFER_INDEX_TYPE uint32_t
#endif

#define SPRITE_WIDTH   16
#define SPRITE_HEIGHT   16
//static const uint8_t PROGMEM sprite_bmp[] =
//{
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000,
//    0b00000000, 0b00000000
//};

static const uint8_t PROGMEM man_bmp[] =
{
    0b00000001, 0b10000000,
    0b00000011, 0b11000000,
    0b00000111, 0b11100000,
    0b00000111, 0b11100000,
    0b00000011, 0b11000000,
    0b00000001, 0b10000000,
    0b00111111, 0b11111000,
    0b00000001, 0b00000000,
    0b00000001, 0b00000000,
    0b00000001, 0b00000000,
    0b00000001, 0b00000000,
    0b00000010, 0b10000000,
    0b00000100, 0b01000000,
    0b00000100, 0b01000000,
    0b00001000, 0b00100000,
    0b00111000, 0b00111000
};

static const uint8_t PROGMEM tortoise_bmp[] =
{
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b000000000,
    0b00110001, 0b111000000,
    0b01011011, 0b111100100,
    0b01111111, 0b111111100,
    0b00011111, 0b111111000,
    0b01100011, 0b111110000,
    0b00000011, 0b000110000
};

Adafruit_SSD1306 display(OLED_PIXEL_WIDTH + OLED_PIXEL_WIDTH_OFFSET, OLED_PIXEL_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup()
{
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }

  display.clearDisplay();

  display.drawBitmap(OLED_PIXEL_WIDTH_OFFSET, OLED_PIXEL_HEIGHT - SPRITE_HEIGHT - 1, man_bmp, SPRITE_WIDTH, SPRITE_HEIGHT, 1);

  display.drawBitmap(OLED_PIXEL_WIDTH_OFFSET + 30, OLED_PIXEL_HEIGHT - SPRITE_HEIGHT - 1, tortoise_bmp, SPRITE_WIDTH, SPRITE_HEIGHT, 1);

  display.drawLine(OLED_PIXEL_WIDTH_OFFSET, OLED_PIXEL_HEIGHT - 1, OLED_PIXEL_WIDTH - 1 + OLED_PIXEL_WIDTH_OFFSET, OLED_PIXEL_HEIGHT - 1, WHITE); // Floor
  
  display.display();
}

void loop()
{

}
