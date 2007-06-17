using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace MyTetris
{
    public class Right : Movement
    {
         public Right(Block block, GameField gameField)
            : base(block, gameField)
        {
        }

        protected override bool canMove(Square square, int units)
        {
            return gameField.CanMove(this, getNewPositionFor(square, units));
        }

        public override bool GoneOutOfBounds(Vector2 position)
        {
            return (position.X > gameField.Bounds.Width - gameField.BLOCK_SIZE);
        }

        public override bool BlockPresent(Vector2 position)
        {
            int x = (int)((position.X) / gameField.BLOCK_SIZE);
            int y = (int)((position.Y) / gameField.BLOCK_SIZE);
            return gameField.IsBlockPresent(x, y);
        }

        protected override Vector2 getNewPositionFor(Square square, int units)
        {
            return Vector2.Add(square.Position, new Vector2(units, 0));
        }
    }
}
