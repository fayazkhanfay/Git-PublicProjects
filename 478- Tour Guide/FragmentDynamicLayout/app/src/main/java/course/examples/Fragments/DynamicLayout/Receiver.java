package course.examples.Fragments.DynamicLayout;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/**
 * Created by FayazKhan on 3/16/16.
 */
public class Receiver extends BroadcastReceiver
{
    public void onReceive(Context arg0, Intent arg1)
    {
        String re= arg1.getStringExtra("receive");
        if(re.equals("Chicago"))
        {
            Intent nextClass = new Intent();
            nextClass.setClassName("course.examples.Fragments.DynamicLayout",
                    "course.examples.Fragments.DynamicLayout.QuoteViewerActivity");
            nextClass.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            arg0.startActivity(nextClass);

        }
        else if (re.equals("Philly"))
        {
            Intent nextClass = new Intent();
            nextClass.setClassName("course.examples.Fragments.DynamicLayout",
                    "course.examples.Fragments.DynamicLayout.SecQuoteViewerActivity");
            nextClass.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            arg0.startActivity(nextClass);
        }

    }
}
