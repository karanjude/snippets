using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MyTetris
{
    public class SBlock : Block
    {
        public SBlock(GameField gameField,Texture2D backgroundTexture, Vector2 origin, Direction direction)
            : base(gameField,
            backgroundTexture, origin, direction)
        { }

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

        private void rotateNorthSouth()
        {
            square2.Position = Vector2.Add(square1.Position, new Vector2(backgroundTexture.Width, 0));
            square3.Position = Vector2.Add(square1.Position, new Vector2(0, backgroundTexture.Height));
            square4.Position = Vector2.Add(square3.Position, new Vector2(-backgroundTexture.Width, 0));
        }

        private void rotateEastWest()
        {
            square1.Position = Vector2.Add(square2.Position, new Vector2(0, -backgroundTexture.Height));
            square3.Position = Vector2.Add(square2.Position, new Vector2(backgroundTexture.Width, 0));
            square4.Position = Vector2.Add(square3.Position, new Vector2(0, backgroundTexture.Height));
        }
    }
}
