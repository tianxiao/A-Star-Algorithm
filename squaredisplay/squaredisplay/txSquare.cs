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
        }

        public void SetDc(Graphics dc)
        {
            this.dc = dc;
        }

        public void SetWindows(int w, int h)
        {
            wwidth = w;
            wheight = h;
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

        private void DrawShell(int i, int j, Color c)
        {
            Point p1 = new Point();
            p1.X = startx + i * cubel;
            p1.Y = starty + j * cubel;
            Point p2 = new Point();
            p2.X = p1.X + cubel;
            p2.Y = p1.Y + cubel;

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

            int wl = cubel*m;
            int wh = cubel*n;

            Pen graypen = new Pen(Color.Gray,1);
            
            for (int i = 0; i <= m; i++)
            { 
                
                dc.DrawLine(graypen, new Point(startx, starty+i*cubel), new Point(startx+wl, starty+i*cubel));
            }

            for (int i = 0; i <= n; i++)
            {
                dc.DrawLine(graypen, new Point(startx + i * cubel, starty), new Point(startx + i * cubel, starty + wh));
            }
        }
    }
}
