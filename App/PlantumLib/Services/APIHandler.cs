using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using PlantumLib.Models;
using System.Net;
using System.Net.Http;

namespace PlantumLib.Services
{
    public static class APIHandler
    {

        private static string baseEndpoint = "http://192.168.0.47:5000";

        public static async Task<List<string>> GetCams()
        {

            string EndPoint = baseEndpoint + "/camera_info";
            HttpClient client = new HttpClient();
            try
            {
                using HttpResponseMessage response = await client.GetAsync(EndPoint);
                //        response.EnsureSuccessStatusCode();
                string responseBody = await response.Content.ReadAsStringAsync();
                // Above three lines can be replaced with new helper method below
                // string responseBody = await client.GetStringAsync(uri);
                var st_l = JsonSerializer.Deserialize<CameraList>(responseBody);
                Console.WriteLine(responseBody);
                return st_l.Cameras.ToList();
            }
            catch (HttpRequestException e)
            {
                Console.WriteLine("\nException Caught!");
                Console.WriteLine("Message :{0} ", e.Message);
            }
            return new List<string> { };
        }

        public static async Task<Camera> GetCamera(string CamName)
        {
            string EndPoint = baseEndpoint + "/camera_info?Name=" + CamName;
            HttpClient client = new HttpClient();

            try
            {
                using HttpResponseMessage response = await client.GetAsync(EndPoint);
                //        response.EnsureSuccessStatusCode();
                string responseBody = await response.Content.ReadAsStringAsync();
                var cam = JsonSerializer.Deserialize<Camera>(responseBody);
                       cam.ImagePath = await GetImage(CamName);
                return cam;
            }
            catch (HttpRequestException e)
            {

            }
            return null;
        }

        public static async Task<string> GetImage(string camname)
        {
            string EndPoint = baseEndpoint + "/photo?name=" + camname;
            string apiUrl = "http://192.168.0.47:5000/photo?name=cam1";


            string ImageDataUrl;
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    // Replace "flask_api_endpoint" with the actual endpoint of the Flask API serving the image


                    HttpResponseMessage response = await client.GetAsync(EndPoint);

                    if (response.IsSuccessStatusCode)
                    {
                        byte[] imageBytes = await response.Content.ReadAsByteArrayAsync();
                        ImageDataUrl = $"data:image/jpeg;base64,{Convert.ToBase64String(imageBytes)}";
                        return ImageDataUrl;
                    }
                    else
                    {
                        Console.WriteLine($"Error: {response.StatusCode}");
                        // Handle other status codes as needed
                    }
                }
                catch (HttpRequestException ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                    // Handle the exception appropriately
                }
            }

            return null;


        }

        internal static async Task WaterPlants(string cameraName)
        {
            string EndPoint = baseEndpoint + "/water";
            Plant plant = new Plant()
            {
                CameraName = cameraName,
                Name = cameraName,
                LastWaterDate = DateTime.Now,
            };
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    var serialziedContent = JsonSerializer.Serialize(plant);
                    var content = new StringContent(serialziedContent, Encoding.UTF8, "application/json");
            
                    await client.PostAsync(EndPoint,content);
                }
                catch (HttpRequestException ex)
                {
                    Console.WriteLine(ex.Message );
                }
                }
        }
    }
}
