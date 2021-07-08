namespace Kyrsovay_PCOIB
{
    partial class Start_Window
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Start_Window));
            this.label1 = new System.Windows.Forms.Label();
            this.Create_black_list = new System.Windows.Forms.Button();
            this.Create_white_list = new System.Windows.Forms.Button();
            this.Open_black_list = new System.Windows.Forms.Button();
            this.Open_white_list = new System.Windows.Forms.Button();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.About_programm = new System.Windows.Forms.ToolStripButton();
            this.Delete_black_list = new System.Windows.Forms.Button();
            this.Delete_white_list = new System.Windows.Forms.Button();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(171, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(244, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "Запрет запуска программ";
            // 
            // Create_black_list
            // 
            this.Create_black_list.Location = new System.Drawing.Point(216, 76);
            this.Create_black_list.Name = "Create_black_list";
            this.Create_black_list.Size = new System.Drawing.Size(145, 23);
            this.Create_black_list.TabIndex = 1;
            this.Create_black_list.Text = "Создать черный список";
            this.Create_black_list.UseVisualStyleBackColor = true;
            this.Create_black_list.Click += new System.EventHandler(this.Create_black_list_Click);
            // 
            // Create_white_list
            // 
            this.Create_white_list.Location = new System.Drawing.Point(216, 117);
            this.Create_white_list.Name = "Create_white_list";
            this.Create_white_list.Size = new System.Drawing.Size(145, 23);
            this.Create_white_list.TabIndex = 2;
            this.Create_white_list.Text = "Создать белый список";
            this.Create_white_list.UseVisualStyleBackColor = true;
            this.Create_white_list.Click += new System.EventHandler(this.Create_white_list_Click);
            // 
            // Open_black_list
            // 
            this.Open_black_list.Location = new System.Drawing.Point(400, 76);
            this.Open_black_list.Name = "Open_black_list";
            this.Open_black_list.Size = new System.Drawing.Size(145, 23);
            this.Open_black_list.TabIndex = 3;
            this.Open_black_list.Text = "Открыть черный список";
            this.Open_black_list.UseVisualStyleBackColor = true;
            this.Open_black_list.Click += new System.EventHandler(this.Open_black_list_Click);
            // 
            // Open_white_list
            // 
            this.Open_white_list.Location = new System.Drawing.Point(400, 117);
            this.Open_white_list.Name = "Open_white_list";
            this.Open_white_list.Size = new System.Drawing.Size(145, 23);
            this.Open_white_list.TabIndex = 4;
            this.Open_white_list.Text = "Открыть белый список";
            this.Open_white_list.UseVisualStyleBackColor = true;
            this.Open_white_list.Click += new System.EventHandler(this.Open_white_list_Click);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.About_programm});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(580, 25);
            this.toolStrip1.TabIndex = 5;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // About_programm
            // 
            this.About_programm.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.About_programm.Image = ((System.Drawing.Image)(resources.GetObject("About_programm.Image")));
            this.About_programm.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.About_programm.Name = "About_programm";
            this.About_programm.Size = new System.Drawing.Size(23, 22);
            this.About_programm.Text = "О программе";
            this.About_programm.Click += new System.EventHandler(this.About_programm_Click);
            // 
            // Delete_black_list
            // 
            this.Delete_black_list.Location = new System.Drawing.Point(34, 76);
            this.Delete_black_list.Name = "Delete_black_list";
            this.Delete_black_list.Size = new System.Drawing.Size(145, 23);
            this.Delete_black_list.TabIndex = 6;
            this.Delete_black_list.Text = "Удалить черный список";
            this.Delete_black_list.UseVisualStyleBackColor = true;
            this.Delete_black_list.Click += new System.EventHandler(this.Delete_black_list_Click);
            // 
            // Delete_white_list
            // 
            this.Delete_white_list.Location = new System.Drawing.Point(34, 117);
            this.Delete_white_list.Name = "Delete_white_list";
            this.Delete_white_list.Size = new System.Drawing.Size(145, 23);
            this.Delete_white_list.TabIndex = 7;
            this.Delete_white_list.Text = "Удалить белый список";
            this.Delete_white_list.UseVisualStyleBackColor = true;
            this.Delete_white_list.Click += new System.EventHandler(this.Delete_white_list_Click);
            // 
            // Start_Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(580, 163);
            this.Controls.Add(this.Delete_white_list);
            this.Controls.Add(this.Delete_black_list);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.Open_white_list);
            this.Controls.Add(this.Open_black_list);
            this.Controls.Add(this.Create_white_list);
            this.Controls.Add(this.Create_black_list);
            this.Controls.Add(this.label1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(596, 202);
            this.MinimumSize = new System.Drawing.Size(596, 202);
            this.Name = "Start_Window";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Меню";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Start_Window_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Start_Window_FormClosed);
            this.Load += new System.EventHandler(this.Start_Window_Load);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Create_black_list;
        private System.Windows.Forms.Button Create_white_list;
        private System.Windows.Forms.Button Open_black_list;
        private System.Windows.Forms.Button Open_white_list;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton About_programm;
        private System.Windows.Forms.Button Delete_black_list;
        private System.Windows.Forms.Button Delete_white_list;
    }
}

