//
//GUI- based Asian Options Stock Pricing Program 
//
//<<FAYAZ KHAN>>
//U. of Illinois, Chicago
//CS341, Fall of 2015
//Homework 7
//


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AsianOptionsLib
{
  public partial class Form1 : Form
  {
    double initial;
    double exercise;
    double up ;
    double down ;
    double interest ;
    long periods;
    long sims;
    long temp;
    double elapsedTimeInSecs;
    double price;

    public Form1()
    {
      InitializeComponent();
    }

    /*
     Majority of this comes pregenerated everytime an item is added to Form1
     */
    private void Form1_Load(object sender, EventArgs e)
    {
      /*
       This is normal to leave empty 
       */
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
    
    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {

    }

    private void textBox3_TextChanged(object sender, EventArgs e)
    {

    }

    private void textBox4_TextChanged(object sender, EventArgs e)
    {

    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {

    }

    private void textBox6_TextChanged(object sender, EventArgs e)
    {

    }

    private void textBox7_TextChanged(object sender, EventArgs e)
    {

    }

    private void button1_Click(object sender, EventArgs e)
    {
      /*
       Essentially all of the work is done here because we want everything calculated after 
       * the button is pressed 
       */


      int start = System.Environment.TickCount; //Starts the timer 

      /*
       * Below takes from the text field or the default and comes in as strings and coverts to either 
       * double or or long int 
       */
      initial = System.Convert.ToDouble(textBox1.Text);
      exercise = System.Convert.ToDouble(textBox2.Text);
      up = System.Convert.ToDouble(textBox3.Text);
      down = System.Convert.ToDouble(textBox4.Text);
      interest = System.Convert.ToDouble(textBox5.Text);
      periods = System.Convert.ToInt64(textBox6.Text);
      sims = System.Convert.ToInt64(textBox7.Text);
     
      //I could do waitcursor but was not allowing me to do it maybe missing a library


      /*This function is taken from another file and provided by Prof. Hummel*/
      price=  AsianOptionsLib.Pricing.Simulation(initial, exercise, up, down, interest, periods, sims);


      int stop = System.Environment.TickCount; //ends timer

      elapsedTimeInSecs = (stop - start) / 1000.0; // calculates timer 

      /*Add to displaye in Listbox1*/  
      this.listBox1.Items.Add("Price: " + Math.Round(price,2) + " elapsed time: " + elapsedTimeInSecs);
      /*Not asked to do Rounding but I did (var, places you want)*/


    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      //stuff is added to be displayed from other method for ex this.listBox1
    }
  }
}
