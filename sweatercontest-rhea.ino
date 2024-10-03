#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

// Define shirt colors
uint32_t shirtColors[] = {TFT_YELLOW, TFT_RED, TFT_ORANGE};
int currentColorIndex = 0;
unsigned long previousMillis = 0; // Stores the last time the color was updated
const long interval = 1000; // Interval for color change (1 second)

void setup() {
  tft.init();
  tft.setRotation(1);   // 1 = landscape, 2 = portrait
  tft.fillScreen(TFT_BLACK); // Clear the screen
  drawCurtains();
    // Draw the leaf to ensure it is always on top
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check if it's time to change the color
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time
    currentColorIndex = (currentColorIndex + 1) % 3; // Cycle through colors
  }

  // Draw the curtains

  
  // Draw the person with the current shirt color
  drawPerson(tft.width() / 2, tft.height() / 2, shirtColors[currentColorIndex]);


}

// Function to draw curtains on the edges of the screen
void drawCurtains() {
  uint32_t curtainColor = TFT_RED; // Curtain color
  int16_t curtainWidth = 40; // Width of the curtains
  int16_t screenHeight = tft.height(); // Get the height of the screen

  // Draw left curtain
  tft.fillRect(0, 0, curtainWidth, screenHeight, curtainColor);
  // Draw text on the left curtain
  tft.setTextColor(TFT_WHITE); // Set text color to white
  tft.setTextSize(2); // Set text size
  tft.setCursor(5, 60); // Position the cursor for "Sweater"
  tft.print("Sweater");
  // Draw right curtain
  tft.fillRect(tft.width() - curtainWidth, 0, curtainWidth, screenHeight, curtainColor);
  // Draw text on the right curtain
  tft.setCursor(tft.width() - 5, 60); // Position the cursor for "Contest"
  tft.print("Contest");


}

// Function to draw a stick figure
void drawPerson(int16_t x, int16_t y, uint32_t shirtColor) {
  uint32_t skinColor = TFT_PINK; // Head color
  uint32_t pantsColor = TFT_BLUE; // Pants color
  uint32_t leafColor = TFT_BROWN; // Light brown for the leaf
  uint32_t stemColor = TFT_DARKGREEN; // Dark brown for the stem

  // Adjusted Y position for centering
  int16_t headY = y - 45; // Position head above the body
  int16_t bodyY = y - 30; // Center body vertically
  int16_t bodyHeight = 60; // Reduced body height
  int16_t pantY = bodyY + bodyHeight; // Position for pants

  int16_t leafX = x; // X position for the leaf
  int16_t leafY = y; // Y position for the leaf (middle of the shirt)
  int16_t leafRx = 10; // X radius of the leaf (smaller for rotation)
  int16_t leafRy = 5;// Y radius of the leaf (larger for rotation)

  // Draw head (circle)
  tft.fillCircle(x, headY, 15, skinColor); // Head at (x, headY) with radius 15

  // Draw body (rectangle)
  tft.fillRect(x - 20, bodyY, 40, bodyHeight, shirtColor); // Body centered at (x, bodyY)
    // Leaf positioning

  tft.fillEllipse(leafX, leafY, leafRy, leafRx, leafColor); // Rotated ellipse

  // Draw stem (line)
  tft.drawLine(leafX, leafY + leafRx, leafX, leafY + leafRx + 10, stemColor); // Stem below the leaf
  // Draw arms (rectangles)
  uint32_t armColor = shirtColor; // Use the shirt color for arms
  tft.fillRect(x - 60, bodyY, 40, 15, armColor); // Left arm
  tft.fillRect(x + 20, bodyY, 40, 15, armColor); // Right arm
  

  // Draw pants (two rectangles)
  int16_t pantWidth = 15; // Width of each pant leg
  tft.fillRect(x - 20, pantY, pantWidth, 30, pantsColor); // Left pant
  tft.fillRect(x + 5, pantY, pantWidth, 30, pantsColor); // Right pant
}




