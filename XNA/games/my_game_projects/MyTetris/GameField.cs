using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using MyTetris.Blocks;

namespace MyTetris
{
    public class GameField
    {
        private GraphicsDevice graphicsDevice;
        private KeyboardState keyboardState;
        private GamePadState gamePadState;
        private SpriteBatch spriteBatch;

        private Texture2D squareTexture;
    
        private Block block;
        private BlockFactory blockFactory;
        private Rectangle bounds;
        private bool paused = false;

        public int BLOCK_SIZE;
        private int MAX_ROWS;
        private int MAX_COLS;
        private bool[,] gameState;

        KeyboardState oldState;

        public GameField(GraphicsDevice graphicsDevice)
        {
            this.graphicsDevice = graphicsDevice;
            spriteBatch = new SpriteBatch(this.graphicsDevice);
            oldState = Keyboard.GetState();
        }

        public void Draw()
        {
               this.graphicsDevice.Clear(Color.White);


                spriteBatch.Begin();

                drawGameField(spriteBatch);

                block.Draw(spriteBatch);

                spriteBatch.End();
          
        }



        public void LoadContent(ContentManager content)
        {
            squareTexture = content.Load<Texture2D>("images\\block");
            BLOCK_SIZE = squareTexture.Width;
            bounds = new Rectangle(0, 0, graphicsDevice.Viewport.Width, graphicsDevice.Viewport.Height);
          
            MAX_COLS = bounds.Width / BLOCK_SIZE ;
            MAX_ROWS = bounds.Height / BLOCK_SIZE;
            gameState = new bool[ MAX_COLS,MAX_ROWS ];
            blockFactory = new BlockFactory(squareTexture, this);


            block = blockFactory.CreateBlock();
         }

        public void Update()
        {
            keyboardState = Keyboard.GetState();
            int units = squareTexture.Width;
         
            if (keyboardState.IsKeyDown(Keys.P))
            {
                printGameState();
            }

            if (gameOver())
            {
                Console.WriteLine("Game Over");
                return;
            }
            if (paused) return;

           
           if (!block.MoveDown(1))
            {
               updateGameFieldStateWithBlock(block);
               checkForFullLines();
                block = blockFactory.CreateBlock();
            }
         
          
            if ((keyboardState.IsKeyDown(Keys.Left) && !oldState.IsKeyDown(Keys.Left)) || gamePadState.DPad.Left == ButtonState.Pressed)
                block.MoveLeft(units);
            if ((keyboardState.IsKeyDown(Keys.Right) && !oldState.IsKeyDown(Keys.Right)) || gamePadState.DPad.Right == ButtonState.Pressed)
                block.MoveRight(units);
            if ((keyboardState.IsKeyDown(Keys.Down) /*&& !oldState.IsKeyDown(Keys.Down)*/) || gamePadState.DPad.Down == ButtonState.Pressed)
                block.MoveDown(units);  
            if ((keyboardState.IsKeyDown(Keys.Up) && !oldState.IsKeyDown(Keys.Up)) || gamePadState.DPad.Up == ButtonState.Pressed)
                block.Rotate();
            

            oldState = keyboardState;
        }


        public void UpdateGameFieldStateForSquare(Vector2 squarePosition)
        {
            int x = (int)(squarePosition.X / (float)BLOCK_SIZE);
            int y = (int)((squarePosition.Y) / (float)BLOCK_SIZE) ;
            y++;
            if (y >= MAX_ROWS) { Console.WriteLine("exceeded.."); y--; }
            gameState[x, y] = true;
        }

        public void UnloadContent(ContentManager content)
        {
            content.Unload();
        }

        public bool CanMove(Movement movement, Vector2 position)
        {
            return !movement.GoneOutOfBounds(position) && !movement.BlockPresent(position);
        }


        public bool IsBlockPresent(int x, int y)
        {
            return gameState[x, y] == true;
        }

        public Rectangle Bounds
        {
            get { return bounds; }
        }


        public bool CanRotate(Square square)
        {
            return isRotationBetweenBounds(square) && !squareCollidesWithOther(square);
        }

  
        private bool squareCollidesWithOther(Square square)
        {
            Vector2 position = square.Position;
            int x = (int)((position.X) / BLOCK_SIZE);
            int y = (int)((position.Y) / BLOCK_SIZE);
            if (++y >= MAX_ROWS) y--;
            return gameState[x, y] == true;
        }

        private bool isRotationBetweenBounds(Square square)
        {
            return (square.Position.X >= bounds.X) &&
               (square.Position.X <= bounds.Width - squareTexture.Width) &&
               (square.Position.Y >= bounds.Y) &&
               (square.Position.Y <= bounds.Height - squareTexture.Height);
       
        }

        private void checkForFullLines()
        {
            for (int y = MAX_ROWS - 1; y >= 0; y--)
            {
                if (fullLine(y))
                {
                    shiftAllRowsAboveThisRowDown(y);
                    y++;
                }
            }
        }

        private void shiftAllRowsAboveThisRowDown(int y)
        {
            for (int y1 = y - 1; y1 > 0; y1--)
            {
                for (int x = 0; x < MAX_COLS; x++)
                {
                    gameState[x, y1 + 1] = gameState[x, y1];
                }
            }
            for (int x = 0; x < MAX_COLS; x++)
            {
                gameState[x, 0] = false;
            }
        }

        private bool fullLine(int y)
        {
            bool result = true;
            for (int x = 0; x < MAX_COLS; x++)
            {
                if (!gameState[x, y])
                {
                    result = false;
                    break;
                }
            }
            return result;
        }


        private void drawGameField(SpriteBatch spriteBatch)
        {
            for (int y = 0; y < MAX_ROWS; y++)
            {
                for (int x = 0; x < MAX_COLS; x++)
                {
                    if (gameState[x, y])
                    {
                        spriteBatch.Draw(squareTexture, new Vector2(BLOCK_SIZE * x, BLOCK_SIZE * y), Color.White);
                    }
                }
            }
        }


        private void updateGameFieldStateWithBlock(Block block)
        {
            block.UpdateStateInGameField();
        }

        private void printGameState()
        {
            Console.WriteLine();
            for (int y = 0; y < MAX_ROWS; y++)
            {
                Console.WriteLine();
                for (int x = 0; x < MAX_COLS; x++)
                {
                    Console.Write("{0}", gameState[x, y] == true ? "1" : "0");
                }
            }

        }

        private bool gameOver()
        {
            for (int x = 0; x < MAX_COLS; x++)
            {
                if (gameState[x, 1] == true)
                    return true;
            }
            return false;
        }

    }
}
