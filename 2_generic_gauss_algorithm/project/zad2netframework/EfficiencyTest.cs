using System;
using System.Diagnostics;

namespace zad2netframework
{
    public class EfficiencyTest
    {
        private int dimensions;
        private double [] time;
        private double [] diff;

        public EfficiencyTest(int dim)
        {
            this.dimensions = dim;
            time = new double[ 9 ];
            diff = new double[ 9 ];
        }

        public String Run()
        {
            Console.WriteLine("Test: " + dimensions);
            RunFloat(GaussType.Basic);
            RunFloat(GaussType.Part);
            RunFloat(GaussType.Full);

            //Console.WriteLine("Double");
            RunDouble(GaussType.Basic);
            RunDouble(GaussType.Part);
            RunDouble(GaussType.Full);

            //Console.WriteLine("Fraction");
            //RunFraction(GaussType.Basic);
            //RunFraction(GaussType.Part);
            //RunFraction(GaussType.Full);

            return String.Join(";", time) + ";" + String.Join(";", diff);
        }


        public void RunFloat( GaussType gausstype )
        {
            MyMatrix<float> matrix = new MyMatrix<float>(dimensions);
            Random r = new Random(1234);
            float num;
            for (int y = 0; y < dimensions; y++)
            {
                matrix.SetVectorB(y, 0);
                num = (float)(short)r.Next() / 32768;
                matrix.SetVectorX(y, num);
                for (int x = 0; x < dimensions; x++)
                {
                    num = (float)(short)r.Next() / 32768;
                    matrix.SetMatrixA(x, y, num);
                }
            }
            matrix.Multiplication();

            Stopwatch sw = new Stopwatch();

            switch (gausstype)
            {
                case GaussType.Basic:
                    //Console.WriteLine("  bez wyboru elementu podstawowego");
                    sw.Start();
                      matrix.CalculateG();
                    sw.Stop();
                    time[0] = sw.Elapsed.TotalMilliseconds;
                    diff[0] = matrix.CalculateDiff();
                    break;
                case GaussType.Part:
                    //Console.WriteLine("  z czesciowym wyborem elementu podstawowego");
                    sw.Start();
                      matrix.CalculateGP();
                    sw.Stop();
                    time[1] = sw.Elapsed.TotalMilliseconds;
                    diff[1] = matrix.CalculateDiff();
                    break;
                case GaussType.Full:
                    //Console.WriteLine("  z pelnym wyborem elementu podstawowego");
                    sw.Start();
                      matrix.CalculateGF();
                    sw.Stop();
                    time[2] = sw.Elapsed.TotalMilliseconds;
                    diff[2] = matrix.CalculateDiff();
                    break;
            }

            sw.Stop();
            //Console.WriteLine("    Czas: {0}", sw.Elapsed.TotalMilliseconds);
            //Console.WriteLine("    błąd: " + matrix.CalculateDiff());
        }
        public void RunDouble(GaussType gausstype)
        {
            MyMatrix<double> matrix = new MyMatrix<double>(dimensions);
            Random r = new Random(1234);
            float num;
            for (int y = 0; y < dimensions; y++)
            {
                matrix.SetVectorB(y, 0);
                num = (float)(short)r.Next() / 32768;
                matrix.SetVectorX(y, num);
                for (int x = 0; x < dimensions; x++)
                {
                    num = (float)(short)r.Next() / 32768;
                    matrix.SetMatrixA(x, y, num);
                }
            }
            matrix.Multiplication();

            Stopwatch sw = new Stopwatch();

            switch (gausstype)
            {
                case GaussType.Basic:
                    //Console.WriteLine("  bez wyboru elementu podstawowego");
                    sw.Start();
                    matrix.CalculateG();
                    sw.Stop();
                    time[3] = sw.Elapsed.TotalMilliseconds;
                    diff[3] = matrix.CalculateDiff();
                    break;
                case GaussType.Part:
                    //Console.WriteLine("  z czesciowym wyborem elementu podstawowego");
                    sw.Start();
                    matrix.CalculateGP();
                    sw.Stop();
                    time[4] = sw.Elapsed.TotalMilliseconds;
                    diff[4] = matrix.CalculateDiff();
                    break;
                case GaussType.Full:
                    //Console.WriteLine("  z pelnym wyborem elementu podstawowego");
                    sw.Start();
                    matrix.CalculateGF();
                    sw.Stop();
                    time[5] = sw.Elapsed.TotalMilliseconds;
                    diff[5] = matrix.CalculateDiff();
                    break;
            }
            //Console.WriteLine("    Czas: {0}", sw.Elapsed);
            //Console.WriteLine("    błąd: " + matrix.CalculateDiff());
        }
        public void RunFraction(GaussType gausstype)
        {
            MyMatrix<Fraction> matrix = new MyMatrix<Fraction>(dimensions);
            Random r = new Random(1234);
            float num;
            for (int y = 0; y < dimensions; y++)
            {
                matrix.SetVectorB(y, 0);
                num = (float)(short)r.Next() / 32768;
                matrix.SetVectorX(y, num);
                for (int x = 0; x < dimensions; x++)
                {
                    num = (float)(short)r.Next() / 32768;
                    matrix.SetMatrixA(x, y, num);
                }
            }
            matrix.Multiplication();

            Stopwatch sw = new Stopwatch();

            switch (gausstype)
            {
                case GaussType.Basic:
                    //Console.WriteLine("  bez wyboru elementu podstawowego");
                    sw.Start();
                    matrix.CalculateG();
                    sw.Stop();
                    time[6] = sw.Elapsed.TotalMilliseconds;
                    diff[6] = matrix.CalculateDiff();
                    break;
                case GaussType.Part:
                    //Console.WriteLine("  z czesciowym wyborem elementu podstawowego");
                    sw.Start();
                    matrix.CalculateGP();
                    sw.Stop();
                    time[7] = sw.Elapsed.TotalMilliseconds;
                    diff[7] = matrix.CalculateDiff();
                    break;
                case GaussType.Full:
                    //Console.WriteLine("  z pelnym wyborem elementu podstawowego");
                    sw.Start();
                    matrix.CalculateGF();
                    sw.Stop();
                    time[8] = sw.Elapsed.TotalMilliseconds;
                    diff[8] = matrix.CalculateDiff();
                    break;
            }
            //Console.WriteLine("    Czas: {0}", sw.Elapsed);
            //Console.WriteLine("    błąd: " + matrix.CalculateDiff());
        }

    }
}
