#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include <SPI.h>

#define OLED_PIXEL_WIDTH  64
#define OLED_PIXEL_HEIGHT 48
#define OLED_PIXEL_COUNT  (OLED_PIXEL_WIDTH * OLED_PIXEL_HEIGHT)

#define OLED_PIXEL_TO_X_INDEX(index)  (index % OLED_PIXEL_WIDTH)
#define OLED_PIXEL_TO_Y_INDEX(index)  (index / OLED_PIXEL_WIDTH)

#if (OLED_PIXEL_COUNT <= UINT_LEAST8_MAX)
  #define OLED_BUFFER_TYPE uint8_t
#elif (OLED_PIXEL_COUNT <= UINT_LEAST16_MAX)
  #define OLED_BUFFER_TYPE uint16_t
#elif (OLED_PIXEL_COUNT <= UINT_LEAST32_MAX)
  #define OLED_BUFFER_TYPE uint32_t
#endif

#define OLED_DC     8
#define OLED_CS     10
#define OLED_RESET  7
Adafruit_SSD1306 display(OLED_PIXEL_WIDTH * 2, OLED_PIXEL_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);

uint8_t oled_display_buffer[OLED_PIXEL_COUNT / 8] = {0};

uint8_t get_pixel_value(uint8_t* display_buffer, OLED_BUFFER_TYPE index);
uint8_t set_pixel_value(uint8_t* display_buffer, OLED_BUFFER_TYPE index, uint8_t value);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  for(OLED_BUFFER_TYPE loop_index = 0; loop_index < (OLED_PIXEL_COUNT - 1); loop_index++)
  {
    display.drawPixel(OLED_PIXEL_TO_X_INDEX(loop_index), OLED_PIXEL_TO_Y_INDEX(loop_index), get_pixel_value(oled_display_buffer, loop_index));
    display.display();
    set_pixel_value(oled_display_buffer, loop_index, 2);
  }
  
}

uint8_t get_pixel_value(uint8_t* display_buffer, OLED_BUFFER_TYPE index)
{
  return (display_buffer[index / 8] & (0x1 << (index % 8))) >> (index % 8);
}

uint8_t set_pixel_value(uint8_t* display_buffer, OLED_BUFFER_TYPE index, uint8_t value)
{
  if(value == 0)
  {
    display_buffer[index / 8] &= ~(0x1 << (index % 8));
  }
  else if (value == 1)
  {
    display_buffer[index / 8] |= (0x1 << (index % 8));
  }
  else if (value == 2)
  {
    display_buffer[index / 8] ^= (0x1 << (index % 8));
  }
}
