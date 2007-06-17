using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MyTetris
{
    public class LineBlock : Block
    {
        public LineBlock(GameField gameField, Texture2D backgroundTexture, Vector2 origin, Direction direction)
            : base(gameField,
            backgroundTexture,origin,direction)
        {}

        public override void RotateTo(North north)
        {
            rotateNorthSouth();
        }


        public override void RotateTo(East east)
        {
            rotateEastWest();
        }

        public override void RotateTo(West west)
        {
            rotateEastWest(); 
        }

        public override void RotateTo(South south)
        {
            rotateNorthSouth();
        }

        private void rotateNorthSouth(){
            square2.Position = Vector2.Add(square1.Position, new Vector2(0, backgroundTexture.Height));
            square3.Position = Vector2.Add(square1.Position, new Vector2(0, 2 * backgroundTexture.Height));
            square4.Position = Vector2.Add(square1.Position, new Vector2(0, 3 * backgroundTexture.Height));
        }

        private void rotateEastWest()
        {
            square2.Position = Vector2.Add(square1.Position, new Vector2(backgroundTexture.Width, 0));
            square3.Position = Vector2.Add(square1.Position, new Vector2(2 * backgroundTexture.Width, 0));
            square4.Position = Vector2.Add(square1.Position, new Vector2(3 * backgroundTexture.Width, 0));
        }
    }
}
