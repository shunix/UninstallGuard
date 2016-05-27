package com.shunix.uninstallguard.app;

import android.app.Application;
import android.content.Context;
import android.content.Intent;
import com.shunix.uninstallguard.service.GuardService;

/**
 * @author shunix
 * @since 2016/05/26
 */
public class GuardApplication extends Application {
    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        Intent intent = new Intent(this, GuardService.class);
        startService(intent);
    }
}
