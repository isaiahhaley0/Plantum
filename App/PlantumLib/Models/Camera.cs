using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlantumLib.Models
{
    public class Camera
    {
        public string Name { get; set; }
        public int PhotoCount { get; set; }

        public string ImagePath { get; set; }
        public double Max_Brightness { get; set; }
        public double Min_Brightness { get; set;}
        public double Last_Brightness { get; set; }

        public double PCT_Brightness { get
            {
                var prg = Last_Brightness - Min_Brightness;
                var range = Max_Brightness - Min_Brightness;
                return Math.Round((prg / range * 100),2);

            } }

        public double Hours_Of_Light { get;set; }

    }
}
