using System.Text;

class Node
{
    public bool IsWaterTower;
    public bool IsVillage;
    public int Height;
    public bool Visited;
    public bool Active;

    public List<Node> Neighbors = new();

    public Node(int height)
    {
        Height = height;
    }

    public override string ToString() => this switch
    {
        _ when IsWaterTower => $"[{Height}]",
        _ when IsVillage => $"({Height})",
        _ => $" {Height} ",
    } + (!Active && Visited ? "*" : "") + (Active ? "<" : "");
}

struct Index
{
    public int Row;
    public int Column;

    public Index(int row, int column)
    {
        Row = row;
        Column = column;
    }
}

class Grid
{
    public Node[,] Nodes;
    public int Width;
    public int Height;

    Node Village1;
    Node Village2;

    public Grid(int[] fields, int width, int height, Index village1, Index village2)
    {
        Nodes = new Node[width, height];
        Width = width;
        Height = height;

        foreach (int row in Enumerable.Range(0, height))
        {
            foreach (int col in Enumerable.Range(0, width))
            {
                Nodes[row, col] = new Node(fields[row * width + col]);
            }
        }

        // Construct edges
        foreach (int row in Enumerable.Range(0, width))
        {
            foreach (int col in Enumerable.Range(0, height))
            {
                if (row > 0)
                {
                    Nodes[row, col].Neighbors.Add(Nodes[row - 1, col]);
                }
                if (row < height - 1)
                {
                    Nodes[row, col].Neighbors.Add(Nodes[row + 1, col]);
                }
                if (col > 0)
                {
                    Nodes[row, col].Neighbors.Add(Nodes[row, col - 1]);
                }
                if (col < width - 1)
                {
                    Nodes[row, col].Neighbors.Add(Nodes[row, col + 1]);
                }
            }
        }

        Village1 = Nodes[village1.Row, village1.Column];
        Village2 = Nodes[village2.Row, village2.Column];

        Village1.IsVillage = true;
        Village2.IsVillage = true;
    }


    // Return zero or more candidate water towers locations, sorted by suitability
    public List<Node> ChooseWaterTower()
    {
        // Start from village, always stay level or go up
        List<Node> fromVillage1 = new();
        List<Node> fromVillage2 = new();

        ChooseWaterTowerRecurse(Village1, fromVillage1);
        ResetVisited();

        ChooseWaterTowerRecurse(Village2, fromVillage2);
        ResetVisited();

        Log.Write("Candidates from village 1: ");
        fromVillage1.WriteCollection();

        Log.Write("Candidates from village 2: ");
        fromVillage2.WriteCollection();

        // Choose candidates reachable from both villages
        HashSet<Node> fromBothVillages = new HashSet<Node>(fromVillage1);
        fromBothVillages.IntersectWith(new HashSet<Node>(fromVillage2));

        // Sort by height 
        List<Node> results = fromBothVillages.ToList();
        results.Sort((n1, n2) => n1.Height.CompareTo(n2.Height));

        Log.Write("Candidates from both villages: ");
        fromBothVillages.WriteCollection();

        return results;
    }

    void ResetVisited()
    {
        foreach (var node in Nodes) { node.Visited = false; }
    }

    void ChooseWaterTowerRecurse(Node here, List<Node> maxima)
    {
        here.Visited = true;

        // Purely for debugging
        here.Active = true;
        this.WriteLine();
        here.Active = false;
        Console.ReadLine();

        if (here.Neighbors.Where(nbr => !nbr.Visited).All(nbr => nbr.Height < here.Height))
        {
            maxima.Add(here);
            return;
        }

        foreach (var nbr in here.Neighbors.Where(nbr => !nbr.Visited && nbr.Height >= here.Height))
        {
            ChooseWaterTowerRecurse(nbr, maxima);
        }
    }

    public override string ToString()
    {
        const int maxWidth = 6;
        var sb = new StringBuilder();

        foreach (int row in Enumerable.Range(0, Width))
        {
            foreach (int column in Enumerable.Range(0, Height))
            {
                var node = $"{Nodes[row, column]}";
                sb.Append(node);
                sb.Append(new string(' ', maxWidth - node.Length));
            }

            sb.AppendLine();
        }

        return sb.ToString();
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        string matrix =
            @"1  1  1  1
              1  6  7  4
              1  5  1  3
              1  4  1  2 ";

        Grid grid = GetGrid(matrix, new Index(3, 1), new Index(3, 3));

        List<Node> towers = grid.ChooseWaterTower();

        if (towers.Any())
        {
            towers.First().IsWaterTower = true;
        }

        "Result:".WriteLine();
        grid.WriteLine();
    }

    private static Grid GetGrid(string input, Index village1, Index village2)
    {
        // Parse input into grid
        string[] fields = input.Split(new[] { ' ', '\r', '\t' }, StringSplitOptions.RemoveEmptyEntries);

        // m = input width, n = input height
        int m = Array.FindIndex(fields, field => field.Contains("\n"));
        int n = input.Count(c => c == '\n') + 1;

        int[] intFields = fields
            .Where(field => !field.Contains("\n"))
            .Select(int.Parse)
            .ToArray();

        return new Grid(intFields, m, n, village1, village2);
    }
}

public static class Log
{
    public static void Write(this object o) => Console.Write($"{o}");
    public static void WriteLine(this object o) => Console.WriteLine($"{o}");
    public static void WriteCollection<T>(this IEnumerable<T> e) => WriteLine((object)string.Join(", ", e));
}
