using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;

namespace Gladkov_form
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        ///
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
