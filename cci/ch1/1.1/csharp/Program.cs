using System.Diagnostics;

bool IsUniqueSlow(string s)
{
    foreach (int i in Enumerable.Range(0, s.Length))
    {
        foreach (int j in Enumerable.Range(0, s.Length))
        {
            if (i == j)
            {
                continue;
            }
            if (s[i] == s[j])
            {
                return false;
            }
        }
    }

    return true;
}

bool IsUniqueSorted(string s)
{
    List<char> sorted = s.ToList();
    sorted.Sort();

    foreach (int i in Enumerable.Range(0, s.Length - 1))
    {
        if (sorted[i] == sorted[i + 1])
        {
            return false;
        }
    }
    return true;
}

bool IsUniqueDictionary(string s)
{
    var d = new Dictionary<char, char>();

    foreach (char c in s)
    {
        if (d.ContainsKey(c))
        {
            return false;
        }
        d[c] = c;
    }
    return true;
}

Debug.Assert(IsUniqueSlow("qwer1234"));
Debug.Assert(!IsUniqueSlow("qwer1234q"));

Debug.Assert(IsUniqueSorted("qwer1234"));
Debug.Assert(!IsUniqueSorted("qwer1234q"));

Debug.Assert(IsUniqueDictionary("qwer1234"));
Debug.Assert(!IsUniqueDictionary("qwer1234q"));
