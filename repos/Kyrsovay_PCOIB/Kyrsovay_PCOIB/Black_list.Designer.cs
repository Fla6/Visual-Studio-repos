namespace Kyrsovay_PCOIB
{
    partial class Black_list
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Black_list));
            this.Explorer_reboot = new System.Windows.Forms.Button();
            this.Black_list_on = new System.Windows.Forms.Button();
            this.Black_list_off = new System.Windows.Forms.Button();
            this.List_status = new System.Windows.Forms.Label();
            this.Param_list = new System.Windows.Forms.ListBox();
            this.Param_add = new System.Windows.Forms.Button();
            this.List_satus_label = new System.Windows.Forms.Label();
            this.Param_del = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Explorer_reboot
            // 
            this.Explorer_reboot.Location = new System.Drawing.Point(296, 31);
            this.Explorer_reboot.Name = "Explorer_reboot";
            this.Explorer_reboot.Size = new System.Drawing.Size(156, 23);
            this.Explorer_reboot.TabIndex = 0;
            this.Explorer_reboot.Text = "Перезапустить Explorer";
            this.Explorer_reboot.UseVisualStyleBackColor = true;
            this.Explorer_reboot.Click += new System.EventHandler(this.Explorer_reboot_Click);
            // 
            // Black_list_on
            // 
            this.Black_list_on.Location = new System.Drawing.Point(296, 60);
            this.Black_list_on.Name = "Black_list_on";
            this.Black_list_on.Size = new System.Drawing.Size(156, 23);
            this.Black_list_on.TabIndex = 2;
            this.Black_list_on.Text = "Включить черный список";
            this.Black_list_on.UseVisualStyleBackColor = true;
            this.Black_list_on.Click += new System.EventHandler(this.Black_list_on_Click);
            // 
            // Black_list_off
            // 
            this.Black_list_off.Location = new System.Drawing.Point(296, 89);
            this.Black_list_off.Name = "Black_list_off";
            this.Black_list_off.Size = new System.Drawing.Size(156, 23);
            this.Black_list_off.TabIndex = 3;
            this.Black_list_off.Text = "Выключить черный список";
            this.Black_list_off.UseVisualStyleBackColor = true;
            this.Black_list_off.Click += new System.EventHandler(this.Black_list_off_Click);
            // 
            // List_status
            // 
            this.List_status.AutoSize = true;
            this.List_status.Location = new System.Drawing.Point(293, 10);
            this.List_status.Name = "List_status";
            this.List_status.Size = new System.Drawing.Size(83, 13);
            this.List_status.TabIndex = 4;
            this.List_status.Text = "Статус списка:";
            // 
            // Param_list
            // 
            this.Param_list.FormattingEnabled = true;
            this.Param_list.Location = new System.Drawing.Point(12, 12);
            this.Param_list.Name = "Param_list";
            this.Param_list.Size = new System.Drawing.Size(266, 160);
            this.Param_list.TabIndex = 6;
            // 
            // Param_add
            // 
            this.Param_add.Location = new System.Drawing.Point(296, 118);
            this.Param_add.Name = "Param_add";
            this.Param_add.Size = new System.Drawing.Size(156, 23);
            this.Param_add.TabIndex = 7;
            this.Param_add.Text = "Добавить параметр";
            this.Param_add.UseVisualStyleBackColor = true;
            this.Param_add.Click += new System.EventHandler(this.Param_add_Click);
            // 
            // List_satus_label
            // 
            this.List_satus_label.AutoSize = true;
            this.List_satus_label.Location = new System.Drawing.Point(382, 10);
            this.List_satus_label.Name = "List_satus_label";
            this.List_satus_label.Size = new System.Drawing.Size(0, 13);
            this.List_satus_label.TabIndex = 9;
            // 
            // Param_del
            // 
            this.Param_del.Location = new System.Drawing.Point(296, 147);
            this.Param_del.Name = "Param_del";
            this.Param_del.Size = new System.Drawing.Size(156, 23);
            this.Param_del.TabIndex = 10;
            this.Param_del.Text = "Удалить параметр";
            this.Param_del.UseVisualStyleBackColor = true;
            this.Param_del.Click += new System.EventHandler(this.Param_del_Click);
            // 
            // Black_list
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 184);
            this.Controls.Add(this.Param_del);
            this.Controls.Add(this.List_satus_label);
            this.Controls.Add(this.Param_add);
            this.Controls.Add(this.Param_list);
            this.Controls.Add(this.List_status);
            this.Controls.Add(this.Black_list_off);
            this.Controls.Add(this.Black_list_on);
            this.Controls.Add(this.Explorer_reboot);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(480, 223);
            this.MinimumSize = new System.Drawing.Size(480, 223);
            this.Name = "Black_list";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Черный список";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Black_list_FormClosed);
            this.Load += new System.EventHandler(this.Black_list_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Explorer_reboot;
        private System.Windows.Forms.Button Black_list_on;
        private System.Windows.Forms.Button Black_list_off;
        private System.Windows.Forms.Label List_status;
        private System.Windows.Forms.ListBox Param_list;
        private System.Windows.Forms.Button Param_add;
        private System.Windows.Forms.Label List_satus_label;
        private System.Windows.Forms.Button Param_del;
    }
}