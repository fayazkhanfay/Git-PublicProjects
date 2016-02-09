package com.xyz.fayazkhan.phonenumber;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

/*
*
* Tasks:
* Create 2 activities:
*   1) Main screen takes a phone number and see if it is in proper format
*       but also has to ignore the char around the phone the number
*       proper format: (630)_373-0836 and (630)373-0836
*
*   2)Second activity take in a string and open the sms activity
*       When returning from sms activity
*       clear text box
*       display to the user returning from sms activity

* */


public class MainActivity extends AppCompatActivity
{
    EditText mText;
    //Button mButton;                                       //Not necessary for this project


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mText = (EditText)findViewById(R.id.mainText);
        //mButton = (Button)findViewById(R.id.mainButton);  //Not necessary for this project

    }


    //This method is being called by the button that was linked in front
    //Don't do protected!! because it kept crashing
    //View is a super object
    public void checkString(View view)//option + enter
    {

        String mainText= mText.getText().toString();//Grabs the string from above
        char[] mTArray = mainText.toCharArray();    //converts string to array
        int length = mainText.length();             //length of the phone number

        int count = 0;                              //For the mTArray to specify char in array

        boolean findb = false;                      //this will be true when '(' found
        int phoneNumber =0;                         //location of '(' in mTArray


        // Trying to find '(' from mTArray and then continues
        while(count < length && findb == false)
        {

           if( mTArray[count]== '(')
           {
               findb = true;
               phoneNumber = count;
           }

           count++;
        }


        //The extra length is too account for the extra space at end of string
        if(findb && (phoneNumber + 12) <= length )
        {
            Log.i("Parsing of string", "Success)");
            /*The first 3  positions of number will be the same for both formats*/

            /*
            * If incorrect format will return out of this void method. If correct format
            * will continue on to the next event at the bottom of method.
            * */

            if(!Character.isDigit(mTArray[count++]))
                return;

            if(!Character.isDigit(mTArray[count++]))
                return;


            if(!Character.isDigit(mTArray[count++]))
                return;


            if(mTArray[count++] != ')')
                return;


            /*
            * Below if statements differs in both phone number formats
            *
            * Both if statements are the same but one format accounts for space in between
            * numbers for ex: (630)_373-0836 vs (630)373-0836
            * */
            if(Character.isDigit(mTArray[count]))
            {
                count++;
                while(count<(phoneNumber + 12))
                {

                    if(count== 8 + phoneNumber)
                    {
                        if (mTArray[count] != '-')
                            return;
                    }
                    else
                    {
                        if(!Character.isDigit(mTArray[count]))
                            return;
                    }

                    count++;
                }

            }

            if(Character.isSpaceChar(mTArray[count]))
            {

                count++;
                while(count< 13 + phoneNumber)
                {

                    if(count== 9 + phoneNumber)
                    {
                        if (mTArray[count] != '-')
                            return;
                    }
                    else
                    {
                        if(!Character.isDigit(mTArray[count]))
                            return;
                    }

                    count++;
                }
            }

            //Log.i("string works correctly", "Success)");

            //Below jumps to the next screen
            Intent nextScreen = new Intent(MainActivity.this, Main2Activity.class);
            startActivity(nextScreen);


        }


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
        mText.setText("");//When returning back to screen will remove previous text
        Toast.makeText(MainActivity.this, "Returning to Parsing number...",
                Toast.LENGTH_LONG).show();
    }

}
