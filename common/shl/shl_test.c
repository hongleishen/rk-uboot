#include <stdio.h>
#include <common.h>

#include <asm/io.h>
#include <linux/delay.h>

void _shl_test(void)
{
    printf("hello in %s, ^^^^^^^^^^^^^^^ dwc3_device_hs_test beging ^^^^^^^^^^\n", __func__);
}

void shl_dwc3_writel(unsigned int *addr, unsigned int val)
{
    // unsigned int *addr = (unsigned int *)address;
    printf("Write [0x%p] = 0x%08x\n", addr, val);
    writel(val, addr);
    mdelay(1000);
}



void dwc3_device_hs_test(void)
{
    shl_dwc3_writel((unsigned int *)0xfcc0c704, 0x40000000);      // DWC3_DCTL_CSFTRST
    shl_dwc3_writel((unsigned int *)0xfcc0c110, 0x30c12804);           // set  DWC3_GCTL_CORESOFTRESET DWC3_GCTL
    shl_dwc3_writel((unsigned int *)0xfcc0c2c0, 0x810c0002);           //  set DWC3_GUSB3PIPECTL_PHYSOFTRST
    shl_dwc3_writel((unsigned int *)0xfcc0c200, 0xc0102400);           //  set DWC3_GUSB2PHYCFG_PHYSOFTRST
    shl_dwc3_writel((unsigned int *)0xfcc0c2c0, 0x010c0002);           //  clear DWC3_GUSB3PIPECTL_PHYSOFTRST
    shl_dwc3_writel((unsigned int *)0xfcc0c200, 0x40102400);           //  clear DWC3_GUSB2PHYCFG_PHYSOFTRST
    shl_dwc3_writel((unsigned int *)0xfcc0c110, 0x30c12004);           // clear DWC3_GCTL_CORESOFTRESET
    shl_dwc3_writel((unsigned int *)0xfcc0c11c, 0x0404018a);      // DWC3_GUCTL1  Global User Control Register1  use 2.0 clk
    shl_dwc3_writel((unsigned int *)0xfcc0c110, 0x30c12004);      // DWC3_GCTL   hwparams1, quirk
    shl_dwc3_writel((unsigned int *)0xfcc0c2c0, 0x010c0002);      // DWC3_GUSB3PIPECTL
    shl_dwc3_writel((unsigned int *)0xfcc0c200, 0x40102400);      // DWC3_GUSB2PHYCFG  hsphy_mode
    shl_dwc3_writel((unsigned int *)0xfcc0c200, 0x40101408);      // DWC3_GUSB2PHYCFG quirk version width
    shl_dwc3_writel((unsigned int *)0xfcc0c400, 0x7bd91880);      // DWC3_GEVNTADRLO
    shl_dwc3_writel((unsigned int *)0xfcc0c404, 0x00000000);      // DWC3_GEVNTADRHI
    shl_dwc3_writel((unsigned int *)0xfcc0c408, 0x00000100);      // DWC3_GEVNTSIZ
    shl_dwc3_writel((unsigned int *)0xfcc0c40c, 0x00000000);      // DWC3_GEVNTCOUNT
    shl_dwc3_writel((unsigned int *)0xfcc0c110, 0x30c12004);      // DWC3_GCTL set mode USB_DR_MODE_PERIPHERAL 
    shl_dwc3_writel((unsigned int *)0xfcc0c704, 0x80000000);      // DWC3_DCTL #define DWC3_DCTL_RUN_STOP			(1 << 31)
}