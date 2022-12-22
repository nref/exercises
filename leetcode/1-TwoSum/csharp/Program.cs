public static class Log
{
    public static void WriteLine(this object o) => Console.WriteLine($"{o}");
    public static void WriteCollection<T>(this IEnumerable<T> t) => string.Join(", ", t).WriteLine();
}

public class Solution
{
    public int[] TwoSum(int[] nums, int target)
    {
        return Slow(nums, target);
    }

    public int[] Fast(int[] nums, int target)
    {
        // key: sum. value: indices producing the sum
        Dictionary<int, (int, int)> map = new();

        return null;
    }

    public int[] Slow(int[] nums, int target)
    {
        // Sort the arrays: n lg n
        // Then use the n^2 solution:
        //   two indices, i, j, nested for loops

        // Pair each index with its value so we can sort while keeping the original index 
        List<(int, int)> pairs = nums.Select((num, i) => (num, i)).ToList();
        pairs.Sort((pair1, pair2) => pair1.Item1.CompareTo(pair2.Item1));

        // Since the pairs are sorted, we have a chance of doing better than n^2
        foreach (int i in Enumerable.Range(0, pairs.Count))
        {
            foreach (int j in Enumerable.Range(0, pairs.Count))
            {
                if (i == j)
                {
                    continue;
                }

                if (pairs[i].Item1 + pairs[j].Item1 == target)
                {
                    return new[] { pairs[i].Item2, pairs[j].Item2 };
                }
            }
        }


        throw new ArgumentException($"Liar! No solution for {nums[0]} and {nums[1]}.");
    }
}
