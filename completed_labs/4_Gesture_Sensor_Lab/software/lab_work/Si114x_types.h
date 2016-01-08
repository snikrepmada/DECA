#ifndef SI114X_TYPES
#define SI114X_TYPES

typedef signed char       s8;
typedef signed short      s16;
typedef signed int        s32;
typedef unsigned char     u8;
typedef unsigned short    u16;
typedef unsigned int      u32;

typedef signed char       S8;
typedef signed short      S16;
typedef signed int        S32;
typedef unsigned char     U8;
typedef unsigned short    U16;
typedef unsigned int      U32;

typedef void *            HANDLE;
typedef char *            STRING;
typedef s16               PT_RESULT;
typedef s8                PT_BOOL;

#define PS_THRESHOLD          700

/** Si114x gestures */
typedef enum
{
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  TAP
} gesture_t;

typedef struct 
{
    u16  sequence;       // sequence number
    u32  timestamp;      // 32-bit Timestamp to record
    u8   pad;
    u8   irqstat;        // 8-bit irq status
    u16  vis;            // VIS
    u16  ir;             // IR
    u16  ps1;            // PS1
    u16  ps2;            // PS2
    u16  ps3;            // PS3
    u16  aux;            // AUX
} SI114X_IRQ_SAMPLE;

#define code
#define xdata

#define LSB 0
#define MSB 1
#define b0  0
#define b1  1
#define b2  2
#define b3  3

typedef union uu16
{
    u16 u16;
    s16 s16;
    u8  u8[2];
    s8  s8[2];
} uu16;


typedef union uu32
{
    u32  u32;
    s32  s32;
    uu16 uu16[2];
    u16  u16[2];
    s16  s16[2];
    u8   u8[4];
    s8   s8[4];

} uu32;

typedef char BIT;

#ifndef TRUE
#define TRUE   0xff
#endif

#ifndef FALSE
#define FALSE  0
#endif

#ifndef NULL
#define NULL 0
#endif

#endif

