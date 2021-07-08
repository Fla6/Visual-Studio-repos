namespace Kyrsovay_PCOIB
{
    partial class White_list_add
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(White_list_add));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.White_Param_name = new System.Windows.Forms.TextBox();
            this.White_Param_index = new System.Windows.Forms.TextBox();
            this.White_btn_add = new System.Windows.Forms.Button();
            this.errorProvider_white = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider_white)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(33, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Название параметра";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(33, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Значение параметра";
            // 
            // White_Param_name
            // 
            this.White_Param_name.Location = new System.Drawing.Point(170, 22);
            this.White_Param_name.Name = "White_Param_name";
            this.White_Param_name.Size = new System.Drawing.Size(100, 20);
            this.White_Param_name.TabIndex = 2;
            // 
            // White_Param_index
            // 
            this.White_Param_index.Location = new System.Drawing.Point(170, 58);
            this.White_Param_index.Name = "White_Param_index";
            this.White_Param_index.Size = new System.Drawing.Size(100, 20);
            this.White_Param_index.TabIndex = 3;
            // 
            // White_btn_add
            // 
            this.White_btn_add.Location = new System.Drawing.Point(110, 95);
            this.White_btn_add.Name = "White_btn_add";
            this.White_btn_add.Size = new System.Drawing.Size(75, 23);
            this.White_btn_add.TabIndex = 4;
            this.White_btn_add.Text = "Добавить";
            this.White_btn_add.UseVisualStyleBackColor = true;
            this.White_btn_add.Click += new System.EventHandler(this.White_btn_add_Click);
            // 
            // errorProvider_white
            // 
            this.errorProvider_white.ContainerControl = this;
            // 
            // White_list_add
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(307, 130);
            this.Controls.Add(this.White_btn_add);
            this.Controls.Add(this.White_Param_index);
            this.Controls.Add(this.White_Param_name);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(323, 169);
            this.MinimumSize = new System.Drawing.Size(323, 169);
            this.Name = "White_list_add";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Добавление параметра в реестр";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.White_list_add_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider_white)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox White_Param_name;
        private System.Windows.Forms.TextBox White_Param_index;
        private System.Windows.Forms.Button White_btn_add;
        private System.Windows.Forms.ErrorProvider errorProvider_white;
    }
}