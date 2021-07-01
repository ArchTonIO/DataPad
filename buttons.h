
#ifndef BUTTONS_H
#define BUTTONS_H

/*number of buttons connected*/
#define NUMBUTTONS 21

#define BTN_0 "BTN_0"   //POINTER
#define BTN_1 "BTN_1"   //POINT
#define BTN_2 "BTN_2"   //POLYLINE
#define BTN_3 "BTN_3"   //SRF_FROM_CRV
#define BTN_4 "BTN_4"   //EXTRUDE_CRV
#define BTN_5 "BTN_5"   //JOIN
#define BTN_6 "BTN_6"   //SLPIT
#define BTN_7 "BTN_7"   //GROUP
#define BTN_8 "BTN_8"   //MOVE
#define BTN_9 "BTN_9"   //ROTATE_3D
#define BTN_10 "BTN_10" //BOOLEAN_UNION
#define BTN_11 "BTN_11" //SOLID_FILLET
#define BTN_12 "BTN_12" //HOLE_FROM_CRV
#define BTN_13 "BTN_13" //OFFSET
#define BTN_14 "BTN_14" //DUP_EDGE
#define BTN_15 "BTN_15" //CENT_MARKER
#define BTN_16 "BTN_16" //ALIGN
#define BTN_17 "BTN_17" //UNDO
#define BTN_18 "BTN_18" //COPY
#define BTN_19 "BTN_19" //ENTER
#define BTN_20 "BTN_20" //FN

/*buttons methods*/
void buttons_init();
void buttons_update();
void buttons_print();
bool buttons_is_pressed();

#endif
