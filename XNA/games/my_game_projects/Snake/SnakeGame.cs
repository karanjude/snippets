#region Using Statements
using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Storage;
using Snake.Helper;
using Snake.Sprites;
#endregion

namespace Snake
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class SnakeGame : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        ContentManager content;

        private SpriteBatch spriteBatch;
        private SnakeField snakeField;
        private Vector2 to;
        private KeyboardState keyboardState;
        private KeyboardState oldState;

        private GamePadState gamePadState;
        private double timeDelay;
        private SpriteBatch helperSpriteBatch;
        private RenderTarget2D helperRenderTarget;
        private bool _draw = true;
        private byte r = 255;
        private byte g = 0;
        private byte b = 205;

        public SnakeGame()
        {
            graphics = new GraphicsDeviceManager(this);
            content = new ContentManager(Services);
            graphics.PreferredBackBufferWidth = 600;
            graphics.PreferredBackBufferHeight = 600;
            to = new Vector2(1, 0);
            timeDelay = 0;
        }


        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            spriteBatch = new SpriteBatch(this.graphics.GraphicsDevice);
            snakeField = new SnakeField(this.graphics.GraphicsDevice, spriteBatch);
            snakeField.CreateBranches();
            snakeField.CreateMushrooms();
            snakeField.CreateUserSnake(spriteBatch);
        
            base.Initialize();
        }


        /// <summary>
        /// Load your graphics content.  If loadAllContent is true, you should
        /// load content from both ResourceManagementMode pools.  Otherwise, just
        /// load ResourceManagementMode.Manual content.
        /// </summary>
        /// <param name="loadAllContent">Which type of content to load.</param>
        protected override void LoadGraphicsContent(bool loadAllContent)
        {
            if (loadAllContent)
            {
                Branch.LoadContent(Direction.HORIZONTAL,Position.END ,content.Load<Texture2D>("images\\HorBranchEnd"));
                Branch.LoadContent(Direction.HORIZONTAL,Position.MIDDLE, content.Load<Texture2D>("images\\HorBranchMiddle"));
                Branch.LoadContent(Direction.HORIZONTAL,Position.START, content.Load<Texture2D>("images\\HorBranchStart"));
                Branch.LoadContent(Direction.VERTICAL,Position.START, content.Load<Texture2D>("images\\VertBranchStart"));
                Branch.LoadContent(Direction.VERTICAL,Position.MIDDLE, content.Load<Texture2D>("images\\VertBranchMiddle"));
                Branch.LoadContent(Direction.VERTICAL,Position.END, content.Load<Texture2D>("images\\VertBranchEnd"));
                Mushroom.LoadContent(content.Load<Texture2D>("images\\mushroom"));
                UserSnake.LoadHeadContent(Direction.NORTH, content.Load<Texture2D>("images\\NetterHeadN"));
                UserSnake.LoadHeadContent(Direction.EAST, content.Load<Texture2D>("images\\NetterHeadE"));
                UserSnake.LoadHeadContent(Direction.WEST, content.Load<Texture2D>("images\\NetterHeadW"));
                UserSnake.LoadHeadContent(Direction.SOUTH, content.Load<Texture2D>("images\\NetterHeadS"));
                UserSnake.LoadBodyContent(content.Load<Texture2D>("images\\NetterBody"));
                UserSnake.LoadEmptyContent(content.Load<Texture2D>("images\\empty"));

            }
            snakeField.InitializeBranches();
          
            // TODO: Load any ResourceManagementMode.Manual content
        }


        /// <summary>
        /// Unload your graphics content.  If unloadAllContent is true, you should
        /// unload content from both ResourceManagementMode pools.  Otherwise, just
        /// unload ResourceManagementMode.Manual content.  Manual content will get
        /// Disposed by the GraphicsDevice during a Reset.
        /// </summary>
        /// <param name="unloadAllContent">Which type of content to unload.</param>
        protected override void UnloadGraphicsContent(bool unloadAllContent)
        {
            if (unloadAllContent == true)
            {
                content.Unload();
            }
        }

        int dx = 0;
        int dy = 0;
        int delay = 200;
        int delayThreshold = 0;
        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the default game to exit on Xbox 360 and Windows
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            keyboardState = Keyboard.GetState();
          
            if ((keyboardState.IsKeyDown(Keys.Left) && !oldState.IsKeyDown(Keys.Left)) || gamePadState.DPad.Left == ButtonState.Pressed)
                dx = -1;
            if ((keyboardState.IsKeyDown(Keys.Right) && !oldState.IsKeyDown(Keys.Right)) || gamePadState.DPad.Right == ButtonState.Pressed)
                dx = 1;
            if ((keyboardState.IsKeyDown(Keys.Down) && !oldState.IsKeyDown(Keys.Down)) || gamePadState.DPad.Down == ButtonState.Pressed)
                dy = 1;
            if ((keyboardState.IsKeyDown(Keys.Up) && !oldState.IsKeyDown(Keys.Up)) || gamePadState.DPad.Up == ButtonState.Pressed)
                dy = -1;
            if (keyboardState.IsKeyDown(Keys.R) && !oldState.IsKeyDown(Keys.R))
                this.Restart();
                      
           
            if(!(dx == 0 && dy == 0))
                to = new Vector2(dx,dy);

            oldState = keyboardState;
            dx = dy = 0;
            timeDelay += gameTime.ElapsedGameTime.TotalMilliseconds;
           
            if (timeDelay > delay && !snakeField.IsGameOver())
            {
                _draw = true;
                snakeField.MoveSnake(to);
                if (snakeField.EatenMushroomsSoFar() > delayThreshold && (snakeField.EatenMushroomsSoFar() % 5 == 0))
                {
                    delayThreshold += 5;
                    delay -= 10 * ( delayThreshold / 5);
                }
                timeDelay = 0;
            }


            base.Update(gameTime);
        }

        private void Restart()
        {
            snakeField.Restart();
            snakeField = null;
            GC.Collect();
            this.Initialize();
        }


        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            if (snakeField.IsGameOver())
            {
                graphics.GraphicsDevice.Clear(Color.Red);
            }
            else
            {
                graphics.GraphicsDevice.Clear(new Color(r, g, b));
                spriteBatch.Begin(SpriteBlendMode.AlphaBlend);
                snakeField.Draw();
                spriteBatch.End();
            }
            base.Draw(gameTime);

        }
    }
}