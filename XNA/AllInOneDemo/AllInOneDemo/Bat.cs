using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;

namespace MyGame
{
    public class Bat
    {
        private Texture2D texture;
        private Vector2 position;
        private GraphicsDevice device;

        public void Load(GraphicsDevice device,ContentManager content, string fileName,Vector2 origin)
        {
            this.device = device;
            position = origin;
            texture = content.Load<Texture2D>(fileName);
        }

        public void MoveUp()
        {
            position.Y = position.Y - 2;
            if (position.Y < 0)
                position.Y = device.Viewport.Height + position.Y - texture.Height;
        }

        public void MoveDown()
        {
            position.Y = position.Y + 2;
            position.Y = (position.Y % device.Viewport.Height);
        }

        public BoundingBox BoundingRectangle
        {
            get {
                return new BoundingBox(new Vector3(position.X, position.Y, 0), new Vector3(position.X + texture.Width, position.Y + texture.Height, 0));
            }
        }

        public void Draw(SpriteBatch batch)
        {
            batch.Draw(texture, position, Color.White);
        }

    }
}
