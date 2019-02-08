//Fayaz Khan
//3/16/16

package com.xyz.fayazkhan.giver;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;


/*
* The purpose of this application is to send a broad cast message to another
* app FragmentDynamicLayout. In FDL, we bring up Chicago activity or
* Philly activity
* */



// Simple application to send Broadcast to a receiver.
public class MainActivity extends AppCompatActivity {

    //Think of this as the address of the intent of the other app
    private static final String TOAST = "com.xyz.fayazkhan.reciever.show";;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    /*
    * Both ChicagoClickToast and PhillyClickToast are tagged from activity_main.xml
    * file. When user clicks on button will come into below methods.
    * */
    //Need to press option+enter to import View
    public void ChicagoClickToast(View view)
    {

        Intent aIntent = new Intent(TOAST);
        aIntent.putExtra("receive","Chicago"); //Stacking intents to be used in FDL application
        Toast.makeText(getApplicationContext(), "Broadcasting Chicago Intent",
                Toast.LENGTH_SHORT).show();
        sendOrderedBroadcast(aIntent, null);
    }


    public void PhillyClickToast(View view)
    {
        Intent aIntent = new Intent(TOAST);
        aIntent.putExtra("receive", "Philly"); //Stacking intents to be used in FDL application
        Toast.makeText(getApplicationContext(), "Broadcasting Philly Intent",
                Toast.LENGTH_SHORT).show();
        sendOrderedBroadcast(aIntent, null);
    }


}
