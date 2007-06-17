using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Snake.Helper;

namespace Snake
{
    public class Mushroom : Sprite
    {
        private static Texture2D mushroom;
        private Vector2 point;
        private SnakeField snakeField;
        private GameObject type;

        public Mushroom(SnakeField snakeField, SpriteBatch spriteBatch,Vector2 point)
            : base(spriteBatch)
        {
            this.point = point;
            this.type = GameObject.MUSHROOM;
            this.snakeField = snakeField;
        }

        public override void Draw()
        {
            snakeField.MarkGameObject(point, this.type);
            spriteBatch.Draw(mushroom, point, Color.White);
        }

        public static void LoadContent(Texture2D mushroomTexture)
        {
            mushroom = mushroomTexture;
        }
    }
}
