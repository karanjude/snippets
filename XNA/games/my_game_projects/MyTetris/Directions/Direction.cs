using System;
using System.Collections.Generic;
using System.Text;

namespace MyTetris
{
    public interface Direction
    {
        Direction Rotate(Block block);
    }
}
