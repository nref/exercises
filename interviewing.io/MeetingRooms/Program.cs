// Meetings: [[1,4], [2,5], [7,9]]
//
// 1-----4     7------9
//   2-----5
//
// Algorithm:
//
// Sort meetings by starting time
// find earliest and latest time e.g. from 1 to 9.
//
// Iterate each hour earliest to latest. 
// Each hour:
//   keep count of current rooms in use and max rooms ever in use.
//   decrement room count by number of meetings starting this hour.
//     we do this first because the interval is half-open e.g. [1,4],[4-5] do not conflict
//     update max rooms
//   add increment room count by number of meetings starting at this hour
//     update max rooms
// 
// Complexity: O(n) if we use a dictionary to store meetings
//
namespace Meetings;

public class Program
{
    class Meeting
    {
        public int Start;
        public int End;

        public Meeting() { }
        public Meeting(List<int> hours)
        {
            Start = hours.First();
            End = hours.Last();
        }

        public override string ToString() => $"{Start}-{End}";
    }

    class Scheduler
    {
        Dictionary<int, List<Meeting>> meetingsByStartHour = new();
        Dictionary<int, List<Meeting>> meetingsByEndHour = new();

        List<Meeting> meetings;

        public Scheduler(List<Meeting> meetings)
        {
            this.meetings = meetings;

            foreach (var meeting in meetings)
            {
                Console.WriteLine($"Meeting: {meeting}");
            }

            foreach (var meeting in meetings)
            {
                if (!meetingsByStartHour.TryGetValue(meeting.Start, out List<Meeting>? startingHour))
                {
                    meetingsByStartHour[meeting.Start] = new List<Meeting>();
                }

                if (!meetingsByEndHour.TryGetValue(meeting.End, out List<Meeting>? endingHour))
                {
                    meetingsByEndHour[meeting.End] = new List<Meeting>();
                }

                meetingsByStartHour[meeting.Start].Add(meeting);
                meetingsByEndHour[meeting.End].Add(meeting);
            }
        }

        private (int, int) GetSpan()
        {
            int earliest = meetings.Select(meeting => meeting.Start).Min();
            int latest = meetings.Select(meeting => meeting.End).Max();

            return (earliest, latest);
        }

        public int MaxRoomsNeeded()
        {
            int maxRooms = 0;
            int rooms = 0;

            (int earliest, int latest) = GetSpan();

            foreach (int hour in Enumerable.Range(earliest, latest))
            {
                if (meetingsByEndHour.TryGetValue(hour, out List<Meeting>? ending))
                {
                    rooms -= ending.Count;
                }

                if (meetingsByStartHour.TryGetValue(hour, out List<Meeting>? starting))
                {
                    rooms += starting.Count;
                    maxRooms = Math.Max(rooms, maxRooms);
                }
            }

            return maxRooms;
        }
    }

    public static void Main(string[] args)
    {
        List<List<int>> input = new()
        {
            new() { 1, 4 },
            new() { 2, 5 },
            new() { 7, 9 },
        };

        input.Sort((m1, m2) => m1.First().CompareTo(m2.First()));
        List<Meeting> meetings = input.Select(m => new Meeting(m)).ToList();

        int roomCount = new Scheduler(meetings).MaxRoomsNeeded();
        Console.WriteLine($"Rooms Needed: {roomCount}");
    }
}
