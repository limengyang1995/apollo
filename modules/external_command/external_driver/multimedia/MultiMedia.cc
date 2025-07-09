#include <iostream>
#include "MultiMedia.h"
#include "cyber/common/log.h"

namespace apollo {
namespace external_command {

std::atomic<bool> MultiMedia::is_inited_{false};

int MultiMedia::sys_init(void) {
    RK_S32 ret = 0;
    if (is_inited_.load() == true) {
        return 0;
    }
    ret = RK_MPI_SYS_Init();
    if (ret != RK_SUCCESS) {
        std::cout << "RK_MPI_SYS_Init failed, ret:" << std::hex << ret << std::endl;
        AERROR << "RK_MPI_SYS_Init failed, ret:" << std::hex << ret;
        return ret;
    }

    ret = RK_TDE_Open();
    if (ret != RK_SUCCESS) {
        std::cout << "RK_TDE_Open failed, ret:" << std::hex << ret << std::endl;
        AERROR << "RK_TDE_Open failed, ret:" << std::hex << ret;
        RK_MPI_SYS_Exit();
        return ret;
    }

    std::cout << "MultiMedia::sys_init succeed" << std::endl;
    is_inited_.store(true);
    return ret;
}

int MultiMedia::sys_exit(void) {
    RK_S32 ret = 0;
    if (is_inited_.load() == true) {
        ret = RK_MPI_SYS_Exit();
        is_inited_.store(false);
        std::cout << "MultiMedia::sys_exit succeed" << std::endl;
    }
    return ret;
}
}  // namespace external_command
}  // namespace apollo