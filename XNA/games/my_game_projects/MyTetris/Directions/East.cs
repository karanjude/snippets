using System;
using System.Collections.Generic;
using System.Text;

namespace MyTetris
{
    public class East : Direction
    {
        #region Direction Members

        public Direction Rotate(Block block)
        {
            block.RotateTo(this);
            return Directions.SOUTH;
        }

        #endregion
    }
}
