namespace Hw8Code
{
  partial class Form1
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.listBox1 = new System.Windows.Forms.ListBox();
      this.allMovies = new System.Windows.Forms.Button();
      this.AllUsers = new System.Windows.Forms.Button();
      this.MovieIDReview = new System.Windows.Forms.TextBox();
      this.ReviewMovieID = new System.Windows.Forms.Button();
      this.MovieName = new System.Windows.Forms.TextBox();
      this.AvgRating = new System.Windows.Forms.Button();
      this.eachRating = new System.Windows.Forms.Button();
      this.panel1 = new System.Windows.Forms.Panel();
      this.panel2 = new System.Windows.Forms.Panel();
      this.panel3 = new System.Windows.Forms.Panel();
      this.topN = new System.Windows.Forms.TextBox();
      this.topNAvgRating = new System.Windows.Forms.Button();
      this.TopNReviewMov = new System.Windows.Forms.Button();
      this.TopNUsers = new System.Windows.Forms.Button();
      this.panel4 = new System.Windows.Forms.Panel();
      this.insertMovie = new System.Windows.Forms.Button();
      this.iReview = new System.Windows.Forms.Button();
      this.insertReview = new System.Windows.Forms.TextBox();
      this.trackBar1 = new System.Windows.Forms.TrackBar();
      this.label1 = new System.Windows.Forms.Label();
      this.getUserR = new System.Windows.Forms.TextBox();
      this.userReviews = new System.Windows.Forms.Button();
      this.panel1.SuspendLayout();
      this.panel2.SuspendLayout();
      this.panel3.SuspendLayout();
      this.panel4.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
      this.SuspendLayout();
      // 
      // listBox1
      // 
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new System.Drawing.Point(419, 12);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new System.Drawing.Size(258, 251);
      this.listBox1.TabIndex = 1;
      // 
      // allMovies
      // 
      this.allMovies.Location = new System.Drawing.Point(27, 18);
      this.allMovies.Name = "allMovies";
      this.allMovies.Size = new System.Drawing.Size(75, 23);
      this.allMovies.TabIndex = 4;
      this.allMovies.Text = "All Movies";
      this.allMovies.UseVisualStyleBackColor = true;
      this.allMovies.Click += new System.EventHandler(this.allMovies_Click);
      // 
      // AllUsers
      // 
      this.AllUsers.Location = new System.Drawing.Point(27, 63);
      this.AllUsers.Name = "AllUsers";
      this.AllUsers.Size = new System.Drawing.Size(75, 23);
      this.AllUsers.TabIndex = 5;
      this.AllUsers.Text = "All Users";
      this.AllUsers.UseVisualStyleBackColor = true;
      this.AllUsers.Click += new System.EventHandler(this.AllUsers_Click);
      // 
      // MovieIDReview
      // 
      this.MovieIDReview.Location = new System.Drawing.Point(13, 21);
      this.MovieIDReview.Name = "MovieIDReview";
      this.MovieIDReview.Size = new System.Drawing.Size(100, 20);
      this.MovieIDReview.TabIndex = 6;
      this.MovieIDReview.Text = "124";
      this.MovieIDReview.TextChanged += new System.EventHandler(this.MovieIDReview_TextChanged);
      // 
      // ReviewMovieID
      // 
      this.ReviewMovieID.Location = new System.Drawing.Point(119, 21);
      this.ReviewMovieID.Name = "ReviewMovieID";
      this.ReviewMovieID.Size = new System.Drawing.Size(75, 23);
      this.ReviewMovieID.TabIndex = 7;
      this.ReviewMovieID.Text = "Reviews";
      this.ReviewMovieID.UseVisualStyleBackColor = true;
      this.ReviewMovieID.Click += new System.EventHandler(this.ReviewMovieID_Click);
      // 
      // MovieName
      // 
      this.MovieName.Location = new System.Drawing.Point(3, 6);
      this.MovieName.Name = "MovieName";
      this.MovieName.Size = new System.Drawing.Size(197, 20);
      this.MovieName.TabIndex = 8;
      this.MovieName.Text = "Finding Nemo";
      this.MovieName.TextChanged += new System.EventHandler(this.MovieName_TextChanged);
      // 
      // AvgRating
      // 
      this.AvgRating.Location = new System.Drawing.Point(13, 32);
      this.AvgRating.Name = "AvgRating";
      this.AvgRating.Size = new System.Drawing.Size(75, 39);
      this.AvgRating.TabIndex = 9;
      this.AvgRating.Text = "Average Rating";
      this.AvgRating.UseVisualStyleBackColor = true;
      this.AvgRating.Click += new System.EventHandler(this.AvgRating_Click);
      // 
      // eachRating
      // 
      this.eachRating.Location = new System.Drawing.Point(110, 32);
      this.eachRating.Name = "eachRating";
      this.eachRating.Size = new System.Drawing.Size(75, 39);
      this.eachRating.TabIndex = 10;
      this.eachRating.Text = "Each Rating";
      this.eachRating.UseVisualStyleBackColor = true;
      this.eachRating.Click += new System.EventHandler(this.eachRating_Click);
      // 
      // panel1
      // 
      this.panel1.BackColor = System.Drawing.SystemColors.InactiveCaption;
      this.panel1.Controls.Add(this.AvgRating);
      this.panel1.Controls.Add(this.eachRating);
      this.panel1.Controls.Add(this.MovieName);
      this.panel1.Location = new System.Drawing.Point(12, 182);
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size(214, 81);
      this.panel1.TabIndex = 11;
      // 
      // panel2
      // 
      this.panel2.BackColor = System.Drawing.SystemColors.ButtonFace;
      this.panel2.Controls.Add(this.MovieIDReview);
      this.panel2.Controls.Add(this.ReviewMovieID);
      this.panel2.Location = new System.Drawing.Point(12, 76);
      this.panel2.Name = "panel2";
      this.panel2.Size = new System.Drawing.Size(214, 67);
      this.panel2.TabIndex = 12;
      // 
      // panel3
      // 
      this.panel3.BackColor = System.Drawing.SystemColors.MenuHighlight;
      this.panel3.Controls.Add(this.AllUsers);
      this.panel3.Controls.Add(this.allMovies);
      this.panel3.Location = new System.Drawing.Point(311, 13);
      this.panel3.Name = "panel3";
      this.panel3.Size = new System.Drawing.Size(365, 249);
      this.panel3.TabIndex = 13;
      // 
      // topN
      // 
      this.topN.Location = new System.Drawing.Point(3, 29);
      this.topN.Name = "topN";
      this.topN.Size = new System.Drawing.Size(56, 20);
      this.topN.TabIndex = 14;
      this.topN.Text = "5";
      this.topN.TextChanged += new System.EventHandler(this.topN_TextChanged);
      // 
      // topNAvgRating
      // 
      this.topNAvgRating.Location = new System.Drawing.Point(122, 311);
      this.topNAvgRating.Name = "topNAvgRating";
      this.topNAvgRating.Size = new System.Drawing.Size(140, 23);
      this.topNAvgRating.TabIndex = 15;
      this.topNAvgRating.Text = "Top-N by Avg Rating";
      this.topNAvgRating.UseVisualStyleBackColor = true;
      this.topNAvgRating.Click += new System.EventHandler(this.topNAvgRating_Click);
      // 
      // TopNReviewMov
      // 
      this.TopNReviewMov.Location = new System.Drawing.Point(122, 340);
      this.TopNReviewMov.Name = "TopNReviewMov";
      this.TopNReviewMov.Size = new System.Drawing.Size(140, 23);
      this.TopNReviewMov.TabIndex = 16;
      this.TopNReviewMov.Text = "Top-N Reviewed Movies";
      this.TopNReviewMov.UseVisualStyleBackColor = true;
      this.TopNReviewMov.Click += new System.EventHandler(this.TopNReviewMov_Click);
      // 
      // TopNUsers
      // 
      this.TopNUsers.Location = new System.Drawing.Point(122, 369);
      this.TopNUsers.Name = "TopNUsers";
      this.TopNUsers.Size = new System.Drawing.Size(140, 23);
      this.TopNUsers.TabIndex = 17;
      this.TopNUsers.Text = "Top-N Prolific Users";
      this.TopNUsers.UseVisualStyleBackColor = true;
      this.TopNUsers.Click += new System.EventHandler(this.TopNUsers_Click);
      // 
      // panel4
      // 
      this.panel4.BackColor = System.Drawing.SystemColors.ActiveCaption;
      this.panel4.Controls.Add(this.topN);
      this.panel4.Location = new System.Drawing.Point(25, 311);
      this.panel4.Name = "panel4";
      this.panel4.Size = new System.Drawing.Size(237, 100);
      this.panel4.TabIndex = 18;
      // 
      // insertMovie
      // 
      this.insertMovie.Location = new System.Drawing.Point(311, 310);
      this.insertMovie.Name = "insertMovie";
      this.insertMovie.Size = new System.Drawing.Size(75, 23);
      this.insertMovie.TabIndex = 19;
      this.insertMovie.Text = "Movie";
      this.insertMovie.UseVisualStyleBackColor = true;
      this.insertMovie.Click += new System.EventHandler(this.insertMovie_Click);
      // 
      // iReview
      // 
      this.iReview.Location = new System.Drawing.Point(311, 349);
      this.iReview.Name = "iReview";
      this.iReview.Size = new System.Drawing.Size(75, 23);
      this.iReview.TabIndex = 20;
      this.iReview.Text = "Review";
      this.iReview.UseVisualStyleBackColor = true;
      this.iReview.Click += new System.EventHandler(this.iReview_Click);
      // 
      // insertReview
      // 
      this.insertReview.Location = new System.Drawing.Point(419, 310);
      this.insertReview.Name = "insertReview";
      this.insertReview.Size = new System.Drawing.Size(134, 20);
      this.insertReview.TabIndex = 21;
      this.insertReview.Text = "Finding Nemo";
      // 
      // trackBar1
      // 
      this.trackBar1.Location = new System.Drawing.Point(419, 349);
      this.trackBar1.Maximum = 5;
      this.trackBar1.Minimum = 1;
      this.trackBar1.Name = "trackBar1";
      this.trackBar1.Size = new System.Drawing.Size(104, 45);
      this.trackBar1.TabIndex = 22;
      this.trackBar1.Value = 1;
      this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(529, 354);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(13, 13);
      this.label1.TabIndex = 23;
      this.label1.Text = "5";
      this.label1.Click += new System.EventHandler(this.label1_Click);
      // 
      // getUserR
      // 
      this.getUserR.Location = new System.Drawing.Point(15, 31);
      this.getUserR.Name = "getUserR";
      this.getUserR.Size = new System.Drawing.Size(100, 20);
      this.getUserR.TabIndex = 24;
      this.getUserR.Text = "305344";
      this.getUserR.TextChanged += new System.EventHandler(this.getUserR_TextChanged);
      // 
      // userReviews
      // 
      this.userReviews.Location = new System.Drawing.Point(131, 31);
      this.userReviews.Name = "userReviews";
      this.userReviews.Size = new System.Drawing.Size(94, 23);
      this.userReviews.TabIndex = 25;
      this.userReviews.Text = "User Reviews";
      this.userReviews.UseVisualStyleBackColor = true;
      this.userReviews.Click += new System.EventHandler(this.userReviews_Click);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.SystemColors.ActiveBorder;
      this.ClientSize = new System.Drawing.Size(696, 413);
      this.Controls.Add(this.userReviews);
      this.Controls.Add(this.getUserR);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.trackBar1);
      this.Controls.Add(this.insertReview);
      this.Controls.Add(this.iReview);
      this.Controls.Add(this.insertMovie);
      this.Controls.Add(this.TopNUsers);
      this.Controls.Add(this.TopNReviewMov);
      this.Controls.Add(this.topNAvgRating);
      this.Controls.Add(this.panel2);
      this.Controls.Add(this.listBox1);
      this.Controls.Add(this.panel1);
      this.Controls.Add(this.panel3);
      this.Controls.Add(this.panel4);
      this.ForeColor = System.Drawing.SystemColors.HotTrack;
      this.Name = "Form1";
      this.Text = "Form1";
      this.Load += new System.EventHandler(this.Form1_Load);
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.panel2.ResumeLayout(false);
      this.panel2.PerformLayout();
      this.panel3.ResumeLayout(false);
      this.panel4.ResumeLayout(false);
      this.panel4.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ListBox listBox1;
    private System.Windows.Forms.Button allMovies;
    private System.Windows.Forms.Button AllUsers;
    private System.Windows.Forms.TextBox MovieIDReview;
    private System.Windows.Forms.Button ReviewMovieID;
    private System.Windows.Forms.TextBox MovieName;
    private System.Windows.Forms.Button AvgRating;
    private System.Windows.Forms.Button eachRating;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.Panel panel2;
    private System.Windows.Forms.Panel panel3;
    private System.Windows.Forms.TextBox topN;
    private System.Windows.Forms.Button topNAvgRating;
    private System.Windows.Forms.Button TopNReviewMov;
    private System.Windows.Forms.Button TopNUsers;
    private System.Windows.Forms.Panel panel4;
    private System.Windows.Forms.Button insertMovie;
    private System.Windows.Forms.Button iReview;
    private System.Windows.Forms.TextBox insertReview;
    private System.Windows.Forms.TrackBar trackBar1;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox getUserR;
    private System.Windows.Forms.Button userReviews;
  }
}

