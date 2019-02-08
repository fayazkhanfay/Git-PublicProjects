package com.xyz.fayazkhan.phonenumber;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class Main2Activity extends AppCompatActivity
{
    EditText mText2; //object created to be modified here and it is global
    //Button mButton2;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        mText2 = (EditText)findViewById(R.id.Text2);//now it is linked to front end
        //mButton2 = (Button)findViewById(R.id.button2);// You have to cast

    }

    //Reason for using onRestart vs onResume is so the below method will not be called
    //the first time the activity is called
    @Override //overriding the current activity running in back ground
    protected void onRestart()
    {
        super.onRestart();

        /*
        * This displays a small blue text box when hitting back to return in focus
        * */
        mText2.setText("");//When returning back to screen will remove previous text
        Toast.makeText(Main2Activity.this, "Returning from Compose Message...",
                Toast.LENGTH_LONG).show();
    }

    public void sendMessage(View v)
    {
        //The stuff in green will consistent for sms
        Intent smsIntent = new Intent(Intent.ACTION_VIEW);
        smsIntent.setData(Uri.parse("sms:")); //Be sure not to put space in front of sms:
        smsIntent.putExtra("sms_body",mText2.getText().toString()); //string from this screen
        startActivity(smsIntent);
    }
}
