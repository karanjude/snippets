using System;
using System.Collections.Generic;
using System.Text;

namespace Bees
{
    public class Reference
    {
        Dictionary<String, String> map = new Dictionary<string, string>();

        public const String TAG = "_rfseq";

        public void setTag(String key, String value)
        {
            map.Add("_" + key, value);
        }

        public String Value(string tag)
        {
            String r = map[tag];
            if (r == null)
                return String.Empty;
            r = r.Trim();
            return r;
        }
    }
}
