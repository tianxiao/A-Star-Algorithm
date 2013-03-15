using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace squaredisplay
{

    class txSquare
    {
        int m;
        int n;
        Graphics dc;


        txMap gmap;

        internal txMap Gmap
        {
            get { return gmap; }
        }

        int wwidth;
        int wheight;

        Color[] distancecolorrange;

        Color[] entitiecolors;

        // When you want plot something you need a framework
        // this framework need oringin and the scale factor(x, y);
        double scale = 1;

        int startx;
        int starty;

        // unit square 
        int cubel;

        public txSquare(int l, int h, int ww, int wh)
        {
            m = l;
            n = h;
            //this.dc = dc;
            wwidth = ww;
            wheight = wh;

            gmap = new txMap(l, h);

            InitializeD();

        }

        private void InitializeD()
        {
            SetUnitSquareL();

            InitializeDistanceColorRange();
        }

        public txSquare()
        { }

        public void LoadMap(string filename)
        {
            gmap = new txMap(filename);
            m = gmap.M;
            n = gmap.N;
        }

        public void InitializeDistanceColorRange()
        { 
            int nrange = 10;
            distancecolorrange = new Color[nrange];
            distancecolorrange[0] = Color.Fuchsia;
            distancecolorrange[1] = Color.Gainsboro;
            distancecolorrange[2] = Color.GhostWhite;
            distancecolorrange[3] = Color.Gold;
            distancecolorrange[4] = Color.Goldenrod;
            distancecolorrange[5] = Color.Gray;
            distancecolorrange[6] = Color.GreenYellow;
            distancecolorrange[7] = Color.Honeydew;
            distancecolorrange[8] = Color.HotPink;
            distancecolorrange[9] = Color.IndianRed;

            entitiecolors = new Color[(int)txEntitiesC.NUM_OF_COLORS_IN_E];
            entitiecolors[(int)txEntitiesC.ROAD] = Color.Cornsilk;
            entitiecolors[(int)txEntitiesC.START] = Color.Red;
            entitiecolors[(int)txEntitiesC.GOAL] = Color.Green;
            entitiecolors[(int)txEntitiesC.OBSTACLE] = Color.Brown;
            entitiecolors[(int)txEntitiesC.SHOTEST_PATH] = Color.BlueViolet;
            entitiecolors[(int)txEntitiesC.ACCESSED_CELL] = Color.Cyan;
        }

        public void SetDc(Graphics dc)
        {
            this.dc = dc;
        }

        public void SetWindows(int w, int h)
        {
            wwidth = w;
            wheight = h;

            InitializeD();
        }

        public void Scale(double s)
        {
            scale = s; 
        }

        public void Draw() 
        {
            DrawWareFrame();

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    
                    DrawShell(i, j, entitiecolors[gmap.GetIJValue(i, j)]);
                }
            }
        }

        public void DrawPath(int[] path)
        {
            for (int i = 0; i < path.Length; i+=2)
            {
                DrawShell(path[i], path[i + 1], entitiecolors[(int)txEntitiesC.SHOTEST_PATH]);
            }
        }

        public void DrawAccessedCell(int[] accessed)
        {
            for (int i = 0; i < accessed.Length; i+=2)
            {
                DrawShell(accessed[i], accessed[i + 1], entitiecolors[(int)txEntitiesC.ACCESSED_CELL]);
            }
        }

        private void DrawShell(int i, int j, Color c)
        {
            Point p1 = new Point();
            p1.X = startx + j * cubel;
            p1.Y = starty + i * cubel;

            Rectangle r = new Rectangle();
            r.X = p1.X+1;
            r.Y = p1.Y+1;
            r.Width = cubel-1;
            r.Height = cubel-1;
            
            Brush b = new SolidBrush(c);
            //dc.FillRectangle(p,r);
            dc.FillRectangle(b, r);
        }

        private void SetUnitSquareL()
        {
            int cubew = (int)(wwidth * scale / m);
            int cubeh = (int)(wheight * scale / n);
            cubel = cubew;
            if (cubel > cubeh)
            {
                cubel = cubeh;
            }
        }

        private void DrawWareFrame()
        {
            startx = (int)(wwidth*0.05);
            starty = (int)(wheight*0.05);

            int wl = cubel*(m);
            int wh = cubel*n;

            Pen graypen = new Pen(Color.Gray,1);
            
            for (int i = 0; i <= m; i++)
            { 
                
                dc.DrawLine(graypen, new Point(startx, starty+i*cubel), new Point(startx+wh, starty+i*cubel));
            }

            for (int i = 0; i <= n; i++)
            {
                dc.DrawLine(graypen, new Point(startx + i * cubel, starty), new Point(startx + i * cubel, starty + wl));
            }
        }
    }
}
