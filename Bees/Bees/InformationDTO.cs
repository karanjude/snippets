using System;
using System.Collections.Generic;
using System.Collections;

using System.Text;
using System.IO;
using System.Globalization;

namespace Bees
{
    public class InformationDTO
    {
        Dictionary<String, String> map = new Dictionary<String, String>();
        String[] ITY_VALUES = {"AR","CP", "ER",
                                    "ED",
                                    "LE",
                                    "NO",
                                    "RE",
                                    "SH",
                                    "CR",
                                    "PA"
                                     };

     
        public void setTag(string key, string value)
        {
            if (!key.StartsWith("_"))
                key = "_" + key;
            if (!map.ContainsKey(key))
                map.Add(key, validate(key,upper(key, clean(value.Trim()))));
        }

        private delegate String ValidateDelegate(String key, String value);

        Dictionary<String, ValidateDelegate> keyValidatorMap = new Dictionary<string, ValidateDelegate>();

        public InformationDTO()
        {
            keyValidatorMap.Add(InformationDTO.ITY, ValidateITY);
            keyValidatorMap.Add(InformationDTO.APDAT, ValidateAPDAT);
            keyValidatorMap.Add(InformationDTO.APTXT, ValidateAPTXT);
        }

        private String ValidateAPTXT(String key, String value)
        {
            String[] strings = value.Split(new char[] { ' '});
            int i = 0;
            Array.ForEach<String>(strings, new System.Action<String>(delegate(String target)
            {
                strings[i++] = Char.ToUpper(target[0]) + target.Substring(1);
            }));
            return String.Join(" ", strings);
        }

        private String ValidateAPDAT(String key, String value)
        {
            return new DateTimeConverter().convert(value);
        }

        private String ValidateITY(String key, String value)
        {
            bool result = false;
            result = Array.Exists(ITY_VALUES, new Predicate<String>(delegate(String target)
            {
                return target == value;
            }));
            if (result == true)
                return value;
            return String.Empty;
            
        }

        private string validate(string key, string value)
        {
            if (keyValidatorMap.ContainsKey(key))
            {
                ValidateDelegate validator = keyValidatorMap[key];
                return validator(key, value);
            }
            return value;
        }

        private string upper(string key, string value)
        {
            if (InformationDTO.ITY == key)
                return value.ToUpper();
            return value;
        }



        String[] literals = new String[] { ";", ",", "." };

        private string clean(string value)
        {
            bool dirty = false;
            foreach (String ending in literals)
            {
                if (value.EndsWith(ending))
                {
                    dirty = true;
                    break;
                }
            }
            return cleanTheDirtyString(dirty, value);
            

        }

        private string cleanTheDirtyString(bool dirty, string value)
        {
            if (!dirty)
                return value;
            value = value.Substring(0, value.Length - 1);
            return value;
        }

        delegate void AuthorDelegate(StringBuilder builder, Author author);

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            buildLine(builder, "_ity", true);
            buildLine(builder, "_pii", false);
            buildLine(builder, "_pag", true);
            buildLine(builder, "_url", false);
            buildLine(builder, "_artnr", false);
            buildLine(builder, "_eti", true);
            buildLine(builder, "_net", false);
            buildLine(builder, "_apdat", false);
            buildLine(builder, "_aptxt", false);
            buildAuthors(builder);
            buildLine(builder, "_lit", true);
            buildLine(builder, "_lab", false);
            buildLine(builder, "_kwd", true);
            buildLine(builder, "_abs", false);
            buildLine(builder, "_ref", references.Count, false);
            buildAuthorInformation(builder, new AuthorDelegate(AuthorTitle));
            buildAuthorInformation(builder, new AuthorDelegate(AuthorInitials));
            buildAuthorInformation(builder, new AuthorDelegate(AuthorFamilyName));
            buildFirstAddress(builder);
            buildLine(builder, "_eml", false);
            buildLine(builder, "_doi", false);
            buildReferences(builder);
            return builder.ToString();
        }

        private void buildReferences(StringBuilder builder)
        {
            int i = 1;
            foreach (Reference reference in references)
            {
                builder.Append(Reference.TAG).Append(" ").Append(i.ToString()).Append(Environment.NewLine);
                buildReference(builder, reference);
                i++;
            }
            if (references.Count == 0)
            {
                builder.Append("_rffrt").Append(" ").Append(Environment.NewLine);
            }
        }

        private void buildReference(StringBuilder builder, Reference reference)
        {
            buildReferenceLine(builder, reference, "_rfaut", false);
            buildReferenceLine(builder, reference, "_rfeti", false);
            buildReferenceLine(builder, reference, "_rfnet", false);
            buildReferenceLine(builder, reference, "_rfsti", false);
            buildReferenceLine(builder, reference, "_rfpy1", false);
            buildReferenceLine(builder, reference, "_rfpy2", false);
            buildReferenceLine(builder, reference, "_rfvn1", false);
            buildReferenceLine(builder, reference, "_rfvn2", false);
            buildReferenceLine(builder, reference, "_rfvt", false);
            buildReferenceLine(builder, reference, "_rfis1", false);
            buildReferenceLine(builder, reference, "_rfis2", false);
            buildReferenceLine(builder, reference, "_rfit", false);
            buildReferenceLine(builder, reference, "_rfpag", false);
            buildReferenceLine(builder, reference, "_rfsit", false);
            buildReferenceLine(builder, reference, "_rfurl", false);
            buildReferenceLine(builder, reference, "_rftxt", false);
            buildReferenceLine(builder, reference, "_rffrt", true);
        }

        private void buildReferenceLine(StringBuilder builder, Reference reference, string tag, bool required)
        {
            if (reference.Value(tag) != String.Empty)
            {
                builder.Append(tag).Append(" ").Append(reference.Value(tag)).Append(Environment.NewLine);
            }
            else if (required)
            {
                builder.Append(tag).Append(" ").Append(Environment.NewLine);
            }
        }

        private void buildFirstAddress(StringBuilder builder)
        {
            if (addresses.Count > 0)
            {
                Address first = addresses[0];
                String result = first.ToString();
                result = result.Replace("_a", "_");
                builder.Append(result);
            }
        }

        private void AuthorFamilyName(StringBuilder builder, Author author)
        {
            if (author.LastName != String.Empty)
            {
                builder.Append("_fam ").Append(author.LastName);
            }
        }


        private void AuthorTitle(StringBuilder builder, Author author)
        {
            if (author.Title != String.Empty)
            {
                builder.Append("_tit ").Append(author.Title);
            }
        }

        private void AuthorInitials(StringBuilder builder, Author author)
        {
            if (author.Initials != String.Empty)
            {
                builder.Append("_ini ").Append(author.Initials);
            }
        }

        private void buildAuthorInformation(StringBuilder builder, AuthorDelegate authorDelegate)
        {
            if ((authors.Count > 0))
            {
                Author first = authors[0];
                authorDelegate(builder, first);
                builder.Append(Environment.NewLine);
            }

        }

        private void buildLine(StringBuilder builder, string tag, int value, bool required)
        {
            if (value > 0)
            {
                builder.Append(tag).Append(" ").Append(value.ToString()).Append(Environment.NewLine);
            }

        }

        private StringBuilder buildAuthors(StringBuilder builder)
        {
            int authorCount = authorAddressMap.Keys.Count;
            StringBuilder addressStringBuilder = new StringBuilder();
            int totalNumberOfAddresses = addresses.Count;
            int numberOfAddresses = 0;
            foreach (Author author in authorAddressMap.Keys)
            {
                authorLine(builder, author);
                numberOfAddresses = addressLine(addressStringBuilder, totalNumberOfAddresses, numberOfAddresses, author);
            }
            builder.Append(addressStringBuilder.ToString());
            return builder;
        }

        private int addressLine(StringBuilder addressStringBuilder, int totalNumberOfAddresses, int numberOfAddresses, Author author)
        {
            if (numberOfAddresses <= totalNumberOfAddresses)
            {
                foreach (Address address in authorAddressMap[author])
                {
                    numberOfAddresses++;
                    addressStringBuilder.Append(Address.TAG).Append(" ");
                    addressStringBuilder.Append(numberOfAddresses.ToString());
                    addressStringBuilder.Append(Environment.NewLine);
                    addressStringBuilder.Append(address.ToString());
                }
            }
            return numberOfAddresses;
        }

        private void authorLine(StringBuilder builder, Author author)
        {
            int linkCount = authorAddressMap[author].Count;
            builder.Append(Author.TAG).Append(" ");
            builder.Append(String.Join(",", range(1, linkCount)));
            builder.Append(author.AuthorString).Append(Environment.NewLine);
        }

        private string[] range(int initial, int final)
        {
            List<String> list = new List<string>();
            for (int i = initial; i <= final; i++)
            {
                list.Add(i.ToString());
            }
            return list.ToArray();

        }

        private StringBuilder buildLine(StringBuilder builder, string tag, bool required)
        {
            if (map.ContainsKey(tag))
            {
                String r = map[tag];
                if (r != null)
                {
                    r = r.Trim();
                    if (r != String.Empty)
                        builder.Append(tag).Append(" ").Append(r).Append(Environment.NewLine);
                    else if (required)
                        builder.Append(tag).Append(" ").Append(string.Empty).Append(Environment.NewLine);
                }
            }
            return builder;
        }

        private IList<Author> authors = new List<Author>();

        public IList<Author> Authors
        {
            get
            {
                if (authors.Count == 0)
                    return null;
                return authors;
            }
            set
            {
                ;
            }
        }

        public void AddAuthor(Author author)
        {
            authors.Add(author);
        }

        private IList<Address> addresses = new List<Address>();

        public void AddAddress(Address address)
        {
            addresses.Add(address);
        }

        private Address selectedAddress = null;

        public Address SelectedAddress
        {
            get
            {
                return this.selectedAddress;
            }
            set
            {
                this.selectedAddress = value;
            }
        }

        public IList<Address> Addresses
        {
            get
            {
                if (addresses.Count == 0)
                    return null;
                return addresses;
            }
        }

        Dictionary<Author, List<Address>> authorAddressMap = new Dictionary<Author, List<Address>>();

        public void Link(Author author, Address address)
        {
            if (!authorAddressMap.ContainsKey(author))
            {
                authorAddressMap.Add(author, new List<Address>());
            }
            if (!authorAddressMap[author].Contains(address))
                authorAddressMap[author].Add(address);
        }

        IList<Reference> references = new List<Reference>();

        public void AddReference(Reference reference)
        {
            references.Add(reference);
        }

        private const String ITY = "_ity";

        public String Ity
        {
            set
            {
                setTag(InformationDTO.ITY, value);
            }
            get
            {
                if (map.ContainsKey(InformationDTO.ITY))
                    return map[InformationDTO.ITY];
                return String.Empty;
            }
        }

        private const String APDAT = "_apdat";

        public String Apdat
        {
            set
            {
                setTag(InformationDTO.APDAT, value);
            }
            get
            {
                if (map.ContainsKey(InformationDTO.APDAT))
                    return map[InformationDTO.APDAT];
                return String.Empty;
            }
        }

        private const String APTXT = "_aptxt";

        public String Aptxt
        {
            set
            {
                setTag(InformationDTO.APTXT, value);
            }
            get
            {
                if (map.ContainsKey(InformationDTO.APTXT))
                    return map[InformationDTO.APTXT];
                return String.Empty;
            }
        }

    }
}
