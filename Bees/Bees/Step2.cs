using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Bees
{
    public partial class Step2 : Form
    {
        InformationDTO information = null;
        Step1 step1 = null;

        public Step2(Step1 step1, InformationDTO information)
        {
            this.step1 = step1;
            this.information = information;
            InitializeComponent();
            this.authorComboBox.DataSource = this.information.Authors;
            this.authorComboBox.DisplayMember = "Name";
            this.authorComboBox.ValueMember = "AuthorObject";
            this.addressComboBox.DataSource = this.information.Addresses;
            this.addressComboBox.DisplayMember = "Value";
            this.addressComboBox.ValueMember = "AddressObject";
            
        }

        public Step2()
        {
            InitializeComponent();
        }

        private void Step2_Load(object sender, EventArgs e)
        {
           
        }

        private void addAuthorButton_Click(object sender, EventArgs e)
        {
            new AddAuthor(this.information).ShowDialog();
            this.authorComboBox.DataSource = new List<Author>(this.information.Authors);
        }

        private void addAddressButton_Click(object sender, EventArgs e)
        {
            new AddAddressDialog(this.information).ShowDialog();
            this.addressComboBox.DataSource = new List<Address>(this.information.Addresses);
        }

      

        private void addressTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }

        private void authorTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }

       

        private void addressComboBox_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            addressTextBox.Text = (addressComboBox.SelectedValue as Address).Value;

        }

        private void authorComboBox_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            authorTextBox.Text = (authorComboBox.SelectedValue as Author).Name;
        }

        private void linkButton_Click(object sender, EventArgs e)
        {
            Author author = authorComboBox.SelectedValue as Author;
            Address address = addressComboBox.SelectedValue as Address;
            this.information.Link(author, address);
        }

        private Step3 step3 = null;

        private void nextButton_Click(object sender, EventArgs e)
        {
            if (null == step3)
            {
                step3 = new Step3(this, this.information);
            }
            this.Hide();
            step3.Show();
        }

        private void Step2_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            step1.Show();
        }
            
    }
}