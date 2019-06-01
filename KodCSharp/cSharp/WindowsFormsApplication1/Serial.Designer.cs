namespace WindowsFormsApplication1
{
    partial class Serial
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
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.zatwierdzSygnal = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.zatwierdzParametr = new System.Windows.Forms.Button();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.timerStart = new System.Windows.Forms.Button();
            this.timerStop = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.Odbierz = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 19200;
            this.serialPort1.PortName = "COM5";
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Pila",
            "Trojkat",
            "Trapez",
            "Prostokat",
            "Sinus"});
            this.comboBox1.Location = new System.Drawing.Point(29, 80);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 23;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // zatwierdzSygnal
            // 
            this.zatwierdzSygnal.Location = new System.Drawing.Point(30, 31);
            this.zatwierdzSygnal.Name = "zatwierdzSygnal";
            this.zatwierdzSygnal.Size = new System.Drawing.Size(120, 41);
            this.zatwierdzSygnal.TabIndex = 24;
            this.zatwierdzSygnal.Text = "Zatwierdz Sygnal";
            this.zatwierdzSygnal.UseVisualStyleBackColor = true;
            this.zatwierdzSygnal.Click += new System.EventHandler(this.zatwierdzSygnal_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(310, 80);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 25;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // zatwierdzParametr
            // 
            this.zatwierdzParametr.Location = new System.Drawing.Point(165, 31);
            this.zatwierdzParametr.Name = "zatwierdzParametr";
            this.zatwierdzParametr.Size = new System.Drawing.Size(245, 41);
            this.zatwierdzParametr.TabIndex = 26;
            this.zatwierdzParametr.Text = "Zatwierdz Parametr";
            this.zatwierdzParametr.UseVisualStyleBackColor = true;
            this.zatwierdzParametr.Click += new System.EventHandler(this.zatwierdzParametr_Click);
            // 
            // comboBox2
            // 
            this.comboBox2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "Offset",
            "Amplituda",
            "Czas narastania",
            "Czas opadania",
            "Czas podtrzymania",
            "Okres"});
            this.comboBox2.Location = new System.Drawing.Point(165, 80);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 21);
            this.comboBox2.TabIndex = 27;
            // 
            // timerStart
            // 
            this.timerStart.Location = new System.Drawing.Point(432, 43);
            this.timerStart.Name = "timerStart";
            this.timerStart.Size = new System.Drawing.Size(114, 23);
            this.timerStart.TabIndex = 28;
            this.timerStart.Text = "Generator START";
            this.timerStart.UseVisualStyleBackColor = true;
            this.timerStart.Click += new System.EventHandler(this.timerStart_Click);
            // 
            // timerStop
            // 
            this.timerStop.Location = new System.Drawing.Point(432, 72);
            this.timerStop.Name = "timerStop";
            this.timerStop.Size = new System.Drawing.Size(114, 23);
            this.timerStop.TabIndex = 29;
            this.timerStop.Text = "Generator STOP";
            this.timerStop.UseVisualStyleBackColor = true;
            this.timerStop.Click += new System.EventHandler(this.timerStop_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(165, 154);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(245, 194);
            this.textBox2.TabIndex = 30;
            this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // Odbierz
            // 
            this.Odbierz.Location = new System.Drawing.Point(30, 154);
            this.Odbierz.Name = "Odbierz";
            this.Odbierz.Size = new System.Drawing.Size(120, 23);
            this.Odbierz.TabIndex = 31;
            this.Odbierz.Text = "Odbierz";
            this.Odbierz.UseVisualStyleBackColor = true;
            this.Odbierz.Click += new System.EventHandler(this.Odbierz_Click);
            // 
            // Serial
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(572, 377);
            this.Controls.Add(this.Odbierz);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.timerStop);
            this.Controls.Add(this.timerStart);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.zatwierdzParametr);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.zatwierdzSygnal);
            this.Controls.Add(this.comboBox1);
            this.Name = "Serial";
            this.Text = "Serial";
            this.Load += new System.EventHandler(this.Serial_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button zatwierdzSygnal;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button zatwierdzParametr;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button timerStart;
        private System.Windows.Forms.Button timerStop;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button Odbierz;
    }
}