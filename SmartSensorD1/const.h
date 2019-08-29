const char version[] = "1.1.1";

const int otaPort = 8266;

typedef enum rotaryMovement{
  ROTARY_UP,
  ROTARY_DOWN
};

typedef enum tinfoType{
  TINFO_HP,
  TINFO_HC,
  TINFO_PAPP,
  TINFO_IINST,
  TINFO_LAST
};