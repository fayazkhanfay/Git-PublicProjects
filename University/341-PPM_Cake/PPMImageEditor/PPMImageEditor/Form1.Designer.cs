﻿namespace PPMImageEditor
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
      this.picImage = new System.Windows.Forms.PictureBox();
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
      this.cmdOpen = new System.Windows.Forms.Button();
      this.cmdSaveAs = new System.Windows.Forms.Button();
      this.cmdExit = new System.Windows.Forms.Button();
      this.cmdFS1 = new System.Windows.Forms.Button();
      this.button1 = new System.Windows.Forms.Button();
      this.button2 = new System.Windows.Forms.Button();
      this.button3 = new System.Windows.Forms.Button();
      this.button4 = new System.Windows.Forms.Button();
      this.radioFitImage = new System.Windows.Forms.RadioButton();
      this.radioActualSizeImage = new System.Windows.Forms.RadioButton();
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.picImage)).BeginInit();
      this.SuspendLayout();
      // 
      // picImage
      // 
      this.picImage.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.picImage.BackColor = System.Drawing.Color.Aqua;
      this.picImage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.picImage.Location = new System.Drawing.Point(170, 15);
      this.picImage.Margin = new System.Windows.Forms.Padding(6);
      this.picImage.Name = "picImage";
      this.picImage.Size = new System.Drawing.Size(692, 539);
      this.picImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
      this.picImage.TabIndex = 0;
      this.picImage.TabStop = false;
      // 
      // openFileDialog1
      // 
      this.openFileDialog1.FileName = "openFileDialog1";
      // 
      // cmdOpen
      // 
      this.cmdOpen.Location = new System.Drawing.Point(15, 15);
      this.cmdOpen.Margin = new System.Windows.Forms.Padding(6);
      this.cmdOpen.Name = "cmdOpen";
      this.cmdOpen.Size = new System.Drawing.Size(129, 35);
      this.cmdOpen.TabIndex = 1;
      this.cmdOpen.Text = "Open...";
      this.cmdOpen.UseVisualStyleBackColor = true;
      this.cmdOpen.Click += new System.EventHandler(this.cmdOpen_Click);
      // 
      // cmdSaveAs
      // 
      this.cmdSaveAs.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.cmdSaveAs.Enabled = false;
      this.cmdSaveAs.Location = new System.Drawing.Point(15, 472);
      this.cmdSaveAs.Margin = new System.Windows.Forms.Padding(6);
      this.cmdSaveAs.Name = "cmdSaveAs";
      this.cmdSaveAs.Size = new System.Drawing.Size(129, 35);
      this.cmdSaveAs.TabIndex = 2;
      this.cmdSaveAs.Text = "Save as...";
      this.cmdSaveAs.UseVisualStyleBackColor = true;
      this.cmdSaveAs.Click += new System.EventHandler(this.cmdSaveAs_Click);
      // 
      // cmdExit
      // 
      this.cmdExit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.cmdExit.Location = new System.Drawing.Point(15, 519);
      this.cmdExit.Margin = new System.Windows.Forms.Padding(6);
      this.cmdExit.Name = "cmdExit";
      this.cmdExit.Size = new System.Drawing.Size(129, 35);
      this.cmdExit.TabIndex = 3;
      this.cmdExit.Text = "Exit";
      this.cmdExit.UseVisualStyleBackColor = true;
      this.cmdExit.Click += new System.EventHandler(this.cmdExit_Click);
      // 
      // cmdFS1
      // 
      this.cmdFS1.Enabled = false;
      this.cmdFS1.Location = new System.Drawing.Point(15, 62);
      this.cmdFS1.Margin = new System.Windows.Forms.Padding(6);
      this.cmdFS1.Name = "cmdFS1";
      this.cmdFS1.Size = new System.Drawing.Size(129, 35);
      this.cmdFS1.TabIndex = 4;
      this.cmdFS1.Text = "Test F#";
      this.cmdFS1.UseVisualStyleBackColor = true;
      this.cmdFS1.Click += new System.EventHandler(this.cmdFS1_Click);
      // 
      // button1
      // 
      this.button1.Enabled = false;
      this.button1.Location = new System.Drawing.Point(12, 149);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(129, 39);
      this.button1.TabIndex = 5;
      this.button1.Text = "Grayscale";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // button2
      // 
      this.button2.Enabled = false;
      this.button2.Location = new System.Drawing.Point(12, 194);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(132, 39);
      this.button2.TabIndex = 6;
      this.button2.Text = "FlipHorz";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new System.EventHandler(this.button2_Click);
      // 
      // button3
      // 
      this.button3.Enabled = false;
      this.button3.Location = new System.Drawing.Point(12, 239);
      this.button3.Name = "button3";
      this.button3.Size = new System.Drawing.Size(129, 39);
      this.button3.TabIndex = 7;
      this.button3.Text = "RotateR90";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new System.EventHandler(this.button3_Click);
      // 
      // button4
      // 
      this.button4.Enabled = false;
      this.button4.Location = new System.Drawing.Point(12, 284);
      this.button4.Name = "button4";
      this.button4.Size = new System.Drawing.Size(129, 39);
      this.button4.TabIndex = 8;
      this.button4.Text = "Threshold";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new System.EventHandler(this.button4_Click);
      // 
      // radioFitImage
      // 
      this.radioFitImage.AutoSize = true;
      this.radioFitImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.radioFitImage.Location = new System.Drawing.Point(15, 389);
      this.radioFitImage.Name = "radioFitImage";
      this.radioFitImage.Size = new System.Drawing.Size(102, 24);
      this.radioFitImage.TabIndex = 10;
      this.radioFitImage.TabStop = true;
      this.radioFitImage.Text = "Scale to fit";
      this.radioFitImage.UseVisualStyleBackColor = true;
      this.radioFitImage.CheckedChanged += new System.EventHandler(this.radioFitImage_CheckedChanged);
      // 
      // radioActualSizeImage
      // 
      this.radioActualSizeImage.AutoSize = true;
      this.radioActualSizeImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.radioActualSizeImage.Location = new System.Drawing.Point(15, 424);
      this.radioActualSizeImage.Name = "radioActualSizeImage";
      this.radioActualSizeImage.Size = new System.Drawing.Size(104, 24);
      this.radioActualSizeImage.TabIndex = 11;
      this.radioActualSizeImage.TabStop = true;
      this.radioActualSizeImage.Text = "Actual size";
      this.radioActualSizeImage.UseVisualStyleBackColor = true;
      this.radioActualSizeImage.CheckedChanged += new System.EventHandler(this.radioActualSizeImage_CheckedChanged);
      // 
      // textBox1
      // 
      this.textBox1.Location = new System.Drawing.Point(15, 354);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new System.Drawing.Size(129, 29);
      this.textBox1.TabIndex = 12;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(15, 330);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(152, 24);
      this.label1.TabIndex = 13;
      this.label1.Text = "Threshold below";
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.Yellow;
      this.ClientSize = new System.Drawing.Size(884, 571);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.textBox1);
      this.Controls.Add(this.radioActualSizeImage);
      this.Controls.Add(this.radioFitImage);
      this.Controls.Add(this.button4);
      this.Controls.Add(this.button3);
      this.Controls.Add(this.button2);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.cmdFS1);
      this.Controls.Add(this.cmdExit);
      this.Controls.Add(this.cmdSaveAs);
      this.Controls.Add(this.cmdOpen);
      this.Controls.Add(this.picImage);
      this.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.Margin = new System.Windows.Forms.Padding(6);
      this.Name = "Form1";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "PPM Image Editor";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.picImage)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.PictureBox picImage;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		private System.Windows.Forms.Button cmdOpen;
		private System.Windows.Forms.Button cmdSaveAs;
		private System.Windows.Forms.Button cmdExit;
    private System.Windows.Forms.Button cmdFS1;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.Button button2;
    private System.Windows.Forms.Button button3;
    private System.Windows.Forms.Button button4;
    private System.Windows.Forms.RadioButton radioFitImage;
    private System.Windows.Forms.RadioButton radioActualSizeImage;
    private System.Windows.Forms.TextBox textBox1;
    private System.Windows.Forms.Label label1;
	}
}

