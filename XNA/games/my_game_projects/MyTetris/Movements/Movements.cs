using System;
using System.Collections.Generic;
using System.Text;

namespace MyTetris.Movements
{
    public class Movements
    {
        private Block block;
        private GameField gameField;

        public readonly Movement LEFT;
        public readonly Movement RIGHT;
        public readonly Movement DOWN;


        public Movements(Block block, GameField gameField)
        {
            this.block = block;
            this.gameField = gameField;

            LEFT = new Left(block, gameField);
            DOWN = new Down(block, gameField); 
            RIGHT = new Right(block, gameField);

        }
    }
}
