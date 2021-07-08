using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Win32;
using System.IO;

namespace Kyrsovay_PCOIB
{
    public partial class Black_list_add : Form
    {
        public Black_list_add()
        {
            InitializeComponent();            
        }

        private static Black_list_add f;
        public static Black_list_add fe
        {
            get
            {
                if (f == null || f.IsDisposed) f = new Black_list_add();
                return f;
            }
        }
        public void ShowForm()
        {
            Show();
            Activate();
        }

        private void btn_add_Click(object sender, EventArgs e)
        {
            if (Param_name.Text == "")
            {
                MessageBox.Show("Параметр должен иметь название", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (Param_index.Text == "")
            {
                MessageBox.Show("Параметр должен иметь значение", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (Param_index.Text.Contains(".exe") || Param_index.Text.Contains(".msc") || Param_index.Text.Contains(".txt"))
            {
                RegistryKey k8 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun", true);
                k8.SetValue(Param_name.Text.ToString(), Param_index.Text.ToString(), RegistryValueKind.String);
                k8.Close();
                MessageBox.Show("Параметр добавлен в реестр", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Close();
                Black_list.fl.ShowForm();
            }
            else
            {
                MessageBox.Show("Для работы параметра необходимо указать название программы", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void Black_list_add_FormClosed(object sender, FormClosedEventArgs e)
        {
            Properties.Settings.Default.Save();
            Black_list.fl.ShowForm();
        }
    }
}
