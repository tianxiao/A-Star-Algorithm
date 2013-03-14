using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace squaredisplay
{
    public partial class Form1 : Form
    {

        txSquare square = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Graphics dc = e
            square = new txSquare(10, 10, this.Width, this.Height);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            square.SetDc(e.Graphics);
            base.OnPaint(e);
            Graphics dc = e.Graphics;
            int w = this.Width;
            int h = this.Height;

            square.Draw();

        }
    }
}
