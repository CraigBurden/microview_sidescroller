#include <Adafruit_SSD1306.h>
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


Adafruit_SSD1306 display(OLED_PIXEL_WIDTH + OLED_PIXEL_WIDTH_OFFSET, OLED_PIXEL_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);

uint8_t oled_display_buffer[(OLED_PIXEL_COUNT / 8) + 1] = {0};

uint8_t get_pixel_value_by_coord(uint8_t* display_buffer, uint8_t x, uint8_t y);
uint8_t get_pixel_value_by_index(uint8_t* display_buffer, OLED_BUFFER_INDEX_TYPE index);
uint8_t set_pixel_value_by_coord(uint8_t* display_buffer, uint8_t x, uint8_t y, uint8_t value);
uint8_t set_pixel_value_by_index(uint8_t* display_buffer, OLED_BUFFER_INDEX_TYPE index, uint8_t value);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();

  set_pixel_value_by_coord(oled_display_buffer, 0, 0, 1);
  set_pixel_value_by_coord(oled_display_buffer, 0, 47, 1);
  set_pixel_value_by_coord(oled_display_buffer, 63, 0, 1);
  set_pixel_value_by_coord(oled_display_buffer, 63, 47, 1);
  display.display();
}

void loop() {
  for(OLED_BUFFER_INDEX_TYPE loop_index = 0; loop_index < OLED_PIXEL_COUNT; loop_index++)
  {
    display.drawPixel(OLED_PIXEL_TO_X_INDEX(loop_index) + OLED_PIXEL_WIDTH_OFFSET, OLED_PIXEL_TO_Y_INDEX(loop_index), get_pixel_value_by_index(oled_display_buffer, loop_index));
  }
  display.display();
  
}

uint8_t get_pixel_value_by_coord(uint8_t* display_buffer, uint8_t x, uint8_t y)
{
  OLED_BUFFER_INDEX_TYPE index = x + (y * OLED_PIXEL_WIDTH);
  
  return get_pixel_value_by_index(display_buffer, index);
}

uint8_t get_pixel_value_by_index(uint8_t* display_buffer, OLED_BUFFER_INDEX_TYPE index)
{ 
  return (display_buffer[index / 8] & (0x1 << (index % 8))) >> (index % 8);
}

uint8_t set_pixel_value_by_coord(uint8_t* display_buffer, uint8_t x, uint8_t y, uint8_t value)
{
  OLED_BUFFER_INDEX_TYPE index = x + (y * OLED_PIXEL_WIDTH);
  
  set_pixel_value_by_index(display_buffer, index, value);
}

uint8_t set_pixel_value_by_index(uint8_t* display_buffer, OLED_BUFFER_INDEX_TYPE index, uint8_t value)
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
