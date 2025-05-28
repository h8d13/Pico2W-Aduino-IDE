#include "Adafruit_TinyUSB.h"

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_MOUSE()
};

Adafruit_USBD_HID usb_hid;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  // High speed serial for responsiveness
  Serial.begin(115200);
  
  usb_hid.setPollInterval(1);  // Faster polling
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
  
  while (!TinyUSBDevice.mounted()) {
    delay(1);
  }
  
  // Quick ready signal
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("READY");
}

void loop() {
  // Check for serial data immediately
  if (Serial.available()) {
    char command = Serial.read();
    
    // Any character triggers a click for max responsiveness
    if (usb_hid.ready()) {
      leftClick();
      Serial.println("OK");
    }
    
    // Clear any remaining data
    while (Serial.available()) {
      Serial.read();
    }
  }
}

void leftClick() {
  // Fast click action
  usb_hid.mouseReport(0, MOUSE_BUTTON_LEFT, 0, 0, 0, 0);
  delay(20);  // Shorter click duration for speed
  usb_hid.mouseReport(0, 0, 0, 0, 0, 0);
  
  // Quick LED flash
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}
