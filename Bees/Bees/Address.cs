using System;
using System.Collections.Generic;
using System.Text;

namespace Bees
{
    public class Address
    {
        public const String TAG = "_adseq";

        private String aor1 = null;
        private String aor2 = null;
        private String aor3 = null;
        private String astr = null;
        private String acty = null;
        private String acny = null;
        

        public Address(String aor1, String aor2,
            String aor3, String astr, String acty,
            String acny)
        {
            this.aor1 = aor1;
            this.aor2 = aor2;
            this.aor3 = aor3;
            this.astr = astr;
            this.acty = acty;
            this.acny = acny;

        }

        private String address = null;

        public String Value
        {
            get
            {
                return this.ToString();
            }
            set
            {
                this.address = value;
            }
        }

        private Address d;

        public Address AddressObject
        {
            get
            {
                return this;
            }
  
        }

        public override string ToString()
        {
            if (this.address != null)
                return this.address;

            StringBuilder result = new StringBuilder();
            result.Append(line("aor1", aor1, true));
            result.Append(line("aor2", aor2, true));
            result.Append(line("aor3", aor3, true));
            result.Append(line("astr", astr, true));
            result.Append(line("acty", acty, true));
            result.Append(line("acny", acny, true));
            this.address =  result.ToString();
            return this.address;
        }

        private String line(string tag, string value,bool newline)
        {
            value = value.Trim();
            if (String.Empty == value)
                return value;
            StringBuilder builder = new StringBuilder();
            builder.Append("_" + tag).Append(" ");
            builder.Append(value);
            if(newline)
                builder.Append(Environment.NewLine);
            return builder.ToString();
        }

        public override bool Equals(object obj)
        {
            return (obj as Address).ToString() == this.ToString();
        }

    }
}
