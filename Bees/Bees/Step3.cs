using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Bees
{
    public partial class Step3 : Form
    {
        private InformationDTO information = null;
        private Step2 step2 = null;

        public Step3(Step2 step2,InformationDTO information)
        {
            this.information = information;
            this.step2 = step2;
            InitializeComponent();
        }

        private void Step3_Load(object sender, EventArgs e)
        {
            
        }

        private void NextButton_Click(object sender, EventArgs e)
        {
            information.setTag(lit.Text, litTextBox.Text);
            information.setTag(lab.Text, labTextBox.Text);
            information.setTag(kwd.Text, kwdTextBox.Text);
            information.setTag(abs.Text, absTextBox.Text);
            information.setTag(refLabel.Text, refTextBox.Text);
            information.setTag(eml.Text, emlTextBox.Text);
            information.setTag(doi.Text, doiTextBox.Text);
            new DatFile(information).Show();
            
        }

        private void addReferenceButton_Click(object sender, EventArgs e)
        {
            new AddReferenceDialog(this.information).ShowDialog();

        }

        private void Step3_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void backButton_Click(object sender, EventArgs e)
        {
            this.Hide();
            step2.Show();
        }
    }
}