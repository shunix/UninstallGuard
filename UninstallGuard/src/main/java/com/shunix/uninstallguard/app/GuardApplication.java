package com.shunix.uninstallguard.app;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import com.shunix.uninstallguard.service.GuardService;

import java.util.List;

/**
 * @author shunix
 * @since 2016/05/26
 */
public class GuardApplication extends Application {
    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        if (!isGuardRunning()) {
            Intent intent = new Intent(this, GuardService.class);
            startService(intent);
        }
    }

    private boolean isGuardRunning() {
        boolean result = false;
        String guardProcessName = getPackageName() + ":guard";
        ActivityManager activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
        List<ActivityManager.RunningAppProcessInfo> processInfos = activityManager.getRunningAppProcesses();
        if (processInfos != null && processInfos.size() > 0) {
            for (ActivityManager.RunningAppProcessInfo processInfo : processInfos) {
                if (processInfo.processName.equalsIgnoreCase(guardProcessName)) {
                    result = true;
                    break;
                }
            }
        }
        return result;
    }
}
