using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using cstarwrapper01;

namespace squaredisplay
{
    public partial class Form1 : Form
    {

        txSquare square = null;

        txMapWrapper map  = null;
        txAstarWrapper astar = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Graphics dc = e
            //square = new txSquare(10, 10, this.Width, this.Height);
            square = new txSquare();
            // this need a open file loader.
            square.LoadMap("E:\\gitProject\\A-Star-Algorithm\\maps\\m03.txt");
            square.SetWindows(this.Width, this.Height);

            txMap cmap = square.Gmap;
            map = new txMapWrapper(cmap.M, cmap.N, cmap.Map);

            astar = new txAstarWrapper(map);
            astar.CalculatePath();

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            square.SetDc(e.Graphics);
            base.OnPaint(e);
            Graphics dc = e.Graphics;

            square.Draw();

            int[] path = astar.GetPath();
            int[] accessed = astar.GetAccessed();
            
            //square.DrawAccessedCell(accessed);

            square.DrawPath(path);

        }
    }
}
