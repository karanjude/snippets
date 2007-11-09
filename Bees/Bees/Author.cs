using System;
using System.Collections.Generic;
using System.Text;

namespace Bees
{
    public class Author
    {
        public const String TAG = "_auth"; 

        private String name = null;

        private String title = "";
        private String firstName = "";
        private String lastName = "";
        private String middleName = "";

        public Author(String name)
        {
            this.name = name.Trim();
            String[] parts =  name.Split(new char[] { ' ' });
            if (parts.Length == 4)
            {
                title = trim(parts[0]);
                firstName = trim(parts[1]);
                middleName = trim(parts[2]);
                 lastName = trim(parts[3]);
            }
            else if (parts.Length == 3)
            {
                firstName = trim(parts[0]);
                middleName = trim(parts[1]);
                lastName = trim(parts[2]);
            }
            else if (parts.Length == 2)
            {
                firstName = trim(parts[0]);
                lastName = trim(parts[1]);
            }
        }

        private string trim(string p)
        {
            p = p.Trim();
            if (p.EndsWith(",") || p.EndsWith(";"))
                p = p.Substring(0, p.Length - 1);
            return p;
        }

        public String AuthorString {
            get
            {
                String result = String.Join("*", new String[]{
                    this.LastName,
                    this.Initials,
                    this.FirstName + " " + this.MiddleName
                });
                if (result.Length > 0)
                    return "*" + result;
                return result;
            }
        }

        public String FirstName
        {
            get
            {
                return  this.firstName;
            }
        }


        public String LastName
        {
            get
            {
                return this.lastName;
            }
        }

        public String MiddleName
        {
            get
            {
                return this.middleName;
            }
        }

        public String Title
        {
            get
            {
                return this.title;
            }
        }

        public String Name
        {
            get
            {
                return this.name;
            }
        }

        public String Initials
        {
            get
            {
                List<String> parts = new List<string>();
                if (firstName != String.Empty)
                    parts.Add(firstName.Substring(0,1));
                if (middleName != String.Empty)
                    parts.Add(middleName.Substring(0, 1));
                return String.Join(".", parts.ToArray()) + ".";
            }
        }

        public Author AuthorObject
        {

            get
            {
                return this;
            }
        }

        public override int GetHashCode()
        {
            return this.Name.GetHashCode();
        }
    }
}
