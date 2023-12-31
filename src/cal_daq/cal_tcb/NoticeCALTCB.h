#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CALTCB_VENDOR_ID  (0x0547)
#define CALTCB_PRODUCT_ID (0x1501)

#define USB3_SF_READ   (0x82)
#define USB3_SF_WRITE  (0x06)
extern void USB3Init(void);
extern void USB3Exit(void);
extern int CALTCBopen(int sid);
extern void CALTCBclose(int sid);
extern void CALTCBresetTIMER(int sid);
extern void CALTCBreset(int sid);
extern void CALTCBstart_DAQ(int sid);
extern void CALTCBstop_DAQ(int sid);
extern unsigned long CALTCBread_RUN(int sid);
extern void CALTCBread_LINK(int sid, unsigned long *data);
extern void CALTCBread_MID(int sid, unsigned long *data);
extern void CALTCBwrite_CW(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_CW(int sid, unsigned long mid);
extern void CALTCBsend_TRIG(int sid);
extern void CALTCBwrite_PEDESTAL_TRIGGER_INTERVAL(int sid, unsigned long data);
extern unsigned long CALTCBread_PEDESTAL_TRIGGER_INTERVAL(int sid);
extern void CALTCBwrite_TRIGGER_ENABLE(int sid, unsigned long data);
extern unsigned long CALTCBread_TRIGGER_ENABLE(int sid);
extern void CALTCBwrite_MULTIPLICITY_THR(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_MULTIPLICITY_THR(int sid, unsigned long mid);
extern void CALTCBwrite_HV(int sid, unsigned long mid, unsigned long ch, int univ, float data);
extern float CALTCBread_HV(int sid, unsigned long mid, unsigned long ch, int univ);
extern void CALTCBwrite_THR(int sid, unsigned long mid, unsigned long ch, unsigned long data);
extern unsigned long CALTCBread_THR(int sid, unsigned long mid, unsigned long ch);
extern float CALTCBread_TEMP(int sid, unsigned long mid);
extern void CALTCBwrite_TRIGGER_DELAY(int sid, unsigned long data);
extern unsigned long CALTCBread_TRIGGER_DELAY(int sid);
extern void CALTCBwrite_TRIGGER_LATENCY(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_TRIGGER_LATENCY(int sid, unsigned long mid);
extern void CALTCBwrite_RUN_NUMBER(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_RUN_NUMBER(int sid, unsigned long mid);
extern void CALTCBwrite_DOWN_SAMPLING(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_DOWN_SAMPLING(int sid, unsigned long mid);
extern void CALTCBwrite_DRS_CALIB(int sid, unsigned long mid, unsigned long data);
extern int CALTCB_DRSinit(int sid, unsigned long mid);
extern void CALTCBwrite_PRESCALE(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_PRESCALE(int sid, unsigned long mid);
extern void CALTCBwrite_PULSE_WIDTH(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_PULSE_WIDTH(int sid, unsigned long mid);
extern void CALTCBwrite_RISETIME(int sid, unsigned long mid, unsigned long data);
extern unsigned long CALTCBread_RISETIME(int sid, unsigned long mid);
extern void CALTCBwrite_CF_FRACTION(int sid, unsigned long mid, float data);
extern float CALTCBread_CF_FRACTION(int sid, unsigned long mid);
extern void CALTCBdisable_LINK(int sid, unsigned long ch, unsigned long data);

#ifdef __cplusplus
}
#endif




