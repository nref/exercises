using System;
using System.Linq;
using System.Collections.Generic;

new Solution().solution(5, 3);
new Solution().solution(3, 3);
new Solution().solution(1, 4);

class Solution
{
    public String solution(int A, int B)
    {

        // Algo: find difference of A and B
        // The greater will have that many doubles
        // e.g. 5 - 3 = 2 => aabaab
        // e.g. 3 - 5 = -2 => abbaba 

        double diffd = (A - B) / (double)2;
        int diff = (int)Math.Round(diffd, 0);

        int aDoubles = diff > 0 ? Math.Abs(diff) : 0;
        int bDoubles = diff < 0 ? Math.Abs(diff) : 0;

        var result = new List<char>();

        int i = 0;
        bool lastWasA = Math.Sign(diff) <= 0;

        while (result.Count < A + B)
        {
            i++;

            if (aDoubles > 0 && !lastWasA)
            {
                result.AddRange(new[] { 'a', 'a' });
                aDoubles -= 1;
                lastWasA = true;
                continue;
            }

            if (bDoubles > 0 && lastWasA)
            {
                result.AddRange(new[] { 'b', 'b' });
                bDoubles -= 1;
                lastWasA = false;
                continue;
            }

            result.Add(lastWasA ? 'b' : 'a');
            lastWasA = !lastWasA;
        }

        string str = string.Join("", result);
        Console.WriteLine(str);

        return str;
    }
}

