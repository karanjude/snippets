using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace Bees
{
    public class DateTimeConverter
    {
        private String[] months = {
            "january",
            "february",
            "march",
            "april",
            "may",
            "june",
            "july",
            "august",
            "september",
            "october",
            "november",
            "december"
        };

        public String convert(string datetime)
        {
            PatternApplier applier = new PatternApplier(datetime);
            applier.apply(MonthSpaceDayCommaSpaceYearPattern(datetime));
            applier.apply(DaySlashMonthSlashYearPattern(datetime));
            return applier.result();
        }


        private String DaySlashMonthSlashYearPattern(string datetime)
        {
            Regex daySlashMonthSlashYearPattern = new Regex(@"(?<day>\d+)[/](?<month>\d+)[/](?<year>\d+)", RegexOptions.IgnoreCase);
            Match daySlashMonthSlashYearMatch = daySlashMonthSlashYearPattern.Match(datetime);
            if (daySlashMonthSlashYearMatch.Success)
            {
                String day = daySlashMonthSlashYearMatch.Groups["day"].Value;
                String month = daySlashMonthSlashYearMatch.Groups["month"].Value;
                String year = daySlashMonthSlashYearMatch.Groups["year"].Value;
                return PadWithDigits(year) + padWithZero(month) + padWithZero(day);
            }
            return String.Empty;
        }

        private string PadWithDigits(string year)
        {
            if (year.Length == 2)
            {
                int value = Int32.Parse(year);
                if (value < 50)
                    return (2000 + value).ToString();
                return (1900 + value).ToString();
            }
            return year;

        }

        private string MonthSpaceDayCommaSpaceYearPattern(string datetime)
        {
            Regex monthDayCommaOneSpaceYearPattern = new Regex(@"(?<month>\w+)\s(?<day>\d+)(,)*\s*(?<year>\d+)", RegexOptions.IgnoreCase);
            Match monthDayCommaOneSpaceYearPatternMatch = monthDayCommaOneSpaceYearPattern.Match(datetime);
            if (monthDayCommaOneSpaceYearPatternMatch.Success)
            {
                string month = monthDayCommaOneSpaceYearPatternMatch.Groups["month"].Value;
                string day = monthDayCommaOneSpaceYearPatternMatch.Groups["day"].Value;
                string year = monthDayCommaOneSpaceYearPatternMatch.Groups["year"].Value;
                return year + padWithZero(numeric(month)) + padWithZero(day);
            }
            return String.Empty;
        }

        private string padWithZero(string value)
        {
            if (value.Length == 1)
            {
                return 0.ToString() + value;
            }
            return value;
        }

        private string numeric(string month)
        {
            return (Array.IndexOf<String>(months, month.ToLower())+1).ToString();
        }
    }
}
