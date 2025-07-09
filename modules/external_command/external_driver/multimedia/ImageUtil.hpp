#pragma once

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "rk_debug.h"
#include "rk_mpi_mb.h"
#include "rk_comm_tde.h"
#include "rk_comm_video.h"
#include "rk_mpi_tde.h"
#include "rk_mpi_sys.h"
#include "rk_mpi_cal.h"
#include "cyber/common/log.h"

namespace apollo {
namespace external_command {

class ImageUtil {
public:
    struct Rect {
        int32_t x;
        int32_t y;
        uint32_t width;
        uint32_t height;
    };
    struct Image {
        uint32_t width;
        uint32_t height;
        uint32_t color_fmt;
        MB_BLK data_block{nullptr};  //?? TODO
        void *virtual_addr{nullptr};
    };

    struct BlendInfo {
        Image src_img;
        Rect dst_rect;
        bool data_valid{false};

        void debug_print() {
            AERROR << "width:" << src_img.width << " height:" << src_img.height << " color_fmt:" << src_img.color_fmt
                   << " rect :" << dst_rect.x << " " << dst_rect.y << " " << dst_rect.width << " " << dst_rect.height
                   << " data_valid: " << data_valid;
        }
    };

    static int InitBlendInfo(
            ImageUtil::BlendInfo &blend_info,
            uint32_t width,
            uint32_t height,
            uint32_t color_fmt,
            char *data,
            int32_t dst_x,
            int32_t dst_y,
            int32_t dst_w,
            int32_t dst_h) {
        blend_info.src_img.width = width;
        blend_info.src_img.height = height;
        blend_info.src_img.color_fmt = color_fmt;
        blend_info.data_valid = false;
        PIC_BUF_ATTR_S attr;
        MB_PIC_CAL_S pic_cal;
        attr.u32Width = width;
        attr.u32Height = height;
        if (width == 0 || height == 0) {
            width = 1920;
            height = 1080;
        }
        attr.enPixelFormat = static_cast<PIXEL_FORMAT_E>(color_fmt);
        attr.enCompMode = COMPRESS_MODE_NONE;
        if (data != nullptr) {
            RK_S32 ret = RK_MPI_CAL_TDE_GetPicBufferSize(&attr, &pic_cal);
            // std::cout << "[" << __FUNCTION__ << "|" << __LINE__
            //           << "]-------------------------pic_size:" << pic_cal.u32MBSize << std::endl;
            ret = RK_MPI_SYS_MmzAlloc(&blend_info.src_img.data_block, RK_NULL, RK_NULL, pic_cal.u32MBSize);
            if (ret != RK_SUCCESS) {
                // AERROR << "RK_MPI_SYS_MmzAlloc failed, ret = " << std::hex << ret;
                // std::cout << "[" << __FUNCTION__ << "|" << __LINE__
                //           << "] RK_MPI_SYS_MmzAlloc failed, ret = " << std::hex << ret;
                return -1;
            } else {
                // AERROR << "RK_MPI_SYS_MmzAlloc success, data_block " << std::hex <<
                // blend_info.src_img.data_block; std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "]
                // RK_MPI_SYS_MmzAlloc success, data_block "
                //           << std::hex << blend_info.src_img.data_block << std::endl;
            }
            void *virtual_addr = RK_MPI_MB_Handle2VirAddr(blend_info.src_img.data_block);
            if (virtual_addr == NULL) {
                AERROR << "RK_MPI_MB_Handle2VirAddr failed";
                std::cout << "[" << __FUNCTION__ << "|" << __LINE__ << "] RK_MPI_MB_Handle2VirAddr failed" << std::endl;
                RK_MPI_SYS_MmzFree(blend_info.src_img.data_block);
                return -1;
            }
            memcpy(virtual_addr, data, pic_cal.u32MBSize);
            RK_MPI_SYS_MmzFlushCache(blend_info.src_img.data_block, RK_FALSE);
            blend_info.src_img.virtual_addr = virtual_addr;
            blend_info.data_valid = true;
        }

        blend_info.dst_rect.x = dst_x;
        blend_info.dst_rect.y = dst_y;
        blend_info.dst_rect.width = dst_w;
        blend_info.dst_rect.height = dst_h;

        return 0;
    }

    static int ReleaseBlendInfo(ImageUtil::BlendInfo &blend_info) {
        if (blend_info.src_img.data_block != nullptr) {
            RK_MPI_SYS_MmzFree(blend_info.src_img.data_block);
        }

        return 0;
    }

    static int Blend(std::vector<BlendInfo> &blend_infos, ImageUtil::Image &dst_image) {
        TDE_HANDLE tde_handle = RK_TDE_BeginJob();
        if (RK_ERR_TDE_INVALID_HANDLE == tde_handle) {
            AERROR << "invalid tde handle";
            return -1;
        }

        AERROR << "blend src info ++++++++++++++++++++++++++++++++";
        for (auto blend_info : blend_infos) {
            blend_info.debug_print();
        }
        AERROR << "blend src info --------------------------------";

        RK_S32 ret = RK_SUCCESS;
        TDE_SURFACE_S dst_surface;
        dst_surface.pMbBlk = dst_image.data_block;
        dst_surface.enColorFmt = static_cast<PIXEL_FORMAT_E>(dst_image.color_fmt);
        dst_surface.u32Height = dst_image.height;
        dst_surface.u32Width = dst_image.width;
        dst_surface.enComprocessMode = COMPRESS_MODE_NONE;

        for (auto blend_info : blend_infos) {
            if (blend_info.data_valid == false) {  // TODO
                continue;
            }
            Image &src_img = blend_info.src_img;
            TDE_SURFACE_S src_surface;
            TDE_RECT_S src_rect, dst_rect;

            src_surface.pMbBlk = src_img.data_block;
            src_surface.enColorFmt = static_cast<PIXEL_FORMAT_E>(src_img.color_fmt);
            src_surface.u32Height = src_img.height;
            src_surface.u32Width = src_img.width;
            src_surface.enComprocessMode = COMPRESS_MODE_NONE;

            src_rect.s32Xpos = 0;
            src_rect.s32Ypos = 0;
            src_rect.u32Width = src_img.width;
            src_rect.u32Height = src_img.height;

            dst_rect.s32Xpos = blend_info.dst_rect.x;
            dst_rect.s32Ypos = blend_info.dst_rect.y;
            dst_rect.u32Width = blend_info.dst_rect.width;
            dst_rect.u32Height = blend_info.dst_rect.height;

            // TODO no data
            ret = RK_TDE_QuickCopy(tde_handle, &src_surface, &src_rect, &dst_surface, &dst_rect);
            if (ret != RK_SUCCESS) {
                AERROR << "RK_TDE_QuickCopy failed, ret = " << std::hex << ret;
                RK_TDE_CancelJob(tde_handle);
                return -1;
            }
        }
        ret = RK_TDE_EndJob(tde_handle, RK_FALSE, RK_FALSE, 0);
        if (ret != RK_SUCCESS) {
            AERROR << "RK_TDE_EndJob failed, ret = " << std::hex << ret;
            RK_TDE_CancelJob(tde_handle);
            return -1;
        }

        AERROR << " before wait for done ";
        ret = RK_TDE_WaitForDone(tde_handle);
        if (ret != RK_SUCCESS) {
            AERROR << "RK_TDE_WaitForDone failed, ret = " << std::hex << ret;
            return -1;
        }

        AERROR << " after wait for done ";

        return 0;
    }
};

}  // namespace external_command
}  // namespace apollo