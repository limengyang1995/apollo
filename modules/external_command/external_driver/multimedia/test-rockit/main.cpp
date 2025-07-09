#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include "rk_mpi_vi.h"
#include "rk_mpi_mb.h"
#include "rk_mpi_sys.h"
#include "rk_mpi_venc.h"

const std::string g_cam_dev = "/dev/video0";
const int         g_width   = 1280;
const int         g_height  = 960;
      int         g_cnt     = 0;

#define ISP_BUFFER_NUM 5
#define ISP_DPTH_NUM   (ISP_BUFFER_NUM - 2)

volatile bool sStop = false;
static void sig_handler(int sign)
{
    switch (sign) {
    case SIGINT:
    case SIGTERM:
        sStop = true;
        break;

    default:
        break;
    }
}

void _putRaw(const void* data, int len)
{
    auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    printf("[%lu] Get Raw Data: %p, %d\n", millisec, data, len);
    if ( ++g_cnt % 10 == 0 )
    {
        char name[32] = {0};
        sprintf(name, "PIC-%04d.nv12", g_cnt);
        FILE* fp = fopen(name, "wb");
        if (fp)
        {
            fwrite(data, 1, len, fp);
            fflush(fp);
            fclose(fp);
        }
    }
}

int main()
{
    printf("\033[31m**************** COOKOO RK Demo Run ****************\033[0m\n");
    signal(SIGINT,  sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGKILL, sig_handler);

    MPP_CHN_S stSrcChn;
    RK_S32 s32Ret = RK_FAILURE;

    RK_S32             devId = 0;
    RK_S32             pipeId = 0;
    RK_S32             viChId = 0;
    VI_DEV_ATTR_S      stDevAttr;
    VI_DEV_BIND_PIPE_S stBindPipe;
    VI_CHN_ATTR_S      stChnAttr;
    VIDEO_FRAME_INFO_S stViFrame;

    memset(&stDevAttr,    0, sizeof(VI_DEV_ATTR_S));
    memset(&stBindPipe,   0, sizeof(VI_DEV_BIND_PIPE_S));
    memset(&stChnAttr,    0, sizeof(VI_CHN_ATTR_S));
    memset(&stViFrame,    0, sizeof(VIDEO_FRAME_INFO_S));

    devId     = 0;
    pipeId    = 0;
    viChId    = 0;//VI通道只有4个,8个相机, 2个相机公用1个VI
    stChnAttr.stIspOpt.u32BufCount = ISP_BUFFER_NUM;
    stChnAttr.stIspOpt.enMemoryType = VI_V4L2_MEMORY_TYPE_DMABUF;
    stChnAttr.stIspOpt.enCaptureType = VI_V4L2_CAPTURE_TYPE_VIDEO_CAPTURE;
    stChnAttr.u32Depth = ISP_DPTH_NUM;
    stChnAttr.enPixelFormat = RK_FMT_YUV420SP;
    stChnAttr.stFrameRate.s32SrcFrameRate = -1;
    stChnAttr.stFrameRate.s32DstFrameRate = -1;
    memcpy(stChnAttr.stIspOpt.aEntityName, g_cam_dev.c_str(), g_cam_dev.length());

    RK_MPI_SYS_Init();
    // 0. get dev config status
    s32Ret = RK_MPI_VI_GetDevAttr(devId, &stDevAttr);
    if (s32Ret == RK_ERR_VI_NOT_CONFIG) {
        // 0-1.config dev
        s32Ret = RK_MPI_VI_SetDevAttr(devId, &stDevAttr);
        if (s32Ret != RK_SUCCESS) {
            RK_LOGE("RK_MPI_VI_SetDevAttr %x", s32Ret);
            goto __FAILED;
        }
    } else {
        RK_LOGE("RK_MPI_VI_SetDevAttr already");
    }
    // 1.get  dev enable status
    s32Ret = RK_MPI_VI_GetDevIsEnable(devId);
    if (s32Ret != RK_SUCCESS) {
        // 1-2.enable dev
        s32Ret = RK_MPI_VI_EnableDev(devId);
        if (s32Ret != RK_SUCCESS) {
            RK_LOGE("RK_MPI_VI_EnableDev %x", s32Ret);
            goto __FAILED;
        }
        // 1-3.bind dev/pipe
        stBindPipe.u32Num    = pipeId;
        stBindPipe.PipeId[0] = pipeId;
        s32Ret = RK_MPI_VI_SetDevBindPipe(devId, &stBindPipe);
        if (s32Ret != RK_SUCCESS) {
            RK_LOGE("RK_MPI_VI_SetDevBindPipe %x", s32Ret);
            goto __FAILED;
        }
    } else {
        RK_LOGE("RK_MPI_VI_EnableDev already");
    }
    // 2.config channel
    stChnAttr.stSize.u32Width  = g_width;
    stChnAttr.stSize.u32Height = g_height;
    stChnAttr.enCompressMode   = COMPRESS_MODE_NONE;
    s32Ret = RK_MPI_VI_SetChnAttr(pipeId, viChId, &stChnAttr);
    if (s32Ret != RK_SUCCESS) {
        RK_LOGE("RK_MPI_VI_SetChnAttr %x", s32Ret);
        goto __FAILED;
    }
    // 3.enable channel
    s32Ret = RK_MPI_VI_EnableChn(pipeId, viChId);
    if (s32Ret != RK_SUCCESS) {
        RK_LOGE("RK_MPI_VI_EnableChn %x", s32Ret);
        goto __FAILED;
    }

    while (!sStop)
    {
        //get raw frame
        if ( RK_MPI_VI_GetChnFrame(pipeId, viChId, &stViFrame, 3) == RK_SUCCESS ) {
            _putRaw(RK_MPI_MB_Handle2VirAddr(stViFrame.stVFrame.pMbBlk), RK_MPI_MB_GetLength(stViFrame.stVFrame.pMbBlk));
            RK_MPI_VI_ReleaseChnFrame(pipeId, viChId, &stViFrame);
        }
        
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

__FAILED:
    // 5. disable one chn
    s32Ret = RK_MPI_VI_DisableChn(pipeId, viChId);
    RK_LOGE("RK_MPI_VI_DisableChn %x", s32Ret);
    s32Ret = RK_MPI_VENC_StopRecvFrame(viChId);
    RK_LOGE("destroy enc chn:%d", viChId);
    // 6.disable dev(will diabled all chn)
    s32Ret = RK_MPI_VI_DisableDev(devId);
    RK_LOGE("RK_MPI_VI_DisableDev %x", s32Ret);

    RK_MPI_SYS_Exit();
}
