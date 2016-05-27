package com.shunix.uninstallguard.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

/**
 * @author shunix
 * @since 2016/05/27
 */
public class GuardService extends Service {
    static {
        System.loadLibrary("uninstallguard");
    }

    native void startGuard(String packageName);

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startGuard(getPackageName());
        return START_NOT_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
