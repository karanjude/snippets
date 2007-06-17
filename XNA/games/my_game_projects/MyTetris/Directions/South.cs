using System;
using System.Collections.Generic;
using System.Text;

namespace MyTetris
{
    public class South : Direction
    {
        #region Direction Members

        public Direction Rotate(Block block)
        {
            block.RotateTo(this);
            return Directions.WEST; ;
        }

        #endregion
    }
}
