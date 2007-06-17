using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MyTetris
{
    public class TBlock : Block
    {
        public TBlock(GameField gameField,Texture2D backgroundTexture, Vector2 origin, Direction direction)
            : base(gameField,
            backgroundTexture, origin, direction)
        { }

        public override void RotateTo(North north)
        {
            square2.Position = Vector2.Add(square1.Position, new Vector2( backgroundTexture.Width,0));
            square3.Position = Vector2.Add(square1.Position, new Vector2(2 * backgroundTexture.Width, 0));
            square4.Position = Vector2.Add(square2.Position, new Vector2(0,backgroundTexture.Height));
        }

        public override void RotateTo(East east)
        {
            square1.Position = Vector2.Add(square2.Position, new Vector2(0,-backgroundTexture.Height));
            square3.Position = Vector2.Add(square2.Position, new Vector2(0,backgroundTexture.Height));
            square4.Position = Vector2.Add(square2.Position, new Vector2(-backgroundTexture.Width,0));
        }

        public override void RotateTo(West west)
        {
            square1.Position = Vector2.Add(square2.Position, new Vector2(0, backgroundTexture.Height));
            square3.Position = Vector2.Add(square2.Position, new Vector2(0,-backgroundTexture.Height));
            square4.Position = Vector2.Add(square2.Position, new Vector2(backgroundTexture.Width,0));
        }

        public override void RotateTo(South south)
        {
            square1.Position = Vector2.Add(square2.Position, new Vector2(backgroundTexture.Width, 0));
            square3.Position = Vector2.Add(square2.Position, new Vector2(-backgroundTexture.Width, 0));
            square4.Position = Vector2.Add(square2.Position, new Vector2(0, -backgroundTexture.Height));
        }
    }
}
