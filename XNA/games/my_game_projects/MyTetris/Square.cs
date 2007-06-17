using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;


namespace MyTetris
{
    public class Square
    {
        private Texture2D backgroundTexture;
        private Vector2 position;

        public Square(Texture2D backgroundTexture, Vector2 origin)
        {
            this.backgroundTexture = backgroundTexture;
            this.position = origin;
        }

        public void MoveLeft(int units)
        {
            position.X = position.X - units;
        }

        public void MoveRight(int units)
        {
            position.X = position.X + units;
        }

        public void MoveDown(int units)
        {
            position.Y = position.Y + units;
        }

        public void MoveUp(int units)
        {
            position.Y = position.Y - units;
        }

        public Vector2 Position
        {
            get { return this.position;}
            set { position = value; }
        }

        public Texture2D Texture
        {
            get { return this.backgroundTexture; }
        }
    }
}
