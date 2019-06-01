using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Serial : Form
    {
        public Serial()
        {
            InitializeComponent();
        }

        private void Serial_Load(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
                serialPort1.Open();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void zatwierdzSygnal_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (comboBox1.Text == "Pila")
                {
                    serialPort1.Write("xS1\r");
                }
                else if (comboBox1.Text == "Trojkat")
                {
                    serialPort1.Write("xS2\r");
                }
                else if (comboBox1.Text == "Trapez")
                {
                    serialPort1.Write("xS3\r");
                }
                else if (comboBox1.Text == "Prostokat")
                {
                    serialPort1.Write("xS4\r");
                }
                else if (comboBox1.Text == "Sinus")
                {
                    serialPort1.Write("xS5\r");
                }
                Odbierz_Click2();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void zatwierdzParametr_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                string napis = textBox1.Text;

                if (comboBox2.Text == "Offset")
                {
                    serialPort1.Write("xF");
                }
                if (comboBox2.Text == "Amplituda")
                {
                    serialPort1.Write("xA");
                }
                if (comboBox2.Text == "Czas narastania")
                {
                    serialPort1.Write("xN");
                }
                if (comboBox2.Text == "Czas opadania")
                {
                    serialPort1.Write("xO");
                }
                if (comboBox2.Text == "Czas podtrzymania")
                {
                    serialPort1.Write("xU");
                }
                if (comboBox2.Text == "Okres")
                {
                    serialPort1.Write("xT");
                }
                serialPort1.Write(napis);
                serialPort1.Write("\r");
                //serialPort1.Write("x0\r\n");
                Odbierz_Click2();
            }
        }

            private void timerStart_Click(object sender, EventArgs e)
            {
                if (serialPort1.IsOpen)
                {
                     serialPort1.Write("xZ11\r");
                }
            Odbierz_Click2();

            }

        private void timerStop_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("xZ10\r");
            }
            Odbierz_Click2();
        }

        private void Odbierz_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                string napis = "Error";
                while (napis == "Error")
                {
                    serialPort1.ReadTimeout = 500;
                    serialPort1.Write("xW1\r");

                    try
                    {
                        string odebrane = serialPort1.ReadLine();
                        var parts = odebrane.Split(' ');
                        if (parts[0] == "1")
                        {
                            napis = String.Format("Sygnal : Pila\r\nOffset : {1}\r\nAmplituda : {2}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);
                        }
                        else if (parts[0] == "2")
                        {
                            napis = String.Format("Sygnal : Trojkat\r\nOffset : {1}\r\nAmplituda : {2}\r\nCzas narastania : {3}\r\nCzas opadania : {4}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }
                        else if (parts[0] == "3")
                        {
                            napis = String.Format("Sygnal : Trapez\r\nOffset : {1}\r\nAmplituda : {2}\r\nCzas narastania : {3}\r\nCzas opadania : {4}\r\nCzas podtrzymania : {5}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }
                        else if (parts[0] == "4")
                        {
                            napis = String.Format("Sygnal : Prostokat\r\nOffset : {1}\r\nAmplituda : {2}\r\nCzas podtrzymania : {5}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }
                        else if (parts[0] == "5")
                        {
                            napis = String.Format("Sygnal : Sinus\r\nOffset : {1}\r\nAmplituda :  {2}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }

                    }
                    catch (TimeoutException)
                    {

                    }
                }
                textBox2.Text = napis;
            }
        }

        private void Odbierz_Click2()
        {
            if (serialPort1.IsOpen)
            {
                string napis = "Error";
                while (napis == "Error")
                {
                    serialPort1.ReadTimeout = 500;
                    serialPort1.Write("xW1\r");

                    try
                    {
                        string odebrane = serialPort1.ReadLine();
                        var parts = odebrane.Split(' ');
                       
                        if (parts[0] == "1")
                        {
                            napis = String.Format("Sygnal : Pila\r\nOffset : {1}\r\nAmplituda : {2}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);
                        }
                        else if (parts[0] == "2")
                        {
                            napis = String.Format("Sygnal : Trojkat\r\nOffset : {1}\r\nAmplituda : {2}\r\nCzas narastania : {3}\r\nCzas opadania : {4}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }
                        else if (parts[0] == "3")
                        {
                            napis = String.Format("Sygnal : Trapez\r\nOffset : {1}\r\nAmplituda : {2}\r\nCzas narastania : {3}\r\nCzas opadania : {4}\r\nCzas podtrzymania : {5}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }
                        else if (parts[0] == "4")
                        {
                            napis = String.Format("Sygnal : Prostokat\r\nOffset : {1}\r\nAmplituda : {2}\r\nCzas podtrzymania : {5}\r\nOkres : {6}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }
                        else if (parts[0] == "5")
                        {
                            napis = String.Format("Sygnal : Sinus\r\nOffset : {1}\r\nAmplituda :  {2}\r\nCzy zalaczany : {7}", parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);

                        }

                    }
                    catch (TimeoutException)
                    {
                    }
                }
                textBox2.Text = napis;
            }
        }


        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
