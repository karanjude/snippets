using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Storage;
using Microsoft.Xna.Framework.Content;

namespace MyGame
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    partial class Game1 : Microsoft.Xna.Framework.Game
    {
        int horizontalSpeed = 1;
        int verticalSpeed = 1;
        int spriteX = 0;
        int spriteY = 0;
        bool paused = false;
        bool pauseKeyDown = false;
        private GraphicsDeviceManager graphics;
        private ContentManager content;
        private Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch;
        private Microsoft.Xna.Framework.Graphics.SpriteBatch backgroundBatch;

        private Microsoft.Xna.Framework.Graphics.Texture2D spriteTexture;
        private AnimatedTexture animatedTexture;
        private ScrollingBackground scrollingBackground;
        private RotatingTexture rotatingTexture;
        private Bat batLeft;
        private Bat batRight;
        private Cube cube;
        private int currentFrame = 0;

         private void InitializeComponent()
        {
            this.graphics = new GraphicsDeviceManager(this);
            this.content = new ContentManager(Services);
            graphics.PreferredBackBufferWidth = 800;
            graphics.PreferredBackBufferWidth = 600;
            graphics.IsFullScreen = true;
          
        }

        protected override void Initialize()
        {
            base.Initialize();
            this.IsFixedTimeStep = true;
       
        }

             

        public Game1()
        {
            InitializeComponent();
        }
       
       

        protected override void  Update(GameTime gameTime)
       {
            checkKeys();
            if (!paused)
            {
                // The time since Update was called last
                float elapsed = (float)gameTime.ElapsedGameTime.TotalSeconds;

                currentFrame++;
                currentFrame = currentFrame % 6;
                // TODO: Add your game logic here
                scrollingBackground.Update(elapsed * 100);
                UpdateSprite();
                KeyboardState keyboardState = Keyboard.GetState();
                UpdateLeftBat(keyboardState);
                UpdateRightBat(keyboardState);
                rotatingTexture.Update(elapsed);

                // Let the GameComponents update
                base.Update(gameTime);
            }
        }

        private void UpdateLeftBat(KeyboardState keyBoardState)
        {
            if (keyBoardState.IsKeyDown(Keys.A))
                batLeft.MoveUp();
            else if (keyBoardState.IsKeyDown(Keys.S))
                batLeft.MoveDown();
        }

        private void UpdateRightBat(KeyboardState keyBoardState)
        {
            if (keyBoardState.IsKeyDown(Keys.K))
                batRight.MoveUp();
            else if (keyBoardState.IsKeyDown(Keys.L))
                batRight.MoveDown();
        }


        void checkKeys()
        {
            KeyboardState keyboardState = Keyboard.GetState();
            if (keyboardState.IsKeyDown(Keys.P))
            {
                pauseKeyDown = true;
            }
            if (keyboardState.IsKeyDown(Keys.Escape))
            {
                Exit();
            }
            else if (pauseKeyDown)
            {
                pauseKeyDown = false;
                paused = !paused;
            }
        }

        void UpdateSprite()
        {
            spriteX += horizontalSpeed;
            spriteY += verticalSpeed;

            int MAXX = Window.ClientBounds.Right - spriteTexture.Width;
            int MINX = 0;
            int MAXY = Window.ClientBounds.Bottom - spriteTexture.Height;
            int MINY = 0;

            BoundingBox b = new BoundingBox(new Vector3(spriteX, spriteY, 0), new Vector3(spriteX + spriteTexture.Width, spriteY + spriteTexture.Height, 0));
            if (b.Intersects(batLeft.BoundingRectangle))
            {
                horizontalSpeed *= -1;
                spriteX = (int) batLeft.BoundingRectangle.Max.X;
            }
            else if (b.Intersects(batRight.BoundingRectangle))
            {
                horizontalSpeed *= -1;
            }

            if (b.Intersects(rotatingTexture.BoundingRectangle))
            {
                //horizontalSpeed *= -1;
            }

            if (spriteX > MAXX)
            {
                horizontalSpeed *= -1;
                spriteX = MAXX;
            }
            else if (spriteX < MINX) {
                horizontalSpeed *= -1;
                spriteX = MINX;
            }

            if (spriteY > MAXY)
            {
                verticalSpeed *= -1;
                spriteY = MAXY;
            }
            else if (spriteY < MINY)
            {
                verticalSpeed *= -1;
                spriteY = MINY;
            }
        }


        protected override void LoadGraphicsContent(bool loadAllContent)
        {
            if (loadAllContent)
            {
                spriteBatch = new SpriteBatch(graphics.GraphicsDevice);
                backgroundBatch = new SpriteBatch(graphics.GraphicsDevice);
                animatedTexture = new AnimatedTexture();

                spriteTexture = content.Load<Texture2D>("ball");
                animatedTexture.Load(graphics.GraphicsDevice,content, "strip", 6);
                scrollingBackground = new ScrollingBackground();
                batLeft = new Bat();
                batRight = new Bat();
                batLeft.Load(graphics.GraphicsDevice,content, "bat", new Vector2(125, graphics.GraphicsDevice.Viewport.Height / 2));
                batRight.Load(graphics.GraphicsDevice, content,"bat", new Vector2(graphics.GraphicsDevice.Viewport.Width - 145, graphics.GraphicsDevice.Viewport.Height / 2));
                scrollingBackground.Load(graphics.GraphicsDevice,content, "background");
                rotatingTexture = new RotatingTexture();
                rotatingTexture.Load(graphics.GraphicsDevice,content, "bayleef");
                cube = new Cube();
                cube.Initialize(graphics.GraphicsDevice);
            }
        }

        protected override void UnloadGraphicsContent(bool unloadAllContent)
        {
            if (unloadAllContent)
            {
                content.Unload();
            }
        }

        protected override void Draw(GameTime gameTime)
        {
            graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

            /*backgroundBatch.Begin();
            scrollingBackground.Draw(backgroundBatch);
            backgroundBatch.End();*/
            spriteBatch.Begin(SpriteBlendMode.AlphaBlend);
            Vector2 pos = new Vector2(spriteX, spriteY);
            animatedTexture.DrawFrame(spriteBatch, currentFrame, Vector2.Zero);
            spriteBatch.Draw(spriteTexture, pos, Color.White);
            rotatingTexture.Draw(spriteBatch);
            batLeft.Draw(spriteBatch);
            batRight.Draw(spriteBatch);
            spriteBatch.End();
            
            // Let the GameComponents draw
            cube.Draw();
            base.Draw(gameTime);
        }
    }
}