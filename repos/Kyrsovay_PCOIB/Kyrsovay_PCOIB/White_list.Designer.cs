namespace Kyrsovay_PCOIB
{
    partial class White_list
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(White_list));
            this.Param_white_list = new System.Windows.Forms.ListBox();
            this.White_list_status = new System.Windows.Forms.Label();
            this.White_list_status_label = new System.Windows.Forms.Label();
            this.White_Explorer_reboot = new System.Windows.Forms.Button();
            this.White_list_on = new System.Windows.Forms.Button();
            this.White_list_off = new System.Windows.Forms.Button();
            this.White_Param_add = new System.Windows.Forms.Button();
            this.White_Param_del = new System.Windows.Forms.Button();
            this.Inf_btn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Param_white_list
            // 
            this.Param_white_list.FormattingEnabled = true;
            this.Param_white_list.Location = new System.Drawing.Point(12, 12);
            this.Param_white_list.Name = "Param_white_list";
            this.Param_white_list.Size = new System.Drawing.Size(266, 160);
            this.Param_white_list.TabIndex = 0;
            // 
            // White_list_status
            // 
            this.White_list_status.AutoSize = true;
            this.White_list_status.Location = new System.Drawing.Point(293, 10);
            this.White_list_status.Name = "White_list_status";
            this.White_list_status.Size = new System.Drawing.Size(83, 13);
            this.White_list_status.TabIndex = 1;
            this.White_list_status.Text = "Статус списка:";
            // 
            // White_list_status_label
            // 
            this.White_list_status_label.AutoSize = true;
            this.White_list_status_label.Location = new System.Drawing.Point(382, 10);
            this.White_list_status_label.Name = "White_list_status_label";
            this.White_list_status_label.Size = new System.Drawing.Size(0, 13);
            this.White_list_status_label.TabIndex = 2;
            // 
            // White_Explorer_reboot
            // 
            this.White_Explorer_reboot.Location = new System.Drawing.Point(296, 31);
            this.White_Explorer_reboot.Name = "White_Explorer_reboot";
            this.White_Explorer_reboot.Size = new System.Drawing.Size(156, 23);
            this.White_Explorer_reboot.TabIndex = 3;
            this.White_Explorer_reboot.Text = "Перезапустить Explorer";
            this.White_Explorer_reboot.UseVisualStyleBackColor = true;
            this.White_Explorer_reboot.Click += new System.EventHandler(this.White_Explorer_reboot_Click);
            // 
            // White_list_on
            // 
            this.White_list_on.Location = new System.Drawing.Point(296, 60);
            this.White_list_on.Name = "White_list_on";
            this.White_list_on.Size = new System.Drawing.Size(156, 23);
            this.White_list_on.TabIndex = 4;
            this.White_list_on.Text = "Включить белый список";
            this.White_list_on.UseVisualStyleBackColor = true;
            this.White_list_on.Click += new System.EventHandler(this.White_list_on_Click);
            // 
            // White_list_off
            // 
            this.White_list_off.Location = new System.Drawing.Point(296, 89);
            this.White_list_off.Name = "White_list_off";
            this.White_list_off.Size = new System.Drawing.Size(156, 23);
            this.White_list_off.TabIndex = 5;
            this.White_list_off.Text = "Выключить белый список";
            this.White_list_off.UseVisualStyleBackColor = true;
            this.White_list_off.Click += new System.EventHandler(this.White_list_off_Click);
            // 
            // White_Param_add
            // 
            this.White_Param_add.Location = new System.Drawing.Point(296, 118);
            this.White_Param_add.Name = "White_Param_add";
            this.White_Param_add.Size = new System.Drawing.Size(156, 23);
            this.White_Param_add.TabIndex = 6;
            this.White_Param_add.Text = "Добавить параметр";
            this.White_Param_add.UseVisualStyleBackColor = true;
            this.White_Param_add.Click += new System.EventHandler(this.White_Param_add_Click);
            // 
            // White_Param_del
            // 
            this.White_Param_del.Location = new System.Drawing.Point(296, 147);
            this.White_Param_del.Name = "White_Param_del";
            this.White_Param_del.Size = new System.Drawing.Size(156, 23);
            this.White_Param_del.TabIndex = 7;
            this.White_Param_del.Text = "Удалить параметр";
            this.White_Param_del.UseVisualStyleBackColor = true;
            this.White_Param_del.Click += new System.EventHandler(this.White_Param_del_Click);
            // 
            // Inf_btn
            // 
            this.Inf_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Inf_btn.Location = new System.Drawing.Point(12, 188);
            this.Inf_btn.Name = "Inf_btn";
            this.Inf_btn.Size = new System.Drawing.Size(440, 34);
            this.Inf_btn.TabIndex = 8;
            this.Inf_btn.Text = "Важная информация!";
            this.Inf_btn.UseVisualStyleBackColor = true;
            this.Inf_btn.Click += new System.EventHandler(this.Inf_btn_Click);
            // 
            // White_list
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 234);
            this.Controls.Add(this.Inf_btn);
            this.Controls.Add(this.White_Param_del);
            this.Controls.Add(this.White_Param_add);
            this.Controls.Add(this.White_list_off);
            this.Controls.Add(this.White_list_on);
            this.Controls.Add(this.White_Explorer_reboot);
            this.Controls.Add(this.White_list_status_label);
            this.Controls.Add(this.White_list_status);
            this.Controls.Add(this.Param_white_list);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(480, 273);
            this.MinimumSize = new System.Drawing.Size(480, 273);
            this.Name = "White_list";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Белый список";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.White_list_FormClosed);
            this.Load += new System.EventHandler(this.White_list_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox Param_white_list;
        private System.Windows.Forms.Label White_list_status;
        private System.Windows.Forms.Label White_list_status_label;
        private System.Windows.Forms.Button White_Explorer_reboot;
        private System.Windows.Forms.Button White_list_on;
        private System.Windows.Forms.Button White_list_off;
        private System.Windows.Forms.Button White_Param_add;
        private System.Windows.Forms.Button White_Param_del;
        private System.Windows.Forms.Button Inf_btn;
    }
}