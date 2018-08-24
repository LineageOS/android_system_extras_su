#define LOG_TAG "su"

#include <binder/AppOpsManager.h>
#include <utils/Log.h>

using namespace android;

extern "C" {

int appops_start_op_su(int uid, const char *pkgName) {
    int ret;

    ALOGD("Checking whether app [uid:%d, pkgName: %s] is allowed to be root", uid, pkgName);
    AppOpsManager *ops = new AppOpsManager();

    int mode = ops->startOp(AppOpsManager::OP_SU, uid, String16(pkgName));

    switch (mode) {
        case AppOpsManager::MODE_ALLOWED:
          ALOGD("Privilege elevation allowed by appops");
          ret = 0;
          break;
        default:
          ALOGD("Privilege elevation denied by appops");
          ret = 1;
          break;
    }

    delete ops;
    return ret;
}

void appops_finish_op_su(int uid, const char *pkgName) {
    ALOGD("Finishing su operation for app [uid:%d, pkgName: %s]", uid, pkgName);
    AppOpsManager *ops = new AppOpsManager();
    ops->finishOp(AppOpsManager::OP_SU, uid, String16(pkgName));
    delete ops;
}

}
