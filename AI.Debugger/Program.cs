using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AI.Core;

namespace AI.Debugger
{
	class Program
	{
		static void Main(string[] args)
		{
            AI.Core.LinearAlgebra.MatrixTester.Test();
            Console.WriteLine("Test complete.");
		}
	}
}
