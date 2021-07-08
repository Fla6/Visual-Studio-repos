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
    public partial class Black_list : Form
    {
        public Black_list()
        {
            InitializeComponent();
            
        }

        private static Black_list f;
        public static Black_list fl
        {
            get
            {
                if (f == null || f.IsDisposed) f = new Black_list();
                return f;
            }
        }
        public void ShowForm()
        {
            Show();
            Activate();
        }

        private void Explorer_reboot_Click(object sender, EventArgs e)
        {
            Process[] p1 = Process.GetProcesses();
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

        private void Black_list_Load(object sender, EventArgs e)
        {
            Param_list.Items.Add("Параметр".ToString() + "\t" + "Значение".ToString());
            RegistryKey k7 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
            foreach (string name in k7.GetValueNames())
            {
                Param_list.Items.Add(name + "\t\t" + k7.GetValue(name));
            }
                
            k7.Close();
            RegistryKey k9 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
            if ((List_satus_label.Text = k9.GetValue("DisallowRun").ToString()) == "0")
            {
                List_satus_label.Text = "Выключен";
            }
            else
            {
                List_satus_label.Text = "Включен";
            }
            k9.Close();
        }

        private void Black_list_on_Click(object sender, EventArgs e)
        {
            if (List_satus_label.Text == "Включен")
            {
                MessageBox.Show("Вы уже включили список", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                RegistryKey k5 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
                k5.SetValue("DisallowRun", 1, RegistryValueKind.DWord);
                k5.Close();
                MessageBox.Show("Черный список включен", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                List_satus_label.Text = "Включен";
            }
        }

        private void Black_list_off_Click(object sender, EventArgs e)
        {   
            if (List_satus_label.Text == "Выключен")
            {
                MessageBox.Show("Вы уже выключили список", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                RegistryKey k6 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
                k6.SetValue("DisallowRun", 0, RegistryValueKind.DWord);
                k6.Close();
                MessageBox.Show("Черный список выключен", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                List_satus_label.Text = "Выключен";
            }   
        }

        private void Param_add_Click(object sender, EventArgs e)
        {
            Black_list_add.fe.ShowForm();
            this.Close();
        }

        private void Param_del_Click(object sender, EventArgs e)
        {
            if (Param_list.SelectedItem != null)
            {
                RegistryKey k10 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun", true);
                if (k10 != null)
                {
                    try
                    {
                        DialogResult qa = MessageBox.Show("Вы точно хотите удалить этот параметр?", "Внимание", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                        if (qa == DialogResult.Yes)
                        {
                            k10.DeleteValue(Param_list.SelectedIndex.ToString());
                            k10.Close();
                            Param_list.Items.Remove(Param_list.SelectedItem);
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

        private void Black_list_FormClosed(object sender, FormClosedEventArgs e)
        {
            Properties.Settings.Default.Save();
        }
    }
}
