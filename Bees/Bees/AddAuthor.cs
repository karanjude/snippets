using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Bees
{
    public partial class AddAuthor : Form
    {
        private InformationDTO information = null;

        public AddAuthor(InformationDTO information)
        {
            this.information = information;
            InitializeComponent();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            information.AddAuthor(new Author(authorNameTextBox.Text));
            this.Close();
        }
    }
}