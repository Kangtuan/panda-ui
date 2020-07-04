#ifndef PANDA_UI_H
#define PANDA_UI_H

#include<inttypes.h >

#define SINGLE_PIC        0x8F
#define MOST_PIC1         0x80
#define MOST_PIC2         0x8A
#define LOOP_DLY          0x81
#define LOOP_CLR          0x84
#define GIF_DLY           0x88
#define GIF_CLR           0x89
#define EJECT_PIC         0xD8
#define LOOP_ROLL         0xD9
#define LOOP_ROLL_CLR     0xDB
#define DIGIT_PIC         0x90
#define SIG_CTL_SHOW      0xA0
#define SIG_CTL_CLR       0xA1
#define VIR_CTL_SHOW      0xA2
#define VIR_CTL_CLR       0xA3
#define PROBAR            0xB0
#define RINGDIG           0xDC
#define STRING1           0xC0
#define STRING2           0xC1
#define STRING3           0xC2
#define STRING4           0xC3
#define SET_BLIGHT        0xBA
#define BLIGHT_SWITCH     0xBC
#define POWER             0x9A
#define MERGE             0x9A
#define SCREEN_CHK        0x8B
#define ONLINE_CHK        0xBE
#define VERSION_CHK       0xBF
#define G_DOT             0xDF
#define G_LINE            0xE0
#define G_HLW_CIR         0xE1
#define G_SOLID_CIR       0xE2
#define G_FRAME_CIR       0xE3
#define G_HLW_ELL         0xE4
#define G_SOLID_ELL       0xE5
#define G_FRAME_ELL       0xE6
#define G_HLW_REC         0xE7
#define G_SOLID_REC       0xE8
#define G_FRAME_REC       0xE9
#define G_HLW_ROUND_REC   0xEA
#define G_SOLID_ROUND_REC 0xEB
#define G_FRAME_ROUND_REC 0xEC
#define G_HLW_TRI         0xED
#define G_SOLID_TRI       0xEE
#define G_FRAME_TRI       0xEF
#define G_CYLINDER        0xF4
#define G_FORMWINDOW      0xF6

class PANDA_UI{
    public:
        //PANDA_UI(SoftwareSerial &serial);
        PANDA_UI();
        ~PANDA_UI();
        uint8_t ShowPicture(uint8_t inst, uint8_t index, uint8_t *instArg, uint8_t size);
        uint8_t ShowControl(uint8_t inst, uint8_t index);
        uint8_t ClearControl(uint8_t inst, uint8_t index);
        uint8_t CreateProgressBar(uint8_t inst, uint8_t index);
        uint8_t CreateRingDiagram(uint8_t inst, uint8_t index);
        uint8_t ShowString(uint8_t inst, uint8_t, uint8_t *instArg, uint8_t size);
        uint8_t SetBacklight(uint8_t level);
        uint8_t OpenBacklight(uint8_t mode);
        uint8_t PowerOn(void);
        uint8_t Merge(uint8_t index);
        uint8_t ScreenCheck(void);
        uint8_t OnlineCheck(void);
        uint8_t VersionCheck(void);
        uint8_t Geometry(uint8_t inst, uint8_t index);
        uint8_t ListenEvent();
};

#endif
