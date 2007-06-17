using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace MyTetris
{
    public class Down : Movement
    {
        public Down(Block block, GameField gameField)
            : base(block, gameField)
        {
        }

        protected override bool canMove(Square square, int units)
        {
            return gameField.CanMove(this, getNewPositionFor(square, units));
        }

        protected override Vector2 getNewPositionFor(Square square,int units)
        {
            return   Vector2.Add(square.Position, new Vector2(0, units ));
        }

        public override bool GoneOutOfBounds(Vector2 position)
        {
            return (position.Y >= gameField.Bounds.Height - gameField.BLOCK_SIZE);
        }

        public override bool BlockPresent(Vector2 position)
        {
            int x = (int)(position.X / gameField.BLOCK_SIZE);
            int y = (int)((position.Y + gameField.BLOCK_SIZE) / gameField.BLOCK_SIZE);
            return gameField.IsBlockPresent(x, y);
        }
    }
}
