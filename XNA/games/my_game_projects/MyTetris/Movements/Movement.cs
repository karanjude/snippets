using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MyTetris
{
    public abstract class Movement
    {
        protected Block block;
        protected GameField gameField;

        public Movement(Block block, GameField gameField)
        {
            this.block = block;
            this.gameField = gameField;
        }

        public virtual bool CanMove(int units){
            return canMove(block.Square1, units) &&
               canMove(block.Square2, units) &&
               canMove(block.Square3, units) &&
               canMove(block.Square4, units);
        }

        protected abstract Vector2 getNewPositionFor(Square square , int units);

        protected abstract bool canMove(Square square, int units);


        public abstract bool GoneOutOfBounds(Vector2 position);

        public abstract bool BlockPresent(Vector2 position);
    
        }
}
