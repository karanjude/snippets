namespace Bees
{
    partial class AddAddressDialog
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
            this.label1 = new System.Windows.Forms.Label();
            this.aor1TextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.astrTextBox = new System.Windows.Forms.TextBox();
            this.aor3TextBox = new System.Windows.Forms.TextBox();
            this.aor2TextBox = new System.Windows.Forms.TextBox();
            this.acnyTextBox = new System.Windows.Forms.TextBox();
            this.actyTextBox = new System.Windows.Forms.TextBox();
            this.okButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "aor1";
            // 
            // aor1TextBox
            // 
            this.aor1TextBox.Location = new System.Drawing.Point(103, 16);
            this.aor1TextBox.Name = "aor1TextBox";
            this.aor1TextBox.Size = new System.Drawing.Size(300, 20);
            this.aor1TextBox.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 176);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(27, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "acty";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 136);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(24, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "astr";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 96);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(28, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "aor3";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(28, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "aor2";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(24, 217);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(30, 13);
            this.label6.TabIndex = 6;
            this.label6.Text = "acny";
            // 
            // astrTextBox
            // 
            this.astrTextBox.Location = new System.Drawing.Point(103, 136);
            this.astrTextBox.Name = "astrTextBox";
            this.astrTextBox.Size = new System.Drawing.Size(300, 20);
            this.astrTextBox.TabIndex = 5;
            // 
            // aor3TextBox
            // 
            this.aor3TextBox.Location = new System.Drawing.Point(103, 96);
            this.aor3TextBox.Name = "aor3TextBox";
            this.aor3TextBox.Size = new System.Drawing.Size(300, 20);
            this.aor3TextBox.TabIndex = 4;
            // 
            // aor2TextBox
            // 
            this.aor2TextBox.Location = new System.Drawing.Point(103, 60);
            this.aor2TextBox.Name = "aor2TextBox";
            this.aor2TextBox.Size = new System.Drawing.Size(300, 20);
            this.aor2TextBox.TabIndex = 3;
            // 
            // acnyTextBox
            // 
            this.acnyTextBox.Location = new System.Drawing.Point(103, 217);
            this.acnyTextBox.Name = "acnyTextBox";
            this.acnyTextBox.Size = new System.Drawing.Size(300, 20);
            this.acnyTextBox.TabIndex = 7;
            // 
            // actyTextBox
            // 
            this.actyTextBox.Location = new System.Drawing.Point(103, 176);
            this.actyTextBox.Name = "actyTextBox";
            this.actyTextBox.Size = new System.Drawing.Size(300, 20);
            this.actyTextBox.TabIndex = 6;
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(328, 243);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 30);
            this.okButton.TabIndex = 1;
            this.okButton.Text = "ok";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // AddAddressDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(415, 285);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.actyTextBox);
            this.Controls.Add(this.acnyTextBox);
            this.Controls.Add(this.aor2TextBox);
            this.Controls.Add(this.aor3TextBox);
            this.Controls.Add(this.astrTextBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.aor1TextBox);
            this.Controls.Add(this.label1);
            this.Name = "AddAddressDialog";
            this.Text = "AddAddressDialog";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox aor1TextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox astrTextBox;
        private System.Windows.Forms.TextBox aor3TextBox;
        private System.Windows.Forms.TextBox aor2TextBox;
        private System.Windows.Forms.TextBox acnyTextBox;
        private System.Windows.Forms.TextBox actyTextBox;
        private System.Windows.Forms.Button okButton;
    }
}