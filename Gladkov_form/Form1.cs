using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Runtime;

namespace Gladkov_form
{
    public partial class Form1 : Form
    {
        int threadCount = 0;



        [DllImport("Gladkov_DLL.dll", EntryPoint = "InitializationTransportTec")] private static extern void Initialize();
        [DllImport("Gladkov_DLL.dll", EntryPoint = "SendInt")] private static extern int SendInt(int n);
        [DllImport("Gladkov_DLL.dll", EntryPoint = "Confirm")] private static extern int Confirm();
        [DllImport("Gladkov_DLL.dll", EntryPoint = "SendString")] private static extern void SendString(int nt, string s);
        [DllImport("Gladkov_DLL.dll", EntryPoint = "ConnectToServer")] private static extern void ConnectToServer();
        [DllImport("Gladkov_DLL.dll", EntryPoint = "Disconnect")] private static extern void Disconnect();


        //[DllImport("Gladkov5_DLL.dll", EntryPoint = "InitializationTransportTec")] private static extern void Initialize();
        //[DllImport("Gladkov5_DLL.dll", EntryPoint = "SendInt")] private static extern int SendInt(int n);
        //[DllImport("Gladkov5_DLL.dll", EntryPoint = "Confirm")] private static extern int Confirm();
        //[DllImport("Gladkov5_DLL.dll", EntryPoint = "SendString")] private static extern void SendString(int nt, string s);
        //[DllImport("Gladkov5_DLL.dll", EntryPoint = "ConnectToServer")] private static extern void ConnectToServer();
        //[DllImport("Gladkov5_DLL.dll", EntryPoint = "Disconnect")] private static extern void Disconnect();


        bool flag = false;
        public Form1()
        {
            InitializeComponent();
            Initialize();
            //for (; ; )
            //{
            //    this.Refresh();
            //    System.Threading.Thread.Sleep(500);

        }

        private void button_start_Click(object sender, EventArgs e)
        {
            int l = Convert.ToInt32(textBox1.Text);
            if (!flag)
            {
                listBox1.Items.Add("All threads");
                listBox1.Items.Add("Main thread");
                flag = true;
            }
            else
            {
                threadCount = 0;
                for (int i = 0; i < l; i++)
                {
                    ConnectToServer();
                    SendInt(0);
                    threadCount = Confirm();
                    Disconnect();
                }
            }
            listBox1.Items.Clear();
            listBox1.Items.Add("All threads");
            listBox1.Items.Add("Main thread");
            for (int j = 0; j < threadCount; j++)
            {
                listBox1.Items.Add("Поток номер " + j);

            }
        }
 


        private void button_stop_Click(object sender, EventArgs e)
        {
            if (listBox1.Items.Count == 2)
                return;
            ConnectToServer();
            SendInt(1);
            threadCount = Confirm();
            Disconnect();
            listBox1.Items.Clear();
            listBox1.Items.Add("All threads");
            listBox1.Items.Add("Main thread");
            for (int j = 0; j < threadCount; j++)
            {
                listBox1.Items.Add("Поток номер " + j);
            }
        }

        private void button_send_Click(object sender, EventArgs e)
        {
            int index = listBox1.SelectedIndex;
            ConnectToServer();
            SendInt(2);
            SendString(index - 2, textBox2.Text);
            int threadCount = Confirm();
            Disconnect();
            listBox1.Items.Clear();
            listBox1.Items.Add("All threads");
            listBox1.Items.Add("Main thread");
            for (int j = 0; j < threadCount; j++)
            {
                listBox1.Items.Add("Поток номер " + j);
            }
        }

        //private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        //{
        //    //if (countThreads >= 1)
        //    //    Quit();
        //}
    }
}
