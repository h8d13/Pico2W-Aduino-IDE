#include "Adafruit_TinyUSB.h"

// HID report descriptor using TinyUSB's built-in template
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_MOUSE()
};

// USB HID object
Adafruit_USBD_HID usb_hid;

void setup() {
  // Initialize built-in LED for status
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Set up HID
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
  
  // Wait for USB to be ready
  while (!TinyUSBDevice.mounted()) {
    delay(1);
  }
  
  // Blink LED to show we're ready
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

void loop() {
  // Check if HID is ready
  if (usb_hid.ready()) {
    // Perform left click
    leftClick();
    
    // Wait 2 seconds between clicks
    delay(2000);
  }
}

void leftClick() {
  // Press left mouse button (6 parameters: report_id, buttons, x, y, scroll, pan)
  usb_hid.mouseReport(0, MOUSE_BUTTON_LEFT, 0, 0, 0, 0);
  delay(50);  // Hold for 50ms
  
  // Release left mouse button
  usb_hid.mouseReport(0, 0, 0, 0, 0, 0);
  
  // Blink LED to show click happened
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}
