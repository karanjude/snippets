using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System.Collections;
using Snake.Helper;

namespace Snake
{
    public class Branch : Sprite
    {
        private Direction direction;
        private int size;
        
        private Texture2D start;
        private Texture2D middle;
        private Texture2D end;
        private int headLength;
        private int tailLength;
        private int bodyLength;
        private Vector2 origin;
        private SnakeField snakeField;
        private GameObject type;

        private struct DirectionPositionPair
        {
            private Direction direction;
            private Position position;

            public DirectionPositionPair(Direction direction, Position position) 
            {
                this.direction = direction;
                this.position = position;
            }

            public override bool Equals(object obj)
            {
                DirectionPositionPair other = (DirectionPositionPair)obj;
                return this.direction == other.direction && this.position == other.position;
            }

            public override int GetHashCode()
            {
                return direction.GetHashCode() + position.GetHashCode();
            }
        }

        private static Dictionary<DirectionPositionPair, Texture2D> cache = new Dictionary<DirectionPositionPair, Texture2D>();
        
        public Branch(SnakeField snakeField, SpriteBatch spriteBatch, Direction direction,Vector2 origin, int length) : base(spriteBatch)
        {
            this.direction = direction;
            this.size = length;
            this.headLength = 1;
            this.tailLength = 1;
            this.snakeField = snakeField;
            this.type = GameObject.BRANCH;
            this.bodyLength = length - headLength - tailLength;
            this.origin = origin;
         }

        public void initialize()
        {
            start = cache[new DirectionPositionPair(direction, Position.START)];
            middle = cache[new DirectionPositionPair(direction, Position.MIDDLE)];
            end = cache[new DirectionPositionPair(direction, Position.END)];
       }

        public static void LoadContent(Direction direction,Position position, Texture2D texture)
        {
            cache.Add(new DirectionPositionPair(direction,position), texture);  
        }

        public override void Draw()
        {
            Vector2 point = origin;
            int textureSize = start.Width;
            int dx = 0;
            int dy = 0;
            if (direction == Direction.HORIZONTAL)
                dx = 1 * textureSize;
            if (direction == Direction.VERTICAL)
                dy = 1 * textureSize;

            snakeField.MarkGameObject(point, this.type);
            spriteBatch.Draw(start, point, Color.Pink);
            Vector2 diff = new Vector2(dx, dy);
            point =  point + diff;
            for (int i = 0; i < bodyLength; i++)
            {
                snakeField.MarkGameObject(point, this.type);
                spriteBatch.Draw(middle, point, Color.White);
                point = point + diff;
            }
            spriteBatch.Draw(end, point, Color.White);

        }


        public static void Restart()
        {
            cache.Clear();
        }
    }
}
