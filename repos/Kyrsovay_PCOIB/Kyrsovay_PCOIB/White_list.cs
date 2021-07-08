using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using Microsoft.Win32;

namespace Kyrsovay_PCOIB
{
    public partial class White_list : Form
    {
        public White_list()
        {
            InitializeComponent();
        }

        private static White_list f;
        public static White_list fr
        {
            get
            {
                if (f == null || f.IsDisposed) f = new White_list();
                return f;
            }
        }
        public void ShowForm()
        {
            Show();
            Activate();
        }
        private void White_Explorer_reboot_Click(object sender, EventArgs e)
        {
            Process[] p2 = Process.GetProcesses();
            try
            {
                foreach (Process p in Process.GetProcessesByName("explorer"))
                {
                    p.Kill();
                }
                MessageBox.Show("Проводник перезапущен", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void White_list_Load(object sender, EventArgs e)
        {
            
            Param_white_list.Items.Add("Параметр".ToString() + "\t" + "Значение".ToString());
            RegistryKey k11 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
            foreach (string name in k11.GetValueNames())
            {
                Param_white_list.Items.Add(name + "\t\t" + k11.GetValue(name));
            }
            k11.Close();
            RegistryKey k12 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
            if ((White_list_status_label.Text = k12.GetValue("RestrictRun").ToString()) == "0")
            {
                White_list_status_label.Text = "Выключен";
            }
            else
            {
                White_list_status_label.Text = "Включен";
            }
            k12.Close();
        }

        private void White_list_on_Click(object sender, EventArgs e)
        {
            if (White_list_status_label.Text == "Включен")
            {
                MessageBox.Show("Вы уже включили список", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                RegistryKey k13 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
                k13.SetValue("RestrictRun", 1, RegistryValueKind.DWord);
                k13.Close();
                MessageBox.Show("Белый список включен", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                White_list_status_label.Text = "Включен";
            }
        }

        private void White_list_off_Click(object sender, EventArgs e)
        {
            if (White_list_status_label.Text == "Выключен")
            {
                MessageBox.Show("Вы уже выключили список", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                RegistryKey k14 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
                k14.SetValue("RestrictRun", 0, RegistryValueKind.DWord);
                k14.Close();
                MessageBox.Show("Белый список выключен", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                White_list_status_label.Text = "Выключен";
            }
        }

        private void White_Param_add_Click(object sender, EventArgs e)
        {
            White_list_add.fc.ShowForm();
            this.Close();
        }

        private void White_Param_del_Click(object sender, EventArgs e)
        {
            if (Param_white_list.SelectedItem != null)
            {
                RegistryKey k15 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun", true);
                if (k15 != null)
                {
                    try
                    {
                        DialogResult qb = MessageBox.Show("Вы точно хотите удалить этот параметр?", "Внимание", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                        if (qb == DialogResult.Yes)
                        {
                            k15.DeleteValue(Param_white_list.SelectedIndex.ToString());
                            Param_white_list.Items.Remove(Param_white_list.SelectedItem);
                            k15.Close();
                            MessageBox.Show("Параметр удален из реестра", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                    }
                    catch
                    {
                        MessageBox.Show("Невозможно удалить параметр!", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
            }
            else
            {
                MessageBox.Show("Выберите параметр", "Внмание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void White_list_FormClosed(object sender, FormClosedEventArgs e)
        {
            Properties.Settings.Default.Save();
        }

        private void Inf_btn_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Важно: в некоторых версиях Windows данные действия запрещают сами групповые политики, также перестает открываться " +
                "диспетчер задач и редактор реестра, что в свою очередь не дает вернуть все как было и приходится все исправлять в дополнительных " +
                "параметрах загрузки системы. Чтобы такого не произошло - добавляйте в список разрешенных gpedit.msc и regedit.exe", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
