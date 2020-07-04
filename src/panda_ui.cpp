//#include <SoftwareSerial.h>
#include "panda_ui.h"
#include <iostream>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

#define CMDLENGHT(inst)  ((sizeof(inst))/(sizeof(inst[0])))
#define CMDBASELEN       (0x09)
#define CMDMAXLEN        ((0x40) + (CMDBASELEN))

static const uint8_t startCode = 0xAA;
static const uint8_t endCode[] = {0xE4, 0x1B, 0x11, 0xEE};

//static SoftwareSerial s_serial;

static unsigned short MakeCRC(uint8_t *u8Data, unsigned int u32DataLen)
{
    unsigned short wCRCin = 0x0000;
    unsigned short wCCITTPoly = 0x1021;
    unsigned char bChar = 0;
    int i;

	for (i = 0; i < u32DataLen; i++)
		printf("%02x ", u8Data[i]);
    while(u32DataLen--){
        bChar = *(u8Data++);
        wCRCin ^= (bChar << 8);

        for (i = 0; i < 8; i++){
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCCITTPoly;
            else
                wCRCin <<= 1;
        }
    }

    return wCRCin;
}

static void FillInst(uint8_t *cmd, uint8_t inst, uint8_t index,
                       const uint8_t *arg, uint8_t size)
{
	uint8_t i;
	uint16_t chkSun;
	
	
	cmd[0] = startCode;
	cmd[1] = inst;
	if (index >= 0){
		cmd[2] = index;
		if (NULL == arg){
			for(i = 0; i < 9; i++)
				printf("%02x ", cmd[i]);
			putchar('\n');
			chkSun = MakeCRC(cmd + 1, 2);
			cmd[3] = (chkSun >> 8) & 0xFF;
			cmd[4] = chkSun & 0xFF;
			for (i = 0; i < 4; i++)
				cmd[5 + i] = endCode[i];
		}
		else if (size > 0 && size < (CMDMAXLEN - CMDBASELEN)){
			for (i = 0; i < size; i++)
				cmd[3 + i] = arg[i];
			chkSun = MakeCRC(cmd + 1, 2 + size);
			cmd[3 + size] = (chkSun >> 8) & 0xFF;
			cmd[4 + size] = chkSun & 0xFF;
			for (i = 0; i < 4; i++)
				cmd[5 + size + i] = endCode[i];
		}
	}else{
		if (NULL == arg){
			chkSun = MakeCRC(cmd + 1, 1);
			cmd[2] = (chkSun >> 8) & 0xFF;
			cmd[3] = chkSun & 0xFF;
			for (i = 0; i < 4; i++)
				cmd[4 + i] = endCode[i];
		}
		else if (size > 0 && size < (CMDMAXLEN - CMDBASELEN)){
			for (i = 0; i < size; i++)
				cmd[2 + i] = arg[i];
			
			chkSun = MakeCRC(cmd + 1, 1 + size);
			cmd[2 + size] = (chkSun >> 8) & 0xFF;
			cmd[3 + size] = chkSun & 0xFF;
			for (i = 0; i < 4; i++)
				cmd[4 + size + i] = endCode[i];
		}
	}
}

static int SendInst(uint8_t *inst, int instLen)
{
    int i;
    for (i = 0; i < instLen; i++)
        printf("%02x ", inst[i]);
    printf("\n");
	return 0;
}

static int HandleEvent()
{
}

PANDA_UI::PANDA_UI()
{
    //s_serial = serial;
    cout << "PANDA_UI" << endl; 
}

PANDA_UI::~PANDA_UI()
{
}

uint8_t PANDA_UI::ShowPicture(uint8_t inst, uint8_t index, uint8_t *arg, uint8_t size)
{
    if (NULL == arg){
        uint8_t cmd[CMDBASELEN] = {0};
        FillInst(cmd, inst, index, NULL, -1);
        SendInst(cmd, CMDBASELEN);
    }
    else if ( size > 0 && size < (CMDMAXLEN - CMDBASELEN)){
        uint8_t cmd[CMDMAXLEN] = {0};
        FillInst(cmd, inst, index, arg, size);
        SendInst(cmd, CMDBASELEN + size);
    }        
    else{
        return -1;
    }

    return 0;
}
uint8_t PANDA_UI::ShowControl(uint8_t inst, uint8_t index)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, inst, index, NULL, -1);
    SendInst(cmd, CMDBASELEN);
    return 0;
}
uint8_t PANDA_UI::ClearControl(uint8_t inst, uint8_t index)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, inst, index, NULL, -1);
    SendInst(cmd, CMDBASELEN);
    return 0;
}

uint8_t PANDA_UI::CreateProgressBar(uint8_t inst, uint8_t index)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, inst, index, NULL, -1);
    SendInst(cmd, CMDBASELEN);
    return 0;
}
uint8_t PANDA_UI::CreateRingDiagram(uint8_t inst, uint8_t index)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, inst, index, NULL, -1);
    SendInst(cmd, CMDBASELEN);
    return 0;
}

uint8_t PANDA_UI::ShowString(uint8_t inst, uint8_t index, uint8_t *arg, uint8_t size)
{
	uint8_t cmd[CMDMAXLEN] = {0};
    if (NULL != arg && (size > 0 && size < (CMDMAXLEN - CMDBASELEN))){
        FillInst(cmd, inst, index, arg, size);
    }
    else{
        return -1;
    }

    SendInst(cmd, CMDBASELEN + size);
    return 0;
}
uint8_t PANDA_UI::SetBacklight(uint8_t level)
{
    uint8_t arg = level;
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, SET_BLIGHT, -1, &arg, 1);
    SendInst(cmd, CMDBASELEN - 1);
    return 0;
}
uint8_t PANDA_UI::OpenBacklight(uint8_t mode)
{
    uint8_t arg = mode;
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, BLIGHT_SWITCH, -1, &arg, 1);
    SendInst(cmd, CMDBASELEN - 1);
    return 0;
}

uint8_t PANDA_UI::PowerOn(void)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, POWER, -1, NULL, -1);
    SendInst(cmd, CMDBASELEN - 1);
    return 0;
}

uint8_t PANDA_UI::Merge(uint8_t index)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, MERGE, index, NULL, -1);
    SendInst(cmd, CMDBASELEN);
    return 0;
}
uint8_t PANDA_UI::ScreenCheck(void)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, SCREEN_CHK, -1, NULL, -1);
    SendInst(cmd, CMDBASELEN - 1);
    return 0;
}

uint8_t PANDA_UI::OnlineCheck(void)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, ONLINE_CHK, -1, NULL, -1);
    SendInst(cmd, CMDBASELEN - 1);
    return 0;
}

uint8_t PANDA_UI::VersionCheck(void)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, VERSION_CHK, -1, NULL, -1);
    SendInst(cmd, CMDBASELEN - 1);
    return 0;
}

uint8_t PANDA_UI::Geometry(uint8_t inst, uint8_t index)
{
    uint8_t cmd[CMDBASELEN] = {0};
    FillInst(cmd, inst, index, NULL, -1);
    SendInst(cmd, CMDBASELEN);
    return 0;
}
uint8_t PANDA_UI::ListenEvent()
{
	// 监听串口是否有数据
	// 读数据
	// 处理数据 
}

