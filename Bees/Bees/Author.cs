using System;
using System.Collections.Generic;
using System.Text;

namespace Bees
{
    public class Author
    {
        public const String TAG = "_auth"; 

        private String name = null;

        private bool parsed = false;
        private String title = "";
        private String firstName = "";
        private String lastName = "";
        private String middleName = "";
        private String email = String.Empty;

        public Author(String name)
        {
            this.name = name.Trim();
            String[] parts =  name.Split(new char[] { ' ' });
            parseParts(parts);
        }

        private void parseParts(String[] parts)
        {
            Parse(new PartSegment(TitleFirstNameMiddleNameLastNameEmail), parts);
            Parse(new PartSegment(TitleFirstNameMiddleNameLastName),parts);
            Parse(new PartSegment(FirstNameMiddleNameLastName),parts);
            Parse(new PartSegment(FirstNameLastName),parts);
        }

        private delegate bool PartSegment(String[] parts);


        private void Parse(PartSegment partSegment,String[] parts)
        {
            if (!parsed)
                this.parsed = partSegment(parts);
        }

        private bool FirstNameLastName(String[] parts)
        {
            if (parts.Length == 2)
            {
                firstName = trim(parts[0]);
                lastName = trim(parts[1]);
                return true;
            }
            return false;
        }

        private bool FirstNameMiddleNameLastName(String[] parts)
        {
            if (parts.Length == 3)
            {
                firstName = trim(parts[0]);
                middleName = trim(parts[1]);
                lastName = trim(parts[2]);
                return true;
            }
            return false;
        }

        private bool TitleFirstNameMiddleNameLastName(String[] parts)
        {
            if (parts.Length == 4)
            {
                title = trim(parts[0]);
                firstName = trim(parts[1]);
                middleName = trim(parts[2]);
                lastName = trim(parts[3]);
                return true;
            }
            return false;
        }

        private bool TitleFirstNameMiddleNameLastNameEmail(String[] parts)
        {
            if (parts.Length == 5)
            {
                title = trim(parts[0]);
                firstName = trim(parts[1]);
                middleName = trim(parts[2]);
                lastName = trim(parts[3]);
                this.email = trim(parts[4]);
                return true;
            }
            return false;
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
                List<String> parts = new List<string>();
                parts.Add(this.LastName);
                if(String.Empty != this.Initials)
                    parts.Add(this.Initials);
                parts.Add(this.FirstName);
                if (String.Empty != this.Title)
                    parts.Add(this.Title);
                if (String.Empty != this.email)
                    parts.Add(this.email);
                String result = String.Join("*", parts.ToArray());
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
                if (middleName != String.Empty)
                {
                    parts.Add(middleName.Substring(0, 1));
                    return String.Join(".", parts.ToArray()) + ".";
                }
                return String.Join(".", parts.ToArray());
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
