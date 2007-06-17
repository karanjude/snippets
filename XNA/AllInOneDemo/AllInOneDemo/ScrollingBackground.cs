using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;


namespace MyGame
{
    public class ScrollingBackground
    {
        Texture2D texture;
        int screenHeight, screenWidth;
        Vector2 origin, screenPosition , offset;

        public void Load(GraphicsDevice device,ContentManager content, string fileName)
        {
             texture = content.Load<Texture2D>(fileName);
             screenHeight = device.Viewport.Height;
             screenWidth = device.Viewport.Width;
             origin = new Vector2(0, 0);
             screenPosition = new Vector2(0, 0 );
             offset = new Vector2(texture.Width, 0 );
        }

        public void Update(float delta)
        {
            screenPosition.X += delta;
            screenPosition.X = screenPosition.X % texture.Width;
        }

        public void Draw(SpriteBatch batch)
        {
            //if(screenPosition.X < screenWidth)
                batch.Draw(texture, screenPosition, null, Color.White, 0, origin, 1, SpriteEffects.None, 0f);
            batch.Draw(texture, screenPosition - offset, null, Color.White, 0, origin, 1, SpriteEffects.None, 0f);
                   
        }
    }
}
