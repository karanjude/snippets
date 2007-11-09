using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Bees
{
    public partial class Step1 : Form
    {
        public Step1()
        {
            InitializeComponent();
        }

        
        private Step2 step2 = null;

        private void nextButton_Click(object sender, EventArgs e)
        {
            InformationDTO result = constructDTO();
            //MessageBox.Show(result.ToString());
            if (null == step2)
            {
                step2 = new Step2(this,result);
            }
            this.Hide();
            step2.Show();
        }

        private InformationDTO constructDTO()
        {
            InformationDTO information = new InformationDTO();
            information.setTag(ity.Text,ityTextBox.Text);
            information.setTag(pii.Text, piiTextBox.Text);
            information.setTag(pag.Text, pagTextBox.Text);
            information.setTag(url.Text, urlTextBox.Text);
            information.setTag(artnr.Text, artnrTextBox.Text);
            information.setTag(eti.Text, etiTextBox.Text);
            information.setTag(net.Text, netTextBox.Text);
            information.setTag(apdat.Text, apdatTextBox.Text);
            return information;
        }

        private void ityTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void Step1_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }
    }
}