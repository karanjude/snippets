using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using Bees;

namespace SimpleTests
{
    [TestFixture]
    public class Class1
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

    }
}
