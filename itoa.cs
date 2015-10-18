using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace itoa
{
	class Program
	{
		public static string IToA(int InNumber, int Base)
		{
			if (Base < 2)
				throw new ArgumentOutOfRangeException("Base must be greater than 1");
			
			if (Base > 62)
				throw new ArgumentOutOfRangeException("Base must be lower than 63");

			if (InNumber == 0)
				return "0";

			bool bIsNegative = InNumber < 0;
			if (bIsNegative)
			{
				InNumber *= -1;
			}

			StringBuilder Output = new StringBuilder();
			while (InNumber > 0)
			{
				int Value = InNumber % Base;
				InNumber /= Base;

				char OutputChar;
				if (Value >= 36)
				{
					OutputChar = 'A';
					Value -= 36;
				}
				else if (Value >= 10)
				{
					OutputChar = 'a';
					Value -= 10;
				}
				else
				{
					OutputChar = '0';
				}

				OutputChar += (char)Value;
				Output.Append(OutputChar);
			}

			if (bIsNegative)
				Output.Append('-');

			return new string(Output.ToString().Reverse().ToArray());
		}

		static void Main(string[] args)
		{
			int[] Numbers = { 0, 1, 2, 10, 11, 25, 100, 31337, 987654321 };
			int[] Bases = { 2, 8, 10, 16, 36, 62 };

			foreach (int Number in Numbers)
			{
				foreach (int Base in Bases)
				{
					Console.WriteLine("{0} in base {1} is '{2}'", Number, Base, IToA(Number, Base));
				}
			}
		}
	}
}
