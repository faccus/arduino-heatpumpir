/*
    Mitsubishi Heavy W001CP heatpump control (remote control P/N R61Y23304)
*/
#ifndef MitsubishiW001CPHeatpumpIR_h
#define MitsubishiW001CPHeatpumpIR_h

#include <HeatpumpIR.h>


// Mitsubishi W001CP timing constants
#define MITSUBISHI_W001CP_HDR_MARK          3400   // 3200, A
#define MITSUBISHI_W001CP_HDR_SPACE         1750   // 1600, B
#define MITSUBISHI_W001CP_BIT_MARK          450    // 400,  C
#define MITSUBISHI_W001CP_ONE_SPACE         1300   // 1200, D
#define MITSUBISHI_W001CP_ZERO_SPACE        420    // 400,  E
#define MITSUBISHI_W001CP_RPT_MARK          440    // 400,  F
#define MITSUBISHI_W001CP_RPT_SPACE         17100  // 400,  G

// Mitsubishi W001CP codes
#define MITSUBISHI_W001CP_ON 	         0x40
#define MITSUBISHI_W001CP_OFF 	         0x0

#define MITSUBISHI_W001CP_MODE_DRY	 0x5
#define MITSUBISHI_W001CP_MODE_AUTO	 0x3
#define MITSUBISHI_W001CP_MODE_HEAT	 0x2
#define MITSUBISHI_W001CP_MODE_COOL	 0x1
#define MITSUBISHI_W001CP_MODE_FAN	 0x0

#define MITSUBISHI_W001CP_FAN1		 0x1
#define MITSUBISHI_W001CP_FAN2		 0x3
#define MITSUBISHI_W001CP_FAN3		 0x5
#define MITSUBISHI_W001CP_FAN4		 0x7

#define MITSUBISHI_W001CP_SWING_UP 	 0x0
#define MITSUBISHI_W001CP_SWING_MUP 	 0x1
#define MITSUBISHI_W001CP_SWING_MIDDLE 	 0x2
#define MITSUBISHI_W001CP_SWING_DOWN 	 0x3
#define MITSUBISHI_W001CP_SWING_AUTO 	 0x4


class MitsubishiW001CPHeatpumpIR: public HeatpumpIR
{
  public: // Cannot create generic MitsubishiHeavy heatpump instances
    MitsubishiW001CPHeatpumpIR();

    void send(IRSender& IR, uint8_t powerModeCmd, uint8_t operatingModeCmd, uint8_t fanSpeedCmd, uint8_t temperatureCmd, uint8_t swingVCmd, uint8_t swingHCmd);
    

  private:
    void sendMitsubishiW001CPHeatpump(IRSender& IR, uint8_t powerModeCmd, uint8_t operatingModeCmd, uint8_t fanSpeedCmd, uint8_t temperatureCmd, uint8_t swingV);
};

#endif