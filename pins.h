#ifndef PINS_H
#define PINS_H

   /*Joystick pins*/
   #define JOYSTICK_X_AXIS_GPIO_PIN 27
   #define JOYSTICK_Y_AXIS_GPIO_PIN 28
   #define JOYSTICK_X_AXIS_ADC_PIN  1
   #define JOYSTICK_Y_AXIS_ADC_PIN  2

   /*Leds pin*/
   #define STRIP_PIN 0 

   /*Oled pins*/
   #define OLED_SDA_PIN 4
   #define OLED_SCL_PIN 5
   /*-fixed for now, even if you change them here, they will not really change*/

   /*Buttons pins*/
   #define BTN_0_PIN 1 //POINTER_BTN_PIN 
   #define BTN_1_PIN 2 //POINT_BTN_PIN  
   #define BTN_2_PIN 3 //POLYLINE_BTN_PIN   
   #define BTN_3_PIN 6 //SRF_FROM_CRV_BTN_PIN   
   #define BTN_4_PIN 7 //EXTRUDE_CURVES_BTN_PIN   
   #define BTN_5_PIN 8 //JOIN_BTN_PIN  
   #define BTN_6_PIN 9 //SPLIT_BTN_PIN  
   #define BTN_7_PIN 10 //GROUP_BTN_PIN  
   #define BTN_8_PIN 11 //MOVE_BTN_PIN  
   #define BTN_9_PIN 12 //ROTATE_3D_BTN_PIN   
   #define BTN_10_PIN 13 //BOOLEAN_UNION_BTN_PIN  
   #define BTN_11_PIN 14 //SOLID_FILLET_BTN_PIN  
   #define BTN_12_PIN 15 //HOLE_FROM_CRV_BTN_PIN  
   #define BTN_13_PIN 16 //OFFSET_BTN_PIN  
   #define BTN_14_PIN 17 //DUP_EDGE_BTN_PIN  
   #define BTN_15_PIN 18 //CENT_MARKER_BTN_PIN   
   #define BTN_16_PIN 19 //ALIGN_BTN_PIN  
   #define BTN_17_PIN 20 //UNDO_BTN_PIN  
   #define BTN_18_PIN 21 //COPY_BTN_PIN 
   #define BTN_19_PIN 22 //ENTER_BTN_PIN
   #define BTN_20_PIN 26 //SECOND_FN_BTN_PIN

#endif