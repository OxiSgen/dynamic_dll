using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Gladkov_lab6_oopp
{
   
    public partial class Form1 : Form
    {

        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "From_file")]
        private static extern void From_file();
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "OFname")]
        private static extern void OFname(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "OFsurname")]
        private static extern void OFsurname(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "OFage")]
        private static extern void OFage(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "OFposishion")]
        private static extern void OFposishion(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "OFempl")]
        private static extern void OFempl(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "OFzarp")]
        private static extern void OFzarp(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Fdel")]
        private static extern void Fdel(int i);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = " FinsertEMPL")]
        private static extern void FinsertEMPL(int i);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "InFname")]
        private static extern void InFname(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "InFsurname")]
        private static extern void InFsurname(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "InFage")]
        private static extern void InFage(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "InFposishion")]
        private static extern void InFposishion(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "InFempl")]
        private static extern void InFempl(int i, StringBuilder str);
        [DllImport("MFCLibrary1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "InFzarp")]
        private static extern void InFzarp(int i, StringBuilder str);

        public Form1()
        {
            InitializeComponent();
        }

    

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int index = listBox1.SelectedIndex;
            if (index >= 0)
            {
                Fdel(index);
                listBox1.Items.RemoveAt(index);
            }
        }

        private void выводИзФайлаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            StringBuilder temp = new StringBuilder(256);
            StringBuilder temp1 = new StringBuilder(256);
            From_file();
            //var temp = new StringBuilder(256);
            OFname(0, temp);
            temp1.Append(temp);
            OFsurname(0, temp);
            temp1.Append("  " + temp);
            OFage(0, temp);
            temp1.Append("  " + temp);
            OFposishion(0, temp);
            temp1.Append("  " + temp);
            OFempl(0, temp);
            temp1.Append("  " + temp);
            OFzarp(0, temp);
            temp1.Append("  " + temp);
            listBox1.Items.Add(temp1);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            StringBuilder temp = new StringBuilder(256);
            StringBuilder temp1 = new StringBuilder(256);
            int index = listBox1.SelectedIndex;
            //FinsertEMPL(index);
            Form2 f2 = new Form2();


            OFname(index, temp);
            f2.textBox1.Text = temp.ToString();

            OFsurname(index, temp);
            f2.textBox2.Text = temp.ToString();

            OFage(index, temp);
            f2.textBox3.Text = temp.ToString();

            OFposishion(index, temp);
            f2.textBox4.Text = temp.ToString();

            OFempl(index, temp);
            f2.textBox5.Text = temp.ToString();

            OFzarp(index, temp);
            f2.textBox6.Text = temp.ToString();

            f2.ShowDialog();

            InFname(index, new StringBuilder(f2.textBox1.Text));                 //должно менять вектор с изменением коробки. Пока нифига не делает
            InFsurname(index, new StringBuilder(f2.textBox2.Text));              // уже меняет, но не видит разницы между манагером и эмплоером и выглядит ужасно
            InFage(index, new StringBuilder(f2.textBox3.Text));
            InFposishion(index, new StringBuilder(f2.textBox4.Text));
            InFempl(index, new StringBuilder(f2.textBox5.Text));
            InFzarp(index, new StringBuilder(f2.textBox6.Text));

            listBox1.Items.Clear();
            OFname(index, temp);
            temp1.Append(temp);
            OFsurname(index, temp);
            temp1.Append("  " + temp);
            OFage(index, temp);
            temp1.Append("  " + temp);
            OFposishion(index, temp);
            temp1.Append("  " + temp);
            OFempl(index, temp);
            temp1.Append("  " + temp);
            OFzarp(index, temp);
            temp1.Append("  " + temp);
            listBox1.Items.Add(temp1);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
