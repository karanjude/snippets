using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using Bees;
using System.Text.RegularExpressions;
using System.Globalization;

namespace Bees
{
    [TestFixture]
    public class SimpleTests
    {
        [Test]
        public void testFirstMiddleAndLastName()
        {
            String name = "Jeffrey M. Weinberg";
            Author author = new Author(name);
            Assert.AreEqual("Jeffrey", author.FirstName);
            Assert.AreEqual("M", author.MiddleName);
            Assert.AreEqual("Weinberg", author.LastName);
        }

        [Test]
        public void testTitleFirstMiddleLastName()
        {
            String name = "Dr. Jeffrey M. Weinberg";
            Author author = new Author(name);
            Assert.AreEqual("Jeffrey", author.FirstName);
            Assert.AreEqual("M", author.MiddleName);
            Assert.AreEqual("Weinberg", author.LastName);
            Assert.AreEqual("Dr", author.Title);
            Assert.AreEqual("J.M.", author.Initials);
        }

        [Test]
        public void TestInformationDTOIty()
        {
            InformationDTO information = new InformationDTO();
            String value = "ar";
            information.Ity = value;
            Assert.AreEqual(value.ToUpper(), information.Ity);
        }

        [Test]
        public void TestInformationDTOItyValidation()
        {
            InformationDTO information = new InformationDTO();
            String value = "yz";
            information.Ity = value;
            Assert.AreEqual(String.Empty, information.Ity);
            information = new InformationDTO();
            value = "ar";
            information.Ity = value;
            Assert.AreEqual(value.ToUpper(), information.Ity);
            information = new InformationDTO();
            value = "ER";
            information.Ity = value;
            Assert.AreEqual(value, information.Ity);
            information = new InformationDTO();
            value = "CP";
            information.Ity = value;
            Assert.AreEqual(value, information.Ity);

        }

        [Test]
        public void Test_Apdat_month_space_day_comma_space_year_date_time_conversion()
        {
            String datetime = "June 8, 2000";
            Assert.AreEqual("20000608", new DateTimeConverter().convert(datetime));
        }

        [Test]
        public void Test_Apdat_month_space_day_comma_space_year_date_time_conversion_for_InformationDTO()
        {
            String datetime = "June 8, 2000";
            InformationDTO information = new InformationDTO();
            information.Apdat = datetime;
            Assert.AreEqual("20000608", information.Apdat);
        }

        [Test]
        public void Test_Apdat_day_slash_month_slash_year_date_time_conversion()
        {
            String datetime = "27/5/1999";
            Assert.AreEqual("19990527", new DateTimeConverter().convert(datetime));
            datetime = "27/5/99";
            Assert.AreEqual("19990527", new DateTimeConverter().convert(datetime));
            datetime = "27/5/07";
            Assert.AreEqual("20070527", new DateTimeConverter().convert(datetime));
        }

        [Test]
        public void Test_Apdat_day_slash_month_slash_year_date_time_conversion_for_InformationDTO()
        {
            String datetime = "27/5/1999";
            InformationDTO information = new InformationDTO();
            information.Apdat = datetime;
            Assert.AreEqual("19990527", information.Apdat);
            
            datetime = "27/5/99";
            information = new InformationDTO();
            information.Apdat = datetime;
            Assert.AreEqual("19990527", information.Apdat);

            datetime = "27/5/07";
            information = new InformationDTO();
            information.Apdat = datetime;
            Assert.AreEqual("20070527", information.Apdat);
        }

        [Test]
        public void Test_Apdat_date_conversion_for_non_supported_pattern()
        {
            String datetime = "June 8/ 2000";
            Assert.AreEqual("June 8/ 2000", new DateTimeConverter().convert(datetime));
        }

        [Test]
        public void Test_Apdat_date_conversion_for_non_supported_pattern_for_InformationDTO()
        {
            String datetime = "June 8/ 2000";
            InformationDTO information = new InformationDTO();
            information.Apdat = datetime;
            Assert.AreEqual("June 8/ 2000", information.Apdat);
        }

        [Test]
        public void Test_Aptxt_every_first_letter_is_captial()
        {
            String datetime = "april 2000";
            InformationDTO information = new InformationDTO();
            information.Aptxt = datetime;
            Assert.AreEqual("April 2000", information.Aptxt);

            datetime = "April 2000";
            information = new InformationDTO();
            information.Aptxt = datetime;
            Assert.AreEqual("April 2000", information.Aptxt);
            
        }
      
    }
}
