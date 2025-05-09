#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h>

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         7

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Cube parameters
float angleX = 0;
float angleY = 0;
float size = 50; // Size of the cube
float centerX = 120; // Center of the cube on the X-axis
float centerY = 140; // Center of the cube on the Y-axis

void setup() {
  tft.init(240, 280);  // Initialize display with correct resolution
  tft.setRotation(2);  // Adjust rotation if needed
  tft.fillScreen(ST77XX_BLACK);  // Clear screen with white background
}

void loop() {
  tft.fillScreen(ST77XX_BLACK); // Clear the screen

  drawSpinningCube(centerX, centerY, size, angleX, angleY);

  angleX += 0.05; // Increment angle for rotation
  angleY += 0.03; // Increment angle for rotation

  delay(50); // Control the speed of the spinning
}

void drawSpinningCube(float cx, float cy, float s, float ax, float ay) {
  // Define the cube vertices
  float vertices[8][3] = {
    {-s, -s, -s}, {s, -s, -s}, {s, s, -s}, {-s, s, -s},
    {-s, -s, s}, {s, -s, s}, {s, s, s}, {-s, s, s}
  };

  // Rotate the cube around the X and Y axes
  for (int i = 0; i < 8; i++) {
    float x = vertices[i][0];
    float y = vertices[i][1];
    float z = vertices[i][2];

    // Rotate around X-axis
    float tempY = y * cos(ax) - z * sin(ax);
    float tempZ = y * sin(ax) + z * cos(ax);
    y = tempY;
    z = tempZ;

    // Rotate around Y-axis
    float tempX = x * cos(ay) + z * sin(ay);
    z = -x * sin(ay) + z * cos(ay);
    x = tempX;

    // Project the 3D coordinates to 2D
    int projX = cx + (x * 100) / (z + 200); // Scale based on depth
    int projY = cy + (y * 100) / (z + 200); // Scale based on depth

    // Store the projected vertices
    vertices[i][0] = projX;
    vertices[i][1] = projY;
  }

  // Draw the edges of the cube
  for (int i = 0; i < 4; i++) {
    tft.drawLine(vertices[i][0], vertices[i][1], vertices[(i + 1) % 4][0], vertices[(i + 1) % 4][1], ST77XX_WHITE); // Front face
    tft.drawLine(vertices[i + 4][0], vertices[i + 4][1], vertices[(i + 1) % 4 + 4][0], vertices[(i + 1) % 4 + 4][1], ST77XX_WHITE); // Back face
    tft.drawLine(vertices[i][0], vertices[i][1], vertices[i + 4][0], vertices[i + 4][1], ST77XX_WHITE); // Connecting edges
  }
}
