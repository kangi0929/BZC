
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/prctl.h>




#include "sample_comm.h"

#include <linux/fb.h>
#include "hifb.h"
#include "loadbmp.h"
#include "hi_tde_api.h"
#include "hi_tde_type.h"
#include "hi_tde_errcode.h"
#include "hi_math.h"

#include "sample_hifb.h"


OSD_COLOR_FMT_E  g_osdColorFmt  = OSD_COLOR_FMT_RGB1555;

HI_U8*                   pShowScreen;

int g_hifb_fd = -1;


static struct fb_bitfield s_a32 = {24, 8, 0};
static struct fb_bitfield s_r32 = {16, 8, 0};
static struct fb_bitfield s_g32 = {8,  8, 0};
static struct fb_bitfield s_b32 = {0,  8, 0};




#define HIFB_RED_1555          0xFC00
#define HIFB_RED_8888          0xFFff0000

#define SAMPLE_CURSOR_PATH        "./res/cursor.bmp"
//#define SAMPLE_CURSOR_PATH        "./res/arrow.bmp"   





HI_S32 SAMPLE_HIFB_LoadBmp(const char* filename, HI_U8* pAddr)
{
    OSD_SURFACE_S        Surface;
    OSD_BITMAPFILEHEADER bmpFileHeader;
    OSD_BITMAPINFO       bmpInfo;

    if (GetBmpInfo(filename, &bmpFileHeader, &bmpInfo) < 0)
    {
        SAMPLE_PRT("GetBmpInfo err!\n");
        return HI_FAILURE;
    }
    Surface.enColorFmt = g_osdColorFmt;
    CreateSurfaceByBitMap(filename, &Surface, pAddr);

    return HI_SUCCESS;
}




void set_mouse_pos(int x , int y)
{
    HIFB_POINT_S             stPoint            = {0, 0};
    stPoint.s32XPos=x;
    stPoint.s32YPos = y;

    if(ioctl(g_hifb_fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
    {
        SAMPLE_PRT("set screen original show position failed!\n");

    }


}


void hifb_test()
{

    struct fb_fix_screeninfo fix;
    struct fb_var_screeninfo var;

    HIFB_POINT_S             stPoint            = {0, 0};
    HI_CHAR                  file[12]           = {0};
    HI_BOOL                  bShow;










     strncpy(file, "/dev/fb2", 12);


    /********************************
    * Step 1. open framebuffer device overlay 0
    **********************************/
    g_hifb_fd = open(file, O_RDWR, 0);
    if (g_hifb_fd < 0)
    {
        SAMPLE_PRT("open %s failed!\n", file);

    }

    bShow = HI_FALSE;
    if (ioctl(g_hifb_fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
    {
        SAMPLE_PRT("FBIOPUT_SHOW_HIFB failed!\n");

    }
    /********************************
    * Step 2. set the screen original position
    **********************************/
    /* 2. set the screen original position */

    stPoint.s32XPos = 150;
    stPoint.s32YPos = 150;


    if (ioctl(g_hifb_fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
    {
        SAMPLE_PRT("set screen original show position failed!\n");
        close(g_hifb_fd);

    }


    if (ioctl(g_hifb_fd, FBIOGET_VSCREENINFO, &var) < 0)
    {
        SAMPLE_PRT("Get variable screen info failed!\n");
        close(g_hifb_fd);

    }






    var.transp = s_a32;
    var.red    = s_r32;
    var.green  = s_g32;
    var.blue   = s_b32;
    var.bits_per_pixel = 32;


    g_osdColorFmt    = OSD_COLOR_FMT_RGB8888;
    var.xres_virtual = 30;
    var.yres_virtual = 30;
    var.xres = 30;
    var.yres = 30;
    var.activate       = FB_ACTIVATE_NOW;

    /*********************************
    * Step 5. set the variable screen information
    ***********************************/
    if (ioctl(g_hifb_fd, FBIOPUT_VSCREENINFO, &var) < 0)
    {
        SAMPLE_PRT("Put variable screen info failed!\n");
        close(g_hifb_fd);

    }

    /**********************************
    * Step 6. get the fix screen information
    ************************************/
    if (ioctl(g_hifb_fd, FBIOGET_FSCREENINFO, &fix) < 0)
    {
        SAMPLE_PRT("Get fix screen info failed!\n");
        close(g_hifb_fd);

    }


    /***************************************
    * Step 7. map the physical video memory for user use
    ******************************************/

    pShowScreen = mmap(HI_NULL, fix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, g_hifb_fd, 0);
    if (MAP_FAILED == pShowScreen)
    {
        SAMPLE_PRT("mmap framebuffer failed!\n");
        close(g_hifb_fd);

    }


    memset(pShowScreen, 0x0, fix.smem_len);

    /* time to play*/
    bShow = HI_TRUE;
    if (ioctl(g_hifb_fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
    {
        SAMPLE_PRT("FBIOPUT_SHOW_HIFB failed!\n");

        munmap(pShowScreen, fix.smem_len);

        close(g_hifb_fd);

    }




    /* move cursor */
    SAMPLE_HIFB_LoadBmp(SAMPLE_CURSOR_PATH,pShowScreen);
    if (ioctl(g_hifb_fd, FBIOPAN_DISPLAY, &var) < 0)
    {
                SAMPLE_PRT("FBIOPAN_DISPLAY failed!\n");
                munmap(pShowScreen, fix.smem_len);
                close(g_hifb_fd);

     }




    #if 0
    /* unmap the physical memory */
    #ifndef __HuaweiLite__
    munmap(pShowScreen, fix.smem_len);
    #endif
    bShow = HI_FALSE;
    if (ioctl(pstInfo->fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
    {
        SAMPLE_PRT("FBIOPUT_SHOW_HIFB failed!\n");
        close(pstInfo->fd);
        return HI_NULL;
    }
    close(pstInfo->fd);
    SAMPLE_PRT("[End]\n");
    #endif




}

