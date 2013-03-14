using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace squaredisplay
{

    enum txEntitiesC
    {
        ROAD,
        START,
        GOAL,
        OBSTACLE,
        NUM_OF_COLORS_IN_E
    };

    class txMap
    {
        int[] map;

        int m;

        public int M
        {
            get { return m; }
        }
        int n;

        public int N
        {
            get { return n; }
        }

        public int GetIJValue(int i, int j)
        {
            return map[i * n + j];
        }

        // create a empty map
        public txMap(int m, int n)
        {
            this.m = m;
            this.n = n;

            map = new int[m * n];

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    map[i * m + j] = 0;
                }
            }
        }

        public txMap(string filename)
        {
            m = -1;
            n = -1;
            try
            {
                StreamReader sr = new StreamReader(filename);
                string line;

                int rows = 0;

                while ((line = sr.ReadLine()) != null)
                {
                    string[] sl = line.Split();
                    if (sl.Length == 2)
                    {
                        if (sl[0] == "TABLEROW")
                        {
                            m = int.Parse(sl[1]);
                        }

                        if (sl[0] == "TABLECOLUMN")
                        {
                            n = int.Parse(sl[1]);
                        }
                    }
                    else
                    {
                        if (m == -1 || n == -1)
                        { 
                            // assert!
                        }

                        if (sl.Length == n)
                        {
                            for (int i = 0; i < n; i++)
                            {
                                map[rows * n + i] = int.Parse(sl[i]);
                            }
                            
                            rows++;
                        }
                        else
                        { 
                            // assert!
                        }
                    }

                    
                }
            }
            catch (Exception e)
            {
                ;
            }
        }
    }
}
