package com.shunix.uninstallguard.app;

import android.app.Application;
import android.content.Context;

/**
 * @author shunix
 * @since 2016/05/26
 */
public class GuardApplication extends Application {
    native void startGuard(String packageName);
    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        startGuard(getPackageName());
    }
}
