namespace Bees
{
    partial class Step2
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
            this.addAuthorButton = new System.Windows.Forms.Button();
            this.addAddressButton = new System.Windows.Forms.Button();
            this.authorComboBox = new System.Windows.Forms.ComboBox();
            this.addressComboBox = new System.Windows.Forms.ComboBox();
            this.addressTextBox = new System.Windows.Forms.TextBox();
            this.authorTextBox = new System.Windows.Forms.TextBox();
            this.linkButton = new System.Windows.Forms.Button();
            this.nextButton = new System.Windows.Forms.Button();
            this.backButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // addAuthorButton
            // 
            this.addAuthorButton.Location = new System.Drawing.Point(12, 12);
            this.addAuthorButton.Name = "addAuthorButton";
            this.addAuthorButton.Size = new System.Drawing.Size(86, 23);
            this.addAuthorButton.TabIndex = 0;
            this.addAuthorButton.Text = "Add Author";
            this.addAuthorButton.UseVisualStyleBackColor = true;
            this.addAuthorButton.Click += new System.EventHandler(this.addAuthorButton_Click);
            // 
            // addAddressButton
            // 
            this.addAddressButton.Location = new System.Drawing.Point(359, 12);
            this.addAddressButton.Name = "addAddressButton";
            this.addAddressButton.Size = new System.Drawing.Size(75, 23);
            this.addAddressButton.TabIndex = 1;
            this.addAddressButton.Text = "Add Address";
            this.addAddressButton.UseVisualStyleBackColor = true;
            this.addAddressButton.Click += new System.EventHandler(this.addAddressButton_Click);
            // 
            // authorComboBox
            // 
            this.authorComboBox.FormattingEnabled = true;
            this.authorComboBox.Location = new System.Drawing.Point(12, 55);
            this.authorComboBox.Name = "authorComboBox";
            this.authorComboBox.Size = new System.Drawing.Size(173, 21);
            this.authorComboBox.TabIndex = 2;
            this.authorComboBox.SelectedIndexChanged += new System.EventHandler(this.authorComboBox_SelectedIndexChanged_1);
            // 
            // addressComboBox
            // 
            this.addressComboBox.AllowDrop = true;
            this.addressComboBox.DropDownHeight = 128;
            this.addressComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.addressComboBox.DropDownWidth = 256;
            this.addressComboBox.IntegralHeight = false;
            this.addressComboBox.Location = new System.Drawing.Point(221, 55);
            this.addressComboBox.Name = "addressComboBox";
            this.addressComboBox.Size = new System.Drawing.Size(213, 21);
            this.addressComboBox.TabIndex = 3;
            this.addressComboBox.SelectedIndexChanged += new System.EventHandler(this.addressComboBox_SelectedIndexChanged_1);
            // 
            // addressTextBox
            // 
            this.addressTextBox.Location = new System.Drawing.Point(221, 95);
            this.addressTextBox.Multiline = true;
            this.addressTextBox.Name = "addressTextBox";
            this.addressTextBox.Size = new System.Drawing.Size(213, 130);
            this.addressTextBox.TabIndex = 5;
            this.addressTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.addressTextBox_KeyPress);
            // 
            // authorTextBox
            // 
            this.authorTextBox.Location = new System.Drawing.Point(12, 95);
            this.authorTextBox.Multiline = true;
            this.authorTextBox.Name = "authorTextBox";
            this.authorTextBox.Size = new System.Drawing.Size(173, 130);
            this.authorTextBox.TabIndex = 4;
            this.authorTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.authorTextBox_KeyPress);
            // 
            // linkButton
            // 
            this.linkButton.Location = new System.Drawing.Point(359, 231);
            this.linkButton.Name = "linkButton";
            this.linkButton.Size = new System.Drawing.Size(75, 23);
            this.linkButton.TabIndex = 6;
            this.linkButton.Text = "link";
            this.linkButton.UseVisualStyleBackColor = true;
            this.linkButton.Click += new System.EventHandler(this.linkButton_Click);
            // 
            // nextButton
            // 
            this.nextButton.Location = new System.Drawing.Point(359, 269);
            this.nextButton.Name = "nextButton";
            this.nextButton.Size = new System.Drawing.Size(75, 23);
            this.nextButton.TabIndex = 7;
            this.nextButton.Text = "Next";
            this.nextButton.UseVisualStyleBackColor = true;
            this.nextButton.Click += new System.EventHandler(this.nextButton_Click);
            // 
            // backButton
            // 
            this.backButton.Location = new System.Drawing.Point(278, 269);
            this.backButton.Name = "backButton";
            this.backButton.Size = new System.Drawing.Size(75, 23);
            this.backButton.TabIndex = 8;
            this.backButton.Text = "Back";
            this.backButton.UseVisualStyleBackColor = true;
            this.backButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // Step2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(446, 450);
            this.Controls.Add(this.backButton);
            this.Controls.Add(this.nextButton);
            this.Controls.Add(this.linkButton);
            this.Controls.Add(this.authorTextBox);
            this.Controls.Add(this.addressTextBox);
            this.Controls.Add(this.addressComboBox);
            this.Controls.Add(this.authorComboBox);
            this.Controls.Add(this.addAddressButton);
            this.Controls.Add(this.addAuthorButton);
            this.Name = "Step2";
            this.Text = "Step2";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Step2_FormClosed);
            this.Load += new System.EventHandler(this.Step2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button addAuthorButton;
        private System.Windows.Forms.Button addAddressButton;
        private System.Windows.Forms.ComboBox authorComboBox;
        private System.Windows.Forms.ComboBox addressComboBox;
        private System.Windows.Forms.TextBox addressTextBox;
        private System.Windows.Forms.TextBox authorTextBox;
        private System.Windows.Forms.Button linkButton;
        private System.Windows.Forms.Button nextButton;
        private System.Windows.Forms.Button backButton;
    }
}