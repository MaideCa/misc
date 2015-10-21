using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RLE
{
	class Program
	{
		static string RLEncode(string Input)
		{
			if (Input.Length <= 2)
			{
				return Input;
			}

			StringBuilder EncodedOutput = new StringBuilder();
			char LastChar = Input[0];
			int SequenceCount = 1;

			int Length = Input.Length;
			for (int i = 1; i < Length; ++i)
			{
				char CurrentChar = Input[i];
				if (CurrentChar != LastChar)
				{
					if (SequenceCount > 1)
					{
						EncodedOutput.Append(SequenceCount);
					}

					EncodedOutput.Append(LastChar);
					LastChar = CurrentChar;
					SequenceCount = 1;
				}
				else
				{
					++SequenceCount;
				}

			}

			if (SequenceCount > 1)
			{
				EncodedOutput.Append(SequenceCount);
			}
			EncodedOutput.Append(LastChar);

			return EncodedOutput.ToString();
		}

		static string RLDecode(string Input)
		{
			StringBuilder DecodedOutput = new StringBuilder();
			StringBuilder IntBuilder = new StringBuilder();

			int Length = Input.Length;
			for (int i = 0; i < Length; ++i)
			{
				char CurrentChar = Input[i];
				if (Char.IsDigit(CurrentChar))
				{
					IntBuilder.Append(CurrentChar);
				}
				else
				{
					if (IntBuilder.Length == 0)
					{
						DecodedOutput.Append(CurrentChar);
					}
					else
					{
						DecodedOutput.Append(CurrentChar, Int32.Parse(IntBuilder.ToString()));
						IntBuilder.Clear();
					}
				}
			}

			return DecodedOutput.ToString();
		}

		static void Main(string[] args)
		{
			string[] StringArray = { "aaaabbcccddefg", "aaaaaaaaaaaaaaaaaaaaaa", "abababababababab", "ccbbaa", "abc", "a" };

			foreach (string StringToEncode in StringArray)
			{
				string EncodedString = RLEncode(StringToEncode);
				string DecodedString = RLDecode(EncodedString);
				Debug.Assert(StringToEncode == DecodedString);

				Console.WriteLine("{0} is {1} encoded.", DecodedString, EncodedString);
			}
		}
	}
}
