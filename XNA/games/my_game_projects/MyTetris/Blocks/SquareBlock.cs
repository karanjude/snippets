using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace MyTetris
{
    public class SquareBlock : Block
    {

        public SquareBlock(GameField gameField, Texture2D backgroundTexture, Vector2 origin, Direction direction): base(
            gameField, backgroundTexture,origin,direction)
        {}

            
        public override void RotateTo(North north)
        {
            square2.Position = Vector2.Add(position, new Vector2(backgroundTexture.Width,0));
            square3.Position = Vector2.Add(position, new Vector2(0,backgroundTexture.Height));
            square4.Position = Vector2.Add(position, new Vector2(backgroundTexture.Width,backgroundTexture.Height));
        }

        public override void RotateTo(East east)
        {
        }

        public override void RotateTo(West west)
        {
        }

        public override void RotateTo(South south)
        {
        }
    }
}
