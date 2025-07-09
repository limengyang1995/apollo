#pragma once

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <atomic>
#include "rk_debug.h"
#include "rk_mpi_mb.h"
#include "rk_comm_tde.h"
#include "rk_comm_video.h"
#include "rk_mpi_tde.h"
#include "rk_mpi_sys.h"
#include "rk_mpi_cal.h"

namespace apollo {
namespace external_command {

class MultiMedia {
public:
    static std::atomic<bool> is_inited_;
    static int sys_init(void);
    static int sys_exit(void);
};

}  // namespace external_command
}  // namespace apollo