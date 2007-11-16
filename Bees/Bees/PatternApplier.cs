using System;
using System.Collections.Generic;
using System.Text;

namespace Bees
{
    public class PatternApplier
    {
        private bool resolved = false;
        private StringBuilder builder = new StringBuilder();
        private String value = String.Empty;

        public PatternApplier(String value)
        {
            this.value = value;
        }

        public void apply(string value)
        {
            if (!resolved && (value != String.Empty))
            {
                if (this.value == value)
                    resolved = true;
                builder.Append(value);
            }
        }

        public string result()
        {
            String result =  builder.ToString();
            if (result == String.Empty)
               return this.value;
            return result;
        }
    }
}
