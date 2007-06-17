using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace MyTetris
{
    public class Left : Movement
    {
         public Left(Block block, GameField gameField)
            : base(block, gameField)
        {
        }

        protected override bool canMove(Square square, int units)
        {
            return gameField.CanMove(this, getNewPositionFor(square, units));
        }

        protected override Microsoft.Xna.Framework.Vector2 getNewPositionFor(Square square, int units)
        {
            return Vector2.Subtract(square.Position, new Vector2(units, 0));
        }

        public override bool GoneOutOfBounds(Vector2 position)
        {
            return (position.X < gameField.Bounds.X);
        }

        public override bool BlockPresent(Vector2 position)
        {
            int x = (int)((position.X) / gameField.BLOCK_SIZE);
            int y = (int)((position.Y) / gameField.BLOCK_SIZE);
            return gameField.IsBlockPresent(x, y);
        }
    }
}
