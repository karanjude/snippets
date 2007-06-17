using System;
using System.Collections.Generic;
using System.Text;

namespace MyTetris
{
    public class Directions
    {
        public static Direction NORTH = new North();
        public static Direction SOUTH = new South();
        public static Direction EAST = new East();
        public static Direction WEST = new West();
    }
}
