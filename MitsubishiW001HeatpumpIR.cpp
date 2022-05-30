#include <MitsubishiW001HeatpumpIR.h>

MitsubishiW001HeatpumpIR::MitsubishiW001HeatpumpIR() : HeatpumpIR()
{
  static const char model[] PROGMEM = "mitsubishi_w001";
  static const char info[]  PROGMEM = "{\"mdl\":\"mitsubishi_w001\",\"dn\":\"Mitsubishi W001\",\"mT\":18,\"xT\":30,\"fs\":3}";

  _model = model;
  _info = info;
}

void MitsubishiW001HeatpumpIR::send(IRSender& IR, uint8_t powerModeCmd, uint8_t operatingModeCmd, uint8_t fanSpeedCmd, uint8_t temperatureCmd, uint8_t swingVCmd, uint8_t swingHCmd);
{
  // Sensible defaults for the heat pump mode
  uint8_t powerMode     = MITSUBISHI_W001CP_ON;
  uint8_t operatingMode = MITSUBISHI_W001CP_MODE_AUTO;
  uint8_t fanSpeed      = MITSUBISHI_W001CP_FAN1;
  uint8_t temperature   = 26;
  uint8_t swingV        = MITSUBISHI_W001CP_SWING_UP;

  if (powerModeCmd == POWER_OFF)
  {
    powerMode = MITSUBISHI_W001CP_OFF;
  }

  switch (operatingModeCmd)
  {
    case MODE_AUTO:
      operatingMode = MITSUBISHI_W001CP_MODE_AUTO;
      break;
    case MODE_HEAT:
      operatingMode = MITSUBISHI_W001CP_MODE_HEAT;
      break;
    case MODE_COOL:
      operatingMode = MITSUBISHI_W001CP_MODE_COOL;
      break;
    case MODE_DRY:
      operatingMode = MITSUBISHI_W001CP_MODE_DRY;
      break;
    case MODE_FAN:
      operatingMode = MITSUBISHI_W001CP_MODE_FAN;
      break;
  }

  switch (fanSpeedCmd)
  {
    case FAN_1:
      fanSpeed = MITSUBISHI_W001CP_FAN1;
      break;
    case FAN_2:
      fanSpeed = MITSUBISHI_W001CP_FAN2;
      break;
    case FAN_3:
      fanSpeed = MITSUBISHI_W001CP_FAN3;
      break;
    case FAN_4:
      fanSpeed = MITSUBISHI_W001CP_FAN4;
      break;
  }


  if ( temperatureCmd > 16 && temperatureCmd < 31)
  {
    temperature = (temperatureCmd - 16) << 4;
  }

  switch (swingVCmd)
  {
    case VDIR_SWING:
      swingV = MITSUBISHI_W001CP_SWING_AUTO;
      break;
    case VDIR_UP:
      swingV = MITSUBISHI_W001CP_SWING_UP;
      break;
    case VDIR_MUP:
      swingV = MITSUBISHI_W001CP_SWING_MUP;
      break;
    case VDIR_MIDDLE:
      swingV = MITSUBISHI_W001CP_SWING_MIDDLE;
      break;
    case VDIR_MDOWN:
      swingV = MITSUBISHI_W001CP_SWING_DOWN;
      break;
    case VDIR_DOWN:
      swingV = MITSUBISHI_W001CP_SWING_DOWN;
      break;
  }

  sendMitsubishiW001CPHeatpump(IR, powerMode, operatingMode, fanSpeed, temperature, swingV);
}


void MitsubishiW001HeatpumpIR::sendMitsubishiW001Heatpump(IRSender& IR, uint8_t powerMode, uint8_t operatingMode, uint8_t fanSpeed, uint8_t temperature, uint8_t swingV)
{
  uint8_t MitsubishiW001CPTemplate[] = { 0x23, 0xCB, 0x26, 0x21, 0x0, 0x40, 0x52, 0x35, 0x4, 0x0, 0x0, 0xBF, 0xAD, 0xCA, 0xFB, 0xFF, 0xFF};
  //                                        0     1     2     3    4     5     6     7    8    9   10    11    12    13    14    15    16

  MitsubishiW001CPTemplate[5] = powerMode;

  // Temperature/Mode
  MitsubishiW001CPTemplate[6] = temperature | operatingMode;

  // Vanne/Fan
  MitsubishiW001CPTemplate[7] = (swingV << 4) | fanSpeed;

  // There is no checksum, but some bytes are inverted
  MitsubishiHeavyFDTCTemplate[11] = 0xFF ^ MitsubishiHeavyFDTCTemplate[5];
  MitsubishiHeavyFDTCTemplate[12] = 0xFF ^ MitsubishiHeavyFDTCTemplate[6];
  MitsubishiHeavyFDTCTemplate[13] = 0xFF ^ MitsubishiHeavyFDTCTemplate[7];
  MitsubishiHeavyFDTCTemplate[14] = 0xFF ^ MitsubishiHeavyFDTCTemplate[8];
  MitsubishiHeavyFDTCTemplate[15] = 0xFF ^ MitsubishiHeavyFDTCTemplate[9];
  MitsubishiHeavyFDTCTemplate[16] = 0xFF ^ MitsubishiHeavyFDTCTemplate[10];

  // 38 kHz PWM frequency
  IR.setFrequency(38);

  // Header
  IR.mark(MITSUBISHI_W001CP_HDR_MARK);
  IR.space(MITSUBISHI_W001CP_HDR_SPACE);

  // Data
  for (uint8_t i=0; i<sizeofitsubishiHeavyFDTCTemplate); i++) {
    IR.sendIRbyte(itsubishiHeavyFDTCTemplate[i], MITSUBISHI_W001CP_BIT_MARK, MITSUBISHI_W001CP_ZERO_SPACE, MITSUBISHI_W001CP_ONE_SPACE);
  }

  // End mark
  IR.mark(MITSUBISHI_W001CP_BIT_MARK);  
  IR.space(MITSUBISHI_W001CP_HDR_SPACE);
  
  IR.mark(MITSUBISHI_W001CP_BIT_MARK); 
  IR.space(0);
}
