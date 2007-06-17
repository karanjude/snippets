using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Snake.Sprites;

namespace Snake.Helper
{
    public class SnakeField
    {
        private IList<Branch> branches = new List<Branch>();
        private IList<Mushroom> mushrooms = new List<Mushroom>();
        private UserSnake userSnake;
        private SpriteBatch spriteBatch;
        private GraphicsDevice graphicsDevice;
        private int screenWidth;
        private int screenHeight;

        private readonly int MAX_LENGTH_X;
        private readonly int MAX_LENGTH_Y;

        public  const int IMAGE_WIDTH = 15;
        public const int IMAGE_HEIGHT = 15;
        private bool gameOver = false;

        private GameObject[,] SNAKE_FIELD ;
        private Dictionary<Vector2, Mushroom> cache = new Dictionary<Vector2, Mushroom>();

        public SnakeField(GraphicsDevice graphicsDevice, SpriteBatch spriteBatch)
        {
            this.graphicsDevice = graphicsDevice;
            this.spriteBatch = spriteBatch;
            screenWidth = graphicsDevice.Viewport.Width;
            screenHeight = graphicsDevice.Viewport.Height;
            MAX_LENGTH_X = screenWidth / IMAGE_WIDTH;
            MAX_LENGTH_Y = screenHeight / IMAGE_HEIGHT;
            SNAKE_FIELD = new GameObject[MAX_LENGTH_X, MAX_LENGTH_Y];
        }

        public void CreateBranches()
        {
            branches.Add(new Branch(this, spriteBatch, Direction.HORIZONTAL, new Vector2(0, 0), MAX_LENGTH_X));
            branches.Add(new Branch(this,spriteBatch, Direction.VERTICAL, new Vector2(screenWidth - IMAGE_WIDTH, IMAGE_HEIGHT), MAX_LENGTH_Y - 2));
            branches.Add(new Branch(this,spriteBatch, Direction.HORIZONTAL, new Vector2(0, screenHeight - IMAGE_HEIGHT), MAX_LENGTH_X));
            branches.Add(new Branch(this,spriteBatch, Direction.VERTICAL, new Vector2(0, IMAGE_HEIGHT), MAX_LENGTH_Y - 2));
        }

        public void CreateMushrooms()
        {
            Random random = new Random();

            int numberOfMushrooms = random.Next(70);

            for (int i = 0; i < numberOfMushrooms; i++)
            {
                int x = random.Next(MAX_LENGTH_X - 3) + 1;
                int y = random.Next(MAX_LENGTH_Y -3 ) + 1;
                x *= IMAGE_WIDTH;
                y *= IMAGE_HEIGHT;
                if(SNAKE_FIELD[(int)y / IMAGE_HEIGHT,(int)x / IMAGE_WIDTH] != GameObject.EMPTY)
                    continue;
                SNAKE_FIELD[(int)y / IMAGE_HEIGHT, (int)x / IMAGE_WIDTH] = GameObject.MUSHROOM;
                Mushroom mushroom = new Mushroom(this,spriteBatch, new Vector2(x, y));
                mushrooms.Add(mushroom);
                cache.Add(new Vector2((int)x / IMAGE_WIDTH, (int)y / IMAGE_HEIGHT), mushroom);
            }
        }

        public void DrawBranches()
        {
            foreach (Branch branch in branches)
            {
                branch.Draw();
            }
        }

        public void DrawMushrooms()
        {
            foreach (Mushroom mushroom in mushrooms)
            {
                mushroom.Draw();
            }
        }

        public void InitializeBranches()
        {
            foreach (Branch branch in branches)
            {
                branch.initialize();
            }
        }

        public void MarkGameObject(Vector2 point,GameObject obj)
        {
            SNAKE_FIELD[(int)point.Y / IMAGE_HEIGHT, (int)point.X / IMAGE_WIDTH] = obj;
        }

        public void CreateUserSnake()
        {
            userSnake = new UserSnake(this,this.spriteBatch, new Vector2(MAX_LENGTH_X / 2, MAX_LENGTH_Y / 2), Direction.EAST);
        }

        public void DrawUserSnake()
        {
            userSnake.Draw();
        }

        public void MoveSnake(Vector2 by)
        {
            userSnake.Move(by);
        }

        public void CreateUserSnake(SpriteBatch ss)
        {
            userSnake = new UserSnake(this, ss, new Vector2(MAX_LENGTH_X / 2, MAX_LENGTH_Y / 2), Direction.EAST);
        }

        public void EatAndMove(Vector2 to)
        {
            userSnake.EatAndMove(to);
        }

        public void Draw()
        {
            SNAKE_FIELD.Initialize();
            this.DrawBranches();
            this.DrawMushrooms();
            this.DrawUserSnake();
        }

        public bool IsMushroom(Vector2 point)
        {
            return SNAKE_FIELD[(int)point.Y / IMAGE_HEIGHT, (int)point.X / IMAGE_WIDTH] == GameObject.MUSHROOM;
        }

        public void MarkEmpty(Vector2 point)
        {
            SNAKE_FIELD[(int)point.Y / IMAGE_HEIGHT, (int)point.X / IMAGE_WIDTH] = GameObject.EMPTY;
        }

        private int eatenMushrooms = 0;

        public void AteMushroom(Vector2 point)
        {
            int xx = (int)point.X / IMAGE_WIDTH;
            int yy = (int)point.Y / IMAGE_HEIGHT;
            SNAKE_FIELD[yy,xx ] = GameObject.EMPTY;
            mushrooms.Remove(cache[new Vector2(xx,yy)]);
            eatenMushrooms++;
        }

        public bool IsSnake(Vector2 point)
        {
            return SNAKE_FIELD[(int)point.Y / IMAGE_HEIGHT, (int)point.X / IMAGE_WIDTH] == GameObject.SNAKE;
        }

        public bool IsBranch(Vector2 point)
        {
            return SNAKE_FIELD[(int)point.Y / IMAGE_HEIGHT, (int)point.X / IMAGE_WIDTH] == GameObject.BRANCH;
        }

        public void GameOver()
        {
            this.gameOver = true;
        }

        public bool IsGameOver()
        {
            return this.gameOver;
        }

        public void Restart()
        {
            SNAKE_FIELD.Initialize();
            mushrooms.Clear();
            branches.Clear();
            Branch.Restart();
            UserSnake.Restart();
        }

        public int EatenMushroomsSoFar()
        {
            return this.eatenMushrooms;
        }
    }
}
