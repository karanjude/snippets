using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Bees
{
    public partial class DatFile : Form
    {
        public DatFile(InformationDTO information)
        {
            InitializeComponent();
            String dat = buildDat(information);
            datTextBox.Text = dat;
        }

        private string buildDat(InformationDTO information)
        {
            return information.ToString();
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            DialogResult result = saveFileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                using (TextWriter writer = File.CreateText(saveFileDialog.FileName))
                {
                    writer.Write(datTextBox.Text);
                    writer.Close();
                }
                
            }
        }
    }
}