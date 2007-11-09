using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Bees
{
    public partial class AddAddressDialog : Form
    {
        private InformationDTO information = null;

        public AddAddressDialog(InformationDTO information)
        {
            this.information = information;
            InitializeComponent();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            this.information.AddAddress(new Address(aor1TextBox.Text,
                aor2TextBox.Text, aor3TextBox.Text,
                astrTextBox.Text, actyTextBox.Text,
                acnyTextBox.Text));
            this.Close();
        }
    }
}