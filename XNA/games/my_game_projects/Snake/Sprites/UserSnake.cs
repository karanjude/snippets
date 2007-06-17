using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Snake.Helper;

namespace Snake.Sprites
{
    public class UserSnake : Sprite
    {
        private static Dictionary<Direction, Texture2D> headImages = new Dictionary<Direction, Texture2D>();
        private int length = 4;
        private static Texture2D bodyTexture;
        private static Texture2D empty;

        private Vector2 origin;
        private IList<Vector2> points = new List<Vector2>();
        private IList<Vector2> deltas = new List<Vector2>();
        private Direction direction;
        private Vector2 head;

        private SnakeField snakeField;
        private GameObject type;

        public UserSnake(SnakeField snakeField, SpriteBatch spriteBatch,Vector2 origin,Direction direction)
            : base(spriteBatch)
        {
            this.origin = origin;
            this.direction = direction;
            this.snakeField = snakeField;
            this.type = GameObject.SNAKE;
            this.head = new Vector2(origin.X * 15, origin.Y * 15);
            initailizeBody();
        }

        private void initailizeBody()
        {
            int dx = 0;
            int dy = 0;
            switch (direction)
            {
                case Direction.NORTH:
                    dy = 1; break;
                case Direction.SOUTH:
                    dy = -1; break;
                case Direction.EAST:
                    dx = -1; break;
                case Direction.WEST:
                    dx = 1; break;
            }
            Vector2 p = Vector2.Zero + head;
            for (int i = 1; i <= length; i++)
            {
                p = p + new Vector2(dx * 15, dy * 15);
                points.Add(p);
                deltas.Add(Vector2.Zero);
            }
        }

        public static void LoadHeadContent(Direction direction, Texture2D texture)
        {
            headImages.Add(direction, texture);
        }

        public static void LoadBodyContent(Texture2D texture)
        {
            bodyTexture = texture;
        }

        private Texture2D headTexture;

        public override void Draw()
        {
            headTexture = headImages[direction];
            snakeField.MarkGameObject(head, this.type);
            spriteBatch.Draw(headTexture, head, Color.White);
               
            foreach (Vector2 p in points)
            {
                snakeField.MarkGameObject(p, this.type);
                spriteBatch.Draw(bodyTexture, p, Color.White);
            }
        }

        public void Move(Vector2 to)
        {
            Direction oldDirection = direction;
            if (to.X > 0)
                direction = Direction.EAST;
            else
                direction = Direction.WEST;

            if(to.Y > 0)
                direction = Direction.SOUTH;
            else
                direction = Direction.NORTH;

            Vector2 next = head + new Vector2(to.X * bodyTexture.Width,to.Y * bodyTexture.Height);
            if (snakeField.IsMushroom(next))
            {
                this.EatAndMove(to);
                return;
            }
            else if (snakeField.IsSnake(next))
            {
                if(isOppposite(oldDirection,direction))   
                    snakeField.GameOver();
            }
            else if (snakeField.IsBranch(next))
                snakeField.GameOver();
            
            Vector2 tail = points[points.Count - 1];
            for(int i = points.Count-1; i > 0 ;i--)
            {
                points[i] = points[i - 1];
                snakeField.MarkGameObject(points[i], this.type);
            }
            points[0] = head;
            snakeField.MarkEmpty(tail);
            this.head = head + new Vector2(to.X * bodyTexture.Width,to.Y * bodyTexture.Height);
            snakeField.MarkGameObject(head, this.type);
        }

        private bool isOppposite(Direction oldDirection, Direction direction)
        {
            bool result = false;
            if (oldDirection == Direction.EAST && direction == Direction.WEST)
                return true;
            if (oldDirection == Direction.WEST && direction == Direction.EAST)
                return true;
            if (oldDirection == Direction.NORTH && direction == Direction.SOUTH)
                return true;
            if (oldDirection == Direction.SOUTH && direction == Direction.NORTH)
                return true;
            return result;
        }

        public void EatAndMove(Vector2 to)
        {
            if (to.X > 0)
                direction = Direction.EAST;
            else
                direction = Direction.WEST;

            if (to.Y > 0)
                direction = Direction.SOUTH;
            else
                direction = Direction.NORTH;

            Vector2 tail = points[points.Count-1];
            for (int i = points.Count - 1; i > 0; i--)
            {
                points[i] = points[i - 1];
            }
            points.Add(new Vector2(tail.X, tail.Y));
            points[0] = head;
            this.head = head + new Vector2(to.X * bodyTexture.Width, to.Y * bodyTexture.Height);
            snakeField.AteMushroom(head);
        }

        public static void LoadEmptyContent(Texture2D texture)
        {
            empty = texture;
        }

        public static void Restart()
        {
            headImages.Clear();
        }
    }
}
