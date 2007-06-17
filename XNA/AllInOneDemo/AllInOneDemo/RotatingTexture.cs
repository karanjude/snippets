using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework;

namespace MyGame
{
    public class RotatingTexture
    {
        Texture2D texture;
        Vector2 origin, screenPosition;
        float rotatingAngle = 0f;
        Vector2 position;

        public void Load(GraphicsDevice device,ContentManager content, string fileName)
        {
             texture = content.Load<Texture2D>(fileName);
             origin = new Vector2(texture.Width / 2, texture.Height / 2);
             this.position = origin; 
            screenPosition = new Vector2(device.Viewport.Width / 2, device.Viewport.Height / 2);
        }

        public BoundingBox BoundingRectangle
        {
            get {
                return new BoundingBox(new Vector3(position.X, position.Y, 0), new Vector3(position.X + texture.Width, position.Y + texture.Height, 0));
            }
        }

        public void Update(float delta)
        {
            rotatingAngle += delta;
            rotatingAngle = rotatingAngle % (MathHelper.Pi * 2);
        }

        public void Draw(SpriteBatch batch)
        {
            batch.Draw(texture, screenPosition, null, Color.White, rotatingAngle, origin, 1,SpriteEffects.None,0);
        }
    }
}
