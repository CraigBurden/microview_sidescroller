#include <Adafruit_SSD1306.h>
#include <stdint.h>

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

uint8_t oled_display_buffer[OLED_PIXEL_COUNT / 8] = {0};

uint8_t get_pixel_value(uint8_t* display_buffer, OLED_BUFFER_TYPE index);
uint8_t set_pixel_value(uint8_t* display_buffer, OLED_BUFFER_TYPE index, uint8_t value);

void setup() {
//    uView.begin();              // start MicroView
//    uView.clear(PAGE);          // clear page
//    uView.print("Hello, World!");   // display string
//    uView.display();
}

void loop() {
  for(OLED_BUFFER_TYPE loop_index = 0; loop_index < (OLED_PIXEL_COUNT - 1); loop_index++)
  {
//    uView.pixel(OLED_PIXEL_TO_X_INDEX(loop_index), OLED_PIXEL_TO_Y_INDEX(loop_index), get_pixel_value(oled_display_buffer, loop_index), 0);
//    uView.display();
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
