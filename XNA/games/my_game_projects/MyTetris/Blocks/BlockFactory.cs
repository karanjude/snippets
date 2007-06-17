using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MyTetris.Blocks
{
    public class BlockFactory
    {

        private Random _random = new Random();
        private IList<createBlockDelegate> _blocks = new List<createBlockDelegate>();
        private delegate Block createBlockDelegate();
        private Texture2D squareTexture;
        private GameField gameField;

        public BlockFactory(Texture2D squareTexture,GameField gameField)
        {
            this.squareTexture = squareTexture;
            this.gameField = gameField;

            _blocks.Add(createSquareBlock);
            _blocks.Add(createLineBlock);
            _blocks.Add(createJBlock);
            _blocks.Add(createLBlock);
            _blocks.Add(createTBlock);
            _blocks.Add(createZBlock);
            _blocks.Add(createSBlock);
      
        }

        private Block createSquareBlock()
        {
            return new SquareBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }
        private Block createLineBlock()
        {
            return new LineBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }
        private Block createJBlock()
        {
            return new JBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }
        private Block createLBlock()
        {
            return new LBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }
        private Block createTBlock()
        {
            return new TBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }
        private Block createZBlock()
        {
            return new ZBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }

        private Block createSBlock()
        {
            return new SBlock(gameField, squareTexture, new Vector2(100, 0), Directions.NORTH);
        }


        public Block CreateBlock(){
            int number = _random.Next(0, 7);
            return _blocks[number]();
        }
    }
}
