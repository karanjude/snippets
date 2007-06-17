using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MyTetris
{
    public class LBlock : Block
    {
        public LBlock(GameField gameField, Texture2D backgroundTexture, Vector2 origin, Direction direction)
            : base(gameField,
            backgroundTexture, origin, direction)
        { }

        public override void RotateTo(North north)
        {
            square2.Position = Vector2.Add(square1.Position, new Vector2(0, backgroundTexture.Height));
            square3.Position = Vector2.Add(square1.Position, new Vector2(0, 2 * backgroundTexture.Height));
            square4.Position = Vector2.Add(square3.Position, new Vector2(backgroundTexture.Width, 0));
        }

        public override void RotateTo(East east)
        {
            square2.Position = Vector2.Add(square3.Position, new Vector2(backgroundTexture.Width, 0));
            square1.Position = Vector2.Add(square3.Position, new Vector2(2 * backgroundTexture.Width, 0));
            square4.Position = Vector2.Add(square3.Position, new Vector2(0, backgroundTexture.Height));
         }

        public override void RotateTo(West west)
        {
            square2.Position = Vector2.Add(square3.Position, new Vector2(-backgroundTexture.Width, 0));
            square1.Position = Vector2.Add(square3.Position, new Vector2(-2 * backgroundTexture.Width, 0));
            square4.Position = Vector2.Add(square3.Position, new Vector2(0, -backgroundTexture.Height));
        }

        public override void RotateTo(South south)
        {
            square2.Position = Vector2.Add(square3.Position, new Vector2(0, backgroundTexture.Height));
            square1.Position = Vector2.Add(square3.Position, new Vector2(0, 2 * backgroundTexture.Width));
            square4.Position = Vector2.Add(square3.Position, new Vector2(-backgroundTexture.Width, 0));
        }
    }
}
