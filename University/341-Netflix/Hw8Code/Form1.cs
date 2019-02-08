//
//Netflix Database Application
//
//<<FAYAZ KHAN>>
//U. of Illinois, Chicago
//CS341, Fall 2015
//Homework 8
//

/*
 I was not able to finish Get User Reveiws and unable to 
 fully complete top-N prolific users I didn't have the 
 mental capacity any more to figure out how to change 
 from UserID to UserName 
 
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hw8Code
{
  using System.Data.SqlClient;
  public partial class Form1 : Form
  {


    /*commented the below out because connectionInfo was getting erros and hardcoded it in there*/
    //string version = "v11.0";
    //string filename = "netflix.mdf";


    /*Oringinally had the below in button1_click but I figured it was cleaner out here*/
    string connectionInfo = String.Format(@"Data Source=(LocalDB)\{0};AttachDbFilename
                  =|DataDirectory|\{1};Integrated Security=True;", "v11.0", "netflix.mdf");

    public Form1()
    {
      InitializeComponent();
    }

    private void Form1_Load(object sender, EventArgs e)
    {

    }


    private void allMovies_Click(object sender, EventArgs e)
    {
      string sql, msg;
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 


      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 
        sql = "SELECT MovieID, MovieName FROM Movies Order by MovieName ASC;";
        cmd = new SqlCommand();
        cmd.Connection = db;
        cmd.CommandText = sql;

        //result = cmd.ExecuteScalar();
        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        DataSet ds = new DataSet();
        adapter.Fill(ds);  //Temporary TABLE 
        db.Close(); //Everything recieved from database 


        DataTable dt = ds.Tables["TABLE"]; //linked it to dt


        /*Now display the result in the listbox*/

        foreach (DataRow row in dt.Rows)
        {
           msg = string.Format("{0}: {1}", row["MovieID"].ToString(), row["MovieName"].ToString());
           listBox1.Items.Add(msg);
        }
        
      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in AllMovies: " + excep.Message);
      }
        

    }

    private void AllUsers_Click(object sender, EventArgs e)
    {
      string sql, msg;
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 
        sql = "SELECT UserID, UserName, Occupation FROM Users Order by UserName ASC;";


        cmd = new SqlCommand();
        cmd.Connection = db;
        cmd.CommandText = sql; 

        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        DataSet ds = new DataSet();
        adapter.Fill(ds);  //Temporary TABLE 
        db.Close(); //Everything recieved from database 


        DataTable dt = ds.Tables["TABLE"]; //linked it to dt


        /*Now display the result in the listbox*/

        if (dt.Rows.Count > 0)
        {
          foreach (DataRow row in dt.Rows)
          {
            msg = string.Format("{0}: {1}  {2}", row["UserID"].ToString(), 
              row["UserName"].ToString(), row["Occupation"].ToString());
            listBox1.Items.Add(msg);
          }
        }
        else
          MessageBox.Show("NO USERS");

      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in AllUsers: " + excep.Message);
      }
    }


    private void MovieIDReview_TextChanged(object sender, EventArgs e)
    {

    }

    private void ReviewMovieID_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      string sql, msg;
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 

        
        sql = "SELECT UserID, UserName, Occupation FROM Users Order by UserName ASC;";


        cmd = new SqlCommand();
        cmd.Connection = db;
        cmd.CommandText = sql;

        cmd.CommandText = string.Format("SELECT MovieName FROM Movies WHERE MovieID={0};",
        MovieIDReview.Text);

        object result = cmd.ExecuteScalar();

        if (result == null)
          MessageBox.Show("Movie does not exist");
        else
        {
          listBox1.Items.Add(result.ToString());

          SqlDataAdapter adapter = new SqlDataAdapter(cmd);
          DataSet ds = new DataSet();

          cmd.CommandText = string.Format("SELECT UserID, Rating FROM Reviews WHERE MovieID = {0};",
            MovieIDReview.Text);


          //@ allows you to do more than one line of code 
          cmd.CommandText = string.Format(@"SELECT UserID, Rating FROM Reviews WHERE MovieID={0} 
            ORDER BY Rating Desc, UserID ASC;", MovieIDReview.Text);


          adapter.Fill(ds);  //Temporary TABLE 

          DataTable dt = ds.Tables["TABLE"]; //linked it to dt


          /*Now display the result in the listbox*/

          if (dt.Rows.Count > 0)
          {
            foreach (DataRow row in dt.Rows)
            {
              msg = string.Format("{0}: {1} ", row["UserID"].ToString(),
                row["Rating"].ToString());

              listBox1.Items.Add(msg);
            }
          }
          else
            MessageBox.Show("NO Reviews");

          db.Close();
        }



      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in ReviewMovieID: " + excep.Message);
      }

    }

    private void AvgRating_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 


        cmd = new SqlCommand();
        cmd.Connection = db;

        cmd.CommandText = string.Format(@"SELECT ROUND(AVG(CAST(Rating AS Float)), 4) FROM Reviews
          INNER JOIN Movies ON Reviews.MovieID = Movies.MovieID WHERE Movies.MovieName='{0}';",
           this.MovieName.Text);

        object result = cmd.ExecuteScalar();

        db.Close();


        //result.ToString() is necessary because it will take average of nothing so movie does
        //not exist
        if (result == null|| result.ToString()== "")
          MessageBox.Show("Movie does not exist");
        else
          listBox1.Items.Add(string.Format("Average for '{0}' is {1}",this.MovieName.Text, result.ToString()));
        

      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in AvgRating: " + excep.Message);
      }
    }

    private void MovieName_TextChanged(object sender, EventArgs e)
    {

    }

    private void eachRating_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 


        cmd = new SqlCommand();
        cmd.Connection = db;



        cmd.CommandText = string.Format(@"SELECT Rating, COUNT(Rating) as countRating FROM Reviews
          INNER JOIN Movies ON Reviews.MovieID = Movies.MovieID
          WHERE Movies.MovieName='{0}' GROUP BY Rating ORDER BY Rating DESC;",
          this.MovieName.Text);

        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        DataSet ds = new DataSet();
        adapter.Fill(ds);  //Temporary TABLE 

        db.Close();

        DataTable dt = ds.Tables["TABLE"];

        int total = 0;

        if (dt.Rows.Count == 0)
          MessageBox.Show("Movie does not exist");
        else
        {
          foreach (DataRow row in dt.Rows)
          {

            listBox1.Items.Add(row["Rating"] + ": " + row["countRating"]);

            total = total + Convert.ToInt32(row["countRating"]);
          }

          listBox1.Items.Add(string.Format("Total: {0}", total.ToString()));
        }
      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in EachRating: " + excep.Message);
      }
    }

    private void topN_TextChanged(object sender, EventArgs e)
    {

    }

    private void topNAvgRating_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 


        cmd = new SqlCommand();
        cmd.Connection = db;



        cmd.CommandText = string.Format(
            @"SELECT TOP {0} Movies.MovieName, temp.AvgRating 
            FROM Movies
            INNER JOIN 
              (
                SELECT MovieID, ROUND(AVG(CAST(Rating AS Float)), 4) as AvgRating 
                FROM Reviews
                GROUP BY MovieID
              ) temp
            ON temp.MovieID = Movies.MovieID ORDER BY temp.AvgRating DESC,
            Movies.MovieName Asc;",topN.Text);

        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        DataSet ds = new DataSet();
        adapter.Fill(ds);  //Temporary TABLE 

        db.Close();

        DataTable dt = ds.Tables["TABLE"];


        if (dt.Rows.Count == 0)
          MessageBox.Show("Error with Top-N avg rating");
        else
          foreach (DataRow row in dt.Rows)
              listBox1.Items.Add(row["MovieName"] + ": " + row["AvgRating"]);


      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in TopNAvgRating: " + excep.Message);
      }


    }

    private void TopNReviewMov_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 


        cmd = new SqlCommand();
        cmd.Connection = db;



        cmd.CommandText = string.Format(
            @"SELECT TOP {0} Movies.MovieName, temp.countRating FROM Movies
            INNER JOIN 
              (
                SELECT MovieID, COUNT(*) as countRating 
                FROM Reviews
                GROUP BY MovieID
              ) temp
            ON temp.MovieID = Movies.MovieID
            ORDER BY temp.countRating DESC, Movies.MovieName Asc;", topN.Text);

        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        DataSet ds = new DataSet();
        adapter.Fill(ds);  //Temporary TABLE 

        db.Close();

        DataTable dt = ds.Tables["TABLE"];


        if (dt.Rows.Count == 0)
          MessageBox.Show("Error with Top-N Reviews Movies");
        else
          foreach (DataRow row in dt.Rows)
            listBox1.Items.Add(row["MovieName"] + ": " + row["countRating"]);


      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in TopNReviews: " + excep.Message);
      }
    }

    private void TopNUsers_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 


        cmd = new SqlCommand();
        cmd.Connection = db;

        /*
         cmd.CommandText = string.Format(
            @"SELECT TOP {0} Movies.MovieName, temp.countRating FROM Movies
            INNER JOIN 
              (
                SELECT MovieID, COUNT(*) as countRating 
                FROM Reviews
                GROUP BY MovieID
              ) temp
            ON temp.MovieID = Movies.MovieID
            ORDER BY temp.countRating DESC, Movies.MovieName Asc;", topN.Text);
         
         */


        cmd.CommandText = string.Format(
            @"SELECT TOP {0} UserID, COUNT(*) AS countRating
            FROM Reviews GROUP BY UserID ORDER BY countRating DESC, UserID Asc;",topN.Text);

        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        DataSet ds = new DataSet();
        adapter.Fill(ds);  //Temporary TABLE 

        db.Close();

        DataTable dt = ds.Tables["TABLE"];


        if (dt.Rows.Count == 0)
          MessageBox.Show("Error with Top-N Users");
        else
          foreach (DataRow row in dt.Rows)
            listBox1.Items.Add(row["UserID"] + ": " + row["countRating"]);


      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in TopNUsers: " + excep.Message);
      }
    }

    private void trackBar1_Scroll(object sender, EventArgs e)
    {
      label1.Text = trackBar1.Value.ToString();
    }

    private void label1_Click(object sender, EventArgs e)
    {

    }

    private void insertMovie_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      string sql, msg;
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 


      try//Not necessary here because we have test connection but I want to adopt habit
      {

        db.Open();
        sql = "SELECT MovieID, MovieName FROM Movies Order by MovieName ASC;";
        cmd = new SqlCommand();
        cmd.Connection = db;
        cmd.CommandText = string.Format("INSERT INTO Movies(MovieName) Values('{0}');",
        label1.Text);

        int rowCreated = cmd.ExecuteNonQuery();

        if(rowCreated ==1)
          MessageBox.Show("Movie added");
        else
          MessageBox.Show("Not able to add movie");

        db.Close(); //Everything recieved from database 
      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in InsertMovies: " + excep.Message);
      }
    }

    private void iReview_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      string sql, msg;
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 


      try//Not necessary here because we have test connection but I want to adopt habit
      {

        db.Open();
        sql = "SELECT MovieID, MovieName FROM Movies Order by MovieName ASC;";
        cmd = new SqlCommand();
        cmd.Connection = db;
        cmd.CommandText = string.Format("SELECT MovieID FROM Movies WHERE MovieName='{0}';",
         label1.Text);

        object result = cmd.ExecuteScalar();

        if (result == null || result.ToString() == "")
          MessageBox.Show("Movie does not exist");
        else
        {
          int movieID = Convert.ToInt32(result);
          Random randNum = new Random();
          int userID = randNum.Next(100000, 999999);  // 6-digit user ids:


          cmd.CommandText = string.Format("INSERT INTO Reviews(MovieID, UserID, Rating) Values({0}, {1}, {2});",
          movieID,
          userID,
          label1.Text);
        }

        int rowCreated = cmd.ExecuteNonQuery();

        if (rowCreated == 1)
          MessageBox.Show("Review added");
        else
          MessageBox.Show("Not able to add review");

        db.Close(); //Everything recieved from database 
      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in InsertMovies: " + excep.Message);
      }
    }

    private void getUserR_TextChanged(object sender, EventArgs e)
    {

    }

    private void userReviews_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();
      string sql, msg;
      SqlCommand cmd;

      SqlConnection db = new SqlConnection(connectionInfo); //creating an instance of 

      try//Not necessary here because we have test connection but I want to adopt habit
      {
        db.Open();
        listBox1.Items.Clear();             //clears the listBox1 


        cmd = new SqlCommand();
        cmd.Connection = db;

        cmd.CommandText = string.Format("SELECT MovieID FROM Reviews WHERE UserID={0};",
        getUserR.Text);

        //MessageBox.Show(cmd.CommandText);

        object result = cmd.ExecuteScalar();

        if (result == null || result.ToString() == "")
          MessageBox.Show("Movie does not exist");
        else
        {
          listBox1.Items.Add(result.ToString());

          SqlDataAdapter adapter = new SqlDataAdapter(cmd);
          DataSet ds = new DataSet();

          cmd.CommandText = string.Format("SELECT UserID, Rating FROM Reviews WHERE MovieID = {0};",getUserR.Text);

          cmd.CommandText = string.Format(@"SELECT UserID, Rating FROM Reviews WHERE MovieID={0}
            ORDER BY Rating Desc, UserID ASC;",getUserR.Text);


          adapter.Fill(ds);  //Temporary TABLE 

          DataTable dt = ds.Tables["TABLE"]; //linked it to dt


          /*Now display the result in the listbox*/

          if (dt.Rows.Count > 0)
          {
            
              foreach (DataRow row in dt.Rows)
                listBox1.Items.Add(row["UserID"] + ": " + row["Rating"]);
          }
          else
            MessageBox.Show("NO Reviews");

          db.Close();
        }



      }
      catch (Exception excep)
      {
        MessageBox.Show("Error in userReviews: " + excep.Message);
      }
    }




   
  }
}
