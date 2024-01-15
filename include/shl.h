#ifndef SHL_H
#define SHL_H

extern unsigned int g_cmd_open_my_dbg;
extern unsigned int g_cmd_open_dwc3_writel;
extern unsigned int g_cmd_open_debug;

void wait_input(void);
void _shl_test(void);
void shl_dwc3_writel(unsigned int *addr, unsigned int val);
void dwc3_device_hs_test(void);

#endif