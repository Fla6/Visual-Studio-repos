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

namespace Kyrsovay_PCOIB
{
    public partial class White_list_add : Form
    {
        public White_list_add()
        {
            InitializeComponent();
        }

        private static White_list_add f;
        public static White_list_add fc
        {
            get
            {
                if (f == null || f.IsDisposed) f = new White_list_add();
                return f;
            }
        }
        public void ShowForm()
        {
            Show();
            Activate();
        }
        private void White_btn_add_Click(object sender, EventArgs e)
        {
            if (White_Param_name.Text == "")
            {
                MessageBox.Show("Параметр должен иметь название", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (White_Param_index.Text == "")
            {
                MessageBox.Show("Параметр должен иметь значение", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (White_Param_index.Text.Contains(".exe") || White_Param_index.Text.Contains(".msc") || White_Param_index.Text.Contains(".txt"))
            {
                RegistryKey k16 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun", true);
                k16.SetValue(White_Param_name.Text.ToString(), White_Param_index.Text.ToString(), RegistryValueKind.String);
                k16.Close();
                MessageBox.Show("Параметр добавлен в реестр", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Close();
                White_list.fr.ShowForm();
            }
            else
            {
                MessageBox.Show("Для работы параметра необходимо указать название программы", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }   
        }

        private void White_list_add_FormClosed(object sender, FormClosedEventArgs e)
        {
            Properties.Settings.Default.Save();
            White_list.fr.ShowForm();
        }
    }
}
