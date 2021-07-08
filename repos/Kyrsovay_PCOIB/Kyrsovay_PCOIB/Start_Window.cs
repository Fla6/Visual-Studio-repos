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
using Kyrsovay_PCOIB.Properties;
using System.Diagnostics;

namespace Kyrsovay_PCOIB
{
    public partial class Start_Window : Form
    {
        public Start_Window()
        {
            InitializeComponent();
        }

        private void Create_black_list_Click(object sender, EventArgs e)
        {
            RegistryKey check10 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
            RegistryKey check9 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
            if (check9 == null)
            {
                RegistryKey k18 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
                RegistryKey check = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
                if (check == null)
                {
                    RegistryKey k1 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
                    k1.SetValue("DisallowRun", 0, RegistryValueKind.DWord);
                    k1.Close();
                    RegistryKey k2 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
                    MessageBox.Show("Черный список успешно создан!", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    k2.Close();
                    Open_black_list.Enabled = true;
                }
                
            }
            else if (check9 != null)
            {
                if (check10 != null)
                {
                    MessageBox.Show("Черный список уже был создан.", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    check9.Close();
                    check10.Close();
                }
                else
                {
                    RegistryKey k20 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
                    k20.SetValue("DisallowRun", 0, RegistryValueKind.DWord);
                    k20.Close();
                    RegistryKey k21 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
                    MessageBox.Show("Черный список успешно создан!", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    k21.Close();
                    Open_black_list.Enabled = true;
                }
            }
        }

        private void Create_white_list_Click(object sender, EventArgs e)
        {
            RegistryKey check11 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
            RegistryKey check1 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
            if (check1 == null)
            {
                RegistryKey k23 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
                RegistryKey check12 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
                if (check12 == null)
                {
                    RegistryKey k3 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
                    k3.SetValue("RestrictRun", 0, RegistryValueKind.DWord);
                    k3.Close();
                    RegistryKey k4 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
                    MessageBox.Show("Белый список успешно создан!", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    k4.Close();
                    Open_white_list.Enabled = true;
                }
            }
            else if (check1 != null)
            {
                if (check11 != null)
                {
                    MessageBox.Show("Белый список уже был создан.", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    check1.Close();
                    check11.Close();
                }
                else
                {
                    RegistryKey k23 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
                    k23.SetValue("RestrictRun", 0, RegistryValueKind.DWord);
                    k23.Close();
                    RegistryKey k24 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
                    MessageBox.Show("Белый список успешно создан!", "Внимание!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    k24.Close();
                    Open_white_list.Enabled = true;
                }
            }
        }

        private void Start_Window_Load(object sender, EventArgs e)
        {
            RegistryKey check2 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
            if (check2 == null)
            {
                Open_black_list.Enabled = false;
            }
            else
            {
                Open_black_list.Enabled = true;
                check2.Close();
            }

            RegistryKey check3 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
            if (check3 == null)
            {
                Open_white_list.Enabled = false;
            }
            else
            {
                Open_white_list.Enabled = true;
                check3.Close();
            }
        }

        private void Start_Window_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = MessageBox.Show("Вы хотите закрыть прорамму?", "Внимание!", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes;
        }

        private void About_programm_Click(object sender, EventArgs e)
        {
            MessageBox.Show("(С) ТУСУР, КИБЕВС, Новиков Владислав Олегович, группа 726, 2020", "О программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void Start_Window_FormClosed(object sender, FormClosedEventArgs e)
        {
            Properties.Settings.Default.Save();
        }

        private void Open_black_list_Click(object sender, EventArgs e)
        {
            Black_list.fl.ShowForm();
        }

        private void Open_white_list_Click(object sender, EventArgs e)
        {
            White_list.fr.ShowForm();
        }

        private void Delete_black_list_Click(object sender, EventArgs e)
        {
            RegistryKey check4 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun");
            if (check4 != null)
            {
                RegistryKey k17 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
                k17.DeleteSubKey("DisallowRun");
                k17.DeleteValue("DisallowRun");
                MessageBox.Show("Черный список удален", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
                k17.Close();
                Open_black_list.Enabled = false;
            }
            else
            {
                MessageBox.Show("Черный спиcок уже удален или еще не создан", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void Delete_white_list_Click(object sender, EventArgs e)
        {
            RegistryKey check5 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\RestrictRun");
            if (check5 != null)
            {
                RegistryKey k18 = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
                k18.DeleteSubKey("RestrictRun");
                k18.DeleteValue("RestrictRun");
                MessageBox.Show("Белый список удален", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
                k18.Close();
                Open_white_list.Enabled = false;
            }
            else
            {
                MessageBox.Show("Белый спиcок уже удален или еще не создан", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
    }
}
