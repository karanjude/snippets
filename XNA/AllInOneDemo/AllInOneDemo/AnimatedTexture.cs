using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;

namespace MyGame
{
    public class AnimatedTexture
    {
        public void Load(GraphicsDevice device, ContentManager content, string fileName, int frames)
        {
            _totalFrames = frames;
            _texture = content.Load<Texture2D>(fileName);
        }

        public void DrawFrame(SpriteBatch spriteBatch, int currentFrame, Vector2 vector)
        {
            int width = _texture.Width / _totalFrames;
            Rectangle rectangle = new Rectangle(width * currentFrame,0, width, _texture.Height);
            spriteBatch.Draw(_texture, vector, rectangle, Color.White);
        }

        private int _totalFrames;
        private Texture2D _texture;
    }
}
