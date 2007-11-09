using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using Bees;

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


    }
}
