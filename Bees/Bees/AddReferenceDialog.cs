using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Bees
{
    public partial class AddReferenceDialog : Form
    {
        private InformationDTO information = null;

        public AddReferenceDialog(InformationDTO information)
        {
            this.information = information;
            InitializeComponent();
        }

        public AddReferenceDialog()
        {
            this.information = new InformationDTO();
            InitializeComponent();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            information.AddReference(createReference());
            this.Close();
        }

        private Reference createReference()
        {
            Reference reference = new Reference();
            reference.setTag(rfseq.Text, rfseqTextBox.Text);
            reference.setTag(rfaut.Text, rfautTextBox.Text);
            reference.setTag(rfeti.Text, rfetiTextBox.Text);
            reference.setTag(rfnet.Text, rfnetTextBox.Text);
            reference.setTag(rfsti.Text, rfstiTextBox.Text);
            reference.setTag(rfpy1.Text, rfpy1TextBox.Text);
            reference.setTag(rfpy2.Text, rfpy2TextBox.Text);
            reference.setTag(rfvn1.Text, rfvn1TextBox.Text);
            reference.setTag(rfvn2.Text, rfvn2TextBox.Text);
            reference.setTag(rfvt.Text, rfvtTextBox.Text);
            reference.setTag(rfis1.Text, rfisTextBox.Text);
            reference.setTag(rfis2.Text, rfis2TextBox.Text);
            reference.setTag(rfit.Text, rfitTextBox.Text);
            reference.setTag(rfpag.Text, rfpagTextBox.Text);
            reference.setTag(rfsit.Text, rfsitTextBox.Text);
            reference.setTag(rfurl.Text, rfurlTextBox.Text);
            reference.setTag(rffrt.Text, rffrtTextBox.Text);
            reference.setTag(rftxt.Text, rftxtTextBox.Text);
            return reference;
        }
    }
}