using PlantumLib.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlantumLib.Controllers
{
    public class PlantManager
    {
        //evenetually will be replaced when system recognizes plants
        public void WaterPlant(string CameraName)
        {
            APIHandler.WaterPlants(CameraName); 
        }
    }
}
