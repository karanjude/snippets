using System;
using System.Collections.Generic;
using System.Text;

namespace MyTetris
{
    public class West : Direction
    {
        #region Direction Members

        public Direction Rotate(Block block)
        {
            block.RotateTo(this);
            return Directions.NORTH;
        }

        #endregion
    }
}
