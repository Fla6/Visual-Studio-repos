namespace Kyrsovay_PCOIB
{
    partial class Black_list_add
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Black_list_add));
            this.Param_name = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Param_index = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_add = new System.Windows.Forms.Button();
            this.errorProvider_black = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider_black)).BeginInit();
            this.SuspendLayout();
            // 
            // Param_name
            // 
            this.Param_name.Location = new System.Drawing.Point(170, 22);
            this.Param_name.Name = "Param_name";
            this.Param_name.Size = new System.Drawing.Size(100, 20);
            this.Param_name.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(33, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Название параметра";
            // 
            // Param_index
            // 
            this.Param_index.Location = new System.Drawing.Point(170, 58);
            this.Param_index.Name = "Param_index";
            this.Param_index.Size = new System.Drawing.Size(100, 20);
            this.Param_index.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(33, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Значение параметра";
            // 
            // btn_add
            // 
            this.btn_add.Location = new System.Drawing.Point(110, 95);
            this.btn_add.Name = "btn_add";
            this.btn_add.Size = new System.Drawing.Size(75, 23);
            this.btn_add.TabIndex = 4;
            this.btn_add.Text = "Добавить";
            this.btn_add.UseVisualStyleBackColor = true;
            this.btn_add.Click += new System.EventHandler(this.btn_add_Click);
            // 
            // errorProvider_black
            // 
            this.errorProvider_black.ContainerControl = this;
            // 
            // Black_list_add
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(307, 130);
            this.Controls.Add(this.btn_add);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Param_index);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Param_name);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(323, 169);
            this.MinimumSize = new System.Drawing.Size(323, 169);
            this.Name = "Black_list_add";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Добавление параметра в реестр";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Black_list_add_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider_black)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Param_name;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Param_index;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_add;
        private System.Windows.Forms.ErrorProvider errorProvider_black;
    }
}