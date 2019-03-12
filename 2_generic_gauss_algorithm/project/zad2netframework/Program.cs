using System;
using System.IO;
using System.Text;

namespace zad2netframework
{
    public enum GaussType { Basic, Part, Full };

    class Program
    {
        static void Main()
        {
            StringBuilder header = new StringBuilder();
            header.AppendLine("Time;;;;;;;;;Difference");
            header.AppendLine("Float;;;Double;;;Fraction;;;Float;;;Double;;;Fraction;;");
            header.AppendLine("G;PG;FG;G;PG;FG;G;PG;FG;G;PG;FG;G;PG;FG;G;PG;FG");
            File.WriteAllText( "test.csv" , header.ToString());

            for (int index = 5; index < 501; index+=5)
            {
                StringBuilder content = new StringBuilder();
                EfficiencyTest etest = new EfficiencyTest(index);
                content.AppendLine(etest.Run());
                File.AppendAllText("test.csv", content.ToString() );
            }

            Console.WriteLine("Ready!");
        }
    }
}
