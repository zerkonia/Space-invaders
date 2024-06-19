
#define LASERW           2
#define LASERH           9
#define ELASERW          2
#define ELASERH          2
#define SPWEPONW         10
#define SPWEPONH         84
#define BOSSSPWEPONW     10
#define BOSSSPWEPONH     78
#define PLAYERW          16
#define PLAYERH          16
#define ENEMYW           14
#define ENEMYH           14
#define BOSSW            17
#define BOSSH            15
#define BOSSEYEW         13
#define BOSSEYEH         9
#define STARW            2
#define STARH            2
#define ENEMYFIREW       2
#define ENEMYFIREH       2
#define SMALLEXPLOSIONW  14
#define SMALLEXPLOSIONH  14
#define BARPOINTW        8
#define BARPOINTH        4
#define Full             1
#define Empty            0
#define pressed          0x01
#define not_pressed      0x00
#define alive            1
#define dead             0
#define busy             1
#define ready            0
#define LCDW             127
#define LCDH             127
#define Fire             0x02
#define vibration_on     0x20
#define vibration_off    0x00
#define laser_sw           (*((volatile unsigned long *)0x40024004))
#define special_wepon_sw   (*((volatile unsigned long *)0x40024008))
#define sp_wepon_ready     (*((volatile unsigned long *)0x40025020))
#define sp_wepon_charging  (*((volatile unsigned long *)0x40025008))
#define vib_motor          (*((volatile unsigned long *)0x40024080))
#define yes               1
#define no                0
#define Active            1
#define Inactive          0
#define SDC_CS_PB0        0
#define SDC_CS_PD7        1
#define SDC_CS           (*((volatile unsigned long *)0x40007200))
#define SDC_CS_LOW       0           // CS controlled by software
#define SDC_CS_HIGH      0x80
// de-asserts the CS pin to the card
#define CS_HIGH()  SDC_CS = SDC_CS_HIGH;
// asserts the CS pin to the card
#define CS_LOW()   SDC_CS = SDC_CS_LOW;    
#define DC                (*((volatile unsigned long *)0x40004100))
#define DC_COMMAND        0
#define DC_DATA           0x40
#define RESET             (*((volatile unsigned long *)0x40004200))
#define RESET_LOW         0
#define RESET_HIGH        0x80
#define TFT_CS            (*((volatile unsigned long *)0x40004020))
#define TFT_CS_LOW        0           // CS controlled by software PA3
#define TFT_CS_HIGH       0x08
#define Accelerometer_disable      (*((volatile unsigned long *)0x40024040))
#define No                0x00
#define Yes               0x10
#define FILETESTSIZE 10000
#define MAXBLOCKS 10000
