package org.bitnetcore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class BitnetQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File bitnetDir = new File(getFilesDir().getAbsolutePath() + "/.bitnet");
        if (!bitnetDir.exists()) {
            bitnetDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
